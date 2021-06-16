#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[200001], st;
int anum, bnum, d[200001];

bool visit[200001], finish;

void dfs(int cur)
{
    anum--;
    d[cur] = 0;
    st.push_back(cur);
    visit[cur] = true;
    if(anum == bnum) {
        finish = true;
        return;
    }

    for(int nxt : g[cur]) {
        if(visit[nxt] == true || d[nxt] == 2) continue;
        dfs(nxt);
        if(finish == true) return;
    }

    bnum++;
    d[cur] = 2;
    visit[cur] = false;
    if(anum == bnum) {
        finish = true;
    }

    st.pop_back();
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    anum = n;
    for(int i = 0; i < n; ++i) {
        d[i] = 1;
    }

    dfs(0);

    cout << n - anum - bnum << " " << anum << "\n";
    for(int i = 0; i < st.size(); ++i) {
        cout << st[i] + 1 << " ";
    }
    cout << "\n";
    for(int i = 0; i < n; ++i) {
        if(d[i] == 1) {
            cout << i + 1 << " ";
        }
    }
    cout << "\n";
    for(int i = 0; i < n; ++i) {
        if(d[i] == 2) {
            cout << i + 1 << " ";
        }
    }

    return 0;
}
