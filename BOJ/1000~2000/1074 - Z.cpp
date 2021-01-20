#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n, r, c;

int answer;

void p(int x, int y, int start, int w)
{
	if(w == 1) {
		answer = start;
		return;
	}

	int pivotX = x + (w/2);
	int pivotY = y + (w/2);

	int gap = w * w / 4;

	if(r < pivotX) {
		if(c < pivotY) {
			p(x, y, start, w / 2);
		} else {
			p(x, pivotY, start + gap, w / 2);
		}
	} else {
		if(c < pivotY) {
			p(pivotX, y, start + gap + gap, w / 2);
		} else {
			p(pivotX, pivotY, start + gap + gap + gap, w / 2);
		}
	}
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	cin >> n >> r >> c;

	int twoOverN = 1;
	for(int i = 1; i <= n; i++) {
		twoOverN *= 2;
	}

	p(0, 0, 0, twoOverN);

	cout << answer;

	return 0;
}
