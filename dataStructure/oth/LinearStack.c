#include "myhead.h"

#define MAXSIZ 20
#define ElemType int 

typedef struct{
	ElemType data[MAXSIZ];
	int top;
}stack;

void Init(stack *s){
	s->top = 0;
	return;
}

_Bool Empty(stack *s){
	return s->top==0?1:0;
}

_Bool Push(stack *s,const ElemType* val){
	if(s->top==MAXSIZ)return 0;
	s->data[s->top++] = *val;
	return 1;
}

_Bool Pop(stack *s){
	if(s->top==0)return 0;
	--s->top;
	return 1;
}
int Top(stack *s,ElemType *e){
	if(s->top==0)return -1;
	*e = s->data[s->top-1];
	return 0;
}

int Size(stack *s){
	return s->top;
}

#ifndef TEST

int main(){
	stack s;
	Init(&s);
	int a=6;
	for(int i=0;i<a;++i){
		Push(&s,&i);
	}
	int tmp;
	for(int i=0;i<a;++i){
		Top(&s,&tmp);
		printf("%d ",tmp);
		Pop(&s);
	}
	printf("\n");
	return 0;
}
#endif

