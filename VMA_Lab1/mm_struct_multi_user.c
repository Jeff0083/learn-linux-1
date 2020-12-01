#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


void * print_a(void *a);
void * print_b(void *b);
void * print_c(void *c);

int main(){

    pthread_t t0;
    pthread_t t1;
    pthread_t t2;
   if(pthread_create(&t0, NULL, print_a, NULL) == -1){
        puts("fail to create pthread t0");
        exit(1);
    }
    if(pthread_create(&t1, NULL, print_b, NULL) == -1){
        puts("fail to create pthread t1");
        exit(1);
    }

    if(pthread_create(&t2, NULL, print_c, NULL) == -1){
        puts("fail to create pthread t2");
        exit(1);
    }
   
    void * result;
    if(pthread_join(t0, &result) == -1){
        puts("fail to recollect t0");
        exit(1);
    }
/*
    if(pthread_join(t1, &result) == -1){
        puts("fail to recollect t1");
        exit(1);
    }
    if(pthread_join(t2, &result) == -1){
        puts("fail to recollect t1");
        exit(1);
    }
*/

	while(1);
    return 0;
}

void * print_a(void *a){
   int i = 0; 
   for(i = 0;i < 10; i++){
        sleep(10);
    }
    return NULL;

}


void * print_b(void *b){
    int i = 0;
    for(i=0;i<20;i++){
        sleep(10);
    }
    return NULL;
}


void * print_c(void *c){
    int i = 0;
    for(i=0;i<20;i++){
        sleep(10);
    }
    return NULL;
}



