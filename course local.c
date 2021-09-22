#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct F1 {
        int temp[4];
        char statut; //S=stand O=out E=enCourse
}

int généTemp (){
	srand(time(NULL));
	for(int i=0;i<20;i++)
        {
        int r = (rand()%20)+1;
        }
return r;
}
int main()
{
struct F1 F44;
F44.temp[0] = généTemp();
F44.temp[1] = généTemp();
F44.temp[2] = généTemp();
F44.temp[4] = F44.temp[0]+F44.temp[1]+F44.temp[2];
}
