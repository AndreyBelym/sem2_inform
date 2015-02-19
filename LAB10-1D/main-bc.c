#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define MAX_N 5L

/**************************************/
/*
�㭪�� Compare �ࠢ������ 2 �᫠ a � b.
�᫨ a<b, �����頥��� -1; �᫨ ࠢ�� - �����頥��� 0;
    �᫨ ����� - 1.
��ࠬ����:
a,b - �᫠ ��� �ࠢ�����.
������� ��६����:
����������.
*/
int Compare(double a,double b);


/*
�㭪�� clearline ��頥� ��ப� � 䠩�� f. �����頥� ������⢮
���஡����� ᨬ����� � ��⠭��� ��ப�.
��ࠬ����:
f - ���� ��� ���⪨ ��ப�.
������� ��६����:
count - ������⢮ ���஡����� ᨬ�����;
ch - ⥪�騩 ��⠭�� ᨬ���.
*/
int clearline(FILE *f);


/*
�㭪�� GetReqResult �������� ������� �⢥� "��" ��� "���" �� ���짮��⥫�.
�����頥� 1 � ��砥 ᮣ���� ���짮��⥫�, 0 - � ��砥 ��ᮣ����.
��ࠬ����:
����������.
������� ��६����:
answer - ⥪�騩 �⢥� ���짮��⥫�.
*/
int GetReqResult();


/*
�㭪�� GetOption �������� ����� ���짮��⥫� ���� �� ��᪮�쪨�(�� 10) ��ਠ�⮢,
�।�⠢������ ��ࠬ� �� a �� b. �����頥� ᨬ���, ᮮ⢥�����騩 ��࠭��� ���.
��ࠬ����:
a,b - �࠭��� �।�������� ��ਠ�⮢.
������� ��६����:
ch - ⥪�騩 �⢥� ���짮��⥫�;
ok - 䫠� ������⢨� �訡�� (1 - ��� �訡��).
*/
char GetOption(char a,char b);


/*
�㭪�� fexists() �஢���� ����⢮����� 䠩�� � ������ fname.
�����頥� 1, �᫨ ⠪�� 䠩� �������, ��� 0, �᫨ ���.
��ࠬ����:
fname - ��� 䠩�� ��� �஢�ન.
������� ��६����:
f - �६���� 䠩� ��� �஢�ન.
*/
int fexists(char  *fname);


/*
�㭪�� GetInFile() ����砥� 䠩� f ��� �⥭��.
�����頥� 1, �᫨ ������ ��諠 �ᯥ譮, ���� �����頥��� 0.
��ࠬ����:
f - ����訢���� 䠩�.
������� ��६����:
error - 䫠� �訡�� (1 - �訡��);
req_rslt - 䫠� �⢥� ���짮��⥫� (1 - ᮣ��ᨥ ���짮��⥫�).
*/
int GetInFile(FILE **f);


/*
�㭪�� GetOutFile() ����砥� 䠩� f ��� �����.
�����頥� 1, �᫨ ������ ��諠 �ᯥ譮, ���� �����頥��� 0.
��ࠬ����:
f - ����訢���� 䠩�.
������� ��६����:
error - 䫠� �訡�� (1 - �訡��);
req_rslt - 䫠� �⢥� ���짮��⥫� (1 - ᮣ��ᨥ ���짮��⥫�).
*/
int GetOutFile(FILE **f);


/*
��楤�� PrintVector() ���⠥� ���ᨢ array ࠧ��஬ size 䠩� f.
��ࠬ����:
f - 䠩� ��� �뢮��;
array - ���ᨢ ��� �뢮��;
size - ࠧ��� ���ᨢ�.
������� ��६����:
i - ��६�����-���稪.
*/
void PrintVector(FILE *f,double array[],long size);


/*
�᭮���� ���� �ணࠬ�� ���᪠ ������⢠ ����⮢ ���ᨢ�,
ࠧ����� �⭮�⥫쭮 ��������� �᫠ (�����,����� ��� ࠢ��).
��६����:
size - ࠧ��� ���ᨢ�;
array - ��ࠡ��뢠��� ���ᨢ;
K - �᫮ ��� �ࠢ����� ����⮢ ���ᨢ�;
und,eq,ov - ���-�� ����⮢ ������, ࠢ��� � ������ K;
i - ��६�����-���稪.
*/
int main();


/*
�㭪�� Input() ����砥� �� ���짮��⥫� �����஥ ����⢥���� �᫮ param.
�� �⮬ ��� � ����� ����� �뢮��� ������饥 ᮮ�饭�� message,
� �ਣ��襭�� �� ����� � ���� ����� ��ࠬ��� - name.
�����頥� 1, �᫨ ������ ��諠 �ᯥ譮, ���� �����頥��� 0.
��ࠬ����:
message - ᮮ�饭�� � ��ࠬ���;
name - ��� ��ࠬ���;
param - ����訢���� ��ࠬ���.
������� ��६����:
ok - 䫠� ������⢨� �訡�� (1 - ��� �訡��);
req_rslt - 䫠� �⢥� ���짮��⥫� (1 - ᮣ��ᨥ ���짮��⥫�).
*/
int Input(const char message[],
              const char name[],
              double *param
                    );


