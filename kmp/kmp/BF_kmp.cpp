#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
int BF(const char* str,const char* sub) {
	int len1 = strlen(str);
	int len2 = strlen(sub);
	int i = 0, j = 0;
	while (i < len1 && j < len2) {
		if (str[i] == sub[j]) {
			i++;
			j++;
		}
		else {
			i = i - j+1;
			j = 0;
		}
	}
	if (j < len2)
		return -1;
	return i - j;

}
int BF_Pos(const char* str, const char* sub,int n) {
	int len1 = strlen(str);
	int len2 = strlen(sub);
	int i = n, j = 0;
	while (i < len1 && j < len2) {
		if (str[i] == sub[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}
	if (j < len2)
		return -1;
	return i - j;
}
int* Get_next(const char* sub) {
	int len = strlen(sub);
	int* next = (int*)malloc(sizeof(int) * len);
	if (next == NULL)exit(1);
	next[0] = -1, next[1] = 0;
	int j = 1;
	int k = next[1];
	while (j+1<len)
	{
		if (sub[j] == sub[k]||k==-1) {
			k++;
			j++;
			next[j] = k;
		}
		else {
			k = next[k];
		}
	}
	return next;
}
int* Get_nextval(const char* sub,int * next) {
	int len = strlen(sub);
	int* nextval = (int*)malloc(sizeof(int) * len);
	if (nextval == NULL)exit(1);
	nextval[0] = -1;
	int j = 1;
	int k = -1;
	for (int i = 1;i < len;i++) {
		if (sub[i] == sub[next[i]]) {
			nextval[i] = nextval[next[i]];
		}
		else
			nextval[i] = next[i];
	}

	return nextval;
}
int KMP_Pos(const char* str, const char* sub, int n) {
	int len1 = strlen(str);
	int len2 = strlen(sub);
	int i = n, j = 0;
	int* next = Get_next(sub);
	int* nextval = Get_nextval(sub, next);
	while (i < len1 && j < len2) {
		if (str[i] == sub[j]||j == -1 ) {
			i++;
			j++;
		}
		else {
			j = nextval[j];
		}
	}
	free(next);
	if (j < len2)
		return -1;
	return i - j;
}

int main() {

	const char* str = "ababcabcdabcde";
	const char* sub = "abcd";
	int index1 = BF(str, sub);
	int index2 = BF_Pos(str, sub,7);
	int index3 = KMP_Pos(str, sub, 7);
	printf("%d %d %d", index1, index2,index3);
	return 0;
}