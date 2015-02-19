#include <stdio.h>
#include <ctype.h>
const int highcode=255;
const char
	Alphabet[]="qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
            "ёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";

int GetFiles(FILE **fin,FILE **fout){
  int GetInputFile(FILE **f){
    char fileName [255];
    char ch='Y';int error;
      do{
          printf("Введите имя файла для анализа\n");
          printf("Файл: ");scanf("%255s",fileName);
          *f=fopen(fileName,"r");
          error=*f==NULL;
          if (error) {
              printf("Неправильное имя файла! Повторить ввод? <Y>/<N>\n");
              ch=getchar();
              while (getchar()!='\n');
          };
      } while (toupper(ch)!='N'&&error);
      return !error;
  };

  int GetOutputFile(FILE **f){
    char fileName [255];
    char ch='Y'; int error;
      do{
          printf("Введите имя файла-результата.\n");
          printf("Файл: ");scanf("%255s",fileName);
          *f=fopen(fileName,"w");
          error=*f==NULL;
          if (error) {
              printf("Неправильное имя файла! Повторить ввод? <Y>/<N>\n");
              ch=getchar();
              while (getchar()!='\n');
          };
      } while (toupper(ch)!='N'&&error);
      return !error;
  };

  int log;
    log=GetInputFile(fin);
    if (log){
        log=GetOutputFile(fout);
	};
    return log;
};

void GetCharsFreq(FILE *f, long CharsFreq[]){
  int i;
	for (i=0;i<=highcode;i++){
        CharsFreq[i]=0;
	};
    while ((i=getc(f))!=EOF){
        CharsFreq[i]++;
    };
};

void GetMostFreq(const long CharsFreq[],long *HighestFreq, int *ChCount, char MostFreqChars[]){
  int k,i; unsigned char lettercode;
    k=0; *HighestFreq=0;
	for (i=0;Alphabet[i];i++){
	    lettercode=(unsigned char)Alphabet[i];
        if (CharsFreq[lettercode]>0) {

            if (CharsFreq[lettercode]>*HighestFreq) {
                *HighestFreq=CharsFreq[lettercode];
                k=0;
                MostFreqChars[k]=Alphabet[i]; k++;
			} else
                if (CharsFreq[lettercode]==*HighestFreq) {
                   MostFreqChars[k]=Alphabet[i]; k++;
                };
        };
	};
	*ChCount=k;
};

void PrintResult(FILE *f,const long HighestFq,const int Count,
                           const char Chars[]){
  int i;
    if (Count==1){
		fprintf(f,"Наиболее часто всречается буква\n'%c' в количестве %ld шт.\n",Chars[0],HighestFq);
	} else {
		fprintf(f,"Наиболее часто всречаются буквы\n");
		for (i=0;i<=Count-1;i++){
			fprintf(f,"%u.'%c'. ",i+1,Chars[i]);
		};
	    fprintf(f,"\n\rв количестве %ld шт.\n",HighestFq);
    };
};

int main(){
  FILE *fin,*fout;
  int log; //{TRUE/FALSE}
  int MostFqCount; long HighestFq,CharsFq[255];
  char MostFqChars[255];
    printf("Программа находит самую часто встречающююся букву в тексте следующим образом:\n");
	printf("Программа считывает символы из текстового файла-источника;\n");
	printf("проводя посимольный частотный анализ, далее находит самую частую букву;\n");
	printf("выводит результат на экран и в текстовый файл.\n");
	log = GetFiles(&fin,&fout);
	if (log){
		printf("Выполняется посимвольный частотный анализ...");
		GetCharsFreq(fin,CharsFq);
		fclose(fin); printf("Выполнено!\n");
		printf("Выполняется поиск самой частой буквы...\n");
		GetMostFreq(CharsFq,&HighestFq,&MostFqCount,MostFqChars);
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
    getchar();
    return 0;
}
