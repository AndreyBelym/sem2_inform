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
        printf("Введите цифру от %c до %c.\n",a,b);
		ch=getchar();
		ok=(a<=ch)&&(ch<=b)&&!clearline(stdin);
		if (!ok)
            printf("Неправильный ответ!\n");
    }while (!ok);
	return ch;
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
            printf("Ошибка! Повторить ввод?(Y/N)\n");
            req_rslt=GetReqResult();
        }
    } while(!log&&req_rslt);
    return log;
}
int GetGroup(long *paramVar){
  int log,req_rslt;
    do{
        req_rslt=0;
        printf("Введите номер группы.\n");
        printf("Номер группы: ");
        log=scanf("%ld",paramVar);
        log=!clearline(stdin)&&log;
        if (!log){  //введено не вещественное число?
            printf("Введено не число!\n"
                   "Повторить ввод? Y/N\n");
            req_rslt=GetReqResult();
        }
        if (log&&*paramVar<1){
            log=0;
            printf("Номер группы<=0! Повторить ввод?(Y/N)\n");
            req_rslt=GetReqResult();
        }
    } while(!log&&req_rslt);
    return log;
}
int GetCount(long *paramVar){
  int log,req_rslt;
    do{
        req_rslt=0;
        printf("Введите n - общее количество студентов.(1<=n<=%ld)\n",MAX_N);
        printf("Студентов: ");
        log=scanf("%ld",paramVar);
        log=!clearline(stdin)&&log;
        if (!log){  //введено не вещественное число?
            printf("Введено не число!\n"
                   "Повторить ввод? Y/N\n");
            req_rslt=GetReqResult();
        }
        if (log&&(*paramVar<1||*paramVar>MAX_N)){
            log=0;
            printf("Количество студентов неправильно! Повторить ввод?(Y/N)\n");
            req_rslt=GetReqResult();
        }
    } while(!log&&req_rslt);
    return log;
}
int GetStudent(student *stud){
  int log;
    log=GetString("Введите фамилию студента.\n","Фамилия",stud->LstName,20);
    if (log)
        log=GetString("Введите имя студента.\n","Имя",stud->FstName,20);
    if (log)
        log=GetString("Введите отчество студента.\n","Отчество",stud->SurName,20);
    if (log)
        log=GetString("Введите название университета.\n","Университет",stud->University,50);
    if (log)
        log=GetGroup(&(stud->GroupNum));
    return log;
}

int InputData(long *studCount,student *students){
  long i; int log;
    log=GetCount(studCount);
    for (i=0;log&&i<*studCount;i++){
        printf("****************************\n");
        printf("Ввод данных о студенте №%ld\n",i+1);
        printf("****************************\n");
        log=GetStudent(students+i);
    }
    return log;
}

int CheckData(long studCount,student stud[]){
  long i; char answer;
    printf("1 - проверить данные о каждом студенте по порядку;\n");
    printf("2 - завершить работу;\n");
    printf("0 - продолжить работу.\n");
    answer=GetOption('0','2');
    if (answer=='1')
        for (i=0;i<studCount&&answer!='2';i++){
            printf("****************************");
            printf("Карточка студента №%ld",i*1);
            printf("****************************");
            printf("***Университет: %s Группа: %ld\n",stud[i].University,stud[i].GroupNum);
            printf("%s %s %s\n",stud[i].LstName, stud[i].FstName, stud[i].SurName);
            printf("Правильно?\n"
                   "0 - Да;\n"
                   "1 - Нет, изменить данные;\n"
                   "2 - Нет, завершить программу.\n");
            answer=GetOption('0','2');
            if (answer=='1'){
                printf("****************************");
                printf("Ввод данных о студенте №%ld",i+1);
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
    printf("Найденные одногрупники:");
    printf("\n***Университет: %s Группа: %ld\n",stud[i].University,stud[i].GroupNum);
    printf("%s %s %s\n",stud[i].LstName, stud[i].FstName, stud[i].SurName);
    for (i=1;i<studCount;i++){
        if ((stud[i].GroupNum!=stud[i-1].GroupNum)
           ||strcmp(stud[i].University,stud[i-1].University))
              printf("\n***Университет: %s Группа: %ld\n",stud[i].University,stud[i].GroupNum);
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
    printf("Программа находит одногрупников среди данных студентов.\n");
    log=InputData(&(AllStudents.Count),AllStudents.Stud);
    if (log)
        log=CheckData(AllStudents.Count,AllStudents.Stud);
    if (log){
        FindStudents(AllStudents.Count,AllStudents.Stud,&(FoundedStudents.Count),FoundedStudents.Stud);
        if (FoundedStudents.Count)
            PrintData(FoundedStudents.Count,FoundedStudents.Stud);
        else
            printf("Одногрупников не найдено...");
    } else
        printf("Программа завершена пользователем...");

    printf("Нажмите <Enter>...");
    clearline(stdin);
    return 0;
}
