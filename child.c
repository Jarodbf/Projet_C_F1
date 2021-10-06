#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


int p[2];//entrer/sortie pour le pipe
int tab[3];

struct F1 {
	char id[3];
	int temp[4];
	char statut; //S=stand O=out E=enCourse
};
struct F1 voiture[20];
int geneTemp (){
	int r;
    r = (rand()%16)+25;
return r;
}

int * childRand()
{
            for(int j=0;j<3;j++)
            {
            tab[j]= geneTemp();
            printf("child = %d avec le pid %d\n", tab[j], getpid());
            	
            //int affichage = 12;
            
            }
            write(p[1],&tab,sizeof(tab));
            dup2(p[1],1); // envoie le résultat au père
            //close(p[1]);
            //exit(0);
            return tab;
}



int main()
{
pipe(p);

srand(time(NULL));
    for(int i=0;i<2;i++) // loop will run n times (n=5)
    {
        if(fork() == 0)
        {
            //int tab[3];
            //for(int j=0;j<3;j++)
            //{
            //tab[3]= geneTemp();
            //printf("child = %d avec le pid %d\n", tab[3], getpid());
            	
            //int affichage = 12;
            childRand();
            //}
            //write(p[1],&tab,sizeof(tab));
            //dup2(p[1],1); // envoie le résultat au père
            //close(p[1]);
            //exit(0);
            //return tab;
        }
        else
        {
            
        //for(int i=0;i<2;i++)
          //  {
                wait(NULL);
                int tab2[3];
                //voiture[i].temp[j] = read(p[0],&voiture[i].temp[j],sizeof(voiture[i].temp[j]));
                for(int j=0;j<3;j++)
                {
                read(p[0],tab2,sizeof(tab2));
                
                voiture[i].temp[j] = tab2[j];
                printf("parent = %d\n", voiture[i].temp[j]);
                }
                //printf("parent = %d\n", voiture[i].temp[j]);
                //close(p[0]);
            //}
        }
    }

strcpy(voiture[0].id,"F44");
voiture[0].temp[3] = voiture[0].temp[0]+voiture[0].temp[1]+voiture[0].temp[2];
printf("%s \n%d %d %d %d\n",voiture[0].id,voiture[0].temp[0],voiture[0].temp[1],voiture[0].temp[2],voiture[0].temp[3]);
strcpy(voiture[1].id,"F45");
voiture[1].temp[3] = voiture[1].temp[0]+voiture[1].temp[1]+voiture[1].temp[2];
printf("%s \n%d %d %d %d\n",voiture[1].id,voiture[1].temp[0],voiture[1].temp[1],voiture[1].temp[2],voiture[1].temp[3]);

}
