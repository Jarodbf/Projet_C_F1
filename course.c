#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

struct F1 voitcpy[21];

sem_t s, sm;

int geneTemp (int x){
	int r=(abs(rand()*x)% (40000 -25000 +1))+25000;
	return  r/1000;
}

void essaiQualifCourse(int k)
{
	int pid; 
	if ((pid = fork()) == 0)
		{
			sem_wait(&sm);
					if (voitures[k].statut != 'O')
					{
						if (voitures[k].statut == 'S')
						{
							voitures[k].statut = 'E';
						}
						if (geneTemp(getpid()) == 39)
						{
							voitures[k].statut = 'S';
						}
						if (geneTemp(getpid())+geneTemp(getpid())+geneTemp(getpid())+geneTemp(getpid()) == 143)
						{
							voitures[k].statut = 'O';
						}
						if (voitures[k].statut == 'E')
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
						}
					}
					sem_post(&sm);
					exit(1);
		}
	else
	{
	wait(NULL);
	}	
}

void CourseV(int k)
{
	int pid;
	if ((pid = fork()) == 0)
		{
			sem_wait(&sm);
			do{
					if (voitures[k].statut != 'O')
					{
						if (voitures[k].statut == 'S')
						{
							voitures[k].statut = 'E';
						}
						if (geneTemp(getpid()) == 36)
						{
							voitures[k].statut = 'S';
							voitures[k].temp[5] += 3;
						}
						if (geneTemp(getpid())+geneTemp(getpid())+geneTemp(getpid())+geneTemp(getpid()) == 143)
						{
							voitures[k].statut = 'O';
							voitures[k].temp[5] += 500;
						}
						if (voitures[k].statut == 'E')
						{
							voitures[k].temp[0] = geneTemp(getpid());
							
							voitures[k].temp[1] = geneTemp(getpid());
									
							voitures[k].temp[2] = geneTemp(getpid());
									
							voitures[k].temp[3] = voitures[k].temp[0] + voitures[k].temp[1] +voitures[k].temp[2];
									
							voitures[k].temp[4] = voitures[k].temp[0] + voitures[k].temp[1] +voitures[k].temp[2];
							
							voitures[k].temp[5] += voitures[k].temp[3];
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
			}while(voitures[k].statut == 'S');
			sem_post(&sm);
			exit(1);
		
		}	
	else
	{
	wait(NULL);
	}			
}

int getTour(char * tour){
	int V = 21;
	if (strcmp(tour,"Q2")==0 || strcmp(tour,"Q3")==0 || strcmp(tour,"C1")==0)
	{
		int fichier =0;
		if (strcmp(tour,"Q2")==0)
		{
			V = V-5;
			fichier = open("Q1.txt", O_RDONLY );
			for(int k = 15; k<20 ; k++)
			{
				voitures[k].lost = 1;
			}
		}
		else if(strcmp(tour,"Q3")==0)
		{
			V = V-10;
			fichier = open("Q2.txt", O_RDONLY );
			for(int k = 10; k<20 ; k++)
			{
				voitures[k].lost = 1;
			}
		}
		else
		{
			fichier = open("Q3.txt", O_RDONLY );
		}
		char* str = malloc(sizeof(char)*500);
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
		for(int k = 0; k<20 ; k++)
		{
			voitures[k].id = pos[k];
		}
	}
	return V;
}