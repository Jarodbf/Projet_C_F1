#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct F1 {
	char id[3];
	int temp[4];
	char statut; //S=stand O=out E=enCourse
};


float r=0;

float geneTemp (){
	srand(time(NULL));
	for(int i=0;i<20;i++)
        {
        r = (rand()%16)+25;
        }
return r;
}
int main()
{

struct F1 voiture[20];
strcpy(voiture[0].id,"F44");
voiture[0].temp[0] = geneTemp();
voiture[0].temp[1] = geneTemp();
voiture[0].temp[2] = geneTemp();
voiture[0].temp[3] = voiture[0].temp[0]+voiture[0].temp[1]+voiture[0].temp[2];
printf("%s \n%d %d %d %d\n",voiture[0].id,voiture[0].temp[0],voiture[0].temp[1],voiture[0].temp[2],voiture[0].temp[3]);

}
