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

#define Data_type int
#define INIT_SIZE 20
typedef struct{
	int size;
	int max_size;
	Data_type *seqence;
}cvector;

void InitCvector(cvector *);
int LengthCvector(cvector*);
int LocateCvector(cvector*,const Data_type*);
_Bool GetEleCvector(cvector*,int,Data_type*);
_Bool InsertCvector(cvector*,int,const Data_type*);
void Print(cvector*);
_Bool EmptyCvector(cvector*);
void DestroyCvector(cvector*);
_Bool CvectorPush(cvector *vec,const Data_type* val);
static cvector* newSpace(cvector *vec);

void InitCvector(cvector *vec){
	vec->max_size = INIT_SIZE;
	vec->size = 0;
	vec->seqence = malloc(sizeof(Data_type)*vec->max_size);
	return;
}

int LengthCvector(cvector* vec){
	return vec->size;
}

//return the first underpos if the val is exist
int LocateCvector(cvector* vec,const Data_type* val){
	for(int i=0;i<vec->size;++i)
		if(vec->seqence[i]==*val)return i;
	return -1;
}
_Bool GetEleCvector(cvector* vec,int index,Data_type *dst){
	if(index >= vec->size)return 0;
	*dst = vec->seqence[index];
	return 1;
}
static cvector* newSpace(cvector *vec){
	vec->max_size *= 2;
	Data_type* res = malloc(sizeof(Data_type)*vec->max_size);
	if(res==NULL){
		vec->max_size /= 2;
		return NULL;
	}
	memcpy(res,vec->seqence,sizeof(Data_type)*vec->size);
	free(vec->seqence);
	vec->seqence = res;
	return vec;
}


_Bool InsertCvector(cvector* vec,int index,const Data_type* val){
	if(vec->size==vec->max_size){
		vec = newSpace(vec);
		if(vec==NULL)return 0;
	}
	if(index < 0 || index > vec->size)return 0;
	int pos = vec->size+1;
	while(--pos!=index){
		vec->seqence[pos] = vec->seqence[pos-1];
	}
	vec->seqence[index] = *val;
	++vec->size;
	return 1;
}

void Print(cvector* vec){
	for(int i=0;i<vec->size;++i)
		printf("%d ",vec->seqence[i]);
	printf("\n");
}
_Bool EmptyCvector(cvector* vec){
	if(vec->size==0)return 1;
	else return 0;
}

void DestroyCvector(cvector* vec){
	free(vec->seqence);
	return;
}

_Bool CvectorPush(cvector *vec,const Data_type* val){
	if(vec->size==vec->max_size){
		vec = newSpace(vec);
		if(vec==NULL)return 0;
	}
	vec->seqence[vec->size++] = *val;
	return 1;
}


#ifndef MYNODEB
int main(){
	cvector tmp;
	InitCvector(&tmp);
	for(int i=0;i<35;i++)CvectorPush(&tmp,&i);
	int num = 9;
	for(int i=0;i<5;++i)
	InsertCvector(&tmp,5,&num);
	Print(&tmp);
	printf("max_size is:%d\n",tmp.max_size);
	DestroyCvector(&tmp);
	return 0;
}
#endif



	
