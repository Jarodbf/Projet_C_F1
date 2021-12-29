#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include "SharedMemory.h"

# define V  21
# define T  5
struct F1 voitcpy[21];

int Bid[4];
int geneTemp (int x){
	int r=(abs(rand()*x)% (40000 -25000 +1))+25000;
	return  r/1000;
}

void afficheTab() {
	system("clear");
printf(" IDV |  BS1   |  BS2   |  BS3   |  BT   |\n\n");
for(int k=0;k<V-1;k++)//voiture
    {
       printf(" F%2d | %2d | %2d | %2d | %2ds \n",voitcpy[k].id,voitcpy[k].temp[0],voitcpy[k].temp[1],voitcpy[k].temp[2],voitcpy[k].temp[3]);
    }
	printf(" Best S1: %d\n",voitcpy[20].BStemp[0]);
	printf(" Best S2: %d\n",voitcpy[20].BStemp[1]);
	printf(" Best S3: %d\n",voitcpy[20].BStemp[2]);
	printf(" Best Temp Total: %d\n",voitcpy[20].BStemp[3]);
	printf("--------------------------------------------------------------\n");
	//printf(" F%2d | %3.2fs | F%2d | %3.2fs | F%2d | %3.2fs |\n",Bid[0],voiture[0].BStemp[0],Bid[1],voiture[0].BStemp[1],Bid[2],voiture[0].BStemp[2]);
}


int main()
{
srand(time(NULL));

int pid;
int NumVoit[20] = {44, 77, 11, 33, 3, 4, 5, 18, 14, 31, 16, 55, 10, 22, 7, 99, 9, 47, 6, 63};
//for(int i=0;i<20;i++){
	//voiture[i].id = NumVoit[i];
//}
connectShm();
for(int i=0;i<4;i++){
voitures[20].BStemp[i] = 999;
}
struct timeval st , et;
     int oui = 0;
     while(oui < 12){
		gettimeofday(&st , NULL);
		sleep(1);
		for(int k = 0; k<20 ; k++)
		{
			voitures[k].id = NumVoit[k]; 
		if ((pid = fork()) == 0)
		{ 
			voitures[k].temp[0] = geneTemp(getpid());
			if(voitures[k].temp[0] > voitcpy[k].temp[0] && voitcpy[k].temp[0] != 0)
			{
				voitures[k].temp[0] = voitcpy[k].temp[0];
			}
			voitures[k].temp[1] = geneTemp(getpid());
			if(voitures[k].temp[1] > voitcpy[k].temp[1] && voitcpy[k].temp[1] != 0)
			{
				voitures[k].temp[1] = voitcpy[k].temp[1];
			}
			voitures[k].temp[2] = geneTemp(getpid());
			if(voitures[k].temp[2] > voitcpy[k].temp[2] && voitcpy[k].temp[2] != 0)
			{
				voitures[k].temp[2] = voitcpy[k].temp[2];
			}
			voitures[k].temp[3] = voitures[k].temp[0] + voitures[k].temp[1] +voitures[k].temp[2];
			if(voitures[20].BStemp[0]>voitures[k].temp[0])
			{
				voitures[20].BStemp[0] = voitures[k].temp[0];
			}
			if(voitures[20].BStemp[1]>voitures[k].temp[1])
			{
				voitures[20].BStemp[1] = voitures[k].temp[1];
			}
			if(voitures[20].BStemp[2]>voitures[k].temp[2])
			{
				voitures[20].BStemp[2] = voitures[k].temp[2];
			}
			if(voitures[20].BStemp[3]>voitures[k].temp[3])
			{
				voitures[20].BStemp[3] = voitures[k].temp[3];
			}
			
			exit(1);
		}
		
			else{
			wait(NULL);// passe au père
			memcpy(&voitcpy,voitures,sizeof(struct F1)*21);
			}
		}
		gettimeofday(&et , NULL);
     oui += (et.tv_sec - st.tv_sec);
     printf("\nTotal time taken is : %lu seconds and %lu microseconds\n",(oui),(et.tv_usec - st.tv_usec));
		afficheTab();
}
disconectShm();
 //afiche le tableau des données 
return 0;
}