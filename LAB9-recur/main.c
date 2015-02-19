#include <stdio.h>
#include "messages.h"
#include <ctype.h>
#include <math.h>

#define FUNC_NAME "sin(x)"
double f(double x){
    return 0.0005-x;
}

int clearline(FILE *f){
  int count=0;
	while (!feof(f)&&(getc(f)!='\n')) count++;
	return count;
}

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

/***** ФУНКЦИЯ ВВОДА ВЕЩЕСТВЕННОГО ПАРАМЕТРА *****/
int GetParam(const char paramName[], //paramName - имя запрашиваемого параметра;
              const char paramCond[], //paramCond - дополнительная информация о параметре;
              double *param
                    ){
  int log,req_rslt;
    do {
        printf(MSG_REQUEST_PARAM,paramName,paramCond);
        printf("%s: ",paramName);
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

/***** ФУНКЦИЯ ВВОДА ДАННЫХ *****/
int InputData(double *a, //a,b - границы отрезка поиска корня;
                double *b,
                double  *eps  //eps - точность вычислений;
                    ){
  int log=1,req_rslt=1;
    do {
        log=GetParam("a","",a);
        if (log)
            log=GetParam("b","b>a.",b);
        if (log&&!(*b>*a)) {
            log=0;
            printf(MSG_BOUND_ERROR);
            printf(MSG_REPEAT_INPUT);
            req_rslt=GetReqResult();
        }
    } while (!log&&req_rslt);
    if (log)
        do {
            log=GetParam("eps","eps>0.",eps);
            if (log &&!(*eps>0)) {
                log=0;
                printf(MSG_PRECISION_ERROR);
                printf(MSG_REPEAT_INPUT);
                req_rslt=GetReqResult();
            }
        } while (!log&&req_rslt);
    return log;
}

/***** ФУНКЦИЯ ПРОВЕРКИ ДАННЫХ *****/
int CheckData(const double a, //a,b - границы отрезка поиска корня;
                const double b,
                const double  eps  //eps - точность вычислений;
                ){
    printf(MSG_REQUEST_VERIFY,a,b,eps);
    return GetReqResult();

}


/***** ФУНКЦИЯ РАСЧЕТА КОРНЯ *****/
double Root(double (*f)(double x), //f - анализируемая функция;
                const double a, //a,b - границы отрезка поиска корня;
                const double b,
                const double  eps  //eps - точность вычислений;
                    ){
  double c;
    c=(a+b)/2;
    if (b-a>eps)
        if ((*f)(c)*(*f)(a)<=0)
            return Root(f,a,c,eps);
        else
            return Root(f,c,b,eps);
    else
        return c;
}
/***** ФУНКЦИЯ ПОЛУЧЕНИЯ КОРНЯ *****/
double GetRoot( double (*f)(double x), //f - анализируемая функция;
                  const double a, //a,b - границы отрезка поиска корня;
                  const double b,
                  const double  eps,  //eps - точность вычислений;
                  double *f_root  //f_root - найденный корень
                        ){
    if (!(b>a))
        return 1;
    else {
        if (!(eps>0))
            return 2;
        else {
            if (f(a)*f(b)>0)
                return 3;
            else {
                *f_root=Root(f,a,b,eps);
                return 0;
            }
        }
    }
}


/***** ОСНОВНАЯ ПРОГРАММА *****/

int main(){
    //a,b - границы отрезка поиска корня;
    //eps - точность вычислений;
    //log - переменная состояния;
    //code - код ошибки поиска корня}

  double a,b,eps,f_root;
  int log; int code;

    printf(MSG_WELCOME,FUNC_NAME);
    log=InputData(&a,&b,&eps);
    if (log)
        log=CheckData(a,b,eps);
    if (log) {
        code=GetRoot(&f,a,b,eps,&f_root);
        switch (code){
            case 0:
                printf(MSG_RESULT,a,b,f_root);
            break;
            case 1:
                printf(MSG_BOUND_ERROR);
            break;
            case 2:
                printf(MSG_PRECISION_ERROR);
            break;
            case 3:
                printf(MSG_NOT_FOUND,a,b);
            break;
        }
    }
    else
        printf(MSG_ABORTED);
    printf(MSG_PRESS_ANYKEY);
    clearline(stdin);
    return 0;
}
