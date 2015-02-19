#include <stdio.h>
#include <ctype.h>
const int highcode=255;
const char
	Alphabet[]="qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
            "������������������������������������������������������������������";

int GetFiles(FILE **fin,FILE **fout){
  int GetInputFile(FILE **f){
    char fileName [255];
    char ch='Y';int error;
      do{
          printf("������� ��� ����� ��� �������\n");
          printf("����: ");scanf("%255s",fileName);
          *f=fopen(fileName,"r");
          error=*f==NULL;
          if (error) {
              printf("������������ ��� �����! ��������� ����? <Y>/<N>\n");
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
          printf("������� ��� �����-����������.\n");
          printf("����: ");scanf("%255s",fileName);
          *f=fopen(fileName,"w");
          error=*f==NULL;
          if (error) {
              printf("������������ ��� �����! ��������� ����? <Y>/<N>\n");
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
		fprintf(f,"�������� ����� ���������� �����\n'%c' � ���������� %ld ��.\n",Chars[0],HighestFq);
	} else {
		fprintf(f,"�������� ����� ���������� �����\n");
		for (i=0;i<=Count-1;i++){
			fprintf(f,"%u.'%c'. ",i+1,Chars[i]);
		};
	    fprintf(f,"\n\r� ���������� %ld ��.\n",HighestFq);
    };
};

int main(){
  FILE *fin,*fout;
  int log; //{TRUE/FALSE}
  int MostFqCount; long HighestFq,CharsFq[255];
  char MostFqChars[255];
    printf("��������� ������� ����� ����� ������������� ����� � ������ ��������� �������:\n");
	printf("��������� ��������� ������� �� ���������� �����-���������;\n");
	printf("������� ����������� ��������� ������, ����� ������� ����� ������ �����;\n");
	printf("������� ��������� �� ����� � � ��������� ����.\n");
	log = GetFiles(&fin,&fout);
	if (log){
		printf("����������� ������������ ��������� ������...");
		GetCharsFreq(fin,CharsFq);
		fclose(fin); printf("���������!\n");
		printf("����������� ����� ����� ������ �����...\n");
		GetMostFreq(CharsFq,&HighestFq,&MostFqCount,MostFqChars);
		if (MostFqCount!=0){
            PrintResult(stdout,HighestFq,MostFqCount,MostFqChars);
            PrintResult(fout,HighestFq,MostFqCount,MostFqChars);
        } else {
            printf("� ������ ��� ����.\n");
            fprintf(fout,"� ������ ��� ����.\n");
        }

        fclose(fout);
    }else{
        printf("����� �� ���� �������. ��������� ���������.\n");
	}
    printf("������� <Enter>...\n");
    getchar();
    return 0;
}
