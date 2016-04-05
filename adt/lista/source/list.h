//AEDS 2
//LIST ABSTRACT DATA TYPE
//DOUGLAS RODRIGUES DE ALMEIDA
//
//List ADT Header

#ifndef LIST_H
#define LIST_H

typedef struct _TListNode {
	int Value;
	TListNode* Previous;
	TListNode* Next;
} TListNode;

typedef struct _TList {
	TListNode Header;
} TList;

TList* TList_Create(void);
void TList_Destroy(TList** PList);
void TList_Add(TList* List, int Value);
void TList_Clear(TList* List);
void TList_Delete(TList* List, int Position);
void TList_Insert(TList* List, int Value, int Position);

#endif