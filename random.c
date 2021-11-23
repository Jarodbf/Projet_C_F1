#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int geneTemp (int x){
	int r=(abs(rand()*x)% (40000 -25000 +1))+25000;
	return  r/1000;
}
