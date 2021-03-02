#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

constexpr ll INF = 200000000000000000;

int n;
ll dis;
ll d[1000001], r[1000001];
ll res = INF;

void p()
{
    ll mn = INF;
    int mnIdx = 0;
    for(ll i = 0; i < n; ++i) {
        ll tmp = d[0] + dis * i;
        r[i] = d[i] - tmp;
        if(mn > r[i]) {
            mn = r[i];
            mnIdx = i;
        }
    }
    if(mn < 0) {
        ll v = -r[mnIdx];
        for(int i = 0; i < n; ++i) {
            r[i] += v;
        }
    }

    ll mx = -1;
    for(int i = 0; i < n; ++i) {
        if(mx < r[i]) mx = r[i];
    }
    if(res > mx) res = mx;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> dis;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    p();
    for(int i = 0; i < n; ++i) {
        d[i] = -d[i];
    }
    p();
    

    if(res % 2 == 0) {
        cout << res / 2 << ".0";
    } else {
        cout << res / 2 << ".5";
    }

    return 0;
}
