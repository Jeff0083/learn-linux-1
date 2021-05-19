#include<stdio.h>
#include<stdlib.h>

int main(){

    FILE *fp0 = NULL;	
    fp0 = fopen("/dev/my_mutex","r+");
    if (fp0 == NULL)
    {
        printf("Open my_mutex Error!\n");
        return -1;
    }
    sleep(5);
    close(fp0);
    return 0;
}
