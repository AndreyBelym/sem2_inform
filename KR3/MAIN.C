#include <stdio.h>
#include <stdlib.h>
#include "messages.h"
#include <ctype.h>
#include <time.h>

#define MAX_ON_SCREEN_COUNT 1
int CheckData(double **array,long size);
int InputData(double ***array,long *size);
int PrintResult(double **array,long size);
void FreeArray(double ***array,long size);
int QuickSort(double **arr, long size);
void PrintMatrix(FILE *f,double **array,long size);
int GetParam(const char message[], //paramName - имя запрашиваемого параметра;
              const char name[], //paramCond - дополнительная информация о параметре;
              double *param
                    );
int GetParamFile(FILE *f,
              double *param
                    );

int GetParamLong(const char message[], //paramName - имя запрашиваемого параметра;
              const char name[], //paramCond - дополнительная информация о параметре;
              long *param
                    );
int GetParamFileLong(FILE *f,
              long *param
                    );

int clearline(FILE *f){
  int count=0;
	while (!feof(f)&&(getc(f)!='\n')) count++;
	return count;
}
int GetReqResult(void);

int GetReqResult(){
  char answer;
    answer=getchar();
    clearline(stdin);
    while (toupper(answer)!='Y'
           &&toupper(answer)!='N'){
        printf(MSG_REQUEST_ERROR);
        answer=getchar();
        clearline(stdin);
    }

    return toupper(answer)=='Y';
}
int fexists(char  *fname){
  FILE *f;
    f=fopen(fname,"r");
    if (f!=NULL) fclose(f);
    return f!=NULL;
}
int GetInFile(FILE **f){
  int error,req_rslt;
  char fileName[255]="\0";
    do{
        printf(MSG_REQUEST_INFILE);
        //считать строку (gets() deprecated!)
        printf("%s: ",NFO_FILE);scanf("%255[^\n]",fileName);
        clearline(stdin);
        if (!(fileName[0])){
            error=1;
            //*f=stdin;
            //return 1;
        } else
            *f=fopen(fileName,"r");
        error=*f==NULL;
        if (error) {
            printf(MSG_FILE_REQUEST_ERROR);
            req_rslt=GetReqResult();
        };
    } while (req_rslt&&error);
    return !error;
  };
///////////////////////////////////////
  int GetOutFile(FILE * * f){
  char fileName [255]="\0";
  int error=0,req_rslt;
    do{
        printf(MSG_REQUEST_OUTFILE);
        //считать строку (gets() deprecated!)
        printf("%s: ",NFO_FILE);scanf("%255[^\n]",fileName);
        clearline(stdin);
        if (!(fileName[0])){
            *f=stdout;
            return 1;
        }
        if (fexists(fileName)){
            error=1;
            printf(MSG_FILE_EXISTS);
            printf(MSG_REWRITE_FILE);
            error=!GetReqResult();

         };
         if (!error){
            while (!feof(stdin)&&(getc(stdin)!='\n'));
            *f=fopen(fileName,"w");
            error=*f==NULL;
         };
         if (error) {
            printf(MSG_FILE_REQUEST_ERROR);
            req_rslt=GetReqResult();
         };
    } while (req_rslt&&error);
    return !error;
  };
int main(){
  int log,req_rslt;
  double **array; long size;
    printf(MSG_WELCOME);

    do {
        log=InputData(&array,&size);
        if (log)
            log=CheckData(array,size);
        if (!log){
            printf(MSG_VERIFY_ERROR);
            printf(MSG_REPEAT_INPUT);
            req_rslt=GetReqResult();
        }
    } while (!log&&req_rslt);
    if (log){
        log=QuickSort(array,size);
        if (log){
            log=PrintResult(array,size);
        } else
            printf(MSG_ARRAY_TOOLONG);
        FreeArray(&array,size);
    } ;
    if (log) printf(MSG_OPERATION_SUCCEEDED); else printf(MSG_ABORTED);
    printf(MSG_PRESS_ANYKEY);
    clearline(stdin);
    return 0;
}
int PrintResult(double **array,long size){
  int log=1,req_rslt=0; FILE *f;
    printf(MSG_RESULT,size,size);
    do{
    log=GetOutFile(&f);
    if (log&&(f==stdout)&&size>=(MAX_ON_SCREEN_COUNT)){
        log=0;
        printf(MSG_MATRIX_TOO_BIG_FOR_SCREEN);
        printf(MSG_FILE_NEEDED);
        printf(MSG_REPEAT_INPUT);
        req_rslt=GetReqResult();
    }
    } while (!log&&req_rslt);
    if (log){

        PrintMatrix(f,array,size);
        if (f!=stdout)
            fclose(f);
    }
    return log;
}
void PrintMatrix(FILE *f,double **array,long size){
  long i,j;
    for (i=0;(i<=size-1);i++){
        for (j=0;(j<=size-1);j++)
            fprintf(f,"%8.4lf ",array[i][j]);
        fprintf(f,"\n");
    }
}
typedef struct __stack__{
    long value;
    struct __stack__ *prev;
} STACK;

