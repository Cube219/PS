#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n;
char d[66][66];
char buf[100000];
int bufNum = 0;

void p(int x, int y, int w)
{
	char t = d[x][y];
	bool b = true;
	for(int i = 0; i < w; i++) {
		for(int j = 0; j < w; j++) {
			if(t != d[x + i][y + j]) {
				b = false;
				break;
			}
		}
	}

	if(b == true) {
		buf[bufNum++] = t;
		return;
	}

	// Divide
	buf[bufNum++] = '(';
	int w2 = w / 2;
	p(x, y, w2);
	p(x, y + w2, w2);
	p(x + w2, y, w2);
	p(x + w2, y + w2, w2);
	buf[bufNum++] = ')';
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> d[i];
	}

	p(0, 0, n);

	buf[bufNum] = '\0';

	cout << buf;

	return 0;
}
