#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define MAX_N 5L

/**************************************/
/*
Функция Compare сравнивает 2 числа a и b.
Если a<b, возвращается -1; если равны - возвращается 0;
    если больше - 1.
Параметры:
a,b - числа для сравнения.
Локальные переменные:
отсутствуют.
*/
int Compare(double a,double b);


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
Процедура PrintVector() печатает массив array размером size файл f.
Параметры:
f - файл для вывода;
array - массив для вывода;
size - размер массива.
Локальные переменные:
i - переменная-счетчик.
*/
void PrintVector(FILE *f,double array[],long size);


/*
Основная часть программы поиска количества элементов массива,
различных относительно заданного числа (больше,меньше или равно).
Переменные:
size - размер массива;
array - обрабатываемый массив;
K - число для сравнения элементов массива;
und,eq,ov - кол-во элементов меньших, равных и больших K;
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
size -  размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
elem_name - имя элемента;
msg - сообщение об элементе;
i - переменная-счетчик.
*/
int InputConsole(double array[],long size);


/*
Функция InputFile() позволет пользователю считать массив array размером size из файла.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
size -  размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
f - файл для ввода;
ch - текущий считанный символ;
i - переменная-счетчик.
*/
int InputFile(double array[],long size);


/*
Функция InputRandom() позволет пользователю заполнить массив array случайными числами.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
size -  размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
req_rslt - флаг ответа пользователя (1 - согласие пользователя);
min, max - границы генерации случайных чисел;
i - переменная-счетчик.
*/
int InputRandom(double array[],long size);


/*
Функция InputData позволяет запросить у пользователя размер size массива array,
а также число K, отсносительного которого будут сравниваться элементы array,
и заполнить array различными способами.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
size -  размер массива;
K - число для сравнения элементов массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
msg - сообщение об параметре.
*/
int InputData(double array[],long *size,double *K);

/**************************************/
int Compare(double a,double b){
    if (a<b)
        return -1;
    else if (a==b)
        return 0;
    else
        return 1;
}
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
            printf("Неправильное имя файла! \n");
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
void PrintVector(FILE *f,double array[],long size){
  int i;
    for (i=0;i<size;i++){

        fprintf(f,"%10.4lf",array[i]);
    }
    fprintf(f,"\n");

}
int main(){
  long size;
  double array[MAX_N];
  double K;
  long eq,ov,und,i;
  int log,req_rslt;
    und=ov=eq=0;
    printf("Программа находит количество элементов массива размером m,\n"
           "больших, равных и меньших K.\n");
    do{
        req_rslt=0;
        log=InputData(array,&size,&K);
        if (log){
            printf("Числа:\n");
            PrintVector(stdout,array,size);
            printf("будут сравниваться относительно %lf. OK (Y/N)?:\n",K);
            log=GetReqResult();
        }
        if(!log){
            printf("Ввод не завершен или отменен!\nПовторить(Y/N)?\n");
            req_rslt=GetReqResult();
        }
    }while(!log&&req_rslt);

    if (log){
        for (i=0;i<size;i++){
            switch(Compare(array[i],K)){
                case -1: und++;
                break;
                case 0: eq++;
                break;
                case 1: ov++;
                break;
            }
        }
        printf("Количестов элементов массива,\n"
               "меньших %lf: %ld;\n"
               "равных %lf: %ld;\n"
               "больших %lf: %ld;\n",
                        K,und,
                        K,eq,
                        K,ov);
    } else printf("Программа прервана...");
    printf("Нажмите <ENTER>...");
    clearline(stdin);
    return 0;
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
int InputConsole(double array[],long size){
  int log=1; char elem_name[20]; char msg[50]; long i;

    for(i=0;log&&i<size;i++){
        sprintf(elem_name,"A[%ld]",i+1);
        sprintf(msg,"Введите %s - вещественное число.\n",elem_name);
        log=Input(msg,elem_name,array+i);

        }
    return log;
}
int InputFile(double array[],long size){
  int log=1; FILE *f; long i; char ch;
    log=GetInFile(&f);
    if (log){
            for (i=0;(i<size)&&log;i++){
                while((ch=getc(f))==' '||ch=='\t');
                if (ch!='\n')
                    ungetc(ch,f);
                else
                    log=0;
                if (log){
                    log=fscanf(f,"%lf",array+i);
                }
            }
            if (log)
                log=!clearline(f)&&log;
            if (!log){
                //i--;j--;
                printf("Ошибка при чтении из файла элемента [%ld].\n",i);

            }
            if (f!=stdin)
                fclose(f);
    } else printf("Неправильное имя файла! \n");

    return log;
}
int InputRandom(double array[],long size){
  int log=1,req_rslt=0; double min,max; long i;
    srand (time(NULL));

    log=Input("Введите min - минимальное из случайных чисел.\n","min",&min);
    if (log)
        do{
            req_rslt=0;
            log=Input("Введите max - минимальное из случайных чисел.\n","max",&max);
            if (log&&max<min){
               log=0;
                printf("Верхняя граница (max) меньше нижней (min)!\n");
                printf("Хотите повторить ввод? (Y/N)\n");
                req_rslt=GetReqResult();
            }
        } while (!log&&req_rslt);
    if (log){
        for (i=0;i<size;i++)
                array[i]=(double)((double)rand()/RAND_MAX *(max-min) + min);

    }
    return log;
}

int InputData(double array[],long *size,double *K){
  int log=1; char msg[50];
    sprintf(msg,"Введите m - размер массива. 1<=m<=%ld.\n",MAX_N);
    log=InputIndex(msg,"m",size,MAX_N);
    if (log)
        log=Input("Введите K - вещественное число.\n","K",K);
    if (log){
        printf("Заполните массив:\n"\
							"1 - заполнить случайными числами;\n"\
							"2 - ввести из файла;\n"\
							"3 - ввести с клавиатуры;\n"\
							"0 - завершить программу.\n");
        switch(GetOption('0','3')){
            case '1':
                log=InputRandom(array,*size);
            break;
            case '2':
                log=InputFile(array,*size);
            break;
            case '3':
                log=InputConsole(array,*size);
            break;
            default:
                printf("Ввод отменён!\n");
                log=0;
        }
    }

    return log;
}
