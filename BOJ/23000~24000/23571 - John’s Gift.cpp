#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<int> a, b;

bool ck(int k)
{
    int i = n - 1;
    for(; i >= 0; --i) {
        if(abs(a[i] - b[i]) > k) break;
    }
    if(i <= 0) return true;

    int st = i - 1;
    i = st;
    // i - i+1
    for(; i >= 0; --i) {
        if(abs(a[i] - b[i + 1]) > k) break;
    }
    for(; i >= 0; --i) {
        if(abs(a[i] - b[i]) > k) break;
    }
    if(i < 0) return true;

    // i+1 - i
    i = st;
    for(; i >= 0; --i) {
        if(abs(a[i + 1] - b[i]) > k) break;
    }
    for(; i >= 0; --i) {
        if(abs(a[i] - b[i]) > k) break;
    }
    if(i < 0) return true;

    return false;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    a.resize(n); b.resize(n);
    for(int& v : a) cin >> v;
    for(int& v : b) cin >> v;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int lo = -1, hi = 1000000000;
    while(lo + 1 < hi) {
        int m = (lo + hi) / 2;
        if(ck(m)) {
            hi = m;
        } else {
            lo = m;
        }
    }

    int res = 1000000001;
    int i = n - 1;
    for(; i >= 0; --i) {
        if(abs(a[i] - b[i]) > hi) break;
    }
    if(i <= 0) {
        res = a[0];
    } else {
        int st = i - 1;
        // i - i+1
        i = st;
        for(; i >= 0; --i) {
            if(abs(a[i] - b[i + 1]) > hi) break;
        }
        for(; i >= 0; --i) {
            if(abs(a[i] - b[i]) > hi) break;
        }
        if(i < 0) res = a[st + 1];

        // i+1 - i
        i = st;
        for(; i >= 0; --i) {
            if(abs(a[i + 1] - b[i]) > hi) break;
        }
        int tmp = a[i + 1];
        for(; i >= 0; --i) {
            if(abs(a[i] - b[i]) > hi) break;
        }
        if(i < 0) res = tmp;
    }

    cout << res;

    return 0;
}
