#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define V  2
# define T  5

struct F1 {
	char id[3];
	int temp[4];
	char statut; //S=stand O=out E=enCourse
};

struct F1 voiture[V];

int geneTemp (){
	int r;
    r = (rand()%16)+25;
return r;
}

void afficheTab() {
printf(" IDV | BS1 | BS2 | BS3 | BT \n\n");
for(int k=0;k<V;k++)//voiture
    {
       printf(" %s | %3d | %3d | %3d | %3d |\n",voiture[k].id,voiture[k].temp[0],voiture[k].temp[1],voiture[k].temp[2],voiture[k].temp[3]);
    }
}


int main()
{
srand(time(NULL));
strcpy(voiture[0].id,"F44");
strcpy(voiture[1].id,"F45");

int tempT;
for(int i=0;i<T;i++) //tour
{
    for(int j=0;j<3;j++)// secteurs
    {
        for(int k=0;k<V;k++)//voiture
        {
            voiture[k].temp[j] = geneTemp();
            /*tempT=geneTemp();
            if(tempT>voiture[k].temp[j]){
               voiture[k].temp[j] = tempT();
            }*/
        }
    }

    for(int k=0;k<V;k++)//comptage temps tot
    {
        voiture[k].temp[3] = voiture[k].temp[0]+voiture[k].temp[1]+voiture[k].temp[2];
        /*tempT = voiture[k].temp[0]+voiture[k].temp[1]+voiture[k].temp[2];
        if(tempT>voiture[k].temp[3]){
            voiture[k].temp[3] = tempT;
        }*/
    }
}
afficheTab();
}
