#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef treeNode{
	treeNode *lchld,*rchld;
	void *data;
	void *key;
}node,*Node;

typedef binarySearchTree{
	Node head;	
	int size;
	size_t szt;
	size_t szk;
	int keyCmp(const void*,const void*);
}BST;

void BST_Init(BST*,size_t szt,size_t szk,int(*)(const void*,const void*));
bool BST_Insert(BST*,void *key,void *data);
void *BST_Find(BST*,void *key);
bool BST_Erase(BST*,void *key);
int BST_SubTreeHigh(Node);
void BST_Travel(BST*);
void BST_Destroy(BST*);
#endif




