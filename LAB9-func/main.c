#include <stdio.h>
#include <ctype.h>
#include "messages.h"

/****** МАКРОСЫ-КОНСТАНТЫ ******/
#define MAX_K 5UL //максимальное кол-во выбираемых элементов для перестанок
#define MAX_N 20UL //число элементов в множестве для перестанок

/****** ПРОТОТИПЫ ФУНКЦИЙ ******/
int Ready(void);
unsigned long GetComb(unsigned long k,unsigned long n);
int clearline(FILE *f);
unsigned long ext_fact(unsigned long beg,unsigned long end);

/****** MAIN PROGRAM *****/
int main(){


  unsigned long i,M[MAX_K];
    printf(MSG_WELCOME,MAX_N,MAX_K);
    if(Ready()){
        for(i=1;i<=MAX_K;i++)
            M[i-1]=GetComb(i,MAX_N);

        printf(MSG_SUCCESS,MAX_N);
        for(i=0;i<=MAX_K-1;i++)
            printf("%ld: %ld\n",i+1,M[i]);
        }
    else
        printf(MSG_ABORTED);
    printf(MSG_PRESS_ANYKEY);
    clearline(stdin);
    return 0;
}
/***** END MAIN PROGRAM *****/
int GetAskResult(){
  char answer;
    answer=getchar();
    clearline(stdin);
    while (toupper(answer)!='Y'
           &&toupper(answer)!='N'){
        printf(MSG_ASK_ERROR);
        answer=getchar();
        clearline(stdin);
    }

    return toupper(answer)=='Y';
}

int Ready(void){
    printf(MSG_ASK_READY);
    return GetAskResult();
}

unsigned long GetComb(unsigned long k,unsigned long n){
  unsigned long max_fact;
    if(k>n/2)
        max_fact=k;
    else
        max_fact=n-k;
    return ext_fact(max_fact+1,n)/ext_fact(1,n-max_fact);


}

unsigned long ext_fact(unsigned long beg,unsigned long end){
  unsigned long fact=1,i;
    for (i=beg;i<=end;i++)
        fact*=i;
    return fact;
}

int clearline(FILE *f){
  int count=0;
	while (!feof(f)&&(getc(f)!='\n')) count++;
	return count;
}