/*
�㭪�� InputIndex() ����砥� �� ���짮��⥫� ������ ���ᨢ� -
�����஥ ������� 楫�� �᫮ index �� �஬���⪠ �� 0 �� ���孥� �࠭��� h_bound.
�� �⮬ ��� � ����� ����� �뢮��� ������饥 ᮮ�饭�� message,
� �ਣ��襭�� �� ����� � ���� ����� ��ࠬ��� - name.
�����頥� 1, �᫨ ������ ��諠 �ᯥ譮, ���� �����頥��� 0.
��ࠬ����:
message - ᮮ�饭�� � ��ࠬ���;
name - ��� ��ࠬ���;
index - ����訢���� ������;
h_bound - ������ �࠭�� ������.
������� ��६����:
ok - 䫠� ������⢨� �訡�� (1 - ��� �訡��);
req_rslt - 䫠� �⢥� ���짮��⥫� (1 - ᮣ��ᨥ ���짮��⥫�).
*/
int InputIndex(const char message[],const char name[],long *index,long h_bound);


/*
�㭪�� InputConsole() �������� ���짮��⥫� ����� ���ᨢ array ࠧ��஬ size � ����������.
�����頥� 1, �᫨ ������ ��諠 �ᯥ譮, ���� �����頥��� 0.
��ࠬ����:
array - ���ᨢ ��� �����;
size -  ࠧ��� ���ᨢ�.
������� ��६����:
log - 䫠� ������⢨� �訡�� (1 - ��� �訡��);
elem_name - ��� �����;
msg - ᮮ�饭�� �� �����;
i - ��६�����-���稪.
*/
int InputConsole(double array[],long size);


/*
�㭪�� InputFile() �������� ���짮��⥫� ����� ���ᨢ array ࠧ��஬ size �� 䠩��.
�����頥� 1, �᫨ ������ ��諠 �ᯥ譮, ���� �����頥��� 0.
��ࠬ����:
array - ���ᨢ ��� �����;
size -  ࠧ��� ���ᨢ�.
������� ��६����:
log - 䫠� ������⢨� �訡�� (1 - ��� �訡��);
f - 䠩� ��� �����;
ch - ⥪�騩 ��⠭�� ᨬ���;
i - ��६�����-���稪.
*/
int InputFile(double array[],long size);


/*
�㭪�� InputRandom() �������� ���짮��⥫� ��������� ���ᨢ array ��砩�묨 �᫠��.
�����頥� 1, �᫨ ������ ��諠 �ᯥ譮, ���� �����頥��� 0.
��ࠬ����:
array - ���ᨢ ��� �����;
size -  ࠧ��� ���ᨢ�.
������� ��६����:
log - 䫠� ������⢨� �訡�� (1 - ��� �訡��);
req_rslt - 䫠� �⢥� ���짮��⥫� (1 - ᮣ��ᨥ ���짮��⥫�);
min, max - �࠭��� �����樨 ��砩��� �ᥫ;
i - ��६�����-���稪.
*/
int InputRandom(double array[],long size);