STACK * push(STACK *list, long value){
  STACK *new_elem;
    new_elem=malloc(sizeof(STACK));
    if (new_elem!=NULL){
        new_elem->value=value;
        new_elem->prev=list;
    }
    return new_elem;
}

STACK *pop(STACK *list){
  STACK *temp;
    if (list!=NULL){
        temp=list->prev;
        free(list);
    } else temp=NULL;
    return temp;
}
int QuickSort(double **array, long size) {

  int log=1;
  double  med,swap;
  STACK *low=NULL, *high=NULL, *temp;
  long i,j, L, R;
    low=push(low,0);high=push(high,size-1);
    log=(low!=NULL)&&(high!=NULL);
    while (log&&(low!=NULL)&&(high!=NULL)){
        L=low->value; R=high->value;
        low=pop(low);high=pop(high);
        while (log&&(L<R)){
            i=L;j=R;med=array[(L+R)/2][(L+R)/2];
            do {
                while (array[i][i]<med) i++;
                while (med<array[j][j]) j--;
                if (i<=j){
                    swap=array[i][i];array[i][i]=array[j][j];array[j][j]=swap;
                    i++;j--;
                }
            }while (i<=j);
            if ((j-L)<(R-i)){
                if (i<R){
                    log=(temp=push(low,i))!=NULL;
                    if (log){
                        low=temp;
                        log=(temp=push(high,R))!=NULL;
                        if (log)
                            high=temp;
                    }
                }
                R=j;
            } else {
                if (L<j){
                    log=(temp=push(low,L))!=NULL;
                    if (log){
                        low=temp;
                        log=(temp=push(high,j))!=NULL;
                        if (log)
                            high=temp;
                    }
                }
                L=i;
            }
        }
    }
    return log;
}
int AllocArray(double ***array,long size){
  int log; long i;
    *array=NULL;
    *array=malloc(size*sizeof(double*));
    log=*array!=NULL;
    if(log) {
        for (i=0;i<=size-1;i++)
            (*array)[i]=NULL;
        for (i=0;(i<=size-1)&&log;i++){
            (*array)[i]=malloc(size*sizeof(double));
            log=**array!=NULL;
        }
    }
    if (!log)
        FreeArray(array,size);
    return log;
}

void FreeArray(double ***array,long size){
  long i;
    for (i=0;(i<=size-1)&&(*array)[i]!=NULL;i++){
        free((*array)[i]);
        (*array)[i]=NULL;
    };
    if (*array!=NULL){
        free(*array);
        *array=NULL;
    };
}

int InputConsole(double ***array,long *size){
  int log;
  long i,j; char message_elem[255],name_elem[50];
    log=GetParamLong(MSG_REQUEST_SIZE,"m",size);
    if (log) {
        log=AllocArray(array,*size);
        if (log){
            for (i=0;(i<=*size-1)&&log;i++)
                for (j=0;(j<=*size-1)&&log;j++){
                    sprintf(message_elem,MSG_REQUEST_ELEMENT,i,j);
                    sprintf(name_elem,"A[%ld,%ld]: ",i,j);
                    log=GetParam(message_elem,name_elem,(*array)[i]+j);
                }
            if (!log) FreeArray(array,*size);
        } else
             printf(MSG_MEMALLOC_ERROR);
    };
    return log;
}

