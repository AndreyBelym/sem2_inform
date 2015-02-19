#include <stdio.h>
#include <ctype.h>
void test(const int *a){
    printf("%p\n",a);
}
int main( void )
{
	int a=255;printf("%p\n",&a);
    test(&a);
    getchar();
return 0;
}
