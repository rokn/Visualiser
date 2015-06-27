#include "List.h"

ListNode* listGetNode(List*,int);

void ListInit(List *list,int sizeOfElement)
{
    assert(sizeOfElement > 0);
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->elementSize = sizeOfElement;
}

void ListDestroy(List *list)
{
    int i;
    
    for (i = 0; i < list->length; ++i)
    {
        ListRemoveFront(list);
    }    
}

int ListGetSize(List *list)
{
    return list->length;
}

void ListAddFront(List *list, void* newData)
{
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->data = malloc(list->elementSize);
    memcpy(newNode->data, newData, list->elementSize);

    newNode->next = list->head;

    if(list->length!=0)
    {
        list->head->prev = newNode;
    }
    
    newNode->prev =NULL;
    list->head = newNode;


    //length == 0 ?
    if(!list->tail)
    {
        list->tail = list->head;
    }

    list->length ++;
}

void ListAdd(List *list, void* newData)
{
    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->data = malloc(list->elementSize);
    memcpy(newNode->data, newData, list->elementSize);

    newNode->next = NULL;
    newNode->prev = list->tail;

    //length == 0 ?
    if(list->length == 0)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->length ++;
}

void ListRemoveFront(List *list)
{    
    ListNode *node = list->head;    
    list->head = node->next;    
    // list->head->prev = NULL;
    list->length--;

    free(node->data);    
    free(node);

    if(list->length == 0)
    {
        list->tail->data = NULL;
        list->tail = NULL;
    }
}

void ListRemoveLast(List *list)
{
     ListNode *node = list->tail;
     list->tail = node->prev;
     list->tail->next = NULL;
     list->length--;

     free(node->data);
     free(node);
}

void ListPeekFront(List *list, void *result)
{
    assert(list->head != NULL);
    memcpy(result, list->head->data, list->elementSize);
}

void ListPeekLast(List *list, void *result)
{
    assert(list->tail != NULL);
    memcpy(result, list->tail->data, list->elementSize);
}

void ListForEach(List *list, listIterator iterator)
{
    assert(iterator != NULL);

    ListNode *node = list->head;
    bool result = true;

    while(node!=NULL)
    {
        result = iterator(node->data);
        node = node->next;
    }
}

void ListPeekAt(List *list, void *result, int index)
{
    // listGetNode(list,index);
    memcpy(result, listGetNode(list,index)->data, list->elementSize);
}

void ListRemoveAt(List *list,int index)
{
    // printf("index:%d , size:%d",index,list->length);
    ListNode *node = listGetNode(list,index);
    if(index > 0)
    {
        node->prev->next = node->next;
    }
    else
    {
        list->head = node->next;
    }
    if(index < list->length-1)
    {
        node->next->prev = node->prev;
    }
    else
    {
        list->tail = node->prev;
    }

    free(node->data);
    free(node);

    list->length--;
}

ListNode* listGetNode(List *list,int index)
{
    // printf("node%d %d\n",index,list->length);
    assert(index>=0 && index < list->length);
    int i;
    ListNode *currNode = list->head;

    for (i = 1; i <= index; ++i)
    {
        currNode = currNode->next;
    }

    return currNode;
}

void ListInsert(List *list, void *newData, int index)
{
    assert(index >= 0 && index < list->length);

    if(index == 0)
    {
        ListAddFront(list, newData);
        return;
    }

    ListNode *indexNode = listGetNode(list,index);

    ListNode *newNode = malloc(sizeof(ListNode));
    newNode->data = malloc(list->elementSize);
    memcpy(newNode->data, newData, list->elementSize);

    newNode->next = indexNode;

    indexNode->prev->next = newNode;
    indexNode->prev = newNode;

    list->length ++;
}

void ListReplace(List *list, void *newData, int index)
{
    // printf("replace%d %d\n",index,list->length);
    memcpy(listGetNode(list,index)->data, newData, list->elementSize);
}