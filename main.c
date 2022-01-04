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
#include <fcntl.h>
#include <semaphore.h>

int V = 21;
# define T  5
sem_t s;

struct F1 voitcpy[21];
struct F1 classment[21];

int Bid[4];
int geneTemp (int x){
	int r=(abs(rand()*x)% (40000 -25000 +1))+25000;
	return  r/1000;
}

void afficheTab() {
	int kTemp;
//	system("clear");
printf("   IDV   |  S1   |  S2   |  S3   |   TEMP TOT    |   BTEMP   |   ECART   |   STATUS   |\n\n");
memcpy(&classment,voitcpy,sizeof(struct F1)*21);
for (int i=0; i<V-1;i++){
	for (int y=i+1; y<V-1;y++){
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
		if (classment[k].lost == 0){
			
		   printf("   F%2d   |   %2d   |   %2d   |   %2d   |   %2ds   |   %2ds   | %c  ",classment[k].id,classment[k].temp[0],classment[k].temp[1],classment[k].temp[2],classment[k].temp[3],classment[k].temp[4],classment[k].statut);
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
    }
	printf(" Best S1 par F%2d: %2d\n",voitcpy[20].idBst[0], voitcpy[20].BStemp[0]);
	printf(" Best S2 par F%2d: %2d\n",voitcpy[20].idBst[1], voitcpy[20].BStemp[1]);
	printf(" Best S3 par F%2d: %2d\n",voitcpy[20].idBst[2], voitcpy[20].BStemp[2]);
	printf(" Best Temp Total par F%2d: %2d\n",voitcpy[20].idBst[3], voitcpy[20].BStemp[3]);
	printf("--------------------------------------------------------------\n");

}
void Ecrit(char *tour){
	char buff[1024];
	int f;
	if(strcmp(tour , "P1")==0){
    f = open("P1.txt", O_WRONLY); 
	}
	else if(strcmp(tour , "P2")==0){
    f = open("P2.txt", O_WRONLY); 
	}
	else if(strcmp(tour , "P3")==0){
    f = open("P3.txt", O_WRONLY); 
	}
	else if(strcmp(tour ,"Q1")==0){
    f = open("Q1.txt", O_WRONLY); 
	}
	else if(strcmp(tour , "Q2")==0){
    f = open("Q2.txt", O_WRONLY); 
	}
	else if(strcmp(tour , "Q3")==0){
    f = open("Q3.txt", O_WRONLY); 
	}
    if(f < 0){ // vérifie que le fichier se soit ouvert
        perror("file ");
        exit(0);
    }
    for(int k=0;k<V-1;k++)//voiture
    {
       sprintf(buff,"%d\n",classment[k].id);
       write(f, buff, strlen(buff));
	}
	close(f);
}
int main(int argc,char *argv[])
{
	sem_init(&s, 1, 1);
	int oui = 56;
	srand(time(NULL));
	if (argc > 1)
	{
		int pid; 
		int NumVoit[20] = {44, 77, 11, 33, 3, 4, 5, 18, 14, 31, 16, 55, 10, 22, 7, 99, 9, 47, 6, 63}; 
		connectShm();
		for(int k = 0; k<V-1 ; k++)
		{
			voitures[k].lost = 0;
			voitures[k].id = NumVoit[k];
		}
		
		if (strcmp(argv[1],"Q2")==0 || strcmp(argv[1],"Q3")==0)
		{
			int fichier =0;
			if (strcmp(argv[1],"Q2")==0){
				V = V-5;
				fichier = open("Q1.txt", O_RDONLY );
				for(int k = 15; k<20 ; k++)
				{
					voitures[k].lost = 1;
				}
			}
			else{
				V = V-10;
				fichier = open("Q2.txt", O_RDONLY );
				for(int k = 10; k<20 ; k++)
				{
					voitures[k].lost = 1;
				}
			}
			char* str = malloc(sizeof(char)*50);
			int red;
			char *classement;
			red = read(fichier, str, sizeof(str)*30); 
			close(fichier);
			int pos[20];
			int i=0;
			classement = strtok(str,"\n");
			while(classement!=NULL){
				pos[i] = atoi(classement);
				classement = strtok(NULL,"\n"); // prochaine phrase si présente
				i++;
			}
			for(int k = 0; k<V-1 ; k++)
			{
			voitures[k].id = pos[k];
			}
		}
		for(int i=0;i<4;i++){
		voitures[20].BStemp[i] = 999;
		}
			for(int k = 0; k<V-1 ; k++)
				{
				voitures[k].statut = 'E';
				}
		struct timeval tempInitial , tempFinal;
			int seconde = 0;
			while(seconde < 12){
				gettimeofday(&tempInitial , NULL);
				sleep(1);
				for(int k = 0; k<V-1 ; k++)
				{
					if (voitures[k].lost == 0){
						if ((pid = fork()) == 0)
						{
							//printf("\n%d\n", oui);

							sem_wait(&s);
							
							if (voitures[k].statut != 'O'){
								if (voitures[k].statut == 'S'){
									voitures[k].statut = 'E';
								}
								if (geneTemp(getpid()) == 39){
									voitures[k].statut = 'S';
								}
								if (geneTemp(getpid())+geneTemp(getpid())+geneTemp(getpid())+geneTemp(getpid()) == 143){
									voitures[k].statut = 'O';
								}
								if (voitures[k].statut == 'E'){
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
								}
							}
							//printf("child");
							sem_getvalue(&s, &oui);
							sem_post(&s);
														

							exit(1);
						}
					
						
						
						
					}
					
				}
				//printf("parent");
						if(sem_wait(&s) == 0){
							
							//printf("\n%d\n", oui);
							}
						memcpy(&voitcpy,voitures,sizeof(struct F1)*21);
						sem_post(&s);
				gettimeofday(&tempFinal , NULL);
			seconde += (tempFinal.tv_sec - tempInitial.tv_sec);
			
				afficheTab();
				Ecrit(argv[1]);
				//printf("\nTotal time taken is : %d seconds and %lu microseconds\n",(seconde),(tempFinal.tv_usec - tempInitial.tv_usec));
		}
		disconectShm();

	}
 //afiche le tableau des données
 sem_destroy(&s);
return 0;
}


