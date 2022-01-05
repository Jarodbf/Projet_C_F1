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
#include "course.c"
#include <fcntl.h>

int V = 21;

struct F1 classment[21];

void afficheTab(char *NumCourse) {
	int kTemp;
//	system("clear");
if(strcmp(NumCourse , "C1")!=0)
{
	printf("   IDV   |  S1   |  S2   |  S3   |   TEMP   |   BTEMP   |   STATUS  |   ECART    |\n\n");
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
		if(voitures[i].temp[4]==500)
			{
				voitures[i].temp[4] = 0;
			}
	}
}
else
{
	printf("   IDV   |  S1   |  S2   |  S3   |   TEMP   |   BTEMP   |   TEMP TOT   |   STATUS  |   ECART    |\n\n");
	memcpy(&classment,voitcpy,sizeof(struct F1)*21);
	for (int i=0; i<V-1;i++){
		for (int y=i+1; y<V-1;y++){
				if(classment[i].temp[5]>classment[y].temp[5])
				{
					classment[20] = classment[i];
					classment[i] = classment[y];
					classment[y] = classment[20];
				}
		}
	}
	for (int i=0; i<V-1;i++){
		if (classment[i].statut == 'O'){
			classment[i].temp[5] -= 500;
		}
	}
}

for(int k=0;k<V-1;k++)//voiture
    {
		if (classment[k].lost == 0){
			if(strcmp(NumCourse , "C1")==0)
			{
			   printf("N°%d   F%2d   |   %2d   |   %2d   |   %2d   |   %2ds   |   %2ds   |   %2ds   | %c  ",k+1,classment[k].id,classment[k].temp[0],classment[k].temp[1],classment[k].temp[2],classment[k].temp[3],classment[k].temp[4],classment[k].temp[5],classment[k].statut);
			   if(k == 0)
			   {
				   printf("0s\n");
			   }
			   else
			   {
				   kTemp = k-1;
				   
				   printf("%2ds\n",abs(classment[k].temp[5] - classment[kTemp].temp[5]));
				}
			}
			else{
				printf("N°%d   F%2d   |   %2d   |   %2d   |   %2d   |   %2ds   |   %2ds   | %c  ",k+1,classment[k].id,classment[k].temp[0],classment[k].temp[1],classment[k].temp[2],classment[k].temp[3],classment[k].temp[4],classment[k].statut);
			   if(k == 0)
			   {
				   printf("0s\n");
			   }
			   else
			   {
				   kTemp = k-1;
				   printf("%2ds\n",abs(classment[k].temp[4] - classment[kTemp].temp[4]));
				}
			}
		}
    }
	printf(" Best S1 par F%2d: %2d\n",voitcpy[20].idBst[0], voitcpy[20].BStemp[0]);
	printf(" Best S2 par F%2d: %2d\n",voitcpy[20].idBst[1], voitcpy[20].BStemp[1]);
	printf(" Best S3 par F%2d: %2d\n",voitcpy[20].idBst[2], voitcpy[20].BStemp[2]);
	printf(" Best Temp par F%2d: %2d\n",voitcpy[20].idBst[3], voitcpy[20].BStemp[3]);
	printf("--------------------------------------------------------------\n");

}
void Ecrit(char *tour){
	char buff[1024];
	int f;
	if(strcmp(tour , "P1")==0){
		if(!(f = open("P1.txt", O_WRONLY)))
		{}
		else{
			system("touch P1.txt");
			f = open("P1.txt", O_WRONLY);
		}
	}
	else if(strcmp(tour , "P2")==0){
		if(!(f = open("P2.txt", O_WRONLY)))
		{}
		else{
			system("touch P2.txt");
			f = open("P2.txt", O_WRONLY);
			}
	}
	else if(strcmp(tour , "P3")==0){
		if(!(f = open("P3.txt", O_WRONLY)))
		{}
		else{
			system("touch P3.txt");
			f = open("P3.txt", O_WRONLY);
			}
	}
	else if(strcmp(tour , "Q1")==0){
		if(!(f = open("Q1.txt", O_WRONLY)))
		{}
		else{
			system("touch Q1.txt");
			f = open("Q1.txt", O_WRONLY);
			}
	}
	else if(strcmp(tour , "Q2")==0){
		if(!(f = open("Q2.txt", O_WRONLY)))
		{}
		else{
			system("touch Q2.txt");
			f = open("Q2.txt", O_WRONLY);
			}
	}
	else if(strcmp(tour , "Q3")==0){
		if(!(f = open("Q3.txt", O_WRONLY)))
		{}
		else{
			system("touch Q3.txt");
			f = open("Q3.txt", O_WRONLY);
			}
	}
	else if(strcmp(tour , "C1")==0){
		if(!(f = open("C1.txt", O_WRONLY)))
		{}
		else{
			system("touch C1.txt");
			f = open("C1.txt", O_WRONLY);
			}
	}
    if(f < 0){ // vérifie que le fichier se soit ouvert
        perror("file ");
        exit(0);
    }
    for(int k=0;k<20;k++)//voiture
    {
       sprintf(buff,"%d\n",classment[k].id);
       write(f, buff, strlen(buff));
	}
	if (strcmp(tour , "C1")==0)
	{
		sprintf(buff,"Best Temp:%d Voiture F%d\n",voitcpy[20].BStemp[3],voitcpy[20].idBst[3]);
		write(f, buff, strlen(buff));
	}
	close(f);
}
int main(int argc,char *argv[])
{
sem_init(&s, 0, 1);
sem_init(&sm, 0, 1);
srand(time(NULL));
if (argc > 1)
{
	if (strcmp(argv[1],"C1")==0 || strcmp(argv[1],"P1")==0 || strcmp(argv[1],"P2")==0 || strcmp(argv[1],"P3")==0 || strcmp(argv[1],"Q1")==0 || strcmp(argv[1],"Q2")==0 || strcmp(argv[1],"Q3")==0)
	{
		int NumVoit[20] = {44, 77, 11, 33, 3, 4, 5, 18, 14, 31, 16, 55, 10, 22, 7, 99, 9, 47, 6, 63}; 
		connectShm();
		for(int k = 0; k<V-1 ; k++)
		{
			voitures[k].lost = 0;
			voitures[k].id = NumVoit[k];
		}
		V = getTour(argv[1]);
		for(int i=0;i<4;i++){
		voitures[20].BStemp[i] = 999;
		}
		for(int k = 0; k<V-1 ; k++)
		{
			voitures[k].statut = 'E';
			voitures[k].temp[5] = 0;
		}
		struct timeval tempInitial , tempFinal;
		int seconde = 0;
		if (strcmp(argv[1],"C1")!=0)
		{
			
			while(seconde < 12)
			{
				sem_wait(&s);
				gettimeofday(&tempInitial , NULL);
				sleep(1);
					for(int k = 0; k<V-1 ; k++)
					{
						if (voitures[k].lost == 0)
						{
						essaiQualifCourse(k);
						}
					}
					sem_post(&s);
					memcpy(&voitcpy,voitures,sizeof(struct F1)*21);
				gettimeofday(&tempFinal , NULL);
				seconde += (tempFinal.tv_sec - tempInitial.tv_sec);
				 
				afficheTab(argv[1]);
				Ecrit(argv[1]);
				printf("\nTotal time taken is : %d seconds and %lu microseconds\n",(seconde),(tempFinal.tv_usec - tempInitial.tv_usec));
			}
		}
		else
		{
			for(int i=0;i<3;i++)
			{
				sem_wait(&s);
				gettimeofday(&tempInitial , NULL);
				sleep(1);
					for(int k = 0; k<V-1 ; k++)
					{
					CourseV(k);
					}
					sem_post(&s);
					memcpy(&voitcpy,voitures,sizeof(struct F1)*21);
				gettimeofday(&tempFinal , NULL);
				seconde += (tempFinal.tv_sec - tempInitial.tv_sec);
				 
				afficheTab(argv[1]);
				Ecrit(argv[1]);
				printf("\nTours numéro: %d\n",i+1);
			}
		}
		disconectShm();
	}
	else
	{
		printf("Maivais argument veuillez entrée un des suivant: P1, P2, P3, Q1, Q2, Q3, C1");
	}
}
else
{
	printf("Veuillez entrée un argument: P1, P2, P3, Q1, Q2, Q3, C1");
}
 //afiche le tableau des données
sem_destroy(&s); 
sem_destroy(&sm);
return 0;
}


