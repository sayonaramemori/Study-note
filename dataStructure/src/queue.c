#include "myhead.h"
#define ElemType int
#define MAXSIZ 20

typedef struct{
	int front;
	int rear;
	ElemType data[MAXSIZ];
}queue,*Queue;

void Init(Queue q){
	q->front = 0;
	q->rear = 0;
	return;
}

_Bool Push(Quene q,ElemType val){
	if((q->rear+1)%MAXSIZ==q->front)return 0;
	data[q->rear] = val;
	q->rear = (q->rear+1)%MAXSIZ;
	return 1;
}

_Bool DeQuene(Quene q,ElemType *e){
	if(q->front==q->rear)return 0;
	*e = q->data[q->front];
	q->front = (q->front+1)%MAXSIZ;
	return 1;
}

