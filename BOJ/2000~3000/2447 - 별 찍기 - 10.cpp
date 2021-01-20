#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n;

int answer;

char d[7000][7000];
int width;

int main(void)
{
	d[0][0] = '*';
	width = 1;
	// freopen("input.txt", "r", stdin);
	
	cin >> n;

	while(n > 1) {
		for(int sx = 0; sx < width; sx++) {
			for(int sy = 0; sy < width; sy++) {
				d[sx][sy + width] = d[sx][sy];
				d[sx][sy + width + width] = d[sx][sy];

				d[sx + width][sy] = d[sx][sy];
				d[sx + width][sy + width + width] = d[sx][sy];

				d[sx + width + width][sy] = d[sx][sy];
				d[sx + width + width][sy + width] = d[sx][sy];
				d[sx + width + width][sy + width + width] = d[sx][sy];
			}
		}

		width *= 3;

		n /= 3;
	}

	for(int i = 0; i < width; i++) {
		for(int j = 0; j < width; j++) {
			if(d[i][j] == '*')
				cout << d[i][j];
			else
				cout << ' ';
		}
		cout << endl;
	}

	return 0;
}
