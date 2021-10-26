#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define V  20
# define T  5

struct F1 {
	int id;
	float temp[4];
	float BStemp[4];
	char statut; //S=stand O=out E=enCourse
};

struct F1 voiture[V];

int Bid[4];
float geneTemp (){
	float r;
    r = (((rand())%16000)+25000);
return r/1000;
}

void afficheTab() {
printf(" IDV |  BS1   |  BS2   |  BS3   |  BT   |\n\n");
for(int k=0;k<V;k++)//voiture
    {
       printf(" F%2d | %3.2fs | %3.2fs | %3.2fs | %dm%2ds |\n",voiture[k].id,voiture[k].temp[0],voiture[k].temp[1],voiture[k].temp[2],((int)voiture[k].temp[3]/60),((int)voiture[k].temp[3]%60));
    }
	printf("--------------------------------------------------------------\n");
	printf(" F%2d | %3.2fs | F%2d | %3.2fs | F%2d | %3.2fs |\n",Bid[0],voiture[0].BStemp[0],Bid[1],voiture[0].BStemp[1],Bid[2],voiture[0].BStemp[2]);
}


int main()
{
srand(time(NULL));
int NumVoit[20] = {44, 77, 11, 33, 3, 4, 5, 18, 14, 31, 16, 55, 10, 22, 7, 99, 9, 47, 6, 63};
for(int i=0;i<20;i++){
	voiture[i].id = NumVoit[i];
}

float tempT;
for(int i=0;i<T;i++) //tour
{
    for(int j=0;j<3;j++)// secteurs
    {
        for(int k=0;k<V;k++)//voiture
        {
		if(i==0){
           		voiture[k].temp[j] = geneTemp();
		}
		else{
			tempT=geneTemp();
			if(tempT>voiture[k].temp[j]){
			voiture[k].temp[j] = tempT;
			}
		}
        }
    }

    for(int k=0;k<V;k++)//comptage temps tot
    {
	    if(i==0){
		voiture[k].temp[3] = voiture[k].temp[0]+voiture[k].temp[1]+voiture[k].temp[2];
	    }
	    else{
		tempT = voiture[k].temp[0]+voiture[k].temp[1]+voiture[k].temp[2];
		if(tempT>voiture[k].temp[3]){
		    voiture[k].temp[3] = tempT;
		}
       	 }
    }
	
	for(int j=0;j<3;j++)// secteurs
    {
		float cache = voiture[0].temp[j];
        for(int k=0;k<V;k++)// meilleur bstemp1 2 3 voiture | not semaphore 
        {
			if(cache>voiture[k].temp[j]){
			voiture[0].BStemp[j] = voiture[k].temp[j];
			cache = voiture[k].temp[j];
			Bid[j] = k;
			}
		}
    }
}
afficheTab();
}
