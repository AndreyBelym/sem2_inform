#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#define MAX_SCREEN_ELEM 15
#define MAX_SIZE 5L
/*
Функция SumDiag рассчитывает сумму диагональных элементов квадоатной матрицы array
размером size. Возвращает искомую сумму.
Параметры:
array - массив для суммирования диагональных элементов;
size - размер массива.
Локальный переменные:
s - сумма диагональных элементов. 
i - переменная-счнтчик.
*/
double SumDiag(double **array,long size);

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
Функция GetReqResult позволяет получить ответ "да" или "нет" от пользователя.
Возвращает 1 в случае согласия пользователя, 0 - в случае несогласия.
Параметры:
отсутствуют.
Локальные переменные:
answer - текущий ответ пользователя.
*/
int GetReqResult();

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
int GetOutFile(FILE * * f);

/*
Основная часть программы подсчета суммы элементов на диагоналях матрицы.
Переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
req_rslt - флаг ответа пользователя (1 - согласие пользователя);
array - массив для подсчета суммы элементов на диагоналях;
summa - сумма элементов на диагоналях;
size - размер массива.
*/
int main();

/*
Функция CheckData() позволяет пользователю проверить введенный массив array размером size x size.
Параметры:
array - массив для проверки;
size - размер массива.
Локальные переменные:
отсутствуют.
*/
int CheckData(double **array,long size);

/*
Функция InputFile() позволет пользователю считать массив array размером size x size из файла.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
size - размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
f - файл для ввода;
ch - текущий считанный символ;
i,j - переменные-счетчики.
*/
int InputFile(double ***array,long *size);

/*
Функция InputConsole() позволет пользователю считать массив array размером size x size с клавиатуры.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
size - размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
elem_name - имя элемента;
msg - сообщение об элементе;
i,j - переменные-счетчики.
*/
int InputConsole(double ***array,long *size);

/*
Функция InputRandom() позволет пользователю заполнить массив array размером size x size случайными числами.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
size - размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
min, max - границы генерации случайных чисел;
i,j - переменные-счетчики.
*/
int InputRandom(double ***array,long *size);

/*
Функция InputData позволяет запросить у пользователя размер size квадратной матрицы array,
и заполнить array различными способами.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
size - размер массива;
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки).
*/
int InputData(double ***array,long *size);

/*
Функция PrintResult выводит массив array размером size x size
и cумму элементов его диагоналей summa в файл и на экран.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для вывода;
size - размер массива;
summa - сумма элементов на диагоналях.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
f - файл для вывода.
*/
int PrintResult(double **array,long size,double summa);

/*
Функция AllocArray() выделяет динамическую память под массив array
размером size x size.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для выделения памяти;
size - размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
i - переменная-счетчик;
*/
int AllocArray(double ***array,long size);
/*
Функция-процедура FreeArray() освобождает выделенную ранее память под массив array
размером size x size.
Параметры:
array - массив для освобождения памяти;
size - размер массива.
Локальные переменные:
i - переменная-счетчик;
*/
void FreeArray(double ***array,long size);

/*
Процедура PrintMatrix() печатает массив array размером size x size в файл f.
Параметры:
f - файл для вывода;
array - массив для вывода;
size - размер массива.
Локальные переменные:
i,j - переменные-счетчики.
*/
void PrintMatrix(FILE *f,double **array,long size);

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

double SumDiag(double **array,long size){
  long i; double s=0;
    for (i=0;i<size;i++){
        s+=array[i][i]+array[i][size-1-i];
    }
    if (size%2) s-=array[size/2][size/2];
    return s;
}

int clearline(FILE *f){
  int count=0;char ch;
	while (!feof(f)&&((ch=getc(f))!='\n'))
        if(ch!=' '&&ch!='\t')
            count++;
	return count;
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

int GetReqResult(void);

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
            printf("Неправильное имя файла! \n");
            printf("Хотите повторить ввод? (Y/N)\n");
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
            printf( "Хотите повторить ввод? (Y/N)\n");
            req_rslt=GetReqResult();
        };
    } while (req_rslt&&error);
    return !error;
  };
