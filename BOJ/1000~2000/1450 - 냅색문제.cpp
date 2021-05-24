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
ll c;
int d[31];
vector<ll> mp;
ll res;

void bt(int idx, ll v)
{
    if(idx == n / 2) {
        mp.push_back(v);
        return;
    }
    v += d[idx];
    bt(idx + 1, v);
    v -= d[idx];
    bt(idx + 1, v);
}

void bt2(int idx, ll v)
{
    if(idx == n) {
        ll remain = c - v;
        if(remain < 0) return;
        int idx = upper_bound(mp.begin(), mp.end(), remain) - mp.begin();
        res += idx;
        return;
    }
    v += d[idx];
    bt2(idx + 1, v);
    v -= d[idx];
    bt2(idx + 1, v);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> c;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    bt(0, 0);
    sort(mp.begin(), mp.end());
    bt2(n / 2, 0);

    cout << res;

    return 0;
}
