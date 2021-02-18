#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int n, k;
int d[200001], d2[200001];
int num[200001];
int maxV;
 
int res;
 
int m, mIdx;
 
void next()
{
    mIdx++;
    if(num[m] <= mIdx) {
        for(int i = m + 1; i <= maxV; ++i) {
            if(num[i] > 0) {
                m = i;
                mIdx = 0;
                return;
            }
        }
    }
}
 
void prev()
{
    mIdx--;
    if(mIdx < 0) {
        for(int i = m - 1; i >= 1; --i) {
            if(num[i] > 0) {
                m = i;
                mIdx = num[i] - 1;
                return;
            }
        }
    }
}
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i];
        d2[i] = d[i];
        num[d[i]]++;
        if(maxV < d[i]) maxV = d[i];
    }
    sort(d2 + 1, d2 + n + 1);
    m = (n + 1) / 2;
    for(int i = 1; i <= n; ++i) {
        if(d2[i] == d2[m]) {
            mIdx = m - i;
            m = d2[m];
            break;
        }
    }
 
    res = m;
 
    int l = 1, r = n;
    while(r - l + 1 > k) {
        int removed = 0;
        if(d[l] < d[r]) {
            removed = d[l];
        } else {
            removed = d[r];
        }
 
        int nn = r - l + 1;
 
        if(m > removed) { // left
            if(nn % 2 == 0) {
                next();
            }
        } else if(m < removed) { // right
            if(nn % 2 == 1) {
                prev();
            }
        } else {
            if(num[m] == 1) {
                next();
            } else if(nn % 2 == 1) {
                prev();
            } else if(nn % 2 == 0 && num[m] - 1 == mIdx) {
                next();
            }
        }
 
        if(res < m) res = m;
 
        if(d[l] < d[r]) {
            num[d[l]]--;
            l++;
        } else {
            num[d[r]]--;
            r--;
        }
    }
 
    cout << res;
 
    return 0;
}
