#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define MAX_N 5L
#define MAX_M 5L
/***************************/
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
Функция GetOption позволяет выбрать пользователю один из нескольких(до 10) вариантов,
представленных цифрами от a до b. Возвращает символ, соответствующий выбранной цифре.
Параметры:
a,b - границы предлагаемых вариантов.
Локальные переменные:
ch - текущий ответ пользователя;
ok - флаг отсутствия ошибки (1 - нет ошибки).
*/
char GetOption(char a,char b);


/*
Функция fexists() проверяет существование файла с именем fname.
Возвращает 1, если такой файл существует, или 0, если нет.
Параметры:
fname - имя файла для проверки.
Локальные переменные:
f - временный файл для проверки.
*/
int fexists(char  *fname);


/*
Функция GetInFile() получает файл f для чтения.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
f - запрашиваемый файл.
Локальные переменные:
error - флаг ошибки (1 - ошибка);
req_rslt - флаг ответа пользователя (1 - согласие пользователя).
*/
int GetInFile(FILE **f);


/*
Функция GetOutFile() получает файл f для записи.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
f - запрашиваемый файл.
Локальные переменные:
error - флаг ошибки (1 - ошибка);
req_rslt - флаг ответа пользователя (1 - согласие пользователя).
*/
int GetOutFile(FILE **f);


/*
Функция PrintResult выводит массив array размером m x n в файл и на экран.
Параметры:
array - массив для вывода;
n,m - размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
f - файл для вывода.
*/
int PrintResult(double array[][MAX_M],long n,long m);


/*
Процедура PrintMatrix() печатает массив array размером n x m в файл f.
Параметры:
f - файл для вывода;
array - массив для вывода;
n,m - размер массива.
Локальные переменные:
i,j - переменные-счетчики.
*/
void PrintMatrix(FILE *f,double array[][MAX_M],long n,long m);


/*
Основная часть программы умножения столбца матрицы на число.
Переменные:
n,m - размер массива;
array - обрабатываемый массив;
Jmulti - номер столбца для умножения;
K - число для умножения.
i - переменная-счетчик.
*/
int main();


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
int Input(const char message[],
              const char name[],
              double *param
                    );


/*
Функция InputIndex() получает от пользователя индекс массива -
некоторое длинное целое число index из промежутка от 0 до верхней границы h_bound.
При этом она в процессе запроса выводит поясняющее сообщение message,
и приглашение ко вводу в виде имени параметра - name.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
message - сообщение о параметре;
name - имя параметра;
index - запрашиваемый индекс;
h_bound - верхняя граница индекса.
Локальные переменные:
ok - флаг отсутствия ошибки (1 - нет ошибки);
req_rslt - флаг ответа пользователя (1 - согласие пользователя).
*/
int InputIndex(const char message[],const char name[],long *index,long h_bound);


/*
Функция InputConsole() позволет пользователю считать массив array размером size с клавиатуры.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
n,m - размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
elem_name - имя элемента;
msg - сообщение об элементе;
i,j - переменные-счетчики.
*/
int InputConsole(double array[][MAX_M],long *n,long *m);


/*
Функция InputFile() позволет пользователю считать массив array размером size из файла.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
n,m - размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
f - файл для ввода;
ch - текущий считанный символ;
i,j - переменные-счетчики.
*/
int InputFile(double array[][MAX_M],long *n,long *m);


/*
Функция InputRandom() позволет пользователю заполнить массив array случайными числами.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
n,m - размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
req_rslt - флаг ответа пользователя (1 - согласие пользователя);
min, max - границы генерации случайных чисел;
i,j - переменные-счетчики.
*/
int InputRandom(double array[][MAX_M],long *n,long *m);


/*
Функция InputData позволяет запросить у пользователя размеры n и m массива array,
номер столбца Jmulti и число K для умножения,
и заполнить array различными способами.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
n,m - размер массива;
Jmulti - номер столбца для умножения;
K - число для умножения.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки).
*/
int InputData(double array[][MAX_M],long *n,long *m,long *Jmulti,double *K);


/*
Функция InputParams запрашивает у пользователя некоторые из параметров расчета:
размеры n и m массива array,
номер столбца Jmulti и число K для умножения.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
n,m - размер массива;
Jmulti - номер столбца для умножения;
K - число для умножения.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
msg - сообщение об параметре.
*/
int InputParams(long *n,long *m,long *Jmulti,double *K);
/***************************/

