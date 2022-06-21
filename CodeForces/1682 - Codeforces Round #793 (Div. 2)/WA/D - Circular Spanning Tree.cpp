#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    string d;
    cin >> d;

    if((n & 1) == 0) {
        bool f = true;
        for(char v : d) if(v == '0') f = false;

        if(f) {
            cout << "YES\n";
            for(int i = 2; i <= n; ++i) {
                cout << "1 " << i << "\n";
            }
            return;
        }
    }

    struct Edge
    {
        int u, v;
    };
    vector<Edge> res;

    auto ck = [&](int st) {
        res.clear();
        vector<int> deg(n, 0);
        auto addEdge = [&](int u, int v) {
            res.push_back({ u, v });
            deg[u]++; deg[v]++;
        };
        addEdge(st, (st + 1) % n);

        int last = (st + 1) % n;
        int cur = (last + 1) % n;
        int remainR = 0;
        while(cur != st) {
            if(d[cur] == '0') {
                addEdge(last, cur);
                if((deg[last] + remainR) & 1) {
                    if(remainR == 0) {
                        int back = (st - 1 + n) % n;
                        if(d[back] == '0') {
                            return false;
                        }
                        addEdge(last, back);
                        st = back;
                    } else {
                        addEdge(cur, (cur - 1 + n) % n);
                        remainR--;
                    }
                }
                for(int i = 1; i <= remainR; ++i) {
                    addEdge(last, (last + i) % n);
                }
                remainR = 0;
                last = cur;
            } else {
                remainR++;
            }
            cur = (cur + 1) % n;
        }
        if((deg[last] + remainR) & 1) {
            return false;
        }

        for(int i = 1; i <= remainR; ++i) {
            addEdge(last, (last + i) % n);
        }
        return true;
    };

    for(int i = 0; i < n; ++i) {
        if(d[i] == '1' && d[(i + 1) % n] == '0') {
            if(ck(i)) {
                cout << "YES\n";
                for(auto [u, v] : res) {
                    cout << u + 1 << " " << v + 1 << "\n";
                }
                return;
            }
        }
    }

    reverse(d.begin(), d.end());
    for(int i = 0; i < n; ++i) {
        if(d[i] == '1' && d[(i + 1) % n] == '0') {
            if(ck(i)) {
                cout << "YES\n";
                for(auto [u, v] : res) {
                    cout << n - u << " " << n - v << "\n";
                }
                return;
            }
        }
    }

    cout << "NO\n";
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
