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

void solve()
{
    int n, m;
    cin >> n >> m;
    struct Node
    {
        char ch;
        int v;
    };
    vector<Node> d(m);
    vector<char> use(n * 2 + 1, false);
    for(auto& v : d) {
        string tmp;
        cin >> v.ch >> tmp >> v.v;
        use[v.v] = true;
    }

    set<int> remain;
    for(int i = n * 2; i >= 1; --i) {
        if(!use[i]) remain.insert(i);
    }
    if(!use[1]) {
        cout << "NO";
        return;
    }

    struct Insert
    {
        int idx;
        int v;
        int nxt;
    };
    vector<Insert> p;
    for(int i = 1; i < m; ++i) {
        if(d[i - 1].ch == d[i].ch) {
            p.push_back({ i - 1, d[i - 1].v, -1 });
        }
    }
    sort(p.begin(), p.end(), [](const auto& l, const auto& r) {
        return l.v < r.v;
    });
    for(auto& cur : p) {
        auto it = remain.upper_bound(cur.v);
        if(it == remain.end()) {
            cout << "NO";
            return;
        }

        cur.nxt = *it;
        remain.erase(it);
    }

    int last = -1;
    if(remain.size() & 1) {
        auto it = prev(remain.end());
        last = *it;
        remain.erase(it);
    }

    sort(p.begin(), p.end(), [](const auto& l, const auto& r) {
        return l.idx > r.idx;
    });

    struct Res
    {
        char ch;
        bool isChain;
        int v;
    };
    vector<Res> res;

    for(int i = 0; i < m; ++i) {
        res.push_back({ d[i].ch, false, d[i].v });

        int cur = d[i].ch == 'A' ? 0 : 1;

        if(p.size() > 0 && p.back().idx == i) {
            Res tmp;
            tmp.isChain = true;
            if(d[i].ch == 'A') tmp.ch = 'B';
            else tmp.ch = 'A';

            cur = 1 - cur;

            tmp.v = p.back().nxt;
            res.push_back(tmp);

            p.pop_back();
        }

        if(d[i].v == 1) {
            while(remain.size() > 0) {
                cur = 1 - cur;

                Res tmp;
                tmp.isChain = true;
                if(cur == 0) tmp.ch = 'A';
                else tmp.ch = 'B';

                auto it = remain.begin();
                tmp.v = *it;
                remain.erase(it);

                res.push_back(tmp);
            }
        }
    }

    if(last != -1) {
        if(res.back().v >= last) {
            cout << "NO";
            return;
        }
        Res tmp;
        tmp.ch = res.back().ch == 'A' ? 'B' : 'A';
        tmp.isChain = true;
        tmp.v = last;
        res.push_back(tmp);
    }

    cout << "YES\n";
    for(auto& v : res) {
        cout << v.ch << " ";
        if(v.isChain) cout << "CHAIN ";
        else cout << "BLOCK ";
        cout << v.v << "\n";
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
