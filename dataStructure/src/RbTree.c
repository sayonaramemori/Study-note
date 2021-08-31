#include "RbTree.h"
#include "queue.h"
#define RR 0
#define RL 1
#define LR 2
#define LL 3
static inline RbNode* parentOf(RbNode* cur);
static inline RbNode* newRbNode(RbTree *tree,const void *key,const void *data);
static inline void leftUp(RbTree*,RbNode *top);
static inline void rightUp(RbTree*,RbNode *top);
static inline RbNode* brotherOf(RbNode *cur);
void fixAfterInsert(RbTree *tree,RbNode *cur);


static inline RbNode* parentOf(RbNode* cur){
	return cur->parent;
}

static inline RbNode* newRbNode(RbTree *tree,const void *key,const void *data){
	RbNode *node = malloc(sizeof(RbNode));
	if(node==NULL)return NULL;
	node->data = malloc(sizeof(tree->szt));
	if(node->data==NULL){
		free(node);
		return NULL;
	}
	node->key = malloc(sizeof(tree->szk));
	if(node->key==NULL){
		free(node->data);
		free(node);
		return NULL;
	}
	memcpy(node->data,data,tree->szt);
	memcpy(node->key,key,tree->szk);
	node->color = RED;
	node->parent = NULL;
	node->lchld = NULL;
	node->rchld = NULL;
	return node;
}


static inline void leftUp(RbTree *tree,RbNode *newTop){
	RbNode *top = newTop->parent;
	top->rchld = newTop->lchld;
	if(top->rchld!=NULL)top->rchld->parent = top;
	newTop->lchld = top;
	newTop->parent = top->parent;
	top->parent = newTop;
	if(newTop->parent==NULL) tree->root = newTop;
	else (newTop->parent->lchld==top)?(newTop->parent->lchld = newTop):(newTop->parent->rchld = newTop);
	return;
}

static inline void rightUp(RbTree *tree,RbNode *newTop){
	RbNode *top = newTop->parent;
	top->lchld = newTop->rchld;
	if(top->lchld!=NULL)top->rchld->parent = top;
	newTop->rchld = top;
	newTop->parent = top->parent;
	top->parent = newTop;
	if(newTop->parent==NULL) tree->root = newTop;
	else (newTop->parent->lchld==top)?(newTop->parent->lchld = newTop):(newTop->parent->rchld = newTop);
	return;
}

static inline RbNode* brotherOf(RbNode *cur){
	RbNode *parent = parentOf(cur);
	return (parent->lchld==cur)?(parent->rchld):(parent->lchld);
}


void RbTreeInit(RbTree *tree,size_t szt,size_t szk,int (*keyCmp)(const void*,const void*)){
	tree->root = NULL;
	tree->size = 0;
	tree->szt = szt;
	tree->szk = szk;
	tree->keyCmp = keyCmp;
	return;
}

//should receive cur's parent node
void handleBroRed(RbTree *tree,RbNode *grandpa){
	grandpa->lchld->color = BLK;
	grandpa->rchld->color = BLK;
	grandpa->color = RED;
	RbNode *pgrandpa = parentOf(grandpa);
	if(pgrandpa==NULL){
		grandpa->color = BLK;
		return;
	}else if(pgrandpa->color==BLK)return;
	else fixAfterInsert(tree,grandpa);
}

//cur is the new inserted node
//parent is the father of the new insert node
void fixAfterInsert(RbTree *tree,RbNode *cur){
	RbNode* parent = parentOf(cur);
	if(parent->parent==NULL||parent->color==BLK){
		parent->color = BLK;
		return;
	}
	//parent is red:
	RbNode *uncle = brotherOf(parent);
	RbNode *grandpa = parentOf(parent);
	if(uncle==NULL||uncle->color==BLK){
		int type = 0;
		if(parent->lchld==cur) type |= RL;
		if(grandpa->lchld==parent) type |= LR;
		switch(type){
			case RR:
				parent->color = BLK;
				grandpa->color = RED;
				leftUp(tree,parent);
				break;
			case RL:
				cur->color = BLK;
				grandpa->color = RED;
				rightUp(tree,cur);
				leftUp(tree,cur);
				break;
			case LR:
				cur->color = BLK;
				grandpa->color = RED;
				leftUp(tree,cur);
				rightUp(tree,cur);
				break;
			case LL:
				parent->color = BLK;
				grandpa->color = RED;
				rightUp(tree,parent);
				break;
			default:
				break;
		}
	}else{
		handleBroRed(tree,grandpa);
		return;
	}
}
	

bool RbTreeInsert(RbTree* tree,const void *key,const void *data){
	if(tree->root==NULL){
		tree->root = newRbNode(tree,key,data);
		if(tree->root==NULL)return 0;
		++tree->size;
		tree->root->color = BLK;
		return 1;
	}
	int cmpRes = 0;
	RbNode *cur = tree->root;
	bool flag = 1;
	while(flag){
		cmpRes = tree->keyCmp(key,cur->key);
		switch(cmpRes){
			case -1:
				if(cur->lchld!=NULL)
					cur = cur->lchld;
				else {
					flag = 0;
					cur->lchld = newRbNode(tree,key,data);
					if(cur->lchld==NULL)return 0;
					cur->lchld->parent = cur;
					fixAfterInsert(tree,cur->lchld);
				}
				break;
			case 0:
				return 0;
			case 1:
				if(cur->rchld!=NULL)
					cur = cur->rchld;
				else{
					flag = 0;
					cur->rchld = newRbNode(tree,key,data);
					if(cur->rchld==NULL)return 0;
					cur->rchld->parent = cur;
					fixAfterInsert(tree,cur->rchld);
				}
				break;
			default:
				printf("It never come Here\n");
				break;
		}
	}
	++tree->size;
	return 1;
}

void print(const RbNode* node){
	const int *val = node->data;
	if(node->parent==NULL){
		if(node->color==RED)
		printf("%2d R NULL\n",*val);
		else
		printf("%2d B NULL\n",*val);
		return;
	}
	const int *pa = node->parent->data;
	if(node->color==RED)
	printf("%2d R %2d\n",*val,*pa);
	else
	printf("%2d B %2d\n",*val,*pa);
}

void travel(RbTree* tree){
	RbNode*cur = tree->root;
	if(cur==NULL){
		printf("nothing Here\n");
		return;
	}
	queue q;
	QueueInit(&q,sizeof(cur));
	EnQueue(&q,&cur);
	while(DeQueue(&q,&cur)){
		if(cur->lchld!=NULL)EnQueue(&q,&cur->lchld);
		if(cur->rchld!=NULL)EnQueue(&q,&cur->rchld);
		print(cur);
	}
	QueueDestroy(&q);
	return;
}


#if 1
int mycmp(const void*lhs,const void*rhs){
	const int *ls = lhs;
	const int *rs = rhs;
	if(*ls==*rs)return 0;
	if(*ls>*rs)return 1;
	else return -1;
}

int main(){
	RbTree t;
	RbTreeInit(&t,sizeof(int),sizeof(int),mycmp);
	for(int i=1;i<19;++i)
		RbTreeInsert(&t,&i,&i);
	travel(&t);
	return 0;
}
#endif

