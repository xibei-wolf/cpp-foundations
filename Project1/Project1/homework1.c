#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void insertInOrder(Node** head, int value) {
    Node* newNode = createNode(value);
    if (newNode == NULL) {
        return;
    }

    if (*head == NULL || (*head)->data > value) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* current = *head;
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d   ", current->data);
        current = current->next;
    }
}

void freeList(Node* head) {
    Node* current = head;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main() {
    Node* head = NULL;
    // 初始化链表
    insertInOrder(&head, 1);
    insertInOrder(&head, 3);
    insertInOrder(&head, 5);

    printf("原始链表: ");
    printList(head);

    printf("请输入插入的值：");
    int x ;
    scanf("%d", &x);
    insertInOrder(&head, x);
    printf("插入 %d 后的链表: ", x);
    printList(head);

    freeList(head);
    return 0;
}