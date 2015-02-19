#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#define FIRST_STEPS_COUNT 16
#define H_MIN 0.1
#define EPS_MIN 0.00001
double d,e;
double f(double x){
    if (x<=d)
        return sqrt(3)*(x-d)/3-d;
    else if (x<=e)
        return -x;
    else
        return (x-e)*sqrt(3)-e;
}

/**********************/
/*
Функция clearline очищает строку в файле f. Возвращает количество
непробельных символов в считанной строке.
Параметры:
f - Файл для очистки строки.
Локальные переменные:
count - количество непробельных символов;
ch - текущий считанный символ.
*/
int clearline(FILE *f);

/*
Функция GetReqResult позволяет получить ответ "да" или "нет" от пользователя.
Возвращает 1 в случае согласия пользователя, 0 - в случае несогласия.
Параметры:
отсутствуют.
Локальные переменные:
answer - текущий ответ пользователя.
*/
int GetReqResult();

/*
Функция Input() получает от пользователя некоторое вещественное число param.
При этом она в процессе запроса выводит поясняющее сообщение message,
и приглашение ко вводу в виде имени параметра - name.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
message - сообщение о параметре;
name - имя параметра;
param - запрашиваемый параметр.
Локальные переменные:
ok - флаг отсутствия ошибки (1 - нет ошибки);
req_rslt - флаг ответа пользователя (1 - согласие пользователя).
*/
int Input(const char message[], //paramName - имя запрашиваемого параметра;
              const char name[], //paramCond - дополнительная информация о параметре;
              double *param
                    );

/*
Функция InputWithLBound() получает от пользователя некоторое вещественное число param,
минимальное значение которого ограничено значением l_bound.
При этом она в процессе запроса выводит поясняющее сообщение message,
и приглашение ко вводу в виде имени параметра - name.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
message - сообщение о параметре;
name - имя параметра;
param - запрашиваемый параметр;
h_bound - верхняя граница параметра.
Локальные переменные:
ok - флаг отсутствия ошибки (1 - нет ошибки);
req_rslt - флаг ответа пользователя (1 - согласие пользователя).
*/
int InputWithLBound(const char message[],const char name[],double *param,double l_bound);

/*
Функция InputWithHBound() получает от пользователя некоторое вещественное число param,
максимальное значение которого ограничено значением h_bound.
При этом она в процессе запроса выводит поясняющее сообщение message,
и приглашение ко вводу в виде имени параметра - name.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
message - сообщение о параметре;
name - имя параметра;
param - запрашиваемый параметр;
h_bound - верхняя граница параметра.
Локальные переменные:
ok - флаг отсутствия ошибки (1 - нет ошибки);
req_rslt - флаг ответа пользователя (1 - согласие пользователя).
*/
int InputWithHBound(const char message[],const char name[],double *param,double h_bound);

/*
Основная часть программы расчета определённого интеграла.
Переменные:
a,b - границы интервала интегрирования,
eps - точность вычислений,
result - вычисленное значение интеграла;
log - флаг отсутствия ошибки (1 - нет ошибки),
req_rslt - флаг ответа пользователя (1 - согласие пользователя);
*/
int main();

/*
Функция InputData позволяет запросить у пользователя параметры функции d и e,
границы интеграла интегрирования a и b, и точность вычислений eps.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
d,e - параметры функции;
a,b - границы интервала интегрирования;
eps - точность вычислений.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки).
*/
int InputData(
              double *d,
              double *e,
              double *a, //a,b - границы отрезка поиска корня;
                double *b,
                double  *eps  //eps - точность вычислений;
                    );

/*
Функция CheckData() позволяет пользователю проверить введенные данные:
параметры функции d и e,границы интеграла интегрирования a и b,
и точность вычислений eps.
Возвращает 1, если пользователь подтвердил правильность данных, иначе возвращается 0.
Параметры:
d,e - параметры функции;
a,b - границы интервала интегрирования;
eps - точность вычислений.
Локальные переменные:
отсутствуют.
*/
int CheckData(
              const double d,
              const double e,
              const double a, //a,b - границы отрезка поиска корня;
                const double b,
                const double  eps  //eps - точность вычислений;
                );

/*
Функция GetIntegral рассчитывает значение определенного интеграла от beg до end,
для функции f, с точностью eps.
Возвращает значение вычисленного интеграла.
Параметры:
f - подынтегральная функция;
beg,end - границы интервала интегрирования;
eps - точность вычислений.
Локальные переменные:
beg0 - текущая левая граница интегрирования,
reslt - текущее вычисленное значение интеграла,
reslt0 - предыдущее вычисленное значение интеграла,
h - шаг интегрирования;
*/
double GetIntegral(double (*f)(double x),
                    double beg,
                    double end,
                    double eps
                        );

/*
Функция SumFunc() рассчитывает значения функции f,
для каждого x из диапазона от beg до end с шагом step,
и возвращает сумму вычисленных значений.
Параметры:
f - анализируемая функция;
beg,end - границы изменения аргумента функции f;
step -  шаг изменения аргумента функции f.
Локальные переменные:
reslt - сумма вычисленных значений функции f.
*/
double SumFunc(double (*f)(double x),
                    double beg,
                    double end,
                    double step
                  );
/**********************/




int clearline(FILE *f){
  int count=0;
	while (!feof(f)&&(getc(f)!='\n')) count++;
	return count;
}

