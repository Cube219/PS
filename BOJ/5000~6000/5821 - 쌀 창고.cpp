#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using lli = long long int;

int r;
lli l, b;
lli x[100001];
lli sumLeft[100001], sumRight[100001];
lli res = -1;

lli p(int left, int right)
{
    int mid = (left + right) / 2;

    lli lSum = sumLeft[mid] - sumLeft[left];
    lSum -= (x[mid] - x[left]) * left;
    lli rSum = sumRight[mid] - sumRight[right];
    rSum -= (x[right] - x[mid]) * (r - right - 1);

    return lSum + rSum;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> r >> l >> b;
    for(int i = 0; i < r; i++) {
        cin >> x[i];
    }

    int currentNum = 1;
    for(int i = 1; i < r; i++) {
        if(x[i - 1] == x[i]) {
            sumLeft[i] = sumLeft[i - 1];
            currentNum++;
            continue;
        }

        lli gap = x[i] - x[i - 1];
        sumLeft[i] = sumLeft[i - 1] + gap * currentNum;
        currentNum++;
    }

    currentNum = 1;
    for(int i = r - 2; i >= 0; i--) {
        if(x[i] == x[i + 1]) {
            sumRight[i] = sumRight[i + 1];
            currentNum++;
            continue;
        }

        lli gap = x[i + 1] - x[i];
        sumRight[i] = sumRight[i + 1] + gap * currentNum;
        currentNum++;
    }

    lli left = 1, right = r;
    while(left <= right) {
        lli mid = (left + right) / 2;
        bool isPos = false;
        for(int i = 0; i <= r - mid; i++) {
            lli totalSum = p(i, i + mid - 1);
            if(totalSum <= b) {
                isPos = true;
                break;
            }
        }

        if(isPos == true) {
            if(mid > res) res = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << res;

    return 0;
}
