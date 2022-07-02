#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct Fenwick
{
    int n;
    vector<ll> t;
    Fenwick(int _n) : n(_n + 1), t(_n + 1, 0) {}

    void update(int pos, ll dv)
    {
        pos++;
        for(; pos < n; pos += (pos & -pos)) t[pos] += dv;
    }

    ll query(int pos)
    {
        pos++;
        ll res = 0;
        for(; pos > 0; pos -= (pos & -pos)) res += t[pos];
        return res;
    }
};

void solve()
{
    int n;
    cin >> n;
    struct Query
    {
        ll t, a, b;
    };
    vector<Query> qList(n);
    vector<ll> vv;
    auto getvv = [](ll a, ll b) {
        if(b % a == 0) return b / a * 2;
        bool aPos = a > 0 ? true : false;
        bool bPos = b > 0 ? true : false;
        if(aPos == bPos) return b / a * 2 + 1;
        else return b / a * 2 - 1;
    };
    for(auto& q : qList) {
        cin >> q.t >> q.a;

        if(q.t == 1) {
            cin >> q.b;
            if(q.a == 0) continue;

            vv.push_back(getvv(q.a, q.b * (-1)));
        } else {
            vv.push_back(q.a * 2);
        }
    }

    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());
    auto getv = [&](ll a, ll b) {
        ll tmp = getvv(a, b);
        return lower_bound(vv.begin(), vv.end(), tmp) - vv.begin();
    };
    Fenwick fw(vv.size());

    bool isZero = false;
    set<int> has;
    int q1Num = 0, negANum = 0;
    for(auto [t, a, b] : qList) {
        if(t == 1) {
            if(a == 0) {
                if(b == 0) {
                    isZero = true;
                    continue;
                }
                if(b < 0) negANum++;
                continue;
            }

            b *= -1;
            int v = getv(a, b);
            fw.update(v, 1);
            has.insert(v);

            q1Num++;
            if(a < 0) negANum++;
        } else {
            if(isZero) {
                cout << "0\n";
                continue;
            }
            int v = getv(1, a);
            auto it = has.lower_bound(v);
            if(it != has.end() && *it == v) {
                cout << "0\n";
                continue;
            }

            ll num = fw.query(v);
            bool isPos = (q1Num & 1) ? false : true;
            if(negANum & 1) isPos = !isPos;
            if(num & 1) isPos = !isPos;

            if(isPos) cout << "+\n";
            else cout << "-\n";
        }
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
