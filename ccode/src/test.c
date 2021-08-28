#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void test(){
	void *a = malloc(sizeof(int)*3);
	int *d = malloc(sizeof(int)*4);
	printf("size of a is %ld\n",sizeof(a));
	int b=1,c=2;
	memcpy(a,&b,sizeof(b));
	memcpy(a+sizeof(int),&c,sizeof(c));
	printf("a ptr is %p\n",a);
	printf("a ptr is %p\n",a+1);
	printf("a ptr is %p\n",a+2);
	printf("b ptr is %p\n",d);
	printf("b ptr is %p\n",d+1);
	int b1=10;
	int c2=20;
	memcpy(&b1,a,sizeof(b1));
	memcpy(&c2,a+sizeof(int),4);
	printf("In a, %d , %d\n",b1,c2);
	
}
int main(){
	test();
	return 0;
}
