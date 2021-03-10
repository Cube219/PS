#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, maxK;
struct Edge
{
    int dst;
    int k;
    bool isDown;
};
vector<Edge> eg[400002];
Edge stEg[200002][2];
vector<int> g[400002];

int rev(int v)
{
    if(v % 2 == 0) return v - 1;
    else return v + 1;
}

bool generate(int k)
{
    for(int i = 1; i <= n * 2; ++i) {
        g[i].clear();
    }

    for(int i = 1; i <= n * 2; ++i) {
        int cnt = 0;
        for(int j = 0; j < eg[i].size(); ++j) {
            if(eg[i][j].k > k) continue;
            cnt++;
        }
        if(cnt == 2) {
            int a = eg[i][0].dst * 2;
            int b = eg[i][1].dst * 2;

            if(eg[i][0].isDown == false) a--;
            if(eg[i][1].isDown == false) b--;

            g[a].push_back(rev(b));
            g[b].push_back(rev(a));
        }
    }

    for(int i = 1; i <= n; ++i) {
        int cnt = 0;
        bool isDown = false;
        for(int j = 0; j < 2; ++j) {
            if(stEg[i][j].k <= k) {
                cnt++;
                isDown = stEg[i][j].isDown;
            }
        }

        if(cnt == 0) {
            return false;
        }
        if(cnt == 1) {
            int a = i * 2;
            if(isDown == false) a--;
            g[rev(a)].push_back(a);
        }
    }

    return true;
}

int d[400002], dNum = 1;
bool finish[400002];
vector<int> st;
int scc[400002], sNum;

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

            scc[top] = sNum;
            finish[top] = true;

            if(top == cur) break;
        }
        sNum++;
    }
    return ret;
}

bool pos()
{
    for(int i = 1; i <= n * 2; ++i) {
        d[i] = 0;
        finish[i] = false;
        scc[i] = 0;
    }
    st.clear();
    dNum = 1;
    sNum = 0;

    for(int i = 1; i <= n * 2; ++i) {
        if(d[i] == 0) dfs(i);
    }

    for(int i = 1; i <= n * 2; i += 2) {
        if(scc[i] == scc[i + 1]) return false;
    }
    return true;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        int a, k;
        cin >> a >> k;
        maxK = max(maxK, k);
        eg[a].push_back({ i, k, false });
        stEg[i][0] = { a, k, false };

        cin >> a >> k;
        maxK = max(maxK, k);
        eg[a].push_back({ i, k, true });
        stEg[i][1] = { a, k, true };
    }

    int l = 0, r = maxK + 10;
    while(l < r) {
        int m = (l + r) / 2;

        bool res = generate(m);
        if(res == false) {
            l = m + 1;
            continue;
        }

        if(pos() == true) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    if(l > maxK) l = -1;
    cout << l;

    return 0;
}
