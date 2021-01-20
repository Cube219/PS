#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
using namespace std;

int main(void)
{
	int count = 0;
	while(true) {
		char c = getchar();
		if(c == EOF)
			break;

		count++;

		printf("%c", c);
		if(count == 10) {
			printf("\n");
			count = 0;
		}
	}

	return 0;
}
