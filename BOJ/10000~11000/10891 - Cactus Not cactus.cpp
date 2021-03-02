#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[100001];
bool res = true;

int d[100001], dNum = 1;
vector<vector<int>> bccNode;
vector<pair<int, int>> st1;
bool has[100001];
int cnt[100001];

int dfs(int cur, int prev)
{
    d[cur] = dNum++;

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(nxt == prev) continue;

        if(d[cur] > d[nxt]) {
            st1.push_back({ cur, nxt });
        }

        if(d[nxt] != 0) ret = min(ret, d[nxt]);
        else {
            int t = dfs(nxt, cur);

            if(t >= d[cur]) {
                int eNum = 0, vNum = 1;
                bccNode.push_back({});
                auto& cbccNode = bccNode.back();
                while(1) {
                    auto top = st1.back();
                    st1.pop_back();
                    eNum++;

                    if(d[top.first] < d[top.second]) {
                        vNum++;
                        cbccNode.push_back(top.second);
                    }

                    if(top.first == cur) break;
                }
                cbccNode.push_back(cur);
                if(vNum < eNum) {
                    res = false;
                }
                if(vNum == eNum) {
                } else {
                    bccNode.pop_back();
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

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(int i = 1; i <= n; i++) {
        if(d[i] == 0) {
            dfs(i, -1);
        }
    }

    for(int i = 0; i < bccNode.size(); ++i) {
        auto& cbccNode = bccNode[i];
        for(int j = 0; j < cbccNode.size(); ++j) {
            cnt[cbccNode[j]]++;
        }
    }

    for(int i = 1; i <= n; ++i) {
        if(cnt[i] > 1) {
            res = false;
            break;
        }
    }

    if(res == true) cout << "Cactus";
    else cout << "Not cactus";

    return 0;
}
