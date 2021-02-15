#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n1, n2, n3, n4;
pair<int, int> a[201], b[201], c[201], d[201];
int idxa[201], idxb[201], idxc[201], idxd[201];
int m1, m2, m3;
pair<int, int> d1[201], d2[201], d3[201];

ll dp[201][4];
int block[200001];
ll res = 9999999999;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n1 >> n2 >> n3 >> n4;
    for(int i = 0; i < n1; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    for(int i = 0; i < n2; ++i) {
        cin >> b[i].first;
        b[i].second = i;
    }
    for(int i = 0; i < n3; ++i) {
        cin >> c[i].first;
        c[i].second = i;
    }
    for(int i = 0; i < n4; ++i) {
        cin >> d[i].first;
        d[i].second = i;
    }
    sort(a, a + n1);
    sort(b, b + n2);
    sort(c, c + n3);
    sort(d, d + n4);
    a[n1].first = 9999999999;
    b[n2].first = 9999999999;
    c[n3].first = 9999999999;
    d[n4].first = 9999999999;

    for(int i = 0; i < n1; ++i) {
        idxa[a[i].second] = i;
    }
    for(int i = 0; i < n2; ++i) {
        idxb[b[i].second] = i;
    }
    for(int i = 0; i < n3; ++i) {
        idxc[c[i].second] = i;
    }
    for(int i = 0; i < n4; ++i) {
        idxd[d[i].second] = i;
    }

    cin >> m1;
    for(int i = 0; i < m1; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        d1[i].first = idxa[l];
        d1[i].second = idxb[r];
    }
    cin >> m2;
    for(int i = 0; i < m2; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        d2[i].first = idxb[l];
        d2[i].second = idxc[r];
    }
    cin >> m3;
    for(int i = 0; i < m3; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        d3[i].first = idxc[l];
        d3[i].second = idxd[r];
    }
    sort(d1, d1 + m1);
    sort(d2, d2 + m2);
    sort(d3, d3 + m3);

    for(int i = 0; i < n2; ++i) {
        dp[i][0] = a[0].first;
        block[i] = 0;
    }
    for(int i = 0; i < m1; ++i) {
        int left = d1[i].first;
        int right = d1[i].second;

        if(block[right] == left) {
            block[right]++;
            dp[right][0] = a[left + 1].first;
        }
    }
    for(int i = 0; i < n3; ++i) {
        dp[i][1] = b[0].first;
        block[i] = 0;
    }
    for(int i = 0; i < m2; ++i) {
        int left = d2[i].first;
        int right = d2[i].second;

        if(block[right] == left) {
            block[right]++;
            dp[right][1] = b[left + 1].first;
        }
    }
    for(int i = 0; i < n4; ++i) {
        dp[i][2] = c[0].first;
        block[i] = 0;
    }
    for(int i = 0; i < m3; ++i) {
        int left = d3[i].first;
        int right = d3[i].second;

        if(block[right] == left) {
            block[right]++;
            dp[right][2] = c[left + 1].first;
        }
    }

    for(int i = 0; i < n4; ++i) {
        ll tmp = 0;
        tmp = d[i].first;

        int idx = dp[i][2];
        tmp += c[idx].first;
        idx = dp[i][1];
        tmp += b[idx].first;
        idx = dp[i][0];
        tmp += a[idx].first;

        if(res > tmp) res = tmp;
    }

    if(res == 9999999999) res = -1;
    cout << res;

    return 0;
}
