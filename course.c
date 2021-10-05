#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct F1 {
	char id[3];
	int temp[4];
	char statut; //S=stand O=out E=enCourse
};
struct F1 voiture[20];

void geneTemp (int x){
	int r;
	srand(time(NULL));
	for(int i=0;i<3;i++)
        {
        r = (rand()%16)+25;
		voiture[x].temp[i] = r;
        }
}
int main()
{

geneTemp(0);
geneTemp(1);

strcpy(voiture[0].id,"F44");
voiture[0].temp[3] = voiture[0].temp[0]+voiture[0].temp[1]+voiture[0].temp[2];
printf("%s \n%d %d %d %d\n",voiture[0].id,voiture[0].temp[0],voiture[0].temp[1],voiture[0].temp[2],voiture[0].temp[3]);
strcpy(voiture[1].id,"F45");
voiture[1].temp[3] = voiture[1].temp[0]+voiture[1].temp[1]+voiture[1].temp[2];
printf("%s \n%d %d %d %d\n",voiture[1].id,voiture[1].temp[0],voiture[1].temp[1],voiture[1].temp[2],voiture[1].temp[3]);

}
