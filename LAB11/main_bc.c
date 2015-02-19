#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_N 10L
typedef struct{
    char FstName[20],LstName[20],SurName[20],University[50];
    long GroupNum;
} student;
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
        printf("������ ���� �� %c �� %c.\n",a,b);
		ch=getchar();
		ok=(a<=ch)&&(ch<=b)&&!clearline(stdin);
		if (!ok)
            printf("���ࠢ���� �⢥�!\n");
    }while (!ok);
	return ch;
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
int GetString(const char message[],const char name[],char paramVar[],long size){
  int log,req_rslt; char format[15];
    sprintf(format,"%%%ld[^\n]",size);
    do{
        req_rslt=0;
        printf("%s",message);
        printf("%s: ",name);
        log=scanf(format,paramVar);
        log=!clearline(stdin)&&log;
        if (!log||!strcmp(paramVar,"")){
            log=0;
            printf("�訡��! ������� ����?(Y/N)\n");
            req_rslt=GetReqResult();
        }
    } while(!log&&req_rslt);
    return log;
}
int GetGroup(long *paramVar){
  int log,req_rslt;
    do{
        req_rslt=0;
        printf("������ ����� ��㯯�.\n");
        printf("����� ��㯯�: ");
        log=scanf("%ld",paramVar);
        log=!clearline(stdin)&&log;
        if (!log){  //������� �� ����⢥���� �᫮?
            printf("������� �� �᫮!\n"
                   "������� ����? Y/N\n");
            req_rslt=GetReqResult();
        }
        if (log&&*paramVar<1){
            log=0;
            printf("����� ��㯯�<=0! ������� ����?(Y/N)\n");
            req_rslt=GetReqResult();
        }
    } while(!log&&req_rslt);
    return log;
}
int GetCount(long *paramVar){
  int log,req_rslt;
    do{
        req_rslt=0;
        printf("������ n - ��饥 ������⢮ ��㤥�⮢.(1<=n<=%ld)\n",MAX_N);
        printf("��㤥�⮢: ");
        log=scanf("%ld",paramVar);
        log=!clearline(stdin)&&log;
        if (!log){  //������� �� ����⢥���� �᫮?
            printf("������� �� �᫮!\n"
                   "������� ����? Y/N\n");
            req_rslt=GetReqResult();
        }
        if (log&&(*paramVar<1||*paramVar>MAX_N)){
            log=0;
            printf("������⢮ ��㤥�⮢ ���ࠢ��쭮! ������� ����?(Y/N)\n");
            req_rslt=GetReqResult();
        }
    } while(!log&&req_rslt);
    return log;
}
int GetStudent(student *stud){
  int log;
    log=GetString("������ 䠬���� ��㤥��.\n","�������",stud->LstName,20);
    if (log)
        log=GetString("������ ��� ��㤥��.\n","���",stud->FstName,20);
    if (log)
        log=GetString("������ ����⢮ ��㤥��.\n","����⢮",stud->SurName,20);
    if (log)
        log=GetString("������ �������� 㭨������.\n","���������",stud->University,50);
    if (log)
        log=GetGroup(&(stud->GroupNum));
    return log;
}

int InputData(long *studCount,student *students){
  long i; int log;
    log=GetCount(studCount);
    for (i=0;log&&i<*studCount;i++){
        printf("****************************\n");
        printf("���� ������ � ��㤥�� �%ld\n",i+1);
        printf("****************************\n");
        log=GetStudent(students+i);
    }
    return log;
}

int CheckData(long studCount,student stud[]){
  long i; char answer;
    printf("1 - �஢���� ����� � ������ ��㤥�� �� ���浪�;\n");
    printf("2 - �������� ࠡ���;\n");
    printf("0 - �த������ ࠡ���.\n");
    answer=GetOption('0','2');
    if (answer=='1')
        for (i=0;i<studCount&&answer!='2';i++){
            printf("****************************");
            printf("����窠 ��㤥�� �%ld",i*1);
            printf("****************************");
            printf("***���������: %s ��㯯�: %ld\n",stud[i].University,stud[i].GroupNum);
            printf("%s %s %s\n",stud[i].LstName, stud[i].FstName, stud[i].SurName);
            printf("�ࠢ��쭮?\n"
                   "0 - ��;\n"
                   "1 - ���, �������� �����;\n"
                   "2 - ���, �������� �ணࠬ��.\n");
            answer=GetOption('0','2');
            if (answer=='1'){
                printf("****************************");
                printf("���� ������ � ��㤥�� �%ld",i+1);
                printf("****************************");
                GetStudent(&stud[i]);
            }
        }

    return answer!='2';
}
void FindStudents(long inStudCount,
                    student inStud[],
                    long *outStudCount,
                    student outStud[]){
  long k=0,i,j; int founded;int outed[MAX_N];
    for (i=0;i<MAX_N;i++)
        outed[i]=0;
    founded=0;

    for (i=0;i<inStudCount-1;i++){
        if (!outed[i]){
            for (j=i+1;j<inStudCount;j++)
                if (!outed[j]
                   &&(inStud[i].GroupNum==inStud[j].GroupNum)
                   &&!strcmp(inStud[i].University,inStud[j].University)){
                    founded=1;
                    outStud[k++]=inStud[j];
                    outed[j]=1;
                }
            if (founded) {
                outStud[k++]=inStud[i];
                founded=0;
            }

        }
    }


    *outStudCount=k;
}

void PrintData(long studCount,student stud[]){
  long i=0;
    printf("�������� ������㯭���:");
    printf("\n***���������: %s ��㯯�: %ld\n",stud[i].University,stud[i].GroupNum);
    printf("%s %s %s\n",stud[i].LstName, stud[i].FstName, stud[i].SurName);
    for (i=1;i<studCount;i++){
        if ((stud[i].GroupNum!=stud[i-1].GroupNum)
           ||strcmp(stud[i].University,stud[i-1].University))
              printf("\n***���������: %s ��㯯�: %ld\n",stud[i].University,stud[i].GroupNum);
        printf("%s %s %s\n",stud[i].LstName, stud[i].FstName, stud[i].SurName);
    }


}

typedef struct{
    long Count;
    student Stud[MAX_N];
} students;

int main(){
  students AllStudents, FoundedStudents;
  int log;
    printf("�ணࠬ�� ��室�� ������㯭���� �।� ������ ��㤥�⮢.\n");
    log=InputData(&(AllStudents.Count),AllStudents.Stud);
    if (log)
        log=CheckData(AllStudents.Count,AllStudents.Stud);
    if (log){
        FindStudents(AllStudents.Count,AllStudents.Stud,&(FoundedStudents.Count),FoundedStudents.Stud);
        if (FoundedStudents.Count)
            PrintData(FoundedStudents.Count,FoundedStudents.Stud);
        else
            printf("������㯭���� �� �������...");
    } else
        printf("�ணࠬ�� �����襭� ���짮��⥫��...");

    printf("������ <Enter>...");
    clearline(stdin);
    return 0;
}
