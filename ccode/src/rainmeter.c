#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "queue.h"

typedef struct range{
	int s;
	int e;
}range;

void getrange(int *height,int heightSize,Queue q){
	int start=-1,end=heightSize;
	int guard = end - 1;
	while(height[++start]==0)if(start==guard)return;
	while(height[--end]==0);
	range tmp = {.s = start, .e = end};
	//find from left to get the highest pos
	for(int i=start+1;i<=end;++i){
		if(height[start]>height[i])continue;
		else if(height[start]==height[i]){
			tmp.e = i;
		}else{
			tmp.e = i;
			EnQueue(q,&tmp);
			start = i;
			tmp.s = i;
		}
	}
	if(height[tmp.s]==height[tmp.e]&&tmp.e!=tmp.s){
		_Bool res = EnQueue(q,&tmp);
		start = tmp.e;
	}
	tmp.e = end;
	for(int i=end-1;i>=start;--i){
		if(height[end]>height[i])continue;
		else if(height[end]==height[i]){
			tmp.s = i;
		}else{
			tmp.s = i;
			EnQueue(q,&tmp);
			end = i;
			tmp.e = i;
		}
	}
	return;
}

static inline int getrain(const range *rang,int *height){
	int number = (height[rang->s]>height[rang->e])?height[rang->e]:height[rang->s];
	int res = 0;
	for(int i=rang->s+1;i<rang->e;++i){
		res += (number - height[i]);
	}
	return res;
}
		

int trap(int* height, int heightSize){
	queue resq;
	Queue qptr = &resq;
	QueueInit(qptr,sizeof(range));
	getrange(height,heightSize,qptr);
	range tmp;
	int res = 0;
	while(DeQueue(qptr,&tmp)){
		printf("Range(%d,%d)\n",tmp.s,tmp.e);
		res += getrain(&tmp,height);	
	}
	QueueDestroy(qptr);
	return res;
}

#if 1
int main(){
	int a[] = {4,2,0,3,2,5};
	int res = trap(a,sizeof(a)/sizeof(int));
	printf("res is %d\n",res);
	return 0;
}
#endif
