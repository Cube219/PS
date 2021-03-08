#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, m, k;
vector<int> g[4005];

int d[4005], dNum = 1;
bool finish[4005];
vector<int> st;
int scc[4005], sccNum;

void init()
{
    int sz = n * 2 + m * 2;
    for(int i = 0; i <= sz; ++i) {
        g[i].clear();
        d[i] = 0;
        finish[i] = false;
        scc[i] = 0;
    }
    dNum = 1;
    sccNum = 0;
    st.clear();
}

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

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m >> k;

        init();

        for(int i = 0; i < k; ++i) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;

            if(r1 == r2 && c1 == c2) continue;

            bool right, down;

            if(c1 < c2) {
                if(r1 < r2) {
                    right = true;
                    down = true;
                } else {
                    right = true;
                    down = false;
                }
            } else {
                if(r1 < r2) {
                    right = false;
                    down = true;
                } else {
                    right = false;
                    down = false;
                }
            }

            int a = r1 * 2;
            int b = c2 * 2 + n * 2;
            int c = r2 * 2;
            int d = c1 * 2 + n * 2;
            if(right == false) {
                a--;
                c--;
            }
            if(down == false) {
                b--;
                d--;
            }
            // (A&B)|(C&D) = (A|C)&(A|D)&(B|C)&(B|D)
            g[rev(a)].push_back(c);
            g[rev(c)].push_back(a);
            g[rev(a)].push_back(d);
            g[rev(d)].push_back(a);
            g[rev(b)].push_back(c);
            g[rev(c)].push_back(b);
            g[rev(b)].push_back(d);
            g[rev(d)].push_back(b);
        }

        int sz = n * 2 + m * 2;

        for(int i = 1; i <= sz; ++i) {
            if(d[i] == 0) dfs(i);
        }

        bool res = true;
        for(int i = 1; i <= sz; i += 2) {
            if(scc[i] == scc[i + 1]) {
                res = false;
                break;
            }
        }

        if(res == true) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
