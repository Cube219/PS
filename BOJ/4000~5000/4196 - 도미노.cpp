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
vector<int> g[100001];
int ssc[100001], sscNum = 1;
int in[100001];

vector<int> st;
int d[100001], dNum = 1;
bool finish[100001];

int dfs(int cur)
{
    d[cur] = dNum++;
    st.push_back(cur);

    int r = d[cur];
    for(int nxt : g[cur]) {
        if(d[nxt] == 0) {
            r = min(r, dfs(nxt));
        } else if(finish[nxt] == false) {
            r = min(r, d[nxt]);
        }
    }

    if(r == d[cur]) {
        while(1) {
            int t = st.back();
            st.pop_back();
            ssc[t] = sscNum;
            finish[t] = true;

            if(t == cur) break;
        }
        sscNum++;
    }
    return r;
}

void init()
{
    st.clear();
    for(int i = 1; i <= n; ++i) {
        g[i].clear();
        d[i] = 0;
        finish[i] = false;
        ssc[i] = 0;
    }

    for(int i = 1; i <= sscNum; ++i) {
        in[i] = 0;
    }

    sscNum = 1;
    dNum = 1;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; ++tt) {
        cin >> n >> m;
        init();

        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
        }

        for(int i = 1; i <= n; ++i) {
            if(finish[i] == false) dfs(i);
        }

        for(int i = 1; i <= n; ++i) {
            for(int j : g[i]) {
                if(ssc[i] != ssc[j]) {
                    in[ssc[j]]++;
                }
            }
        }

        int res = 0;
        for(int i = 1; i <= sscNum - 1; ++i) {
            if(in[i] == 0) res++;
        }
        cout << res << "\n";
    }
    

    return 0;
}
