#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n, a;
long long int t[123457], att[123457], hp[123457];

int main(void)
{
	// freopen("input.txt", "r", stdin);

	cin >> n >> a;

	long long int l = 0, h = 0;
	for(int i = 0; i < n; i++) {
		cin >> t[i] >> att[i] >> hp[i];
		h += hp[i]*att[i];
	}
	while(l + 1 < h) {
		long long int mid = (l + h) / 2;

		long long int currentHP = mid;
		long long int currentAtt = a;
		bool isPossible = true;
		for(int i = 0; i < n; i++) {
			if(t[i] == 1) {
				long long int myAttackCount = (hp[i] + currentAtt - 1) / currentAtt;
				long long int monsterAttackCount = (currentHP + att[i] - 1) / att[i];

				if(myAttackCount > monsterAttackCount) {
					isPossible = false;
					break;
				} else {
					currentHP -= att[i] * (myAttackCount-1);
				}
			} else {
				currentHP += hp[i];
				currentAtt += att[i];
				if(currentHP > mid)
					currentHP = mid;
			}
		}

		if(isPossible == true) {
			h = mid;
		} else {
			l = mid;
		}
	}

	cout << h;

	return 0;
}
