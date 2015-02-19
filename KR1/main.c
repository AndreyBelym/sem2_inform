#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "messages.h"
#include <ctype.h>
#define FIRST_STEPS_COUNT 16
#define H_MIN 0.1
double d,e;
double f(double x){
    if (x<=d)
        return sqrt(3)*(x-d)/3-d;
    else if (x<=e)
        return -x;
    else
        return (x-e)*sqrt(3)-e;
}

double GetIntegral(double (*f)(double x),
                    double beg,
                    double end,
                    double eps
                        );
int CheckData(const double d,
              const double e,
              const double a, //a,b - границы отрезка поиска корня;
                const double b,
                const double  eps  //eps - точность вычислений;
                );
int GetReqResult();
int InputData(double *d,
              double *e,
              double *a, //a,b - границы отрезка поиска корня;
                double *b,
                double  *eps  //eps - точность вычислений;
                    );
int clearline(FILE *f){
  int count=0;
	while (!feof(f)&&(getc(f)!='\n')) count++;
	return count;
}

int main(){
  double a,b,eps,result;
  int log,req_rslt;
    printf(MSG_WELCOME);

    do {
        log=InputData(&d,&e,&a,&b,&eps);
        if (log)
            log=CheckData(d,e,a,b,eps);
        if (!log){
            printf(MSG_VERIFY_ERROR);
            printf(MSG_REPEAT_INPUT);
            req_rslt=GetReqResult();
        }
    } while (!log&&req_rslt);
    if (log){
        result=GetIntegral(f,a,b,eps);
        printf(MSG_RESULT,a,b,result,eps);
    } else printf(MSG_ABORTED);
    printf(MSG_PRESS_ANYKEY);
    clearline(stdin);
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
int InputData(double *d,
              double *e,
              double *a, //a,b - границы отрезка поиска корня;
                double *b,
                double  *eps  //eps - точность вычислений;
                    ){
  int log=1,req_rslt=1;
    do {
        log=GetParam(MSG_REQUEST_D,"d",d);
        if (log&&(*d>0)){
            log=0;
            printf(MSG_D_ERROR);
            printf(MSG_REPEAT_INPUT);
            req_rslt=GetReqResult();
        }
    } while (!log&&req_rslt);
    if (log)
        do {
            log=GetParam(MSG_REQUEST_E,"e",e);
            if (log&&(*e<0)){
                log=0;
                printf(MSG_E_ERROR);
                printf(MSG_REPEAT_INPUT);
                req_rslt=GetReqResult();
            }
        } while (!log&&req_rslt);
    if (log)
        log=GetParam(MSG_REQUEST_A,"a",a);
    if (log)
        do {
            log=GetParam(MSG_REQUEST_B,"b",b);
            if (log&&!(*b>*a)) {
                log=0;
                printf(MSG_BOUND_ERROR);
                printf(MSG_REPEAT_INPUT);
                req_rslt=GetReqResult();
            }
        } while (!log&&req_rslt);
    if (log)
        do {
            log=GetParam(MSG_REQUEST_EPS,"eps",eps);
            if (log &&!(*eps>0)) {
                log=0;
                printf(MSG_PRECISION_ERROR);
                printf(MSG_REPEAT_INPUT);
                req_rslt=GetReqResult();
            }
        } while (!log&&req_rslt);
    return log;
}
double SumFunc(double (*f)(double x),
                    double beg,
                    double end,
                    double step
                  ){
  double reslt;
    reslt=(*f)(beg);
    while (beg+step<end){
        beg+=step;
        reslt+=(*f)(beg);

    }
    return reslt;
}
double GetIntegral(double (*f)(double x),
                    double beg,
                    double end,
                    double eps
                        ){
  double beg0,reslt,reslt0,h;
    h=(end-beg)/FIRST_STEPS_COUNT;beg0=beg;
    reslt=h*SumFunc(f,beg,end,h);//инициализация
    do {
        reslt0=reslt; beg0=beg+h/2;
        /*начинаем со второго прямоугольника - площадь первого (удвоенную) уже
        вычислили на предыдущей итерации, шаг пока не изменяем - чтобы не
        обрабатывать прямоугольники с нечётными номерами*/
        reslt=SumFunc(f,beg0,end,h);
        reslt=(reslt0+reslt*h)/2; //так как удвоенная площадь "нечетных"
        							// прямоугольников вычислена ранее,
                                    // делим её пополам: шаг пока ещё удвоенный -
                                    // делим его пополам и считаем площадь "четных"
                                    // прямоугольников; суммируем - получаем площадь
                                    // фигуры
        h=h/2;
        putchar('.');
    } while ((fabs(reslt-reslt0)>eps)||(h>H_MIN));
    printf("OK!\n");
    return reslt;
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

int CheckData(const double d,
              const double e,
              const double a, //a,b - границы отрезка поиска корня;
                const double b,
                const double  eps  //eps - точность вычислений;
                ){
    printf(MSG_REQUEST_VERIFY,a,b,eps,d,e);
    return GetReqResult();
}

