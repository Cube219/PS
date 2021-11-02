#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;

struct GNode
{
    int nxt;
    int c;
};

int n, w, c, h, m;
vector<int> g[1001][21];
bool ish[1001], ism[1001];
vector<int> hlist, nhlist;
int visit[1001][1001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> w >> c >> h >> m;
    for(int i = 0; i < h; ++i) {
        int a;
        cin >> a;
        ish[a] = true;
    }
    for(int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        ism[a] = true;
    }
    for(int i = 0; i < w; ++i) {
        int s, c, t;
        cin >> s >> c >> t;
        g[s][c].push_back(t);
    }

    for(int i = 0; i < n; ++i) {
        if(ish[i] == true) hlist.push_back(i);
        else nhlist.push_back(i);
    }

    bool res = false;
    int vcnt = 0;
    for(auto s1 : hlist) {
        for(int s2 : nhlist) {
            vcnt++;
            visit[s1][s2] = vcnt;
            queue<pair<int, int>> q;
            q.push({ s1, s2 });
            while(q.empty() == false) {
                auto cur1 = q.front().first;
                auto cur2 = q.front().second;
                q.pop();

                if(ism[cur1] == true && ism[cur2] == true) {
                    res = true;
                    break;
                }

                for(int i = 1; i <= c; ++i) {
                    for(int nxt1 : g[cur1][i]) {
                        for(int nxt2 : g[cur2][i]) {
                            if(visit[nxt1][nxt2] == vcnt) continue;

                            visit[nxt1][nxt2] = vcnt;
                            q.push({ nxt1, nxt2 });
                        }
                    }
                }
            }

            if(res == true) break;
        }
        if(res == true) break;
    }

    if(res == true) cout << "YES";
    else cout << "NO";

    return 0;
}
