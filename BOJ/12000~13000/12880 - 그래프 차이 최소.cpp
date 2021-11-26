#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

template <int N>
struct SCC
{
    int d[N], dNum = 1;
    bool finish[N];
    vector<int> st;
    int sccIdx[N];
    int sccNum;

    vector<vector<int>> g;
    int n;
    int mn, mx;

    void init(vector<vector<int>> _g)
    {
        g = _g;
        n = g.size();
    }

    bool process(int _mn, int _mx)
    {
        mn = _mn;
        mx = _mx;
        for(int i = 0; i < n; ++i) {
            d[i] = 0;
            finish[i] = false;
            sccIdx[i] = 0;
        }
        dNum = 1;
        st.clear();

        for(int i = 0; i < n; ++i) {
            if(d[i] == 0) dfs(i);
        }

        for(int i = 1; i < n; ++i) {
            if(sccIdx[0] != sccIdx[i]) return false;
        }
        return true;
    }

    int dfs(int cur)
    {
        d[cur] = dNum++;
        st.push_back(cur);

        int ret = d[cur];
        for(int nxt = 0; nxt < n; ++nxt) {
            if(cur == nxt || g[cur][nxt] < mn || mx < g[cur][nxt]) continue;
            if(d[nxt] == 0) ret = min(ret, dfs(nxt));
            else if(finish[nxt] == false) ret = min(ret, d[nxt]);
        }

        if(ret == d[cur]) {
            sccNum++;
            while(1) {
                int top = st.back();
                st.pop_back();

                sccIdx[top] = sccNum;
                finish[top] = true;

                if(top == cur) break;
            }
        }
        return ret;
    }
};

int n;
vector<vector<int>> map;
SCC<51> scc;

bool ck(int mn, int mx)
{
    return scc.process(mn, mx);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    map.resize(n, vector<int>(n));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> map[i][j];
        }
    }
    scc.init(map);

    int res = 150000;
    int l = 0, r = 0;
    while(r <= 150000) {
        if(ck(l, r) == false) {
            r++;
        } else {
            res = min(res, r - l);
            l++;
            if(l > r) r++;
        }
    }

    cout << res;

    return 0;
}
