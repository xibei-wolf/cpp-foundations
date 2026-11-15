#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define INITSIZE 12
typedef int ELEM_TYPE;
typedef struct List_Node {
	ELEM_TYPE data;
	struct List_Node *next;
}List_Node;
typedef struct List_Address {
	List_Node arr[INITSIZE];
}List_Address;
int Hash(ELEM_TYPE val) {
	return val % INITSIZE;
}
void Init(List_Address* pla) {
	for (int i = 0;i < INITSIZE;i++) {
		pla->arr[i].next = NULL;
	}
}
bool Insert(List_Address* pla,ELEM_TYPE val) {
	int pos = Hash(val);
	List_Node* p = (List_Node*)malloc(sizeof(List_Node));
	if (p == NULL) return false;
	p->data = val;
	p->next = pla->arr[pos].next;
	pla->arr[pos].next = p;
	return true;
}
bool Delet(List_Address* pla,ELEM_TYPE val) {
	int pos = Hash(val);
	List_Node *p = &pla->arr[pos];
	while (p->next!=NULL)
	{
		if (p->next->data == val) {
			List_Node* q = p->next;
			p->next = q->next;
			free(q);
			return true;
		}
		p = p->next;
	}
	return false;
}
List_Node* Search(List_Address* pla, ELEM_TYPE val) {
	int pos = Hash(val);
	List_Node* p = &pla->arr[pos];
	while (p->next != NULL)
	{
		if (p->next->data == val) {
			List_Node* q = p->next;
			return q;
		}
		p = p->next;
	}
	return NULL;
}
void show(List_Address* pla) {
	for (int i = 0;i < INITSIZE;i++) {
		printf("%dÐÐ:", i);
		List_Node* p = pla->arr[i].next;
		while (p!=NULL)
		{
			printf("%d ", p->data);
			p = p->next;
		}
		putchar('\n');
	}
}
int main() {
	List_Address head;
	Init(&head);
	Insert(&head, 12);
	Insert(&head, 67);
	Insert(&head, 56);
	Insert(&head, 16);
	Insert(&head, 25);
	Insert(&head, 37);
	Insert(&head, 22);
	Insert(&head, 29);
	Insert(&head, 15);
	Insert(&head, 47);
	Insert(&head, 48);
	Insert(&head, 34);
	Delet(&head, 15);
	show(&head);

	return 0;
}

