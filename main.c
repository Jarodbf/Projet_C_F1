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
struct F1 classment[21];

int Bid[4];
int geneTemp (int x){
	int r=(abs(rand()*x)% (40000 -25000 +1))+25000;
	return  r/1000;
}

void afficheTab() {
	int kTemp;
	system("clear");
printf("   IDV   |  S1   |  S2   |  S3   |   TEMP TOT    |   BTEMP   |   ECART   |\n\n");
memcpy(&classment,voitcpy,sizeof(struct F1)*21);
for (int i=0; i<20;i++){
	for (int y=i+1; y<20;y++){
		if(classment[i].temp[4]>classment[y].temp[4])
		{
			classment[20] = classment[i];
			classment[i] = classment[y];
			classment[y] = classment[20];
		}
	}
}

for(int k=0;k<V-1;k++)//voiture
    {
       printf("   F%2d   |   %2d   |   %2d   |   %2d   |   %2ds   |   %2ds   |   ",classment[k].id,classment[k].temp[0],classment[k].temp[1],classment[k].temp[2],classment[k].temp[3],classment[k].temp[4]);
	   if(k == 0)
	   {
		   printf("0s\n");
	   }
	   else
	   {
		   kTemp = k-1;
		   
		   printf("%2ds\n",classment[k].temp[4] - classment[kTemp].temp[4]);
	   }
    }
	printf(" Best S1 par F%2d: %2d\n",voitcpy[20].idBst[0], voitcpy[20].BStemp[0]);
	printf(" Best S2 par F%2d: %2d\n",voitcpy[20].idBst[1], voitcpy[20].BStemp[1]);
	printf(" Best S3 par F%2d: %2d\n",voitcpy[20].idBst[2], voitcpy[20].BStemp[2]);
	printf(" Best Temp Total par F%2d: %2d\n",voitcpy[20].idBst[3], voitcpy[20].BStemp[3]);
	printf("--------------------------------------------------------------\n");

}


int main()
{
srand(time(NULL));

int pid;
int NumVoit[20] = {44, 77, 11, 33, 3, 4, 5, 18, 14, 31, 16, 55, 10, 22, 7, 99, 9, 47, 6, 63};
connectShm();
for(int i=0;i<4;i++){
voitures[20].BStemp[i] = 999;
}
struct timeval tempInitial , tempFinal;
     int seconde = 0;
     while(seconde < 12){
		gettimeofday(&tempInitial , NULL);
		sleep(1);
		for(int k = 0; k<20 ; k++)
		{
			voitures[k].id = NumVoit[k]; 
		if ((pid = fork()) == 0)
		{ 
			voitures[k].temp[0] = geneTemp(getpid());
			
			voitures[k].temp[1] = geneTemp(getpid());
			
			voitures[k].temp[2] = geneTemp(getpid());
			
			voitures[k].temp[3] = voitures[k].temp[0] + voitures[k].temp[1] +voitures[k].temp[2];
			
			voitures[k].temp[4] = voitures[k].temp[0] + voitures[k].temp[1] +voitures[k].temp[2];
			if(voitures[k].temp[4] > voitcpy[k].temp[4] && voitcpy[k].temp[4] != 0)
			{
				voitures[k].temp[4] = voitcpy[k].temp[4];
			}

			if(voitures[20].BStemp[0]>voitures[k].temp[0])
			{
				voitures[20].BStemp[0] = voitures[k].temp[0];
				voitures[20].idBst[0] = voitures[k].id;
			}
			if(voitures[20].BStemp[1]>voitures[k].temp[1])
			{
				voitures[20].BStemp[1] = voitures[k].temp[1];
				voitures[20].idBst[1] = voitures[k].id;
			}
			if(voitures[20].BStemp[2]>voitures[k].temp[2])
			{
				voitures[20].BStemp[2] = voitures[k].temp[2];
				voitures[20].idBst[2] = voitures[k].id;
			}
			if(voitures[20].BStemp[3]>voitures[k].temp[3])
			{
				voitures[20].BStemp[3] = voitures[k].temp[3];
				voitures[20].idBst[3] = voitures[k].id;
			}
			
			exit(1);
		}
		
			else{
			wait(NULL);// passe au père
			memcpy(&voitcpy,voitures,sizeof(struct F1)*21);
			}
		}
		gettimeofday(&tempFinal , NULL);
     seconde += (tempFinal.tv_sec - tempInitial.tv_sec);
     
		afficheTab();
		printf("\nTotal time taken is : %d seconds and %lu microseconds\n",(seconde),(tempFinal.tv_usec - tempInitial.tv_usec));
}
disconectShm();
 //afiche le tableau des données 
return 0;
}
