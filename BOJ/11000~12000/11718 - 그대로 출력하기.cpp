#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

char str[102];

int main(void)
{
	while(true) {
		char c = getchar();
		if(c == EOF)
			break;

		printf("%c", c);
	}

	return 0;
}
