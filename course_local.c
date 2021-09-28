e#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct F1 {
	int id;
        int temp[4];
        char statut; //S=stand O=out E=enCourse
}

typedef struct F1 struc_voiture;

int geneTemp (){
	srand(time(NULL));
	for(int i=0;i<20;i++)
        {
        float r = (rand()%16)+25;
        }
return r;
}
int main()
{
/*struct F1 F44;
F44.temp[0] = généTemp();
F44.temp[1] = généTemp();
F44.temp[2] = généTemp();
F44.temp[3] = F44.temp[0]+F44.temp[1]+F44.temp[2];*/
	
struc_voiture voiture[20];
voiture[0].id = "F44";
voiture[0].temp[0] = geneTemp();
voiture[0].temp[1] = geneTemp();
voiture[0].temp[2] = geneTemp();
voiture[0].temp[3] = voiture[0].temp[0]+voiture[0].temp[1]+voiture[0].temp[2];
}
