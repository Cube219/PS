#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    struct Node
    {
        bool down;
        ll sum;
        int cnt;
        vector<ll> d;
    };

    ll n, x;
    cin >> n;
    vector<ll> a(n);
    for(auto& v : a) cin >> v;
    cin >> x;

    vector<Node> d;
    int res = 0;
    for(int i = 0; i < n; ++i) {
        ll v = a[i];
        if(v >= x) {
            if(d.size() == 0 || d.back().down == true) {
                d.push_back({ false, 0, 0, {} });
            }
            d.back().sum += v;
            d.back().cnt++;
            d.back().d.push_back(v);
            res++;
        } else {
            if(d.size() == 0 || d.back().down == false) {
                d.push_back({ true, 0, 0, {} });
            }
            d.back().sum += v;
            d.back().cnt++;
            d.back().d.push_back(v);
        }
    }

    for(int i = 0; i < d.size(); ++i) {
        if(d[i].down == false) continue;

        ll tcnt = 0;
        ll tsum = 0;

        if(d[i].cnt % 2 == 0) {
            // 한쪽만 붙이기
            if(i == 0 || i == d.size() - 1) {
                res += d[i].cnt / 2;
                continue;
            }
            // 왼쪽
            tcnt = d[i - 1].cnt + 1;
            tsum = d[i - 1].sum + d[i].d[0];
            if(tsum >= x * tcnt && d[i - 1].d.back() + d[i].d[0] >= x * 2) {
                res += d[i].cnt / 2;
                continue;
            }

            // 오른쪽
            tcnt = d[i + 1].cnt + 1;
            tsum = d[i + 1].sum + d[i].d.back();
            if(tsum >= x * tcnt && d[i + 1].d[0] + d[i].d.back() >= x * 2) {
                res += d[i].cnt / 2;
                d[i + 1].sum = tsum;
                d[i + 1].cnt = tcnt;
                continue;
            }

            // 안 붙이기
            res += d[i].cnt / 2 - 1;
        } else {
            // 양쪽 붙이기
            ll lcnt = 0, lsum = 1, rcnt = 0, rsum = 1;
            ll lcnt2 = 0, lsum2 = 1, rcnt2 = 0, rsum2 = 1;
            if(i > 0) {
                lcnt = d[i - 1].cnt + 1;
                lsum = d[i - 1].sum + d[i].d[0];
                lcnt2 = 2;
                lsum2 = d[i - 1].d.back() + d[i].d[0];
            }
            if(i < (int)d.size() - 1) {
                rcnt = d[i + 1].cnt + 1;
                rsum = d[i + 1].sum + d[i].d.back();
                rcnt2 = 2;
                rsum2 = d[i + 1].d[0] + d[i].d.back();
            }


            if(lsum >= x * lcnt && rsum >= x * rcnt && lsum2 >= x * lcnt2 && rsum2 >= x * rcnt2) {
                res += d[i].cnt / 2 + 1;
                if(i < (int)d.size() - 1) {
                    d[i + 1].sum = rsum;
                    d[i + 1].cnt = rcnt;
                }
                continue;
            }

            // 안 붙이기
            res += d[i].cnt / 2;
        }
    }

    cout << res << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
