#include <stdio.h> //для fopen/fclose,scanf/fscanf,printf/fprintf
#include <ctype.h> //для toupper()
#include <limits.h> //для UCHAR_MAX
///////////////////////////////////////////////////////////////////////////////
const char
    //алфавит букв
    ALPHABET[]="qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
        "ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";
///////////////////////////////////////////////////////////////////////////////
/*-----ФУНКЦИЯ ПОЛУЧЕНИЯ ФАЙЛОВ-----*/
/*Параметры:
fin - файл для анализа,
fout - файл для вывода.*/
int GetFiles(FILE **fin,FILE **fout);

/*-----ФУНКЦИЯ ПОСИМВОЛЬНОГО ЧАСТОТНОГО АНАЛИЗА-----*/
/*Параметры:
f - файл для анализа,
CharsFreq  массив частот символов.*/
void GetCharsFreq(FILE *f, long CharsFreq[]);

/*-----ФУНКЦИЯ ПОЛУЧЕНИЯ САМЫХ ЧАСТЫХ БУКВ-----*/
/*Параметры:
CharsFreq - массив частот символов, HighestFreq - наивысшая частота букв,
ChCount - количество букв, MostFreqChars - самые частые буквы*/
void GetMostFreq(const long CharsFreq[],long *HighestFreq, int *ChCount, char MostFreqChars[]);

/*-----ФУНКЦИЯ ВЫВОДА САМЫХ ЧАСТЫХ БУКВ НА ЭКРАН-----*/
/*Параметры:
f - файл для вывода, HighestFq - наивысшая частота букв,
Count - количество букв, Chars - буквы для вывода*/
void PrintResult(FILE *f,const long HighestFq,const int Count,const char Chars[]);

///////////////////////////////////////////////////////////////////////////////
int main(){
  FILE *fin,*fout; //входной/выходной файл
  int log; //флаг ошибки
  int MostFqCount; long HighestFq,CharsFq[255];
  //количество самых частых, наивысшая частота, массив частот
  char MostFqChars[255];
  //самые частые буквы
    printf("Программа находит самые часто встречающиеся буквы в заданном тексте;\n");
    printf("и выводит результат на экран и в указанный текстовый файл.\n");
    log = GetFiles(&fin,&fout); //получить файлы
    if (log){
        printf("Выполняется посимвольный частотный анализ...");
        GetCharsFreq(fin,CharsFq);//провести частотный анализ
        fclose(fin); printf("Выполнено!\n");
        printf("Выполняется поиск самой частой буквы...\n");
        //найти самые частые буквы
        GetMostFreq(CharsFq,&HighestFq,&MostFqCount,MostFqChars);
        //что-нибудь найдено?
        if (MostFqCount!=0){
        PrintResult(stdout,HighestFq,MostFqCount,MostFqChars);
        PrintResult(fout,HighestFq,MostFqCount,MostFqChars);
    } else {
        printf("В тексте нет букв.\n");
        fprintf(fout,"В тексте нет букв.\n");
    }

    fclose(fout);
    }else{
    printf("Файлы не были открыты. Программа завершена.\n");
    }
    printf("Нажмите <Enter>...\n");
    (void)getchar();
    return 0;
}
///////////////////////////////////////////////////////////////////////////////
int GetFiles(FILE **fin,FILE **fout){
///////////////////////////////////////
  /*-----ФУНКЦИЯ ПОЛУЧЕНИЯ ФАЙЛА ИСТОЧНИКА------*/
  int GetInputFile(FILE **f);
  /*-----ФУНКЦИЯ ПОЛУЧЕНИЯ ВЫХОДНОГО ФАЙЛА-----*/
  int GetOutputFile(FILE **f);
///////////////////////////////////////
  int log;
    log=GetInputFile(fin);
    if (log){
    log=GetOutputFile(fout);
    };
    return log;
};
///////////////////////////////////////
  int GetInputFile(FILE **f){
  char ch='Y';int error;
  char fileName[255];
    do{
        printf("Введите имя файла для анализа\n");
        //считать строку (gets() deprecated!)
        printf("Файл: ");scanf("%255[^\n]",fileName);
        while (!feof(stdin)&&(getc(stdin)!='\n'));
        *f=fopen(fileName,"r");
        error=*f==NULL;
        if (error) {
            printf("Неправильное имя файла! Повторить ввод? <Y>/<N>\n");
            ch=getchar();
            if (ch!='\n')    //Очистка буфера
              while (!feof(stdin)&&(getc(stdin)!='\n'));
        };
    } while (toupper(ch)!='N'&&error);
    return !error;
  };
///////////////////////////////////////
  int GetOutputFile(FILE * * f){
  char fileName [255];
  char ch='Y'; int error;
    do{
        printf("Введите имя файла-результата.\n");
        //считать строку (gets() deprecated!)
        printf("Файл: ");scanf("%255[^\n]",fileName);
        *f=fopen(fileName,"w");
        while (!feof(stdin)&&(getc(stdin)!='\n'));
        error=*f==NULL;
        if (error) {
            printf("Неправильное имя файла! Повторить ввод? <Y>/<N>\n");
            ch=getchar();
            if (ch!='\n')    //Очистка буфера
              while (!feof(stdin)&&(getc(stdin)!='\n'));
        };
    } while (toupper(ch)!='N'&&error);
    return !error;
  };
///////////////////////////////////////////////////////////////////////////////
void GetCharsFreq(FILE *f, long CharsFreq[]){
  int i;
    for (i=0;i<=UCHAR_MAX;i++){
    CharsFreq[i]=0;
    };
    while ((i=getc(f))!=EOF){
    i=(unsigned char)i;
    CharsFreq[i]++;
    };
};
///////////////////////////////////////////////////////////////////////////////
void GetMostFreq(const long CharsFreq[],long *HighestFreq, int *ChCount, char MostFreqChars[]){
  int k,i; unsigned char lettercode;
    k=0; *HighestFreq=0;
    //просмотрим буквы алфавита
    for (i=0;ALPHABET[i];i++){
        lettercode=(unsigned char)ALPHABET[i];
        //такая буква встречается в тексте?
        if (CharsFreq[lettercode]>0) {
            //самая-самая частая буква
            if (CharsFreq[lettercode]>*HighestFreq) {
                *HighestFreq=CharsFreq[lettercode];
                k=0;  //забыть все уже не самые частые буквы
                MostFreqChars[k]=ALPHABET[i]; k++;
            } else
                //такая же частая?
                if (CharsFreq[lettercode]==*HighestFreq) {
                   MostFreqChars[k]=ALPHABET[i]; k++; //добавим к самым частым
                };
        };
    };
    *ChCount=k;
};
///////////////////////////////////////////////////////////////////////////////
void PrintResult(FILE *f,const long HighestFq,const int Count,
                           const char Chars[]){
  int i;
    if (Count==1){
        fprintf(f,"Наиболее часто встречается буква\n'%c' в количестве %ld шт.\n",Chars[0],HighestFq);
    } else {
        fprintf(f,"Наиболее часто встречаются буквы\n");
        for (i=0;i<=Count-1;i++){
            fprintf(f,"%u.'%c'. ",i+1,Chars[i]);
        };
        fprintf(f,"\n\rв количестве %ld шт.\n",HighestFq);
    };
};
