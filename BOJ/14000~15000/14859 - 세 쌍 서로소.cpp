#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;

ll mobi[1000001];
int n;
int cnt[1000001];

void init(ll r)
{
    for(ll i = 2; i <= r; ++i) {
        if(mobi[i] != 0) continue;
        for(ll j = i; j <= r; j += i) {
            mobi[j]++;
        }
        for(ll j = i * i; j <= r; j += i * i) {
            mobi[j] = -10000000000000;
        }
    }
    mobi[1] = 2;
}

ll copnum(ll r)
{
    ll res = 0;
    for(ll i = 1; i <= r; ++i) {
        if(mobi[i] <= 0) continue;

        ll v = 0;
        for(int j = i; j <= r; j += i) {
            v += cnt[j];
        }

        if(mobi[i] % 2 == 1) res -= v * (v - 1) * (v - 2);
        else res += v * (v - 1) * (v - 2);
    }

    return res / 6;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    int maxa = 0;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        cnt[a]++;
        maxa = max(maxa, a);
    }
    init(maxa);

    cout << copnum(maxa);

    return 0;
}
