#include <stdio.h>
#include <math.h>
int main(void){
  float x1,x2,x3,
        y1,y2,y3,
        a,b,c,
        p,p2,s;
  int log;
    printf("Программа находит площадь и периметр треугольника,\nзаданного координатами вершин,если такой треугольник существует.\n");
    printf("Введите координаты первой вершины треугольника\nx1,y1:");
    log=scanf("%f,%f",&x1,&y1)==2;
    while (!feof(stdin)&&(getc(stdin)!='\n'));
    if (log){
        printf("Введите координаты второй вершины треугольника\nx2,y2:");
        log=scanf("%f,%f",&x2,&y2)==2;
        while (!feof(stdin)&&(getc(stdin)!='\n'));
    }
    if (log){
        printf("Введите координаты третьей вершины треугольника\nx3,y3:");
        log=scanf("%f,%f",&x3,&y3)==2;
        while (!feof(stdin)&&(getc(stdin)!='\n'));
    }
    if (log){
        a=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
        b=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
        c=sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
        if (  (a+b>c)&&
              (a+c>b)&&
              (c+b>a)) {
            p=a+b+c;p2=p/2;
            s=sqrt(p2*(p2-a)*(p2-b)*(p2-c));
            printf("Периметр треугольника равен %.4f;\nПлощадь треугольника равна %.4f.\n",p,s);
            }
        else {
            printf("Треугольник не существует.\n");
        }
    } else
        printf("Работа программы прервана.");
    printf("Нажмите <Enter>...");
    (void)getchar();
    return 0;
}
