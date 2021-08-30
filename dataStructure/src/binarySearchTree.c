#include "tree.h"

#define LL 3
#define RR 0
#define LR 2
#define RL 1
#define maxsize 4
typedef TinyQueue{
	int front;
	int rear;
	Node trace[maxsize];
}*Path;

void TinyInit(Path q){
	q->front = 0;
	q->rear = 0;
	return;
}

void TinyPush(Path q,Node p){
	//full then pop
	if((q->rear+1)%maxsize==q->front)q->front = (q->front+1)%maxsize;
	q->trace[q->rear] = p;
	q->rear = (q->rear+1)%maxsize;
	return;
}

inline Node TinyPop(Path q){
	Node res = q->trace[q->front];
	q->front = (q->front+1)%maxsize;
	return res;
}

inline int TinySize(Path q){
	return (q->rear-q->front+maxsize)%maxsize;
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
	tree->KeyCmp = cmp;
	return;
}

int BST_SubTreeHigh(Node p){
	if(p==NULL)return 0;
	int lh = BST_SubTreeHigh(p->lchld);
	int rh = BST_SubTreeHigh(p->rchld);
	return (lh>rh)?(lh+1):(rh+1);
}
	

bool BST_Insert(BST *tree,void *key,void *data){
	if(tree->head==NULL){
		tree->head = newNode(tree,key,data);
		return 1;
	}
	int cmpres = 0;
	TinyQueue q;
	TinyInit(&q);
	Node cur = tree->head;
	while(cur->lchld!=NULL&&cur->rchld!=NULL){
		TinyPush(&q,cur);
		cmpres = tree->keyCmp(key,cur->key);
		if(cmpres==0)return 0;
		else if(cmpres>0) cur = cur->rchld;
		else cur = cur->lchld;
	}
	//All inserter insert lchld first
	int traceSize = TinySize(&q);
	if(cur->lchld==NULL){
		cmpres = tree->keyCmp(key,cur->key);
		if(cmpres==0)return 0;
		switch(traceSize){
			//if the cur is the head
			case 0:
				if(cmpres>0){
					tree->head = newNode(tree,key,data);
					tree->head->lchld = cur;
				}else cur->lchld = newNode(tree,key,data);	
				break;
			case 3:
			case 2:
			case 1:
				Node pre = TinyPop(&q);
				int type = 0;
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
				Node top = TinyPop(&q);
				int lh = BST_SubTreeHigh(top->lchld);
				int rh = BST_SubTreeHigh(top->rchld);
				cmpres = lh - rh;
				if(cmpres<-1||cmpres>1){
					if(top->lchld==pre) type |= LR;
					else type |= RR;
					switch(type){
						case RR:
							top->rchld = pre->lchld;
							pre->lchld = top;
							break;
						case RL:
							cur = pre->lchld;
							pre->lchld = cur->lchld;
							cur->rchld = pre;
							cur->lchld = top;
							top->rchld = NULL;
							break;
						case LR:
							cur = pre->rchld;
							pre->rchld = cur->lchld;
							cur->lchld = pre;
							cur->rchld = top;
							top->lchld = NULL;
							break;
						case LL:
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
		}
		//cut line -----------------------
	}else{
		cmpres = tree->keyCmp(key,cur->key);
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
		}
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
					newSunNode->rchld = cur;
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

