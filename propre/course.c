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
#include "SharedMemory.h"

# define V  20
# define T  5

int shmid;


int Bid[4];
int geneTemp (int x){
	int r=(abs(rand()*x)% (40000 -25000 +1))+25000;
	return  r/1000;
}

void afficheTab() {
printf(" IDV |  BS1   |  BS2   |  BS3   |  BT   |\n\n");
for(int k=0;k<V+5;k++)//voiture
    {
       printf(" F%2d | %2d | %2d | %2d\n",voitures[1].id,voitures[1].temp[0],voitures[1].temp[1],voitures[1].temp[2]);
    }
	printf("--------------------------------------------------------------\n");
	//printf(" F%2d | %3.2fs | F%2d | %3.2fs | F%2d | %3.2fs |\n",Bid[0],voiture[0].BStemp[0],Bid[1],voiture[0].BStemp[1],Bid[2],voiture[0].BStemp[2]);
}


int main()
{
srand(time(NULL));

int vNum = 0;
int pid;
int NumVoit[20] = {44, 77, 11, 33, 3, 4, 5, 18, 14, 31, 16, 55, 10, 22, 7, 99, 9, 47, 6, 63};
//for(int i=0;i<20;i++){
	//voiture[i].id = NumVoit[i];
//}
connectShm();
for(int k = 0; k<20 ; k++)
  {
	voitures[k].id = NumVoit[k]; 
  if ((pid = fork()) == 0)
  { 
    voitures[1].temp[0] = geneTemp(getpid());
	voitures[1].temp[1] = geneTemp(getpid());
	voitures[1].temp[2] = geneTemp(getpid());
    exit(1);
  }
  
    else{
    wait(NULL);// passe au père
	//printf("%d\n",voitures[1].temp[0]);
	 printf(" F%2d | %2d | %2d | %2d\n",voitures[1].id,voitures[1].temp[0],voitures[1].temp[1],voitures[1].temp[2]);	
	 //afficheTab();
    vNum++;//le conteur des voitures
    
    }
  }
  
afficheTab(); //afiche le tableau des données 
return 0;
}