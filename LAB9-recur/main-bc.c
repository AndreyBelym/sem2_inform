#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define FUNC_NAME "sin(x)"
double f(double x){
    return sin(x);
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
        printf("Неправильный ответ! Допустимо:\n"\
					  "Y - да; N - нет.\n");
        answer=getchar();
        clearline(stdin);
    }

    return toupper(answer);
}
char GetOption(char a,char b){
  char ch; int ok;
    do{
        printf("Введите цифру от %c до %c.\n",a,b);
		ch=getchar();
		ok=(a<=ch)&&(ch<=b)&&!clearline(stdin);
		if (!ok)
            printf("Неправильный ответ!\n");
    }while (!ok);
	return ch;
}
/***** ФУНКЦИЯ ВВОДА ВЕЩЕСТВЕННОГО ПАРАМЕТРА *****/
int GetParam(const char paramName[], //paramName - имя запрашиваемого параметра;
              const char paramCond[], //paramCond - дополнительная информация о параметре;
              double *param
                    ){
  int log; char ch;
    do {
        printf("Введите %s - вещественное число. %s\n",paramName,paramCond);
        printf("%s: ",paramName);
        log=scanf("%lf",param);
        log=!clearline(stdin)&&log;
        if (!log){  //введено не вещественное число?
            printf("Введено неправильное значение!\n");
            printf("Хотите повторить ввод? Y/N\n" );
            ch=GetReqResult();
        }
    } while (!log&&toupper(ch)=='Y'); //пока пользователь не отказался или число некорректное
    return log;
}

/***** ФУНКЦИЯ ВВОДА ДАННЫХ *****/
int InputData(double *a, //a,b - границы отрезка поиска корня;
                double *b,
                double  *eps  //eps - точность вычислений;
                    ){
  char ch='1'; int log=1; //инициализация так и только так! см. ниже, почему
    do{
         switch(toupper(ch)){
            case '2':log=GetParam("a","",a);
            break;
            case '3':log=GetParam("b","b>a.",b);
            break;
            default:
                log=GetParam("a","",a);
                if (log)
                    log=GetParam("b","b>a.",b);
            break;
        }
        if (log&&!(*b>*a)){
            log=0;
            printf("Ошибка! b<=a!\n");
            printf("Повторить ввод?\n");
            printf("1 - ввести а и b;\n");
            printf("2 - ввести только а;\n");
            printf("3 - ввести только b;\n");
            printf("0 - отмена.\n");
            ch=GetOption('0','3');
        }
    }while (!log&&(toupper(ch)!='0'));
    if (log)
        do{
            log=GetParam("eps","eps>0.",eps);
            if (log&&!(*eps>0)){
                log=0;
                printf("Ошибка! eps<=0!\n");
                printf("Повторить ввод?(Y/N)\n");
                ch=GetReqResult();
            }
        }while (!log&&(toupper(ch)=='Y'));
    return log;
}

/***** ФУНКЦИЯ ПРОВЕРКИ ДАННЫХ *****/
int CheckData(const double a, //a,b - границы отрезка поиска корня;
                const double b,
                const double  eps  //eps - точность вычислений;
                ){
    printf("Будет выполнен поиск корня\n"\
                        "на интервале от %1.4lf до %1.4lf с точностью %1.8lf\n"\
                        "Продолжить?(Y/N)\n",a,b,eps);
    return GetReqResult()=='Y';

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

    printf("Программа находит корень функции %s на отрезке [a,b] с точностью eps.\n",FUNC_NAME);
    log=InputData(&a,&b,&eps);
    if (log)
        log=CheckData(a,b,eps);
    if (log) {
        code=GetRoot(&f,a,b,eps,&f_root);
        switch (code){
            case 0:
                printf("Корень на промежутке [%1.4lf,%1.4lf] равен %1.8lf.\n",a,b,f_root);
            break;
            case 1:
                printf("Верхняя граница интервала поиска корня (b) меньше нижней (a)!\n");
            break;
            case 2:
                printf("Точность вычислений (eps) меньше/равна 0!\n");
            break;
            case 3:
                printf("Корня на промежутке [%1.4lf,%1.4lf] не найдено.\n",a,b);
            break;
        }
    }
    else
        printf("Работа программы прервана!\n");
    printf("Нажмите <Enter>...\n");
    clearline(stdin);
    return 0;
}
