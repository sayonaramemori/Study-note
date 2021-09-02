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
static void fixAfterInsert(RbTree *tree,RbNode *cur);
static inline RbNode* getNexNode(RbNode *cur);
static inline RbNode* getPreNode(RbNode *cur);
static RbNode* findNode(RbTree* tree,const void* key);
static inline RbNode* lookDownNext(RbNode *cur);
static inline int getNodeType(RbNode *node);
static inline void swapContent(RbNode *lhs,RbNode *rhs);
static inline bool colorOf(const RbNode *cur);
static inline void nodeClean(RbNode *cur);
static inline int getBroNodeType(RbNode *node);

static inline bool colorOf(const RbNode *cur){
	return (cur==NULL)?BLK:cur->color;
}

static inline void nodeClean(RbNode *cur){
	free(cur->data);
	free(cur->key);
	free(cur);
	return;
}

static inline RbNode* parentOf(RbNode* cur){
	return cur->parent;
}

static inline RbNode* brotherOf(RbNode *cur){
	RbNode *parent = parentOf(cur);
	return (parent->lchld==cur)?(parent->rchld):(parent->lchld);
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
	//pgrandpa may be NULL,not promise grandpa exist his parent
	RbNode *pgrandpa = parentOf(grandpa);
	//grandpa is new root
	if(pgrandpa==NULL){
		grandpa->color = BLK;
		return;
	}else if(pgrandpa->color==BLK)return;
	//Consider grandpa as a new insert node to treat
	else fixAfterInsert(tree,grandpa);
}

