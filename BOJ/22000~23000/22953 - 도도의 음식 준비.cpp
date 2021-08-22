#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999999;

int n, c;
ll a[11], k;
ll res = INF;

bool ck(ll m)
{
    ll cnt = 0;
    for(int i = 0; i < n; ++i) {
        cnt += m / a[i];
    }
    if(cnt < k) return false;
    else return true;
}

ll get()
{
    ll l = 0, r = 1000000000001;
    while(l + 1 < r) {
        ll m = (l + r) / 2;
        if(ck(m) == true) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

void bt(int idx, int curc)
{
    if(curc == 0 || idx == n) {
        res = min(res, get());
        return;
    }

    int lim = min((ll)curc, a[idx] - 1);
    for(int i = 0; i <= lim; ++i) {
        a[idx] -= i;
        bt(idx + 1, curc - i);
        a[idx] += i;
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> c;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    bt(0, c);

    cout << res;

    return 0;
}
