#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* operator of linear table
 * InitList(&L);
 * Length(L);
 * LocateElem(L,e);
 * GetElem(L,i);
 * ListInsert(&L,i,e);
 * ListDelete(&L,i,&e);
 * PrintList(L);
 * Empty(L);
 * DestroyList(&L);
*/

#define INIT_SIZE 20
typedef struct{
	void *seqence;
	int size;
	int max_size;
	size_t szt;
}cvector;

void CvectorInit(cvector *,size_t);
int CvectorSize(cvector*);
_Bool CvectorIndex(cvector*,int,void*);
_Bool CvectorInsert(cvector*,int,const void*);
_Bool CvectorEmpty(cvector*);
_Bool CvectorPushBack(cvector *vec,const void* val);
void *CvectorBack(cvector *vec);
void CvectorDestroy(cvector*);
_Bool CvectorDel(cvector *,int index);
_Bool CvectorErase(cvector *,int begin,int end);
int CvectorFind(cvector* vec,const void* val,_Bool(*compare)(const void *lhs,const void *rhs));
static cvector* newSpace(cvector *vec);

_Bool CvectorDel(cvector *vec,int index){
	if(index>=vec->size||index<0)return 0;
	void *start = vec->seqence+index*vec->szt;
	memmove(start,start+vec->szt,(vec->size-index-1)*vec->szt);
	--vec->size;
	return 1;
}

_Bool CvectorErase(cvector *vec,int begin,int end){
	if(begin<0||end>vec->size||end<=begin)return 0;
	void *start = vec->seqence+begin*vec->szt;
	int number = end - begin;
	memmove(start,start+vec->szt*number,(vec->size-end)*vec->szt);
	vec->size -= number;
	return 1;
}

void *CvectorBack(cvector *vec){
	if(vec->size==0)return NULL;
	else return vec->szt*(vec->size-1)+vec->seqence;
}

void CvectorInit(cvector *vec,size_t size){
	vec->max_size = INIT_SIZE;
	vec->size = 0;
	vec->szt = size;
	vec->seqence = malloc(size*vec->max_size);
	return;
}

int CvectorSize(cvector* vec){
	return vec->size;
}

int CvectorFind(cvector* vec,const void* val,_Bool (*cmp)(const void *,const void*)){
	for(int i=0;i<vec->size;++i)
		if(cmp(val,vec->seqence+i*vec->szt))return i;
	return -1;
}

_Bool CvectorIndex(cvector* vec,int index,void *dst){
	if(index >= vec->size)return 0;
	memcpy(dst,vec->seqence+index*vec->szt,vec->szt);
	return 1;
}

static cvector* newSpace(cvector *vec){
	vec->max_size *= 2;
	void* res = malloc(vec->szt*vec->max_size);
	if(res==NULL){
		vec->max_size /= 2;
		return NULL;
	}
	memcpy(res,vec->seqence,vec->szt*vec->size);
	free(vec->seqence);
	vec->seqence = res;
	return vec;
}

_Bool CvectorInsert(cvector* vec,int index,const void* val){
	if(vec->size==vec->max_size){
		if(newSpace(vec)==NULL)return 0;
	}
	if(index < 0 || index > vec->size)return 0;
	void *start = vec->seqence+index*vec->szt;
	memmove(start+vec->szt,start,(vec->size-index)*vec->szt);
	memcpy(start,val,vec->szt);
	++vec->size;
	return 1;
}


_Bool CvectorEmpty(cvector* vec){
	if(vec->size==0)return 1;
	else return 0;
}

void CvectorDestroy(cvector* vec){
	free(vec->seqence);
	return;
}

_Bool CvectorPushBack(cvector *vec,const void* val){
	if(vec->size==vec->max_size){
		vec = newSpace(vec);
		if(vec==NULL)return 0;
	}
	memcpy(vec->seqence+vec->size*vec->szt,val,vec->szt);
	++vec->size;
	return 1;
}


#ifndef MYNODEB
typedef struct{
	int a;
	char b;
	double c;
}test;

void Print(cvector* vec){
	test tmp;
	for(int i=0;i<vec->size;++i){
		CvectorIndex(vec,i,&tmp);
		printf("(%d,%c,%.2f) ",tmp.a,tmp.b,tmp.c);
	}
	printf("\n");
}
_Bool compare(const void *vlhs,const void *vrhs){
	test *lhs = (test*)vlhs;
	test *rhs = (test*)vrhs;
	if(lhs->a==rhs->a)printf("a equal\n");else return 0;
	if(lhs->b==rhs->b)printf("b equal\n");else return 0;
	if(lhs->c==rhs->c)printf("c equal\n");else return 0;
	return 1;
}

int main(){
	cvector tmp;
	CvectorInit(&tmp,sizeof(test));

	for(int i=0;i<5;i++)CvectorPushBack(&tmp,&(test){i,i+48,i});
	int num = 9;
	Print(&tmp);
	test temp = {
		.a = 3,
		.b='3',
		.c=3};
	printf("max_size is:%d\n",tmp.max_size);
	num = CvectorFind(&tmp,&temp,compare);
	double c = 6.14;
	_Bool res = ((3*1.0+3.14)==c);
	/*
	 * Remember this HOLE 
	 * Double equal operator
	*/
	printf("3*1.0+3.14==6.14,compare res is %d\n",res);
	printf("the find 9,index is %d\n",num);
	CvectorDel(&tmp,num);
	Print(&tmp);
	printf("size is:%d\n",tmp.size);
	CvectorDestroy(&tmp);
	return 0;
}
#endif



	
