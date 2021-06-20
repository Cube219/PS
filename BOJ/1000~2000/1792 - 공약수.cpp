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

ll mobi[50001];
ll msum[50001];

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

    for(int i = 1; i <= r; ++i) {
        if(mobi[i] < 0) mobi[i] = 0;
        else if(mobi[i] % 2 == 1) mobi[i] = -1;
        else mobi[i] = 1;

        msum[i] = msum[i - 1] + mobi[i];
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init(50000);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; ++tt) {
        int a, b, d;
        cin >> a >> b >> d;

        int ed = min(a / d, b / d);

        ll res = 0;
        for(int i = 1; i <= ed;) {
            ll av = a / (i * d);
            ll bv = b / (i * d);
            if(av == 0 || bv == 0) break;
            
            int lastaidx = a / (d * av);
            int lastbidx = b / (d * bv);
            int lastidx = min(lastaidx, lastbidx);
            res += (msum[lastidx] - msum[i - 1]) * av * bv;
            i = lastidx + 1;
        }

        cout << res << "\n";
    }

    return 0;
}
