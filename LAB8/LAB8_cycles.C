#include <stdio.h>
#include <ctype.h>
int main(void){
  long n0,n,i;
  float m;
  char ch='Y'; int log;
    printf("Данная программа позволяет найти такие числа Фибоначчи(и их номера),\n"
           "которые удовлетворяют условию ф(i)<m<ф(i+1), где m - заданное число.\n");
    do{
        printf("Введите m\nm:"); log=scanf("%f",&m)==1;
        while (!feof(stdin)&&(getc(stdin)!='\n'));
        if (!log){
            printf("Ошибка! Повторить ввод?Y\\N\n");
            ch=getchar();
            while (!feof(stdin)&&(getc(stdin)!='\n'));
        }

    } while ((toupper(ch)!='N')&&!log);
    if (log){
        if (m>=1){
            n0=1;n=1;i=2;
            while (m>n){
                n0=(n+=n0)-n0;
                i++;
            }
            printf("Номера чисел: %ld и %ld\n"
                "ф(%ld) = %ld, ф(%ld) = %ld.\n",
                i-1,i,i-1,n0,i,n);
        } else
            printf("Число не лежит между числами Фибоначчи.\n");
    } else
        printf("Работа программы прервана.\n");
    printf("Нажмите <Enter>.\n");
    (void)getchar();
    return 0;
}
