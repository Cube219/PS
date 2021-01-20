#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

int dayPerMon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};

int main(void)
{
	int m, d;
	cin >> m >> d;
	int gap = 0;
	for(int i = 1; i < m; i++) {
		gap += dayPerMon[i];
	}

	gap += d - 1;

	switch(gap % 7) {
	case 0:
		cout << "MON";
		break;
	case 1:
		cout << "TUE";
		break;
	case 2:
		cout << "WED";
		break;
	case 3:
		cout << "THU";
		break;
	case 4:
		cout << "FRI";
		break;
	case 5:
		cout << "SAT";
		break;
	case 6:
		cout << "SUN";
		break;
	}

	return 0;
}
