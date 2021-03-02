#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum = 1;
int n, m;
vector<int> g[51001];

int d[51001], dNum = 1;
vector<pair<int, int>> st;
vector<vector<int>> bccNode;
bool f[51001];
int cnt[51001];

void clear()
{
    for(int i = 1; i <= n; ++i) {
        g[i].clear();
        d[i] = 0;
        f[i] = false;
        cnt[i] = 0;
    }
    n = 0;
    dNum = 1;
    bccNode.clear();
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

            // if(t > d[cur]) {
            //     f[cur] = true;
            // }
            if(t >= d[cur]) {
                bccNode.push_back({});
                auto& cNode = bccNode.back();
                while(1) {
                    auto top = st.back();
                    st.pop_back();

                    if(d[top.first] < d[top.second]) {
                        cNode.push_back(top.second);
                    }

                    if(top.first == cur) break;
                }
                cNode.push_back(cur);
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

    while(1) {
        cin >> m;
        if(m == 0) break;

        n = 0;
        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
            if(n < a) n = a;
            if(n < b) n = b;
        }

        for(int i = 1; i <= n; ++i) {
            if(d[i] == 0) dfs(i, -1);
        }

        for(int i = 0; i < bccNode.size(); ++i) {
            auto& bccN = bccNode[i];
            for(int j = 0; j < bccN.size(); ++j) {
                cnt[bccN[j]]++;
            }
        }
        for(int i = 1; i <= n; ++i) {
            if(cnt[i] > 1) f[i] = true;
        }

        int cRes = 0;
        ll res = 1;
        for(int i = 0; i < bccNode.size(); ++i) {
            auto& bccN = bccNode[i];
            int num = 0;
            for(int j = 0; j < bccN.size(); ++j) {
                if(f[bccN[j]] == true) num++;
            }
            if(num == 1) {
                cRes++;
                if(bccN.size() > 1) {
                    res *= (bccN.size() - 1);
                }
            }
        }
        if(bccNode.size() == 1) {
            cRes = 2;
            ll num = bccNode[0].size();
            res = num * (num - 1) / 2;
        }

        cout << "Case " << tNum << ": " << cRes << " " << res << "\n";

        clear();
        tNum++;
    }

    return 0;
}
