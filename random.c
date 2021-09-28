#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
srand(time(NULL));
for(int i=0;i<20;i++)
        {
        float r = ((rand()%16)+25);
        printf("%d\n",r);
        }
return 0;
}
