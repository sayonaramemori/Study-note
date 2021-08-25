#include "myhead.h"


#define ElemType int
typedef struct node{
	ElemType data;
	struct node* next;
}*Node,node;

Node InitListTable();
_Bool ListHeadInsert(Node head,const ElemType *val);
_Bool ListPush(Node head,const ElemType *val);
ElemType *ListGetElem(Node head,int index);
int ListLocateElem(Node head,const ElemType *val);
_Bool ListInsertBefore(Node head,const ElemType *val,int index);
_Bool ListInsertAfter(Node head,const ElemType *val,int index);
_Bool ListDelete(Node head,int index);
int ListLength(Node head);
void DestroyList(Node head);
static Node LocateIndex(Node head,int index,Node *pre);

Node InitListTable(){
	Node head = malloc(sizeof(node));
	if(head==NULL)return NULL;
	head->next = NULL;
	return head;
}

_Bool ListHeadInsert(Node head,const ElemType *val){
	Node newNode = malloc(sizeof(node));
	if(newNode==NULL)return 0;
	newNode->data = *val;
	newNode->next = head->next;
	head->next = newNode;
	return 1;
}

_Bool ListPush(Node head,const ElemType *val){
	Node cur = head;
	while(cur->next!=NULL)cur = cur->next;
	Node newNode = malloc(sizeof(node));
	if(newNode==NULL)return 0;
	newNode->data = *val;
	newNode->next = NULL;
	cur->next = newNode;
	return 1;
}

static Node LocateIndex(Node head,int index,Node *pre){
	if(index<0)return NULL;
	index += 2;
	Node cur = head;
	Node tmp = cur;
	while(--index&&cur){
		tmp = cur;	
		cur = cur->next;	
	}
	if(index!=0)return NULL;
	if(pre!=NULL)*pre = tmp;
	return cur;
}

ElemType *ListGetElem(Node head,int index){
	if(index<0)return NULL;
	index += 2;
	Node cur = head;
	while(--index&&cur){
		cur = cur->next;	
	}
	if(index!=0)return NULL;
	return &cur->data; 
}
		
int ListLocateElem(Node head,const ElemType *val){
	Node cur = head->next;
	for(int i=0;cur!=NULL;++i){
		if(cur->data == *val)return i;
	}
	return -1;
}

_Bool ListInsertBefore(Node head,const ElemType *val,int index){
	Node pre;
	Node ptr = LocateIndex(head,index,&pre);
	if(ptr==NULL)return 0;
	Node newNode = malloc(sizeof(node));
	if(newNode==NULL)return 0;
	newNode->data = *val;
	newNode->next = ptr;
	pre->next = newNode;
	return 1;
}

_Bool ListInsertAfter(Node head,const ElemType *val,int index){
	Node ptr = LocateIndex(head,index,NULL);
	if(ptr==NULL)return 0;
	Node lat = ptr->next;
	Node newNode = malloc(sizeof(node));
	if(newNode==NULL)return 0;
	newNode->data = *val;
	newNode->next = lat;
	ptr->next = newNode;
	return 1;
}

_Bool ListDelete(Node head,int index){
	Node pre;
	Node ptr = LocateIndex(head,index,&pre);
	if(ptr==NULL)return 0;
	pre->next = ptr->next;
	free(ptr);
	return 1;
}
	
int ListLength(Node head){
	int res = 0;
	Node cur=head->next;
	while(cur){
		cur = cur->next;
		++res;
	}
	return res;
}
void DestroyList(Node head){
	Node cur = head;
	Node next;
	while(cur){
		next = cur->next;
		free(cur);
		cur = next;
	}
	return;
}
void ListPrint(Node head){
	Node cur = head->next;
	while(cur){
		printf("%d ",cur->data);
		cur = cur->next;
	}
	printf("\n");
	return;
}

#ifndef TEST
int main(){
	node *test = InitListTable();
	for(int i=0;i<10;++i)ListHeadInsert(test,&i);
	ListDelete(test,4);
	int val = 5;
	ListInsertAfter(test,&val,3);
	ListPrint(test);
	DestroyList(test);
	return 0;
}

#endif
