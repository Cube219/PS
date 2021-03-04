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
bool pos = true;
int res[20002];

int d[20002], dNum = 1;
vector<int> st;
int scc[20002], sccNum;
vector<vector<int>> sccs;
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
        else if(finish[nxt] == false) ret = min(ret, d[nxt]);
    }
    
    if(ret == d[cur]) {
        sccs.push_back({});
        auto& sc = sccs.back();
        while(1) {
            int top = st.back();
            st.pop_back();

            sc.push_back(top);
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
    for(int i = 0; i < m; ++i) {
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

    for(int i = 1; i <= n * 2; ++i) {
        if(d[i] == 0) dfs(i);
    }

    for(int i = 1; i <= n * 2; i += 2) {
        if(scc[i] == scc[i + 1]) {
            pos = false;
            break;
        }
    }

    if(pos == true) {
        for(int i = 1; i <= n; ++i) {
            res[i] = -1;
        }

        for(int i = sccs.size() - 1; i >= 0; --i) {
            auto& sc = sccs[i];
            for(int j = 0; j < sc.size(); ++j) {
                int cur = (sc[j] + 1) / 2;
                if(res[cur] == -1) {
                    if((sc[j] + 1) % 2 == 1) { // true인 경우
                        res[cur] = 0;
                    } else { // false인 경우
                        res[cur] = 1;
                    }
                }
            }
        }
    }

    if(pos == false) {
        cout << "0";
    } else {
        cout << "1\n";
        for(int i = 1; i <= n; ++i) {
            cout << res[i] << " ";
        }
    }

    return 0;
}
