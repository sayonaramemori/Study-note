#define MAXSIZ 20
#include "queue.h"

#ifndef QUEUE_H
#define QUEUE_H
typedef struct{
	int front;
	int rear;
	void *data;
	int maxsize;
	size_t szt;
}queue,*Queue;
#endif


void QueueDestroy(Queue q){
	free(q->data);
	return;
}

void QueueInit(Queue q,size_t size){
	q->front = 0;
	q->szt = size;
	q->rear = 0;
	q->maxsize = MAXSIZ;
	q->data = malloc(size*MAXSIZ);
	return;
}

_Bool EnQueue(Queue q,const void *val){
	if((q->rear+1)%q->maxsize==q->front){
		_Bool res = QueueNewSpace(q);
		if(!res)return 0;
	}
	memcpy(q->data+q->szt*q->rear,val,q->szt);
	q->rear = (q->rear+1)%q->maxsize;
	return 1;
}

_Bool DeQueue(Queue q,void *e){
	if(q->front==q->rear)return 0;
	if(e!=NULL)
	memcpy(e,q->data+q->front*q->szt,q->szt);
	q->front = (q->front+1)%q->maxsize;
	return 1;
}

_Bool QueueEmpty(Queue q){
	return q->front==q->rear;
}

int QueueSize(Queue q){
	return (q->rear - q->front + q->maxsize)%q->maxsize;
}

_Bool QueueNewSpace(Queue q){
	int newsize = q->maxsize*2;
	void *data = malloc(q->szt*newsize);
	if(data==NULL)return 0;
	int index = 0;
	if(q->front==0){
		memcpy(data,q->data,q->maxsize*q->szt);
		index = q->maxsize - 1;
	}	
	else{
		void *tmp = malloc(q->szt);
		for(;DeQueue(q,tmp);++index)
			memcpy(data+index*q->szt,tmp,q->szt);
		free(tmp);
	}
	q->front = 0;
	q->rear = index;
	q->maxsize = newsize;
	free(q->data);
	q->data = data;
	return 1;
}




#if 0
int main(){
	queue q;
	QueueInit(&q,sizeof(int));
	for(int i=0;i<22;i++)EnQueue(&q,&i);
	printf("Size:%d\n",QueueSize(&q));
	int tmp;
	for(int i=0;i<22;i++){
		DeQueue(&q,&tmp);
		printf("%d ",tmp);
	}
	int a = 20;
	EnQueue(&q,&a);
	printf("Size:%d\n",QueueSize(&q));
	printf("\n");
	QueueDestroy(&q);
	return 0;
}
#endif
