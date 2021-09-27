#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

using ll = long long int;

struct Range
{
    ll time;
    ll pos;
    ll epos;
    ll cnt;

    void calcnt(int l)
    {
        if(time < 0) cnt = 0;
        else {
            cnt = time / l + 1;
            cnt = min(cnt, epos - pos);
        }
    }

    bool operator<(const Range& rhs) const
    {
        return cnt < rhs.cnt;
    }
};

ll n;
int m, k;
int l, s, e;
int num;
ll t;
ll d[3001];
priority_queue<Range> pq;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    cin >> l >> e >> s;
    cin >> t;
    for(int i = 0; i < m; ++i) {
        cin >> d[i];
    }

    ll res = 0;
    for(int i = 0; i < m - 1; ++i) {
        Range r;
        r.time = t - (d[i] - 1) * e;
        r.pos = d[i];
        r.epos = d[i + 1];
        r.calcnt(l);

        res += r.cnt;
        r.pos += r.cnt;
        r.time -= r.cnt * s;
        r.calcnt(l);

        pq.push(r);
    }
    if((d[m - 1] - 1) * e <= t) res++;

    for(int i = 0; i < k - m; ++i) {
        Range r = pq.top();
        pq.pop();

        res += r.cnt;
        r.pos += r.cnt;
        r.time -= r.cnt * s;
        r.calcnt(l);

        pq.push(r);
    }

    cout << res - 1;

    return 0;
}
