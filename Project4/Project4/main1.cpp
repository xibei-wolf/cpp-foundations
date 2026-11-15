#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
int a[] = { -2,1,-3,4,-1,2,1,-5,4 };
int main() {
	int len = sizeof(a) / sizeof(int);
	int b[20] = { 0 }, loc[20] = { 0 };
	int max = 0;
	b[len - 1] = a[len - 1], loc[len - 1] = a[len - 1];
	for (int i = len - 2;i >= 0;i--) {
		if (b[i + 1] > 0) {
			b[i] = b[i + 1] + a[i];
			loc[i] = loc[i + 1];
		}
		else {
			b[i] = a[i];
			loc[i] = i;
		}
	}
	for (int j = 1;j < len;j++) {
		if (b[j] > b[max])
			max = j;
	}


	printf("最大子数组和为：%d\n", b[max]);
	printf("下标为%d,%d", max, loc[max]);
	return 0;
}