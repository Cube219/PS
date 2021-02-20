#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
char str[301][301];
vector<int> g[301];

int scc[301], sNum;
int sccFirst[301];

int d[301], dNum = 1;
vector<int> st;
bool finish[301];
bool connected[301][301];

vector<pair<int, int>> res;

int dfs(int cur)
{
    st.push_back(cur);
    d[cur] = dNum++;

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(d[nxt] == 0) ret = min(ret, dfs(nxt));
        else if(finish[nxt] == false) ret = min(ret, d[nxt]);
    }

    if(ret == d[cur]) {
        while(1) {
            int top = st.back();
            st.pop_back();

            scc[top] = sNum;
            finish[top] = true;

            if(top == cur) break;
        }
        sccFirst[sNum] = cur;
        sNum++;
    }

    return ret;
}

void init()
{
    st.clear();
    for(int i = 0; i < n; ++i) {
        g[i].clear();
        d[i] = 0;
        finish[i] = false;
        for(int j = 0; j < n; ++j) {
            connected[i][j] = false;
        }
    }

    for(int i = 0; i < sNum; ++i) {
        scc[i] = 0;
    }
    sNum = 0;
    dNum = 1;
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
            cin >> str[i];
            for(int j = 0; j < n; ++j) {
                if(i == j) continue;
                if(str[i][j] == '1') {
                    g[i].push_back(j);
                    // connected[i][j] = true;
                }
            }
        }

        for(int i = 0; i < n; ++i) {
            if(finish[i] == false) {
                dfs(i);
            }
        }

        for(int i = 0; i < n; ++i) {
            for(int j : g[i]) {
                if(scc[i] != scc[j]) {
                    connected[scc[i]][scc[j]] = true;
                }
            }
        }

        for(int k = 0; k < sNum; ++k) {
            for(int i = 0; i < sNum; ++i) {
                for(int j = 0; j < sNum; ++j) {
                    if(connected[i][j] && connected[i][k] && connected[k][j]) {
                        connected[i][j] = false;
                    }
                }
            }
        }

        vector<int> tmp;
        for(int i = 0; i < sNum; ++i) {
            tmp.clear();
            for(int j = 0; j < n; ++j) {
                if(scc[j] == i) tmp.push_back(j);
            }

            if(tmp.size() > 1) {
                for(int j = 0; j < tmp.size() - 1; ++j) {
                    res.push_back({ tmp[j], tmp[j + 1] });
                }
                res.push_back({ tmp.back(), tmp.front() });
            }
        }

        for(int i = 0; i < sNum; ++i) {
            for(int j = 0; j < sNum; ++j) {
                if(connected[i][j] == true) {
                    res.push_back({ sccFirst[i], sccFirst[j] });
                }
            }
        }

        cout << res.size() << "\n";
        for(int i = 0; i < res.size(); ++i) {
            cout << res[i].first + 1 << " " << res[i].second + 1 << "\n";
        }
    }

    return 0;
}
