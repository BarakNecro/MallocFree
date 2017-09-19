#pragma once
#include <stdio.h>

#define QUESTION2_MAX 1679615
#define QUESTION2_STR_SIZE_MAX 4
#define QUESTION2_RIDIX 36

#define QUESTION7_LEFT 0
#define QUESTION7_RIGHT 1

#define QUESTION7_SHOW_FALSE 0
#define QUESTION7_SHOW_TRUE 1

#define QUESTION7_FREE_SUCCESS 1
#define QUESTION7_FREE_FAILED 0

void HowMuchOne(int*);

char* TenTo36(unsigned int num);

void HForLF();

void UpsideDownMem(int *pNum);

void UpsideDownStr(char *arr, int arrSize);

void StrRotate(char *str, int strSize, int rotateSize);


//链表相关开始
typedef struct _LinkedNode {
	char data;
	struct _LinkedNode *next;
}LinkedNode, *PLinkedNode;

typedef struct _XorLinkedList {
	PLinkedNode head;
	PLinkedNode tail;
}XorLinkedList, *PXorLinkedList;

PLinkedNode XorPLinkedNode(PLinkedNode node1, PLinkedNode node2);

PXorLinkedList initXorLinkedList();

int showMyList(PXorLinkedList list, int D, int show);

void insertNode(PXorLinkedList list, char data, int D);

void deleteNode(PXorLinkedList list, int D);

int _freeXorLinkedList(PXorLinkedList list);

void freeXorLinkedList(PXorLinkedList list);