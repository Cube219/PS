#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int nn, mm, aa[200001], bb[200001];
vector<int> a, b;
int d[200001];

int process()
{
    int n = a.size();
    int m = b.size();
    if(n == 0 || m == 0) return 0;

    for(int i = 0; i < n; ++i) {
        d[i] = 0;
    }

    int i = 0, j = 0;
    while(i < n && j < m) {
        if(a[i] == b[j]) {
            d[i]++;
            i++;
            j++;
            d[i] = d[i - 1];
        } else if(a[i] < b[j]) {
            i++;
            d[i] = d[i - 1];
        } else {
            j++;
        }
    }
    while(i < n) {
        d[i] = d[i - 1];
        i++;
    }

    int res = 0;

    int l = 0, r = 0;
    while(l < m && r < m) {
        auto it = upper_bound(a.begin(), a.end(), b[r]);
        if(it == a.begin()) {
            r++;
            if(r == m) break;
            continue;
        }
        --it;
        int cnt = it - a.begin() + 1;
        while(cnt < b[r] - b[l] + 1) {
            l++;
        }
        int mx = r - l + 1;
        mx += d[n - 1] - d[cnt - 1];


        res = max(res, mx);
        r++;
    }

    return res;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> nn >> mm;
        for(int i = 0; i < nn; ++i) {
            cin >> aa[i];
        }
        for(int i = 0; i < mm; ++i) {
            cin >> bb[i];
        }

        int res = 0;
        for(int i = 0; i < nn; ++i) {
            if(aa[i] > 0) a.push_back(aa[i]);
        }
        for(int i = 0; i < mm; ++i) {
            if(bb[i] > 0) b.push_back(bb[i]);
        }
        res += process();
        a.clear();
        b.clear();
        for(int i = nn - 1; i >= 0; --i) {
            if(aa[i] < 0) a.push_back(-aa[i]);
        }
        for(int i = mm - 1; i >= 0; --i) {
            if(bb[i] < 0) b.push_back(-bb[i]);
        }
        res += process();
        a.clear();
        b.clear();

        cout << res << "\n";
    }

    return 0;
}
