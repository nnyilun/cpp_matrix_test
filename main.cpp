#include <iostream>
#include "matrix.h"
#include <stdio.h>
#include <string.h>
using namespace std;

void fun(int a, int b, int c) {
	printf("%d", sizeof(int*));
}

int main() {
	int a = 0;
	int* p;
	fun(a++, a++, a++);

	return 0;
}

char* reverse(char* dest, int size) {
	char temp[2333];
	for (int i = size - 1; i >= 0; i--) {
		temp[size - i] = dest[i];
	}
	return temp;
}