int main(){
  double a,b,eps,result;
  int log,req_rslt;
    printf("Программа выполняет расчет определенного интеграла\n"\
                    "на интервале от a до b с точностью eps для f(x)...\n"\
                    "       / (√3/3)*(x+d)/3+d , x<=d, d<0 (1);\n"\
                    "f(x) =||  -x, d<x<=e, d<0, e>0 (2);\n"\
                    "       \\ √3*(x-e)-e , e<x, e>0 (3).\n");
    printf("\
            Y ^\n\
              |\n\
              |      @ (3)\n\
           xx |     .\n\
         * | o| c   @      X\n\
------**---x--o--x-.------->\n\
    *     d   |o | @\n\
 **           | o|.\n\
  (1)         |  xx \n\
              | (2)\n\
              |\n\
              |\n");
    printf("*** - ЛИНИЯ (1) - наклон к оси OX - 30°.\n"
           "ooo - ЛИНИЯ (2) - наклон к оси OX - -45°.\n"
           "@.@ - ЛИНИЯ (3) - наклон к оси OX - 60°.\n"
           "x - точки пересечения графиков функций (c и d);\n"
           "         задаются с клавиатуры.\n");

    do {
        log=InputData(&d,&e,&a,&b,&eps);
        if (log)
            log=CheckData(d,e,a,b,eps);
        if (!log){
            printf("Введенные данные некорректны!\n");
            printf("Хотите повторить ввод? Y/N\n");
            req_rslt=GetReqResult();
        }
    } while (!log&&req_rslt);
    if (log){
        result=GetIntegral(f,a,b,eps);
        printf("Интеграл на промежутке [%1.4lf,%1.4lf] равен %1.8lf+-%1.8lf.\n",a,b,result,eps);
    } else printf("Работа программы прервана!\n");
    printf("Нажмите <Enter>...\n");
    clearline(stdin);
    return 0;
}
int Input(const char message[], //paramName - имя запрашиваемого параметра;
              const char name[], //paramCond - дополнительная информация о параметре;
              double *param
                    ){
  int log,req_rslt;
    do {
        req_rslt=0;
        printf("%s",message);
        printf("%s: ",name);
        log=scanf("%lf",param);
        log=!clearline(stdin)&&log;
        if (!log){  //введено не вещественное число?
            printf("Введено неправильное значение!\n");
            printf("Хотите повторить ввод? Y/N\n");
            req_rslt=GetReqResult();
        }
    } while (!log&&req_rslt); //пока пользователь не отказался или число некорректное
    return log;
}
int InputWithLBound(const char message[],const char name[],double *param,double l_bound){
  int log,req_rslt;
    do{
        req_rslt=0;
        printf("%s",message);
        printf("%s: ",name);
        log=scanf("%lf",param);
        log=!clearline(stdin)&&log;
        if (!log){  //введено не вещественное число?
            printf("Введено не число!\n"
                   "Повторить ввод? Y/N\n");
            req_rslt=GetReqResult();
        }
        if (log&&(*param<l_bound)){
            log=0;
            printf("Ошибка! %s меньше %lf!\n"
                   "Повторить ввод(Y/N)?\n",name,l_bound);
            req_rslt=GetReqResult();
        }
    } while(!log&&req_rslt);
    return log;
}
int InputWithHBound(const char message[],const char name[],double *param,double h_bound){
  int log,req_rslt;
    do{
        req_rslt=0;
        printf("%s",message);
        printf("%s: ",name);
        log=scanf("%lf",param);
        log=!clearline(stdin)&&log;
        if (!log){  //введено не вещественное число?
            printf("Введено не число!\n"
                   "Повторить ввод? Y/N\n");
            req_rslt=GetReqResult();
        }
        if (log&&(*param>h_bound)){
            log=0;
            printf("Ошибка! %s больще %lf!\n"
                   "Повторить ввод(Y/N)?\n",name,h_bound);
            req_rslt=GetReqResult();
        }
    } while(!log&&req_rslt);
    return log;
}
int InputData(
              double *d,
              double *e,
              double *a, //a,b - границы отрезка поиска корня;
                double *b,
                double  *eps  //eps - точность вычислений;
                    ){
  int log=1; char msg[100];
    log=InputWithHBound("Введите d - точка пересечения линий (1) и (2) - вещественное число. d<0.\n","d",d,0);
    if (log)
        log=InputWithLBound("Введите е - точка пересечения линий (2) и (3) - вещественное число. e>0.\n","e",e,0);
    if (log)
        log=Input("Введите а - ниж. граница интегрирования - вещественное число.\n","a",a);
    if (log){
        sprintf(msg,"Введите b - верх. граница интегрирования -вещественное число. b>%lf.\n",*a);
        log=InputWithLBound(msg,"b",b,*a);
    }
    if (log)
        log=InputWithLBound("Введите eps - точность вычислений - вещественное число. eps>0.\n","eps",eps, EPS_MIN);
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
        printf("Неправильный ответ! Допустимо:\n"\
					  "Y - да; N - нет.\n");
        answer=getchar();
        clearline(stdin);
    }

    return toupper(answer)=='Y';
}

int CheckData(
              const double d,
              const double e,
              const double a, //a,b - границы отрезка поиска корня;
                const double b,
                const double  eps  //eps - точность вычислений;
                ){
    printf("Будет выполнен расчет определенного интеграла\n"\
                        "на интервале от %1.4lf до %1.4lf с точностью %1.8lf.\n"\
                        "Параметры функции: d=%1.4lf; e=%1.4lf.\n"\
                        "Продолжить?(Y/N)\n",a,b,eps,d,e);
    return GetReqResult();
}