int main(){
  int log,req_rslt;
  double **array,summa; long size;
    printf("Программа находит сумму элементов диагоналей\n"\
                     "матрицы размера mxm.\n");

    do {
        log=InputData(&array,&size);
        if (log){
            log=CheckData(array,size);
            if (!log){
                FreeArray(&array,size);
                printf( "Введенные данные некорректны или ввод отменён!\n");
                printf( "Хотите повторить ввод? (Y/N)\n");
                req_rslt=GetReqResult();
        }

        }
    } while (!log&&req_rslt);
    if (log){
        summa=SumDiag(array,size);
        log=PrintResult(array,size,summa);
        FreeArray(&array,size);
    } ;
    if (log) printf("Работа успешно выполнена!\n");else printf("Работа программы прервана!\n");
    printf("Нажмите <Enter>...\n");
    clearline(stdin);
    return 0;
}
int PrintResult(double **array,long size,double summa){
  int log=1; FILE *f;
    printf("Сумма элементов на диагоналях матрицы равна %lf.\n",summa);
    printf("1 - вывод матрицы на экран (затем возможен вывод матрицы и суммы в файл);\n"\
							"2 - вывод матрицы и суммы в файл без вывода на экран.\n");
    switch(GetOption('1','2')){
        case '1':
            if(size>MAX_SCREEN_ELEM){
                printf( "Массив %ldx%ld слишком большой для вывода на экран!\n",size,size);
                log=0;
            } else
                PrintMatrix(stdout,array,size);
            printf("Хотите вывести матрицу в файл? Y/N\n");
            if (GetReqResult()){
                if ((log=GetOutFile(&f))){
                    PrintMatrix(f,array,size);fclose(f);
                    fprintf(f,"Сумма элементов на диагоналях матрицы равна %lf.\n",summa);
                }
        }
        break;
        case '2':
            if ((log=GetOutFile(&f))){
                PrintMatrix(f,array,size);
                fprintf(f,"Сумма элементов на диагоналях матрицы равна %lf.\n",summa);
            }
        break;
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

int AllocArray(double ***array,long size){
  int log; long i;
    *array=NULL;
    *array=(double**)malloc(size*sizeof(double*));
    log=*array!=NULL;
    if(log) {
        for (i=0;i<=size-1;i++)
            (*array)[i]=NULL;
        for (i=0;(i<=size-1)&&log;i++){
            (*array)[i]=(double*)malloc(size*sizeof(double));
            log=**array!=NULL;
        }
    }
    if (!log)
        FreeArray(array,size);
    return log;
}

void FreeArray(double ***array,long size){
  long i;
    if (*array!=NULL){
        for (i=0;(i<=size-1)&&(*array)[i]!=NULL;i++){
            free((*array)[i]);
            (*array)[i]=NULL;
        };
        free(*array);
        *array=NULL;
    };
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
int InputConsole(double ***array,long *size){
  int log=1;
  long i,j; char msg[255],name[50];
    sprintf(msg,"Введите  m - размер матрицы. 1<=m<=%ld.\n",MAX_SIZE);
    log=InputIndex(msg,"m",size,MAX_SIZE);
    if (log) {
        log=AllocArray(array,*size);
        if (log){
            for (i=0;(i<=*size-1)&&log;i++)
                for (j=0;(j<=*size-1)&&log;j++){
                    sprintf(msg,"Введите элемент А[%ld,%ld].\n",i,j);
                    sprintf(name,"A[%ld,%ld]: ",i,j);
                    log=Input(msg,name,(*array)[i]+j);
                }
        if (!log) FreeArray(array,*size);
        } else
             printf("Ошибка выделения памяти!\n");
    };
    return log;
}

int InputFile(double ***array,long *size){
  int log; FILE *f; long i,j; char ch;
    log=/*1;f=stdin;*/GetInFile(&f);
    if (log){
        //log=InputFileLong(f,size)&&(size>0);
        log=fscanf(f,"%ld",size)&&!clearline(f);
        if (!log){
            printf("Размер массива не указан в файле!\n");

        } else {
            log=AllocArray(array,*size);
            if (log){
                for (i=0;(i<=*size-1)&&log;i++){
                    for (j=0;(j<=*size-2)&&log;j++){
                        //log=InputFile(f,(*array)[i]+j);
                        while((ch=getc(f))==' '||ch=='\t');
                        if (ch!='\n')
                            ungetc(ch,f);
                        else
                            log=0;
                        if (log){
                            log=fscanf(f,"%lf",(*array)[i]+j);
                        }
                    }
                    if (log){
                        while((ch=getc(f))==' '||ch=='\t');
                        if (ch!='\n')
                            ungetc(ch,f);
                        else
                            log=0;
                        if (log)
                            log=fscanf(f,"%lf",(*array)[i]+j)&&!clearline(f);j++;
                    }
                };
                if (!log){
                    //i--;j--;
                    printf("Ошибка при чтении из файла элемента %ld,%ld.\n",i,j);

                }
                if (f!=stdin)
                    fclose(f);
                if (!log) FreeArray(array,*size);
            } else
                 printf("Ошибка выделения памяти!\n");
        }
    } else printf("Неправильное имя файла! \n");

    return log;
}
int InputRandom(double ***array,long *size){
  int log=1; double min,max; long i,j; char msg[150];
    sprintf(msg,"Введите  m - размер матрицы. 1<=m<=%ld.\n",MAX_SIZE);
    log=InputIndex(msg,"m",size,MAX_SIZE);
    if (log){
        log=AllocArray(array,*size);
    if (log)
        log=Input("Введите min - минимальное из случайных чисел.\n","min",&min);
    if (log)
        log=InputWithLBound("Введите max - максимальное из случайных чисел.\n","max",&max,min);


        if (log){
            for (i=0;i<=*size-1;i++)
                for (j=0;j<=*size-1;j++)
                    (*array)[i][j]=(double)((double)rand()/RAND_MAX *(max-min) + min);

        } else printf("Ошибка выделения памяти!\n");
    }
    return log;
}
int InputData(double ***array,long *size){
  int log=1;
    printf("Заполните матрицу:\n"\
							"1 - заполнить случайными числами;\n"\
							"2 - ввести из файла;\n"\
							"3 - ввести с клавиатуры;\n"\
							"0 - завершить программу.\n");
    switch(GetOption('0','3')){
        case '1':
            log=InputRandom(array,size);
        break;
        case '2':
            log=InputFile(array,size);
        break;
        case '3':
            log=InputConsole(array,size);
        break;
        default:
            printf("Ввод отменён!\n");
            log=0;
    }
    return log;
}
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
            printf( "Введено неправильное значение!\n");
            printf("Хотите повторить ввод? (Y/N)\n");
            req_rslt=GetReqResult();
        }
    } while (!log&&req_rslt); //пока пользователь не отказался или число некорректное
    return log;

}


int CheckData(double **array,long size){
    printf("Будет выполнен расчет суммы элементов диагоналях матрицы %ldx%ld :\n",size,size);
    if (size<=MAX_SCREEN_ELEM){
        PrintMatrix(stdout,array,size);
        printf("Продолжить?(Y/N)\n");
    } else {
        printf("Массив %ldx%ld слишком большой для вывода на экран!\n",size,size);
        printf("Вы уверены в правильности введенных данных?(Y/N)\n");
    }

    return GetReqResult();
}
