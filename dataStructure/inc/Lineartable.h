#ifndef CVECTOR
#define CVECTOR
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

#endif