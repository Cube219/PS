#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n;
int d[3000][3000];
int c1, c2, c3;

void p(int x, int y, int w){
	int t = d[x][y];
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
		if(t == -1)
			c1++;
		else if(t == 0)
			c2++;
		else
			c3++;

		return;
	}

	int w3 = w / 3;

	p(x, y, w3);
	p(x, y + w3, w3);
	p(x, y + w3 + w3, w3);

	p(x+w3, y, w3);
	p(x+w3, y + w3, w3);
	p(x+w3, y + w3 + w3, w3);

	p(x+w3+w3, y, w3);
	p(x + w3 + w3, y + w3, w3);
	p(x + w3 + w3, y + w3 + w3, w3);
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	cin >> n;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			scanf("%d", &d[i][j]);
		}
	}

	p(0, 0, n);

	cout << c1 << endl;
	cout << c2 << endl;
	cout << c3 << endl;

	return 0;
}
