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
        printf("���ࠢ���� �⢥�! �����⨬�:\n"\
					  "Y - ��; N - ���.\n");
        answer=getchar();
        clearline(stdin);
    }

    return toupper(answer);
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
/***** ������� ����� ������������� ��������� *****/
int GetParam(const char paramName[], //paramName - ��� ����訢������ ��ࠬ���;
              const char paramCond[], //paramCond - �������⥫쭠� ���ଠ�� � ��ࠬ���;
              double *param
                    ){
  int log; char ch;
    do {
        printf("������ %s - ����⢥���� �᫮. %s\n",paramName,paramCond);
        printf("%s: ",paramName);
        log=scanf("%lf",param);
        log=!clearline(stdin)&&log;
        if (!log){  //������� �� ����⢥���� �᫮?
            printf("������� ���ࠢ��쭮� ���祭��!\n");
            printf("���� ������� ����? Y/N\n" );
            ch=GetReqResult();
        }
    } while (!log&&toupper(ch)=='Y'); //���� ���짮��⥫� �� �⪠����� ��� �᫮ �����४⭮�
    return log;
}

/***** ������� ����� ������ *****/
int InputData(double *a, //a,b - �࠭��� ��१�� ���᪠ ����;
                double *b,
                double  *eps  //eps - �筮��� ���᫥���;
                    ){
  char ch='1'; int log=1; //���樠������ ⠪ � ⮫쪮 ⠪! �. ����, ��祬�
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
            printf("�訡��! b<=a!\n");
            printf("������� ����?\n");
            printf("1 - ����� � � b;\n");
            printf("2 - ����� ⮫쪮 �;\n");
            printf("3 - ����� ⮫쪮 b;\n");
            printf("0 - �⬥��.\n");
            ch=GetOption('0','3');
        }
    }while (!log&&(toupper(ch)!='0'));
    if (log)
        do{
            log=GetParam("eps","eps>0.",eps);
            if (log&&!(*eps>0)){
                log=0;
                printf("�訡��! eps<=0!\n");
                printf("������� ����?(Y/N)\n");
                ch=GetReqResult();
            }
        }while (!log&&(toupper(ch)=='Y'));
    return log;
}

/***** ������� �������� ������ *****/
int CheckData(const double a, //a,b - �࠭��� ��१�� ���᪠ ����;
                const double b,
                const double  eps  //eps - �筮��� ���᫥���;
                ){
    printf("�㤥� �믮���� ���� ����\n"\
                        "�� ���ࢠ�� �� %1.4lf �� %1.4lf � �筮���� %1.8lf\n"\
                        "�த������?(Y/N)\n",a,b,eps);
    return GetReqResult()=='Y';

}


/***** ������� ������� ����� *****/
double Root(double (*f)(double x), //f - ��������㥬�� �㭪��;
                const double a, //a,b - �࠭��� ��१�� ���᪠ ����;
                const double b,
                const double  eps  //eps - �筮��� ���᫥���;
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
/***** ������� ��������� ����� *****/
double GetRoot( double (*f)(double x), //f - ��������㥬�� �㭪��;
                  const double a, //a,b - �࠭��� ��१�� ���᪠ ����;
                  const double b,
                  const double  eps,  //eps - �筮��� ���᫥���;
                  double *f_root  //f_root - �������� ��७�
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


/***** �������� ��������� *****/

int main(){
    //a,b - �࠭��� ��१�� ���᪠ ����;
    //eps - �筮��� ���᫥���;
    //log - ��६����� ���ﭨ�;
    //code - ��� �訡�� ���᪠ ����}

  double a,b,eps,f_root;
  int log; int code;

    printf("�ணࠬ�� ��室�� ��७� �㭪樨 %s �� ��१�� [a,b] � �筮���� eps.\n",FUNC_NAME);
    log=InputData(&a,&b,&eps);
    if (log)
        log=CheckData(a,b,eps);
    if (log) {
        code=GetRoot(&f,a,b,eps,&f_root);
        switch (code){
            case 0:
                printf("��७� �� �஬���⪥ [%1.4lf,%1.4lf] ࠢ�� %1.8lf.\n",a,b,f_root);
            break;
            case 1:
                printf("������ �࠭�� ���ࢠ�� ���᪠ ���� (b) ����� ������ (a)!\n");
            break;
            case 2:
                printf("��筮��� ���᫥��� (eps) �����/ࠢ�� 0!\n");
            break;
            case 3:
                printf("���� �� �஬���⪥ [%1.4lf,%1.4lf] �� �������.\n",a,b);
            break;
        }
    }
    else
        printf("����� �ணࠬ�� ��ࢠ��!\n");
    printf("������ <Enter>...\n");
    clearline(stdin);
    return 0;
}
