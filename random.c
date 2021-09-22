#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
int tab[20] = {1};
int tab2[2000] = {1};
int j;
srand(time(NULL));
for(int i=0;i<19;i++)
    {

    for(j=0;j<1999;j++)
    {
        while(tab2[j] > 45 || tab2[j] < 20)
        {
        tab2[j] = (rand()%50 )+1;
        }
    }
        sleep(0.1);
        tab[i] = tab2[i*99];
        printf("%d\n", tab[i]);
    }
return 0;
}
