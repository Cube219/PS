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
vector<pair<int, ll>> g[100001];
bool neg[100001], visit[100001];
ll v[100001];
bool pos = true, isset;
ll x;

void dfs(int cur, int par)
{
    visit[cur] = true;

    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        ll cost = nx.second;
        if(nxt == par) continue;

        if(visit[nxt] == false) {
            neg[nxt] = !neg[cur];
            v[nxt] = -v[cur] + cost;
            dfs(nxt, cur);
        } else {
            if(neg[nxt] != neg[cur]) {
                if(v[nxt] + v[cur] != cost) {
                    pos = false;
                }
            } else {
                ll tmp = cost - v[cur] - v[nxt];
                if(neg[cur] == true) tmp *= -1;
                if(tmp % 2 != 0) {
                    pos = false;
                } else {
                    tmp /= 2;
                    if(isset == false) {
                        isset = true;
                        x = tmp;
                    } else if(x != tmp) {
                        pos = false;
                    }
                }
            }
        }
        if(pos == false) break;
    }
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
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }

    dfs(0, -1);
    vector<ll> vv(n);
    for(int i = 0; i < n; ++i) {
        if(neg[i] == false) vv[i] = v[i];
        else vv[i] = -v[i];
    }
    sort(vv.begin(), vv.end());

    if(pos == false) {
        cout << "No";
    } else {
        if(isset == false) {
            x = -vv[n / 2];
        }

        cout << "Yes\n";
        for(int i = 0; i < n; ++i) {
            ll tmp = 0;
            if(neg[i] == false) tmp += x;
            else tmp -= x;
            tmp += v[i];
            cout << tmp << " ";
        }
    }

    return 0;
}
