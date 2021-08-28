#include "myhead.h"
#define ElemType int
#define MAXSIZ 20

typedef struct{
	int front;
	int rear;
	ElemType data[MAXSIZ];
}queue,*Queue;

void QueueInit(Queue q){
	q->front = 0;
	q->rear = 0;
	return;
}

_Bool EnQueue(Queue q,ElemType val){
	if((q->rear+1)%MAXSIZ==q->front)return 0;
	q->data[q->rear] = val;
	q->rear = (q->rear+1)%MAXSIZ;
	return 1;
}

_Bool DeQueue(Queue q,ElemType *e){
	if(q->front==q->rear)return 0;
	*e = q->data[q->front];
	q->front = (q->front+1)%MAXSIZ;
	return 1;
}

#if 1 
int main(){
	queue q;
	QueueInit(&q);
	for(int i=0;i<5;i++)EnQueue(&q,i);
	int tmp;
	for(int i=0;i<5;i++){
		DeQueue(&q,&tmp);
		printf("%d ",tmp);
	}
	printf("\n");
	return 0;
}
#endif
