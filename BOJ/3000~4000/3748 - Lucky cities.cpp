#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
vector<int> g[100001];

vector<pair<int, int>> st;
int d[100001], dNum = 1;
vector<vector<pair<int, int>>> bcc;

queue<pair<int, int>> q;
vector<int> g2[100001];
bool has[100001];
int depth[100001];
int res;

void init()
{
    st.clear();
    bcc.clear();
    for(int i = 1; i <= n; ++i) {
        g[i].clear();
        d[i] = 0;
        has[i] = false;
    }
    dNum = 1;
    res = 0;
}

int dfs(int cur, int prev)
{
    d[cur] = dNum++;

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(nxt == prev) continue;
        if(d[cur] > d[nxt]) {
            st.push_back({ cur, nxt });
        }

        if(d[nxt] != 0) ret = min(ret, d[nxt]);
        else {
            int t = dfs(nxt, cur);
            if(t >= d[cur]) {
                bcc.push_back({});
                vector<pair<int, int>>& nbcc = bcc.back();
                while(1) {
                    auto top = st.back();
                    st.pop_back();

                    nbcc.push_back(top);
                    if(top.first == cur) break;
                }
            }
            ret = min(ret, t);
        }

    }

    return ret;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        init();
        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        for(int i = 1; i <= n; ++i) {
            if(d[i] == 0) dfs(i, -1);
        }

        for(auto& b : bcc) {
            for(int i = 0; i < b.size(); ++i) {
                g2[b[i].first].push_back(b[i].second);
                g2[b[i].second].push_back(b[i].first);
            }
            bool pos = false;
            q.push({ b[0].first, 1 });
            while(q.empty() == false) {
                int cur = q.front().first;
                int dep = q.front().second;
                q.pop();
                depth[cur] = dep;

                for(int nxt : g2[cur]) {
                    if(depth[nxt] == 0) {
                        q.push({ nxt, dep + 1 });
                    } else if(depth[nxt] == dep) {
                        pos = true;
                        break;
                    }
                }
                if(pos == true) {
                    while(q.empty() == false) q.pop();
                    break;
                }
            }
            if(pos == true) {
                for(int i = 0; i < b.size(); ++i) {
                    has[b[i].first] = true;
                    has[b[i].second] = true;
                }
            }
            for(int i = 0; i < b.size(); ++i) {
                int n1 = b[i].first;
                int n2 = b[i].second;
                g2[n1].clear();
                g2[n2].clear();
                depth[n1] = 0;
                depth[n2] = 0;
            }
        }

        for(int i = 1; i <= n; ++i) {
            if(has[i] == true) res++;
        }
        cout << res << endl;
    }

    return 0;
}
