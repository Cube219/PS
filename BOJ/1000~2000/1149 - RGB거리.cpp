#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n;
int rgb[1001][3], d[1001][3];

int main(void)
{
	// freopen("input.txt", "r", stdin);

	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> rgb[i][0] >> rgb[i][1] >> rgb[i][2];
	}

	d[0][0] = rgb[0][0];
	d[0][1] = rgb[0][1];
	d[0][2] = rgb[0][2];

	for(int i = 1; i < n; i++) {
		for(int j = 0; j < 3; j++) {
			int min = 2147483647;
			for(int k = 0; k < 3; k++) {
				if(j == k)
					continue;

				if(d[i - 1][k] < min)
					min = d[i - 1][k];
			}

			d[i][j] = min + rgb[i][j];
		}
	}

	int min = 2147483647;
	for(int i = 0; i < 3; i++) {
		if(min > d[n - 1][i])
			min = d[n - 1][i];
	}
	cout << min;

	return 0;
}
