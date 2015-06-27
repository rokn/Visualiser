#ifndef GENERICS
#define GENERICS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int bool;
enum { false, true };

typedef bool (*listIterator)(void*);

typedef struct listNode ListNode;

struct listNode {
    void *data;
    ListNode *next;
    ListNode *prev;
};

typedef struct {
    ListNode *head;
    ListNode *tail;
    int length;
    int elementSize;
} List;

void ListInit(List*,int);
void ListDestroy(List*);
int ListGetSize(List*);
void ListAddFront(List*, void*);
void ListInsert(List*, void*, int);
void ListAdd(List*, void*);
void ListRemoveFront(List*);
void ListRemoveLast(List*);
void ListRemoveAt(List*,int);
void ListPeekFront(List*, void*);
void ListPeekLast(List*, void*);
void ListPeekAt(List *, void *, int);
void ListForEach(List*, listIterator);
void ListReplace(List*, void*, int);

#endif