int InputFile(double ***array,long *size){
  int log; FILE *f; long i,j;
    log=GetInFile(&f);
    if (log){
        log=GetParamFileLong(f,size);
        if (!log){
            printf(MSG_SIZE_FREAD_ERROR);

        } else {
            log=AllocArray(array,*size);
            if (log){
                for (i=0;(i<=*size-1)&&log;i++)
                    for (j=0;(j<=*size-1)&&log;j++){
                        log=GetParamFile(f,(*array)[i]+j);
                    };
                if (!log){
                    i--;j--;
                    printf(MSG_ARR_FREAD_ERROR,i,j);

                }
                if (f!=stdin)
                    fclose(f);
                //else clearline(stdin);
                if (!log) FreeArray(array,*size);
            } else
                 printf(MSG_MEMALLOC_ERROR);
        }
    } else printf(MSG_FILE_REQUEST_ERROR);

    return log;
}
int InputRandom(double ***array,long *size){
  int log,req_rslt; long min,max,i,j;
    srand (time(NULL));
    log=GetParamLong(MSG_REQUEST_SIZE,"m",size);

    if (log)
        log=GetParamLong(MSG_REQUEST_MIN_RANDOM,"min",&min);
    if (log)
        do{
            log=GetParamLong(MSG_REQUEST_MAX_RANDOM,"max",&max);
            if (log&&!(max>=min)) {
                log=0;
                printf(MSG_BOUND_ERROR);
                printf(MSG_REPEAT_INPUT);
                req_rslt=GetReqResult();
            }
        }while (!log&&req_rslt);
    if (log){
        log=AllocArray(array,*size);
        if (!log)
            printf(MSG_MEMALLOC_ERROR);
    };
    if (log){
        for (i=0;i<=*size-1;i++)
            for (j=0;j<=*size-1;j++)
                (*array)[i][j]=(double)((double)rand()/RAND_MAX * (max - min) + min);
    }
    return log;
}
int InputData(double ***array,long *size){
  int log=1,req_rslt=1;
    printf(MSG_REQUEST_RANDOM);
    req_rslt=GetReqResult();
    if (req_rslt){
        log=InputRandom(array,size);
        return log;
    } else {
        printf(MSG_REQUEST_FILE);
        req_rslt=GetReqResult();
    };
    if (log&&req_rslt){
        log=InputFile(array,size);
        return log;
    } else {
        printf(MSG_REQUEST_CONSOLE);
        req_rslt=GetReqResult();
    } ;
    if (log&&req_rslt){
        log=InputConsole(array,size);
        return log;
    } else {
        printf(MSG_INPUT_CANCELED);
        return 0;
    } ;
    return 0;
}
int GetParam(const char message[], //paramName - имя запрашиваемого параметра;
              const char name[], //paramCond - дополнительная информация о параметре;
              double *param
                    ){
  int log,req_rslt;
    do {
        printf("%s",message);
        printf("%s: ",name);
        log=scanf("%lf",param);
        log=!clearline(stdin)&&log;
        if (!log){  //введено не вещественное число?
            printf(MSG_INPUT_ERROR);
            printf(MSG_REPEAT_INPUT);
            req_rslt=GetReqResult();
        }
    } while (!log&&req_rslt); //пока пользователь не отказался или число некорректное
    return log;

}

int GetParamFile(FILE *f,
              double *param
                    ){

    //log=!clearline(stdin)&&log;
    return fscanf(f,"%lf",param);
}

int GetParamLong(const char message[], //paramName - имя запрашиваемого параметра;
              const char name[], //paramCond - дополнительная информация о параметре;
              long *param
                    ){
  int log,req_rslt;
    do {
        printf("%s",message);
        printf("%s: ",name);
        log=scanf("%ld",param);
        log=!clearline(stdin)&&log;
        if (!log){  //введено не вещественное число?
            printf(MSG_INPUT_ERROR);
            printf(MSG_REPEAT_INPUT);
            req_rslt=GetReqResult();
        }
    } while (!log&&req_rslt); //пока пользователь не отказался или число некорректное
    return log;
}
int GetParamFileLong(FILE *f,
              long *param
                    ){

    //log=!clearline(stdin)&&log;
    return fscanf(f,"%ld",param);
}

int CheckData(double **array,long size){
    printf(MSG_CHECK_INFO,size,size);
    if (size<=MAX_ON_SCREEN_COUNT){
        PrintMatrix(stdout,array,size);
        printf(MSG_REQUEST_VERIFY);
    } else {
        printf(MSG_MATRIX_TOO_BIG_FOR_SCREEN);
        printf(MSG_REQUEST_TRUST);
    }
    return GetReqResult();
}
