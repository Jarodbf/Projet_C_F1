#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
srand(time(NULL));
for(int i=0;i<20;i++)
        {
        int r = (rand()%20)+1;
        printf("%d\n",r);
        }
return 0;
}
