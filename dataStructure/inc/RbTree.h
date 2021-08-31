#ifndef RB_TREE_H
#define RB_TREE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define RED 1
#define BLK 0

typedef struct RbNode{
	struct RbNode *parent;
	struct RbNode *lchld;
	struct RbNode *rchld;
	void *data;
	void *key;
	bool color;
}RbNode;

typedef struct RbTree{
	struct RbNode *root;
	int size;
	size_t szt;
	size_t szk;
	int (*keyCmp)(const void*,const void*);
}RbTree;

void RbTreeInit(RbTree*,size_t szt,size_t szk,int(*)(const void*,const void*));
void RbTreeDestroy(RbTree*);
bool RbTreeInsert(RbTree*,const void *key,const void *val);
bool RbTreeErase(RbTree*,const void* key);
void *RbTreeFind(RbTree*,const void* key);

#endif


