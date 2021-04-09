#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;

ll n, k, p;
ll res;
map<ll, ll> rowXOR, colXOR;
map<ll, ll> rowCnt, colCnt;
map<pair<ll, ll>, ll> mp;

void add(ll r, ll c, ll x)
{
    res -= n - colCnt[rowXOR[r]];
    res -= n - rowCnt[colXOR[c]];
    rowCnt[rowXOR[r]]--;
    colCnt[colXOR[c]]--;

    rowXOR[r] ^= x;
    colXOR[c] ^= x;
    rowCnt[rowXOR[r]]++;
    colCnt[colXOR[c]]++;
    res += n - colCnt[rowXOR[r]];
    res += n - rowCnt[colXOR[c]];
}

void remove(ll r, ll c, ll x)
{
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> p;
    rowCnt[0] = n;
    colCnt[0] = n;
    for(int i = 0; i < k; ++i) {
        ll r, c, x;
        cin >> r >> c >> x;
        add(r, c, x);
        mp[{r, c}] = x;
    }
    for(int i = 0; i < p; ++i) {
        ll r1, r2, c1, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        ll pw = mp[{r1, c1}];
        mp.erase({ r1, c1 });
        add(r1, c1, pw);
        mp[{r2, c2}] = pw;
        add(r2, c2, pw);

        cout << res << "\n";
    }

    return 0;
}
