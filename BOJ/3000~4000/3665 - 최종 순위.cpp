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
int d[501];
int idx[501];

vector<int> g[501];
int in[501];
int ck[501][501];
queue<int> q;

vector<int> res;
int state;

void init()
{
    for(int i = 1; i <= n; ++i) {
        in[i] = 0;
        g[i].clear();
        for(int j = 1; j <= n; ++j) {
            ck[i][j] = 0;
        }
    }
    while(q.empty() == false) q.pop();
    state = 0;
    res.clear();
}
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;

        init();

        for(int i = 0; i < n; ++i) {
            cin >> d[i];
            idx[d[i]] = i;
        }

        cin >> m;
        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;

            int aIdx = idx[a];
            int bIdx = idx[b];

            if(aIdx < bIdx) {
                swap(a, b);
                swap(aIdx, bIdx);
            }
            g[a].push_back(b);
            in[b]++;

            ck[a][b] = ck[b][a] = 1;
        }

        for(int i = 0; i < n - 1; ++i) {
            for(int j = i + 1; j < n; ++j) {
                int a = d[i];
                int b = d[j];
                if(ck[a][b] == 1) continue;

                g[a].push_back(b);
                in[b]++;
            }
        }

        for(int i = 1; i <= n; ++i) {
            if(in[i] == 0) {
                q.push(i);
            }
        }

        while(q.empty() == false) {
            if(q.size() > 1) {
                state = 1;
                break;
            }

            int cur = q.front();
            q.pop();
            res.push_back(cur);

            for(auto nxt : g[cur]) {
                in[nxt]--;
                if(in[nxt] == 0) {
                    q.push(nxt);
                }
            }
        }

        if(state == 1) {
            cout << "?\n";
        } else if(res.size() != n) {
            cout << "IMPOSSIBLE\n";
        } else {
            for(int i = 0; i < n; ++i) {
                cout << res[i] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
