#include <stdio.h>
#include <ctype.h>


/****** МАКРОСЫ-КОНСТАНТЫ ******/

#define MAX_N 20L //число элементов в множестве для перестанок

/****** ПРОТОТИПЫ ФУНКЦИЙ ******/
int InputData(long *k,long *n);
long GetComb(long k,long n);
int clearline(FILE *f);
long ext_fact(long beg,long end);
int GetAskResult();
int GetParam(const char message[],const char name[],long *param,long h_bound);
/****** MAIN PROGRAM *****/
int main(){


  long i,M[MAX_N];
  int log; long n,k;char ch;
    printf("Программа расчитывает все сочетания из n(0<n<=%ld) по i,\n"\
                    "где i = 1..k(0<k<=n)\n",MAX_N);
    log=InputData(&n,&k);
    if(log){
        printf("Вы готовы? Y/N \n");
        ch=GetAskResult();
        log=ch=='Y';
    }
    if(log){
        for(i=1;i<=k;i++)
            M[i-1]=GetComb(i,n);

        printf("Значения сочетаний из %ld по...\n",n);
        for(i=0;i<=k-1;i++)
            printf("%ld: %ld\n",i+1,M[i]);
        }
    else
        printf("Работа программы прервана!\n");
    printf("Нажмите <Enter>...\n");
    clearline(stdin);
    return 0;
}
/***** END MAIN PROGRAM *****/
int InputData(long *n,long *k){
  int log; char msg[50];
    sprintf(msg,"Введите n. 0<n<=%ld\n",MAX_N);
    log=GetParam(msg,"n",n,MAX_N);
    if (log){
        sprintf(msg,"Введите k. 0<k<=%ld\n",*n);
        log=GetParam(msg,"k",k,*n);
    }
    return log;
}

int GetParam(const char message[],const char name[],long *param,long h_bound){
  int log,req_rslt;
    do{
        req_rslt=0;
        printf("%s",message);
        printf("%s: ",name);
        log=scanf("%ld",param);
        log=!clearline(stdin)&&log;
        if (!log){  //введено не вещественное число?
            printf("Введено не число!\n"
                   "Повторить ввод? Y/N\n");
            req_rslt=GetAskResult()=='Y';
        }
        if (log&&(*param<1||*param>h_bound)){
            log=0;
            printf("Ошибка!%s должен быть больше 0 и меньше %ld!\n",name,h_bound);
            printf("Повторить ввод? Y/N\n");
            req_rslt=GetAskResult()=='Y';
        }
    } while(!log&&req_rslt);
    return log;
}
int GetAskResult(){
  char answer;
    answer=getchar();
    clearline(stdin);
    while (toupper(answer)!='Y'
           &&toupper(answer)!='N'){
        printf("Неправильный ответ! Допустимо:\n"\
					  "Y - да; N - нет.\n");
        answer=getchar();
        clearline(stdin);
    }

    return toupper(answer);
}

long GetComb(long k,long n){
  long max_fact;
    if(k>n/2)
        max_fact=k;
    else
        max_fact=n-k;
    return ext_fact(max_fact+1,n)/ext_fact(1,n-max_fact);


}

long ext_fact(long beg,long end){
  long fact=1,i;
    for (i=beg;i<=end;i++)
        fact*=i;
    return fact;
}

int clearline(FILE *f){
  int count=0;
	while (!feof(f)&&(getc(f)!='\n')) count++;
	return count;
}
