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
vector<pair<int, int>> g[100001];
int ck[100001];
vector<pair<int, int>> t1[100001], t2[100001];
int tnum, t1sz, t2sz;

void dfs(int cur)
{
    if(tnum == 1) t1sz++;
    else t2sz++;
    ck[cur] = tnum;
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        int idx = nx.second;
        if(ck[nxt] != 0) continue;

        if(tnum == 1) {
            t1[cur].push_back({ nxt, idx });
            t1[nxt].push_back({ cur, idx });
        } else {
            t2[cur].push_back({ nxt, idx });
            t2[nxt].push_back({ cur, idx });
        }
        dfs(nxt);
    }
}

void print()
{
    cout << t1sz << " " << t2sz << "\n";
    
    for(int i = 0; i < n; ++i) {
        if(ck[i] == 1) cout << i + 1 << " ";
    }
    cout << "\n";

    vector<int> tmp;
    for(int i = 0; i < n; ++i) {
        for(auto& nx : t1[i]) {
            tmp.push_back(nx.second + 1);
        }
    }
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for(int i = 0; i < tmp.size(); ++i) {
        cout << tmp[i] << " ";
    }
    cout << "\n";

    for(int i = 0; i < n; ++i) {
        if(ck[i] == 2) cout << i + 1 << " ";
    }
    cout << "\n";

    tmp.clear();
    for(int i = 0; i < n; ++i) {
        for(auto& nx : t2[i]) {
            tmp.push_back(nx.second + 1);
        }
    }
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for(int i = 0; i < tmp.size(); ++i) {
        cout << tmp[i] << " ";
    }
    cout << "\n";
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
        g[a].push_back({ b, i });
        g[b].push_back({ a, i });
    }

    for(int i = 0; i < n; ++i) {
        if(ck[i] == 0) {
            tnum++;
            if(tnum > 2) break;
            dfs(i);
        }
    }

    if(tnum == 1) {
        if(t1sz <= 2) {
            cout << "-1";
        } else {
            for(int i = 0; i < n; ++i) {
                if(t1[i].size() == 1) {
                    ck[i] = 2;
                    int nxt = t1[i][0].first;
                    for(int j = 0; j < t1[nxt].size(); ++j) {
                        if(t1[nxt][j].first == i) {
                            t1[nxt].erase(t1[nxt].begin() + j);
                            break;
                        }
                    }
                    t1[i].clear();
                    break;
                }
            }
            t1sz--;
            t2sz++;
            print();
        }
    } else if(tnum == 2) {
        if(t1sz == t2sz) {
            cout << "-1";
        } else {
            print();
        }
    } else {
        cout << "-1";
    }

    return 0;
}
