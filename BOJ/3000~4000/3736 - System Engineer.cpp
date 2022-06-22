#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <string>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve(int n)
{
    vector<vector<int>> g(n);
    int m = n;
    for(int i = 0; i < n; ++i) {
        string buf;
        getline(cin, buf);

        int j = 0;
        int job = 0;
        while(buf[j] != ':') {
            job *= 10;
            job += buf[j++] - '0';
        }

        while(buf[j] != '(') j++;
        j++;
        int num = 0;
        while(buf[j] != ')') {
            num *= 10;
            num += buf[j++] - '0';
        }

        for(int k = 0; k < num; ++k) {
            while(buf[j] < '0' || '9' < buf[j]) j++;

            int com = 0;
            while('0' <= buf[j] && buf[j] <= '9') {
                com *= 10;
                com += buf[j++] - '0';
            }
            g[job].push_back(com - n);
        }
    }

    vector<int> a(n, -1), b(m, -1), level(n);
    auto initLevel = [&]() {
        queue<int> q;
        for(int i = 0; i < n; ++i) {
            if(a[i] == -1) {
                q.push(i);
                level[i] = 0;
            } else level[i] = -1;
        }
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(int nxt : g[cur]) {
                if(b[nxt] != -1 && level[b[nxt]] == -1) {
                    level[b[nxt]] = level[cur] + 1;
                    q.push(b[nxt]);
                }
            }
        }
    };
    auto dfs = [&](auto&& self, int cur) -> bool {
        for(int nxt : g[cur]) {
            if(b[nxt] == -1 || (level[b[nxt]] == level[cur] + 1 && self(self, b[nxt]))) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            }
        }
        return false;
    };
    int flow = 0;
    while(1) {
        initLevel();
        int f = 0;
        for(int i = 0; i < n; ++i) {
            if(a[i] == -1 && dfs(dfs, i)) f++;
        }
        if(f == 0) break;
        flow += f;
    }

    cout << flow << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(1) {
        int n;
        cin >> n;
        if(cin.eof()) break;

        string buf;
        getline(cin, buf);

        solve(n);
    }

    return 0;
}
