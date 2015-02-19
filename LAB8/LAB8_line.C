#include <stdio.h>
#include <math.h>
int main(void){
  float x1,x2,y1,y2,vecx,vecy,fi;
    printf("Программа вычисляет угол наклона вектора, \nзаданного координатами начала и конца, к оси ОХ.\n");
    printf("Введите координаты начала\nx1,y1:");
    scanf("%f,%f",&x1,&y1);
    printf("Введите координаты конца\nx2,y2:");
    scanf("%f,%f",&x2,&y2);
    vecx=x2-x1;
    vecy=y2-y1;
    fi=acos(vecx/sqrt(vecx*vecx+vecy*vecy))*180/M_PI;
    printf("Угол наклона вектора к ОХ равен %.4f\n",fi);
    printf("Нажмите <Enter>.\n");
    (void)getchar();
    return 0;
}