int clearline(FILE *f){
  int count=0;char ch;
	while (!feof(f)&&((ch=getc(f))!='\n'))
        if(ch!=' '&&ch!='\t')
            count++;
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

    return toupper(answer)=='Y';
}
char GetOption(char a,char b){
  char ch; int ok;
    do{
        printf("Введите цифру от %c до %c.\n",a,b);
		ch=getchar();
		ok=(a<=ch)&&(ch<=b);
		ok=!clearline(stdin)&&ok;
		if (!ok)
            printf("Неправильный ответ!\n");
    }while (!ok);
	return ch;
}
int fexists(char  *fname){
  FILE *f;
    f=fopen(fname,"r");
    if (f!=NULL)
        fclose(f);
    return f!=NULL;
}
int GetInFile(FILE **f){
  int error,req_rslt;
  char fileName[255]="\0";
    do{
        req_rslt=0;
        printf("Введите имя файла-источника.\n");
        //считать строку (gets() deprecated!)
        printf("%s: ","Файл");scanf("%255[^\n]",fileName);
        clearline(stdin);
        *f=fopen(fileName,"r");
        error=*f==NULL;
        if (error) {
            printf( "Неправильное имя файла! \n");
            printf("Хотите повторить ввод? (Y/N)\n");
            req_rslt=GetReqResult();
        };
    } while (req_rslt&&error);
    return !error;
  };
int GetOutFile(FILE * * f){
  char fileName [255]="\0";
  int error=0,req_rslt;
    do{
        req_rslt=0;
        printf("Введите имя файла-результата.\n");
        //считать строку (gets() deprecated!)
        printf("%s: ","Файл");scanf("%255[^\n]",fileName);
        clearline(stdin);
        if (fexists(fileName)){
            error=1;
            printf("ВНИМАНИЕ! Указанное имя файла занято!\n");
            printf("ПЕРЕЗАПИСАТЬ ФАЙЛ? (Y/N)\n");
            error=!GetReqResult();
        }
        if (!error){
            *f=fopen(fileName,"w");
            error=*f==NULL;
        }
        if (error) {
            printf("Неправильное имя файла! \n");
            printf("Хотите повторить ввод? (Y/N)\n");
            req_rslt=GetReqResult();
        };
    } while (req_rslt&&error);
    return !error;
  };
int Input(const char message[], //paramName - имя запрашиваемого параметра;
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
            printf("Введено не число!\n"
                   "Повторить ввод? Y/N\n");
            req_rslt=GetReqResult();
        }
    } while (!log&&req_rslt); //пока пользователь не отказался или число некорректное
    return log;

}

