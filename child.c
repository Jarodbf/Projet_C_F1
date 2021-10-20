#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

# define V  20
# define T  5

typedef struct
{
  int id;
  size_t size;
} shm_t;

shm_t *shm_new(size_t size)
{
  shm_t *shm = calloc(1, sizeof *shm);
  shm->size = size;

  if ((shm->id = shmget(IPC_PRIVATE, size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR)) < 0)
  {
    perror("shmget");
    free(shm);
    return NULL;
  }

  return shm;
}

void shm_write(shm_t *shm, void *data)
{
  void *shm_data;

  if ((shm_data = shmat(shm->id, NULL, 0)) == (void *) -1)
  {
    perror("write");
    return;
  }

  memcpy(shm_data, data, shm->size);
  shmdt(shm_data);
}

void shm_read(void *data, shm_t *shm)
{
  void *shm_data;

  if ((shm_data = shmat(shm->id, NULL, 0)) == (void *) -1)
  {
    perror("read");
    return;
  }
  memcpy(data, shm_data, shm->size);
  shmdt(shm_data);
}

void shm_del(shm_t *shm)
{
  shmctl(shm->id, IPC_RMID, 0);
  free(shm);
}

struct F1 {
	int id;
	float temp[4];
	float BStemp[4];
	char statut; //S=stand O=out E=enCourse
};

struct F1 voiture[V];

int Bid[4];
float geneTemp (){
	float r;
    r = (((rand())%16000)+25000);
return r/1000;
}

void afficheTab() {
printf(" IDV |  BS1   |  BS2   |  BS3   |  BT   |\n\n");
for(int k=0;k<V;k++)//voiture
    {
       printf(" F%2d | %3.2fs | %3.2fs | %3.2fs | %dm%2ds |\n",voiture[k].id,voiture[k].temp[0],voiture[k].temp[1],voiture[k].temp[2],((int)voiture[k].temp[3]/60),((int)voiture[k].temp[3]%60));
    }
	printf("--------------------------------------------------------------\n");
	//printf(" F%2d | %3.2fs | F%2d | %3.2fs | F%2d | %3.2fs |\n",Bid[0],voiture[0].BStemp[0],Bid[1],voiture[0].BStemp[1],Bid[2],voiture[0].BStemp[2]);
}


int main()
{
srand(time(NULL));
//int var = 1;
shm_t *shm = shm_new(sizeof voiture[0]);
int vNum = 0;
int pid;
int NumVoit[20] = {44, 77, 11, 33, 3, 4, 5, 18, 14, 31, 16, 55, 10, 22, 7, 99, 9, 47, 6, 63};
for(int i=0;i<20;i++){
	voiture[i].id = NumVoit[i];
}

float tempT;
for(int k = 0; k<20 ; k++)
  {
  if ((pid = fork()) == 0)
  { /* child */
    //var = i;
    //shm_write(shm, &var);
    //printf("child: %d\n", var);
    //return 0;
  
    for(int i=0;i<T;i++) //tour
    {
        for(int j=0;j<3;j++)// secteurs
        {

        if(i==0){
                  voiture[pid].temp[j] = geneTemp();
                  //shm_write(shm, &voiture[k].temp[j]);
        }
        else{
          tempT=geneTemp();
          if(tempT>voiture[pid].temp[j]){
          voiture[pid].temp[j] = tempT;
          //shm_write(shm, &voiture[k].temp[j]);
          }
        }
            
        }

        //for(int k=0;k<V;k++)//comptage temps tot
        {
          if(i==0){
        voiture[pid].temp[3] = voiture[pid].temp[0]+voiture[pid].temp[1]+voiture[pid].temp[2];
          }
          else{
        tempT = voiture[pid].temp[0]+voiture[pid].temp[1]+voiture[pid].temp[2];
        if(tempT>voiture[pid].temp[3]){
            voiture[pid].temp[3] = tempT;
        }
            }
        }
      /**
      for(int j=0;j<3;j++)// secteurs
        {
        float cache = voiture[0].temp[j];
            for(int k=0;k<V;k++)// meilleur bstemp1 2 3 voiture | not semaphore 
            { // marche pas btw
          if(cache>voiture[k].temp[j]){
          voiture[0].BStemp[j] = cache;
          Bid[j] = k;
          }
        }
        }
        **/
    }
    int waitPid = pid/10000;
    sleep(waitPid);// pour pas que les fils finissent tous en même temps
    shm_write(shm, &voiture[pid]);
  }
  int status;
  while (wait(&status) != pid);
  /* */
  shm_read(&voiture[vNum], shm);
  vNum++;
  /* Parent is updated by child */
  //printf("parent: %d\n", var);
}

afficheTab();
shm_del(shm);
}
