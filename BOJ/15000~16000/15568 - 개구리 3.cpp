#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

vector<int> g[6002];

int d[6002], dNum = 1;
bool finish[6002];
vector<int> st;
vector<vector<int>> sccs;
int sccIdx[6002];

int dfs(int cur)
{
    d[cur] = dNum++;
    st.push_back(cur);

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(d[nxt] == 0) ret = min(ret, dfs(nxt));
        else if(finish[nxt] == false) ret = min(ret, d[nxt]);
    }

    if(ret == d[cur]) {
        sccs.push_back({});
        auto& scc = sccs.back();
        while(1) {
            int top = st.back();
            st.pop_back();

            scc.push_back(top);
            sccIdx[top] = sccs.size();
            finish[top] = true;

            if(top == cur) break;
        }
    }
    return ret;
}

int n, m;
int f[3001][5];
pair<int, int> y[3001];
vector<pair<int, bool>> possible[3001];
bool res;
int res2[3001];
int var[3001];

int rev(int v)
{
    if(v % 2 == 0) return v + 1;
    return v - 1;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> f[i][1] >> f[i][2] >> f[i][3] >> f[i][4];
    }
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        possible[a].push_back({ i, false });
        possible[b].push_back({ i, true });
        y[i] = { a, b };
    }
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(i == j) continue;
            if(y[i].first == y[j].first) {
                g[i * 2].push_back(j * 2 + 1);
                g[j * 2].push_back(i * 2 + 1);
            }
            if(y[i].first == y[j].second) {
                g[i * 2].push_back(j * 2);
                g[j * 2 + 1].push_back(i * 2 + 1);
            }
            if(y[i].second == y[j].first) {
                g[i * 2 + 1].push_back(j * 2 + 1);
                g[j * 2].push_back(i * 2);
            }
            if(y[i].second == y[j].second) {
                g[i * 2 + 1].push_back(j * 2);
                g[j * 2 + 1].push_back(i * 2);
            }
        }
    }
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        for(auto& p1 : possible[a]) {
            for(auto& p2 : possible[b]) {
                if(f[p1.first][c] == f[p2.first][c]) continue;

                int p1v = p1.first * 2;
                if(p1.second == true) p1v++;
                int p2v = p2.first * 2;
                if(p2.second == true) p2v++;
                g[p1v].push_back(rev(p2v));
                g[p2v].push_back(rev(p1v));
            }
        }
    }

    for(int i = 0; i < n * 2; ++i) {
        if(d[i] == 0) dfs(i);
    }

    res = true;
    for(int i = 0; i < n * 2; i += 2) {
        if(sccIdx[i] == sccIdx[i + 1]) {
            res = false;
            break;
        }
    }
    if(res == true) {
        for(int i = sccs.size() - 1; i >= 0; --i) {
            auto& scc = sccs[i];
            for(int j = 0; j < scc.size(); ++j) {
                int v = scc[j];
                if(var[v / 2] == 0) {
                    var[v / 2] = (v % 2 == 0) ? 1 : -1;
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            int tmp;
            if(var[i] == -1) {
                tmp = y[i].first;
            } else {
                tmp = y[i].second;
            }
            res2[tmp] = i + 1;
        }
        for(int i = 0; i < n; ++i) {
            if(res2[i] == 0) res = false;
        }
    }
    if(res == true) {
        cout << "YES\n";
        for(int i = 0; i < n; ++i) {
            cout << res2[i] << " ";
        }
    } else {
        cout << "NO";
    }

    return 0;
}
