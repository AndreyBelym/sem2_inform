#include <alloc.h>
#include <stdio.h>
int main(void){
    int far *p; FILE *log;
    int i;
    log=fopen("log.txt","w");
    for (i=1;i<=1024;i++){
        p=malloc(1024);
        if (p==NULL) fprintf(log,"null\n"); else fprintf(log,"ok\n");
    };
    (void)getchar();
    return 0;
}