#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
using namespace std;

int main(void)
{
	const char* a = R"AAA(|\_/|
|q p|   /}
( 0 )"""\
|"^"`    |
||_/=\\__|)AAA";
	printf("%s", a);

	return 0;
}
