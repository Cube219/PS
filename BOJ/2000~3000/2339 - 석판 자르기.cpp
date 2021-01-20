#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n;
int d[20][20];
int cnt;

int p(int x, int y, int width, int height, int wh) // wh: 1->직전에 가로, 2-> 직전에 세로
{
	if(width == 0 || height == 0)
		return 0;

	int cNum = 0, bNum = 0;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if(d[x + i][y + j] == 2)
				cNum++;
			else if(d[x + i][y + j] == 1) {
				bNum++;
			}
		}
	}

	if(bNum == 0) {
		if(cNum == 1)
			return 1;
		else
			return 0;
	}

	int res = 0;
	if(wh != 1) {
		for(int i = 0; i < height; i++) {
			for(int j = 0; j < width; j++) {
				if(d[x + i][y + j] != 1)
					continue;

				// 가로로 자르기
				int temp = 1;
				bool isPossible = true;
				for(int k = 0; k < width; k++) {
					if(d[x + i][y + k] == 2) {
						isPossible = false;
						break;
					}
				}

				if(isPossible) {
					temp *= p(x, y, width, i, 1);
					if(temp != 0)
						temp *= p(x + i + 1, y, width, height - i - 1, 1);

					res += temp;

					break; // 해당 가로줄은 체크 X
				}
			}
		}
	}

	if(wh != 2) {
		for(int j = 0; j < width; j++) {
			for(int i = 0; i < height; i++) {
				if(d[x + i][y + j] != 1)
					continue;

				// 세로로 자르기
				int temp = 1;
				bool isPossible = true;
				for(int k = 0; k < height; k++) {
					if(d[x + k][y + j] == 2) {
						isPossible = false;
						break;
					}
				}
				if(isPossible) {
					temp *= p(x, y, j, height, 2);
					if(temp != 0)
						temp *= p(x, y + j + 1, width - j - 1, height, 2);

					res += temp;

					break; // 해당 세로줄은 체크 X
				}
			}
		}
	}

	return res;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	cin >> n;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			cin >> d[i][j];
		}
	}

	cnt = p(0, 0, n, n, 0);

	if(cnt == 0)
		cout << "-1";
	else
		cout << cnt;

	return 0;
}
