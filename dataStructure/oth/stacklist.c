#include "myhead.h"


/* operator of stack
 * InitStack(&S);
 * StackEmpty(S);
 * Push
 * Pop
 * Top
 * DestoryStack(S)
*/
#define ElemType int
#define NEW(T) malloc(sizeof(T));

typedef struct node{
	struct node *next;
	ElemType data;
}*Node,node;

typedef struct stack{
	Node head;
	int size;
}*Stack,stack;

Stack InitStack(Stack s){
	s->head = NEW(node);
	if(s->head==NULL)return NULL;
	s->head->next = NULL;
	s->size = 0;
	return s;
}
int StackSize(Stack s){
	return s->size;
}
_Bool StackPush(Stack s,const ElemType *val){
	Node newNode = NEW(node);
	if(newNode==NULL)return 0;
	newNode->data = *val;
	newNode->next = s->head->next;
	s->head->next = newNode;
	++s->size;
	return 1;
}
_Bool StackPop(Stack s){
	if(s->head->next==NULL)return 0;
	else{
		Node tmp = s->head->next;
		s->head->next = tmp->next;
		free(tmp);
		--s->size;
		return 1;
	}
}

ElemType* StackTop(Stack s){
	if(s->head->next==NULL)return NULL;
	return &s->head->next->data;
}

void StackDestroy(Stack s){
	while(StackPop(s));
	free(s->head);
	s->head = NULL;
	return;
}

#ifndef TEST
int main(){
	stack s;
	int a = 5;
	if(InitStack(&s)==NULL)return 0;
	for(int i=0;i<a;++i){
		StackPush(&s,&i);
	}
	for(int i=0;i<a;++i){
		printf("%d ",*StackTop(&s));
		StackPop(&s);
	}
	printf("\n");
	StackDestroy(&s);
	return 0;
}

#endif
