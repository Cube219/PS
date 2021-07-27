#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

using ll = long long int;

ll n, w;
ll score[300005];
ll d[300005];

ll cnt;
ll rnk[300005], lastcnt[300005];
ll lazy[300005];

ll res[300005];

void prop(ll s)
{
    lazy[s] += rnk[s] * (cnt - lastcnt[s]);
    lastcnt[s] = cnt;
}

void process(ll a)
{
    ll s = score[a];
    prop(s); prop(s + 1);

    rnk[s]++;
    res[a] += lazy[s] - d[a];

    d[a] = lazy[s + 1];

    score[a] = s + 1;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> w;
    for(int i = 0; i <= w; ++i) {
        rnk[i] = 1;
    }
    for(int i = 0; i < w; ++i) {
        int num;
        cin >> num;
        for(int j = 0; j < num; ++j) {
            int a;
            cin >> a;
            a--;
            process(a);
        }
        cnt++;
    }

    for(int i = 0; i <= w; ++i) {
        prop(i);
    }
    for(int i = 0; i < n; ++i) {
        ll s = score[i];
        res[i] += lazy[s] - d[i];
    }

    cout << fixed << setprecision(10);
    for(int i = 0; i < n; ++i) {
        cout << (long double)res[i] / (long double)w << "\n";
    }

    return 0;
}
