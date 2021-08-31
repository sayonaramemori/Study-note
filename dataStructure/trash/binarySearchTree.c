#include "tree.h"
#include "queue.h"

#define LL 3
#define RR 0
#define LR 2
#define RL 1
#define maxsize 3

typedef struct TinyStack{
	int top;
	int size;
	Node trace[maxsize];
}*Path;

void TinyInit(Path q){
	q->top = 0;
	q->size = 0;
	return;
}

void TinyPush(Path q,Node p){
	q->trace[q->top] = p;
	q->top = (q->top+1)%maxsize;
	if(q->size!=maxsize)++q->size;
	return;
}

static inline Node TinyPop(Path q){
	q->top = (q->top-1+maxsize)%maxsize;
	Node res = q->trace[q->top];
	--q->size;
	return res;
}

static inline int TinySize(Path q){
	return q->size;
}

static inline Node newNode(BST *tree,void *key,void *data){
	Node res = malloc(sizeof(node));
	if(res==NULL)return NULL;
	res->key = malloc(tree->szk);
	if(res->key==NULL){
		free(res);
		return NULL;
	}
	res->data = malloc(tree->szt);
	if(res->data==NULL){
		free(res->key);
		free(res);
		return NULL;
	}
	memcpy(res->key,key,tree->szk);
	memcpy(res->data,data,tree->szt);
	res->lchld = NULL;
	res->rchld = NULL;
	return res;
}

void BST_Init(BST *tree,size_t szt,size_t szk,int (*cmp)(const void*,const void*)){
	tree->head = NULL;
	tree->size = 0;
	tree->szt = szt;
	tree->szk = szk;
	tree->keyCmp = cmp;
	return;
}

int BST_SubTreeHigh(Node p){
	if(p==NULL)return 0;
	int lh = BST_SubTreeHigh(p->lchld);
	int rh = BST_SubTreeHigh(p->rchld);
	return (lh>rh)?(lh+1):(rh+1);
}
	