//cur is the new inserted node
//parent is the father of the new insert node
static void fixAfterInsert(RbTree *tree,RbNode *cur){
	RbNode* parent = parentOf(cur);
	//parent of cur is exist,if the parent is root or black,return
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

static inline RbNode* getPreNode(RbNode *cur){
	RbNode* pre = cur->lchld;
	if(pre==NULL){
		if(cur->parent->rchld==cur)return cur->parent;
		else if(cur->parent->parent->rchld==cur->parent)return cur->parent->parent;
		else NULL;
	}
	while(pre->rchld!=NULL){
		pre = pre->rchld;
	}
	return pre;
}

static inline RbNode* getNexNode(RbNode *cur){
	RbNode *next = cur->rchld;
	if(next==NULL){
		if(cur->parent->lchld==cur)return cur->parent;
		else if(cur->parent->parent->lchld==cur->parent)return cur->parent->parent;
		else return NULL;
	}
	while(next->lchld!=NULL){
		next = next->lchld;
	}
	return next;
}

//this function will be called when the two child node will be erase
static inline RbNode* lookDownNext(RbNode *cur){
	RbNode *next = cur->rchld;
	while(next->lchld!=NULL){
		next = next->lchld;
	}
	return next;
}

static RbNode* findNode(RbTree* tree,const void* key){
	RbNode *cur = tree->root;
	int cmpRes = 0;
	while(cur!=NULL){
		cmpRes = tree->keyCmp(key,cur->key);	
		switch(cmpRes){
			case 0:
				return cur;
			case -1:
				if(cur->lchld==NULL)return NULL;
				else cur = cur->lchld;
				break;
			case 1:
				if(cur->rchld==NULL)return NULL;
				else cur = cur->rchld;
				break;
			default:
				break;
		}
	}
	return cur;
}	

void* RbTreeFind(RbTree* tree,const void* key){
	RbNode *res = findNode(tree,key);
	if(res==NULL)return NULL;
	else return res->data;
}

static inline int getBroNodeType(RbNode *node){
	int res = 4;
	if(colorOf(node->lchld)==BLK)--res;
	if(colorOf(node->rchld)==BLK)--res;
	return res;
}

static inline int getNodeType(RbNode *node){
	int res = 2;
	if(node->lchld==NULL)--res;
	if(node->rchld==NULL)--res;
	return res;
}

static inline void swapContent(RbNode *lhs,RbNode *rhs){
	void *keyTmp = lhs->key;
	void *dataTmp = lhs->data;
	lhs->key = rhs->key;
	lhs->data = rhs->data;
	rhs->key = keyTmp;
	rhs->data = dataTmp;
	return;
}

void handleBlackTerminal(RbTree *tree,RbNode *target){
	int type;
	RbNode *brother;
	//target is not root node 
	//set black condition is for the loop of case 2;
	while(target->parent!=NULL&&colorOf(target)==BLK){
		brother = brotherOf(target);
		//get true brother first
		if(colorOf(brother)==RED){
			if(target->parent->lchld==target){
				brother->color = BLK;
				brother->parent->color = RED;
				leftUp(tree,brother);
				brother = brotherOf(target);
			}else{
				brother->color = BLK;
				brother->parent->color = RED;
				rightUp(tree,brother);
				brother = brotherOf(target);
			}
		}
		//get the brother type
		type = getBroNodeType(brother);
		//judge the target is lchld or rchld
		switch(type){
			case 2://in this case,brother can lend nothing
				brother->color = RED;
				target = brother->parent;
				break;
			case 3:
				if(target->parent->lchld==target){
					if(brother->rchld==NULL){
						brother->lchld->color=colorOf(brother->parent);
						brother->parent->color = BLK;
						RbNode *top = brother->lchld;
						rightUp(tree,top);
						leftUp(tree,top);
					}else{
						brother->rchld->color = BLK;
						brother->color = colorOf(brother->parent);
						brother->parent->color = BLK;
						leftUp(tree,brother);
					}
				}else{
					if(brother->lchld==NULL){
						brother->rchld->color=colorOf(brother->parent);
						brother->parent->color = BLK;
						RbNode *top = brother->rchld;
						leftUp(tree,top);
						rightUp(tree,top);
					}else{
						brother->lchld->color = BLK;
						brother->color = colorOf(brother->parent);
						brother->parent->color = BLK;
						rightUp(tree,brother);
					}
				}
				target = tree->root;
				break;
			case 4:
				brother->rchld->color = BLK;
				brother->color=colorOf(brother->parent);
				brother->parent->color = BLK;
				if(target->parent->lchld==target)
					leftUp(tree,brother);
				else rightUp(tree,brother);
				target = tree->root;
				break;
			default:
				break;
		}
	}
	target->color = BLK;
	return;
}

bool RbTreeErase(RbTree *tree,const void *key){
	RbNode *target = findNode(tree,key);
	if(target==NULL)return 0;
	RbNode *delNode = target;
	int type = 0;
	bool flag = 1;
	while(flag){
		type = getNodeType(target);
		switch(type){
			case 0://terminal node,can be red or blak
				if(target->color==RED)
				(target->parent->lchld==target)?(target->parent->lchld=NULL):(target->parent->rchld=NULL);
				else if(target==tree->root){
					tree->root = NULL;
				}else handleBlackTerminal(tree,target);
				flag = 0;
				break;
			case 1://target is must black
				(target->lchld==NULL)?(delNode=target->rchld):(delNode=target->lchld);
				swapContent(delNode,target);
				target =delNode;
				break;
			case 2://have two child
				delNode = lookDownNext(target);
				swapContent(delNode,target);
				target = delNode;
				break;
			default:
				break;
		}
	}
	(delNode->parent->lchld==delNode)?(delNode->parent->lchld=NULL):(delNode->parent->rchld=NULL);
	nodeClean(delNode);
	--tree->size;
	return 1;
}

#if 1
int mycmp(const void*lhs,const void*rhs){
	const int *ls = lhs;
	const int *rs = rhs;
	if(*ls==*rs)return 0;
	if(*ls>*rs)return 1;
	else return -1;
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


void testfind(RbTree *tree,int val){
	int a = val;
	RbNode *res = findNode(tree,&a);
	int *temp;
	while(res){
		temp = res->data;
		printf("%d ",*temp);
		res = getNexNode(res);
	}
	printf("\n");
	return;
}

void test(){
	RbTree t;
	RbTreeInit(&t,sizeof(int),sizeof(int),mycmp);
	for(int i=0;i<15;++i)
		RbTreeInsert(&t,&i,&i);
	int key = 3;
	travel(&t);
	RbTreeErase(&t,&key);
	travel(&t);
	return;
}


int main(){
	test();
	return 0;
}
#endif

