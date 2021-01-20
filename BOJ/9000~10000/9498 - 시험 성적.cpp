#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
using namespace std;

int main(void)
{
	int n;
	cin >> n;

	if(n >= 90) {
		cout << "A";
	} else if(n >= 80) {
		cout << "B";
	} else if(n >= 70) {
		cout << "C";
	} else if(n >= 60) {
		cout << "D";
	} else {
		cout << "F";
	}

	return 0;
}
