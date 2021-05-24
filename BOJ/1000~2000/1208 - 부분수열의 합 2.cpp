#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, s, d[41];
int mp[8000001];
ll res;

void bt(int idx, int v)
{
    if(idx == n / 2) {
        mp[v + 4000000]++;
        return;
    }
    v += d[idx];
    bt(idx + 1, v);
    v -= d[idx];
    bt(idx + 1, v);
}

void bt2(int idx, int v)
{
    if(idx == n) {
        int remain = s - v;
        res += mp[remain + 4000000];
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

    cin >> n >> s;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    bt(0, 0);
    bt2(n / 2, 0);

    if(s == 0) res--;
    cout << res;

    return 0;
}