int InputIndex(const char message[],const char name[],long *index,long h_bound){
  int log,req_rslt;
    do{
        req_rslt=0;
        printf("%s",message);
        printf("%s: ",name);
        log=scanf("%ld",index);
        log=!clearline(stdin)&&log;
        if (!log){  //введено не вещественное число?
            printf("Введено не число!\n"
                   "Повторить ввод? Y/N\n");
            req_rslt=GetReqResult();
        }
        if (log&&(*index<1||*index>h_bound)){
            log=0;
            printf("Ошибка! %s не принадлежит [1..%ld]!\n"
                   "Повторить ввод(Y/N)?\n",name,h_bound);
            req_rslt=GetReqResult();
        }
    } while(!log&&req_rslt);
    return log;
}
int InputParams(long *n,long *m,long *Jmulti,
                double *K){
  int log; char msg[100];
    sprintf(msg,"Введите n - количество строк массива. 1<=n<=%ld.\n",MAX_N);
    log=InputIndex(msg,"n",n,MAX_N);
    if (log){
        sprintf(msg,"Введите m - количество столбцов массива. 1<=m<=%ld.\n",MAX_M);
        log=InputIndex(msg,"m",m,MAX_M);
    }

    if (log){
        sprintf(msg,"Введите J - номер столбца для умножения. 1<=J<=%ld.\n",*m);
        log=InputIndex(msg,"J",Jmulti,*m);
    }

    if (log)
        log=Input("Введите K - вещественное число.\n","K",K);
    return log;
}
int InputConsole(double array[][MAX_M],long *n,long *m){
  int log=1; char elem_name[20]; long i,j;

    for(i=0;log&&i<*n;i++)
        for(j=0;j<*m&&log;j++){
            sprintf(elem_name,"A[%ld][%ld]",i+1,j+1);
            log=Input("",elem_name,array[i]+j);

        }
    return log;
}
int InputFile(double array[][MAX_M],long *n,long *m){
  int log=1; FILE *f; long i,j; char ch;
    log=GetInFile(&f);
    if (log){
            for (i=0;(i<=*n-1)&&log;i++){
                for (j=0;(j<=*m-1)&&log;j++){
                    while((ch=getc(f))==' '||ch=='\t');
                    if (ch!='\n')
                        ungetc(ch,f);
                    else
                        log=0;
                    if (log){
                        log=fscanf(f,"%lf",array[i]+j);
                    }
                }
                if (log){
                    log=!clearline(f);
                }
            };
            if (!log){
                //i--;j--;
                printf("Ошибка при чтении из файла элемента %ld,%ld.\n",i,j);

            }
            if (f!=stdin)
                fclose(f);
    } else printf("Неправильное имя файла! \n");

    return log;
}
int InputRandom(double array[][MAX_M],long *n,long *m){
  int log=1,req_rslt=0; double min,max; long i,j;
    srand (time(NULL));

    log=Input("Введите min - минимальное из случайных чисел.\n","min",&min);
    if (log)
        do{
            req_rslt=0;
            log=Input("Введите max - минимальное из случайных чисел.\n","max",&max);
            if (log&&max<min){
               log=0;
                printf("Верхняя граница (max) меньше нижней (min)!\n");
                printf( "Хотите повторить ввод? (Y/N)\n");
                req_rslt=GetReqResult();
            }
        } while (!log&&req_rslt);
    if (log){
        for (i=0;i<=*n-1;i++)
            for (j=0;j<=*m-1;j++)
                array[i][j]=(double)((double)rand()/RAND_MAX *(max-min) + min);

    }
    return log;
}
void PrintMatrix(FILE *f,double array[][MAX_M],long n,long m){
  int i,j;
    for (i=0;i<n;i++){
        for(j=0;j<m;j++){
            fprintf(f,"%10.4lf",array[i][j]);
        }
        fprintf(f,"\n");
    }
}
int main(){
  long n,m,Jmulti;
  long i;
  double array[MAX_N][MAX_M];
  double K;
  printf("Программа умножает J-ый столбец массива nxm,\n"
           "на число K.\n");
  int log,req_rslt;
    do{
        log=InputData(array,&n,&m,&Jmulti,&K);
        if (log){
            printf("%ld-й столбец массива:\n",Jmulti);
            PrintMatrix(stdout,array,n,m);
            printf("будет умножен на %lf. OK(Y/N)?\n",K);
            log=GetReqResult();
        }
        if(!log){
            printf("Ввод не завершен или отменен!\nПовторить(Y/N)?\n");
            req_rslt=GetReqResult();
        }
    }while(!log&&req_rslt);
        if (log){
        Jmulti--;
        for (i=0;i<n;i++){
            array[i][Jmulti]*=K;
        }
        PrintResult(array,n,m);
    } else printf("Программа прервана...\n");
    printf("Нажмите <ENTER>...");
    clearline(stdin);
    return 0;
}
int PrintResult(double array[][MAX_M],long n,long m){
  int log=1; FILE *f;
    printf("Работа выполнена!\n");
    printf("1 - вывод матрицы на экран (затем возможен вывод в файл);\n"\
							"2 - вывод матрицы в файл без вывода на экран.\n");
    switch(GetOption('1','2')){
        case '1':
            PrintMatrix(stdout,array,n,m);
            printf("Хотите вывести матрицу в файл? Y/N\n");
            if (GetReqResult()){
                if ((log=GetOutFile(&f))){
                    PrintMatrix(f,array,n,m);fclose(f);
                }
        }
        break;
        case '2':
            if ((log=GetOutFile(&f)))
                PrintMatrix(f,array,n,m);
        break;
    }
    return log;
}
int InputData(double array[][MAX_M],long *n,long *m,long *Jmulti,
                double *K){
  int log=1;
    log=InputParams(n,m,Jmulti,K);
    if (log){
        printf("Заполните матрицу:\n"\
							"1 - заполнить случайными числами;\n"\
							"2 - ввести из файла;\n"\
							"3 - ввести с клавиатуры;\n"\
							"0 - завершить программу.\n");
        switch(GetOption('0','3')){
            case '1':
                log=InputRandom(array,n,m);
            break;
            case '2':
                log=InputFile(array,n,m);
            break;
            case '3':
                log=InputConsole(array,n,m);
            break;
            default:
                printf( "Ввод отменён!\n");
                log=0;
        }
    }

    return log;
}