/*
�㭪�� InputData �������� ������� � ���짮��⥫� ࠧ��� size ���ᨢ� array,
� ⠪�� �᫮ K, ��᭮�⥫쭮�� ���ண� ���� �ࠢ�������� ������ array,
� ��������� array ࠧ���묨 ᯮᮡ���.
�����頥� 1, �᫨ ������ ��諠 �ᯥ譮, ���� �����頥��� 0.
��ࠬ����:
array - ���ᨢ ��� �����;
size -  ࠧ��� ���ᨢ�;
K - �᫮ ��� �ࠢ����� ����⮢ ���ᨢ�.
������� ��६����:
log - 䫠� ������⢨� �訡�� (1 - ��� �訡��);
msg - ᮮ�饭�� �� ��ࠬ���.
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
        printf("���ࠢ���� �⢥�! �����⨬�:\n"\
					  "Y - ��; N - ���.\n");
        answer=getchar();
        clearline(stdin);
    }

    return toupper(answer)=='Y';
}
char GetOption(char a,char b){
  char ch; int ok;
    do{
        printf("������ ���� �� %c �� %c.\n",a,b);
		ch=getchar();
		ok=(a<=ch)&&(ch<=b);
		ok=!clearline(stdin)&&ok;
		if (!ok)
            printf("���ࠢ���� �⢥�!\n");
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
        printf("������ ��� 䠩��-���筨��.\n");
        //����� ��ப� (gets() deprecated!)
        printf("%s: ","����");scanf("%255[^\n]",fileName);
        clearline(stdin);
        *f=fopen(fileName,"r");
        error=*f==NULL;
        if (error) {
            printf("���ࠢ��쭮� ��� 䠩��! \n");
            printf("���� ������� ����? (Y/N)\n");
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
        printf("������ ��� 䠩��-१����.\n");
        //����� ��ப� (gets() deprecated!)
        printf("%s: ","����");scanf("%255[^\n]",fileName);
        clearline(stdin);
        if (fexists(fileName)){
            error=1;
            printf("��������! ��������� ��� 䠩�� �����!\n");
            printf("������������ ����? (Y/N)\n");
            error=!GetReqResult();
        }
        if (!error){
            *f=fopen(fileName,"w");
            error=*f==NULL;
        }
        if (error) {
            printf("���ࠢ��쭮� ��� 䠩��! \n");
            printf("���� ������� ����? (Y/N)\n");
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
    printf("�ணࠬ�� ��室�� ������⢮ ����⮢ ���ᨢ� ࠧ��஬ m,\n"
           "������, ࠢ��� � ������ K.\n");
    do{
        req_rslt=0;
        log=InputData(array,&size,&K);
        if (log){
            printf("��᫠:\n");
            PrintVector(stdout,array,size);
            printf("���� �ࠢ�������� �⭮�⥫쭮 %lf. OK (Y/N)?:\n",K);
            log=GetReqResult();
        }
        if(!log){
            printf("���� �� �����襭 ��� �⬥���!\n�������(Y/N)?\n");
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
        printf("������⮢ ����⮢ ���ᨢ�,\n"
               "������ %lf: %ld;\n"
               "ࠢ��� %lf: %ld;\n"
               "������ %lf: %ld;\n",
                        K,und,
                        K,eq,
                        K,ov);
    } else printf("�ணࠬ�� ��ࢠ��...");
    printf("������ <ENTER>...");
    clearline(stdin);
    return 0;
}
int Input(const char message[], //paramName - ��� ����訢������ ��ࠬ���;
              const char name[], //paramCond - �������⥫쭠� ���ଠ�� � ��ࠬ���;
              double *param
                    ){
  int log,req_rslt;
    do {
        printf("%s",message);
        printf("%s: ",name);
        log=scanf("%lf",param);
        log=!clearline(stdin)&&log;
        if (!log){  //������� �� ����⢥���� �᫮?
            printf("������� �� �᫮!\n"
                   "������� ����? Y/N\n");
            req_rslt=GetReqResult();
        }
    } while (!log&&req_rslt); //���� ���짮��⥫� �� �⪠����� ��� �᫮ �����४⭮�
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
        if (!log){  //������� �� ����⢥���� �᫮?
            printf("������� �� �᫮!\n"
                   "������� ����? Y/N\n");
            req_rslt=GetReqResult();
        }
        if (log&&(*index<1||*index>h_bound)){
            log=0;
            printf("�訡��! %s �� �ਭ������� [1..%ld]!\n"
                   "������� ����(Y/N)?\n",name,h_bound);
            req_rslt=GetReqResult();
        }
    } while(!log&&req_rslt);
    return log;
}
int InputConsole(double array[],long size){
  int log=1; char elem_name[20]; char msg[50]; long i;

    for(i=0;log&&i<size;i++){
        sprintf(elem_name,"A[%ld]",i+1);
        sprintf(msg,"������ %s - ����⢥���� �᫮.\n",elem_name);
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
                printf("�訡�� �� �⥭�� �� 䠩�� ����� [%ld].\n",i);

            }
            if (f!=stdin)
                fclose(f);
    } else printf("���ࠢ��쭮� ��� 䠩��! \n");

    return log;
}
int InputRandom(double array[],long size){
  int log=1,req_rslt=0; double min,max; long i;
    srand (time(NULL));

    log=Input("������ min - �������쭮� �� ��砩��� �ᥫ.\n","min",&min);
    if (log)
        do{
            req_rslt=0;
            log=Input("������ max - �������쭮� �� ��砩��� �ᥫ.\n","max",&max);
            if (log&&max<min){
               log=0;
                printf("������ �࠭�� (max) ����� ������ (min)!\n");
                printf("���� ������� ����? (Y/N)\n");
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
    sprintf(msg,"������ m - ࠧ��� ���ᨢ�. 1<=m<=%ld.\n",MAX_N);
    log=InputIndex(msg,"m",size,MAX_N);
    if (log)
        log=Input("������ K - ����⢥���� �᫮.\n","K",K);
    if (log){
        printf("�������� ������:\n"\
							"1 - ��������� ��砩�묨 �᫠��;\n"\
							"2 - ����� �� 䠩��;\n"\
							"3 - ����� � ����������;\n"\
							"0 - �������� �ணࠬ��.\n");
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
                printf("���� �⬥��!\n");
                log=0;
        }
    }

    return log;
}
