#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100

// 定义联系人结构体
typedef struct {
    char name[50];
    char landline[20];
    char mobile[20];
} Contact;

// 比较函数，用于qsort按名字排序
int compareByName(const void* a, const void* b) {
    return strcmp(((Contact*)a)->name, ((Contact*)b)->name);
}

// 比较函数，用于qsort按固定电话排序
int compareByLandline(const void* a, const void* b) {
    return strcmp(((Contact*)a)->landline, ((Contact*)b)->landline);
}

// 比较函数，用于qsort按手机号码排序
int compareByMobile(const void* a, const void* b) {
    return strcmp(((Contact*)a)->mobile, ((Contact*)b)->mobile);
}

// 查找函数，根据名字查找联系人
Contact* findContactByName(Contact contacts[], int size, const char* name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            return &contacts[i];
        }
    }
    return NULL;
}

// 查找函数，根据固定电话查找联系人
Contact* findContactByLandline(Contact contacts[], int size, const char* landline) {
    for (int i = 0; i < size; i++) {
        if (strcmp(contacts[i].landline, landline) == 0) {
            return &contacts[i];
        }
    }
    return NULL;
}

// 查找函数，根据手机号码查找联系人
Contact* findContactByMobile(Contact contacts[], int size, const char* mobile) {
    for (int i = 0; i < size; i++) {
        if (strcmp(contacts[i].mobile, mobile) == 0) {
            return &contacts[i];
        }
    }
    return NULL;
}

void addContact(Contact contacts[], int* numContacts) {
    if (*numContacts < MAX_CONTACTS) {
        printf("请输入联系人姓名: ");
        scanf("%s", contacts[*numContacts].name);
        printf("请输入固定电话: ");
        scanf("%s", contacts[*numContacts].landline);
        printf("请输入手机号码: ");
        scanf("%s", contacts[*numContacts].mobile);
        (*numContacts)++;
    }
    else {
        printf("通讯录已满，无法添加更多联系人。\n");
    }
}

void displayContacts(Contact contacts[], int numContacts) {
    for (int i = 0; i < numContacts; i++) {
        printf("姓名: %-15s 固定电话: %-15s 手机号码: %-15s\n", contacts[i].name, contacts[i].landline, contacts[i].mobile);
    }
}

int main() {
    Contact contacts[MAX_CONTACTS];
    int numContacts = 0;
    int choice;
    char temp[50];

    while (1) {
        printf("\n通讯录管理系统\n");
        printf("1. 添加联系人\n");
        printf("2. 按名字排序\n");
        printf("3. 按固定电话排序\n");
        printf("4. 按手机号码排序\n");
        printf("5. 按名字查找联系人\n");
        printf("6. 按固定电话查找联系人\n");
        printf("7. 按手机号码查找联系人\n");
        printf("8. 显示所有联系人\n");
        printf("9. 退出\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addContact(contacts, &numContacts);
            break;
        case 2:
            qsort(contacts, numContacts, sizeof(Contact), compareByName);
            printf("按名字排序后的通讯录:\n");
            displayContacts(contacts, numContacts);
            break;
        case 3:
            qsort(contacts, numContacts, sizeof(Contact), compareByLandline);
            printf("按固定电话排序后的通讯录:\n");
            displayContacts(contacts, numContacts);
            break;
        case 4:
            qsort(contacts, numContacts, sizeof(Contact), compareByMobile);
            printf("按手机号码排序后的通讯录:\n");
            displayContacts(contacts, numContacts);
            break;
        case 5:
            printf("请输入要查找的联系人姓名: ");
            scanf("%s", temp);
            Contact* foundByName = findContactByName(contacts, numContacts, temp);
            if (foundByName) {
                printf("找到联系人: ");
                printf("姓名: %-15s 固定电话: %-15s 手机号码: %-15s\n", foundByName->name, foundByName->landline, foundByName->mobile);
            }
            else {
                printf("未找到该联系人。\n");
            }
            break;
        case 6:
            printf("请输入要查找的固定电话号码: ");
            scanf("%s", temp);
            Contact* foundByLandline = findContactByLandline(contacts, numContacts, temp);
            if (foundByLandline) {
                printf("找到联系人: ");
                printf("姓名: %-15s 固定电话: %-15s 手机号码: %-15s\n", foundByLandline->name, foundByLandline->landline, foundByLandline->mobile);
            }
            else {
                printf("未找到该联系人。\n");
            }
            break;
        case 7:
            printf("请输入要查找的手机号码: ");
            scanf("%s", temp);
            Contact* foundByMobile = findContactByMobile(contacts, numContacts, temp);
            if (foundByMobile) {
                printf("找到联系人: ");
                printf("姓名: %-15s 固定电话: %-15s 手机号码: %-15s\n", foundByMobile->name, foundByMobile->landline, foundByMobile->mobile);
            }
            else {
                printf("未找到该联系人。\n");
            }
            break;
        case 8:
            printf("所有联系人:\n");
            displayContacts(contacts, numContacts);
            break;
        case 9:
            exit(0);
        default:
            printf("无效的选择，请重新输入。\n");
        }
    }

    return 0;
}

