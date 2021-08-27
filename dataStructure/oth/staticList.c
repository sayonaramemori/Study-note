#include "myhead.h"
#define ElemType int 
#define MAXSIZ 20

typedef struct{
	ElemType data;
	int next;
}StaticList;

typedef struct{
	StaticList *seqence;
	int max_size;
	int size;
}Slist;

Slist* InitSlist(Slist * sl){
	sl->max_size = MAXSIZ;
	sl->size = 0;
	sl->seqence = malloc(sizeof(StaticList)*MAXSIZ);
	if(sl->seqence == NULL)return NULL;
	return sl;
}