bool BST_Insert(BST *tree,void *key,void *data){
	//if root is empty
	if(tree->head==NULL){
		tree->head = newNode(tree,key,data);
		++tree->size;
		return 1;
	}
	int cmpres = 0;
	//A trace Queue
	struct TinyStack q;
	TinyInit(&q);
	Node cur = tree->head;
	while(cur->lchld!=NULL&&cur->rchld!=NULL){
		TinyPush(&q,cur);
		cmpres = tree->keyCmp(key,cur->key);
		if(cmpres==0)return 0;
		else if(cmpres>0) cur = cur->rchld;
		else cur = cur->lchld;
	}
	//At here,the trace is be recording,the max_size is 3,not include the terminal node
	int traceSize = TinySize(&q);
	//All inserter insert lchld first
	if(cur->lchld==NULL){
		cmpres = tree->keyCmp(key,cur->key);
		if(cmpres==0)return 0;
		int type = 0;
		Node pre;
		switch(traceSize){
			case 0://the cur is root node
				if(cmpres>0){
					tree->head = newNode(tree,key,data);
					tree->head->lchld = cur;
				}else cur->lchld = newNode(tree,key,data);	
				break;
			case 3://the top's father is a normal node
			case 2://the top's father is root pointer
			case 1://the pre is the root node
				pre = TinyPop(&q);
				if(cmpres>0){
					Node newSubNode = newNode(tree,key,data);
					newSubNode->lchld = cur;
					if(pre->lchld==cur){
						pre->lchld = newSubNode;
						type |= RL;
					}else{
						pre->rchld = newSubNode;
						type |= RR;
					}
				}else{
					cur->lchld = newNode(tree,key,data);
					(pre->lchld==cur)?(type |= RL):(type |= RR);
				}
				if(traceSize==1)break;
				//---------------------
				Node top = TinyPop(&q);
				int lh = BST_SubTreeHigh(top->lchld);
				int rh = BST_SubTreeHigh(top->rchld);
				cmpres = lh - rh;
				if(cmpres<-1||cmpres>1){
					if(top->lchld==pre) type |= LR;
					else type |= RR;
					switch(type){
						case RR://rotate pre node left
							top->rchld = pre->lchld;
							pre->lchld = top;
							break;
						case RL://rotate cur node right, then rotate cur node left
							cur = pre->lchld;
							pre->lchld = cur->lchld;
							cur->rchld = pre;
							cur->lchld = top;
							top->rchld = NULL;
							break;
						case LR://rotate cur node left, then rotate cur node right
							cur = pre->rchld;
							pre->rchld = cur->lchld;
							cur->lchld = pre;
							cur->rchld = top;
							top->lchld = NULL;
							break;
						case LL://rotate pre node right
							top->lchld = pre->rchld;
							pre->rchld = top;
							break;
						default:
							break;
					}
					if(traceSize==2){
						switch(type){
							case RR:
							case LL:
								tree->head = pre;
								break;
							case RL:
							case LR:
								tree->head = cur;
								break;
							default:
								printf("err\n");
								break;
						}
					}else{
						Node father = TinyPop(&q);
							switch(type){
								case RR:
								case LL:
									(father->lchld==top)?(father->lchld=pre):(father->rchld=pre);
									break;
								case RL:
								case LR:
									(father->lchld==top)?(father->lchld=cur):(father->rchld=cur);
									break;
								default:
									break;
							}
					}
				}
				break;
			default:
				printf("err happend\n");
				break;
			}
	//handle the rchld is empty condition
	}else{
		cmpres = tree->keyCmp(key,cur->key);
		//if cur is root node
		if(traceSize==0){
			if(cmpres==0)return 0;
			else if(cmpres>0){
				cur->rchld = newNode(tree,key,data);
				return 1;
			}else{
				cmpres = tree->keyCmp(key,cur->lchld->key);
				if(cmpres==0)return 0;
				if(cmpres>0){
					tree->head = newNode(tree,key,data);
					tree->head->lchld = cur->lchld;
					tree->head->rchld = cur;
					cur->lchld = NULL;
				}else{
					tree->head = cur->lchld;
					tree->head->lchld = newNode(tree,key,data);
					tree->head->rchld = cur;
					cur->lchld = NULL;
				}
		 	}
		}//other condition,directy insert then ok,cmp the key first
		else{
			cmpres = tree->keyCmp(key,cur->key);
			if(cmpres==0)return 0;
			if(cmpres>0){
				cur->rchld = newNode(tree,key,data);
			}else{
				cmpres = tree->keyCmp(key,cur->lchld->key);
				if(cmpres==0)return 0;
				Node pre = TinyPop(&q);
				Node newSubNode = newNode(tree,key,data);
				if(cmpres>0){
					newSubNode->lchld = cur->lchld;
					newSubNode->rchld = cur;
					cur->lchld = NULL;
					(pre->lchld==cur)?(pre->lchld=newSubNode):(pre->rchld=newSubNode);
				}else{
					cur->lchld->lchld = newSubNode;
					cur->lchld->rchld = cur;
					(pre->lchld==cur)?(pre->lchld=cur->lchld):(pre->rchld=cur->lchld);
					cur->lchld = NULL;
				}
			}
		}
	}
	++tree->size;
	return 1;
}

int mypow(int high){
	int res = 1;
	while(high--){
		res *= 2;
	}
	return res;
}
void BST_Travel(BST *tree,void (*print)(const void*)){
	if(tree->head==NULL){
		printf("Nothing in this tree\n");
		return;
	}
	Node temp;
	queue q;
	QueueInit(&q,sizeof(Node));
	EnQueue(&q,&tree->head);
	int high = 1;
	int index = 0;
	while(DeQueue(&q,&temp)){
		if(temp->lchld!=NULL)EnQueue(&q,&temp->lchld);
		if(temp->rchld!=NULL)EnQueue(&q,&temp->rchld);
		print(temp->data);
		if(++index==(mypow(high)-1)){
			++high;
			printf("\n");
		}
	}
	printf("\n");
	QueueDestroy(&q);
	return;
}

void *BST_Find(BST* tree,void *key);
bool BST_Erase(BST* tree,void *key);

static void nodeDestroy(Node p){
	if(p==NULL)return;
	nodeDestroy(p->lchld);
	nodeDestroy(p->rchld);
	free(p->data);
	free(p->key);
	free(p);
}

void BST_Destroy(BST* tree){
	nodeDestroy(tree->head);
	return;
}

#if 1
void print(const void *val){
	const int *value = val;
	printf("%d ",*value);
	return;
}

int mycmp(const void *lhs,const void *rhs){
	const int *ls = lhs;
	const int *rs = rhs;
	if(*ls>*rs)return 1;
	else if(*ls==*rs)return 0;
	else return -1;
}

int main(){
	BST test;
	BST_Init(&test,sizeof(int),sizeof(int),mycmp);
	for(int i=0;i<50;i++){
		BST_Insert(&test,&i,&i);
	}
	BST_Travel(&test,print);
	BST_Destroy(&test);
	return 0;
}
#endif
