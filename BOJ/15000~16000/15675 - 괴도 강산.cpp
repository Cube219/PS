#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
char map[1002][1002];
vector<int> g[4002];

int d[4002], dNum = 1;
bool finish[4002];
int scc[4002], sccNum;
vector<int> st;

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
        while(1) {
            int top = st.back();
            st.pop_back();

            scc[top] = sccNum;
            finish[top] = true;

            if(top == cur) break;
        }
        sccNum++;
    }

    return ret;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == '#') {
                int rowIdx = i * 2;
                int colIdx = n * 2 + j * 2;
                g[rowIdx].push_back(colIdx);
                g[colIdx].push_back(rowIdx);
                g[rowIdx + 1].push_back(colIdx + 1);
                g[colIdx + 1].push_back(rowIdx + 1);
            } else if(map[i][j] == '*') {
                int rowIdx = i * 2;
                int colIdx = n * 2 + j * 2;
                g[rowIdx].push_back(colIdx + 1);
                g[colIdx].push_back(rowIdx + 1);
                g[rowIdx + 1].push_back(colIdx);
                g[colIdx + 1].push_back(rowIdx);
            }
        }
    }

    int sz = n * 2 + m * 2;

    for(int i = 0; i < sz; ++i) {
        if(d[i] == 0) dfs(i);
    }

    bool res = true;
    for(int i = 0; i < sz; i += 2) {
        if(scc[i] == scc[i + 1]) {
            res = false;
            break;
        }
    }

    if(res == true) cout << "1";
    else cout << "0";

    return 0;
}
