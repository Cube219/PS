#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int v, e;
vector<int> g[10001];
vector<vector<int>> res;

int d[10001];
int dCnt = 1;
bool comp[10001];
vector<int> st;

int dfs(int cur)
{
    d[cur] = dCnt++;
    st.push_back(cur);

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(d[nxt] == 0) {
            ret = min(ret, dfs(nxt));
        } else if(comp[nxt] == false) {
            ret = min(ret, d[nxt]);
        }
    }

    if(ret == d[cur]) {
        res.push_back({});
        while(st.back() != cur) {
            res.back().push_back(st.back());
            comp[st.back()] = true;
            st.pop_back();
        }
        st.pop_back();
        res.back().push_back(cur);
        sort(res.back().begin(), res.back().end());
        comp[cur] = true;
    }
    return ret;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> v >> e;
    for(int i = 0; i < e; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    for(int i = 1; i <= v; ++i) {
        if(d[i] == 0) dfs(i);
    }
    sort(res.begin(), res.end(), [](const vector<int>& l, const vector<int>& r) { return l.front() < r.front(); });

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        for(int j = 0; j < res[i].size(); ++j) {
            cout << res[i][j] << " ";
        }
        cout << "-1\n";
    }

    return 0;
}
