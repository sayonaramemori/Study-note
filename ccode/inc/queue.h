#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
	int front;
	int rear;
	void *data;
	int maxsize;
	int szt;
}queue,*Queue;

int QueueSize(Queue q);
_Bool QueueEmpty(Queue q);
void QueueInit(Queue q,size_t size);
void QueueDestroy(Queue q);
_Bool EnQueue(Queue q,const void *val);
_Bool DeQueue(Queue q,void *e);
_Bool QueueNewSpace(Queue q);

#endif
