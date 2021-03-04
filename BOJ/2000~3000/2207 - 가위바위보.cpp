#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[20002];

int d[20002], dNum = 1;
vector<int> st;
int scc[20002], sccNum;
bool finish[20002];

int rev(int v)
{
    if(v % 2 == 0) return v - 1;
    else return v + 1;
}

int dfs(int cur)
{
    d[cur] = dNum++;
    st.push_back(cur);

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(d[nxt] == 0) ret = min(ret, dfs(nxt));
        if(finish[nxt] == false) ret = min(ret, d[nxt]);
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
        int a, b;
        cin >> a >> b;
        a *= 2; b *= 2;
        if(a < 0) {
            a *= -1;
            a--;
        }
        if(b < 0) {
            b *= -1;
            b--;
        }
        g[rev(a)].push_back(b);
        g[rev(b)].push_back(a);
    }

    for(int i = 1; i <= m * 2; ++i) {
        if(d[i] == 0) dfs(i);
    }

    bool res = true;
    for(int i = 1; i <= m * 2; i += 2) {
        if(scc[i] == scc[i + 1]) {
            res = false;
            break;
        }
    }

    if(res == true) cout << "^_^";
    else cout << "OTL";

    return 0;
}
