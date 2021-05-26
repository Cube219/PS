#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;
using lll = ll;

lll gcd(lll a, lll b)
{
    if(a < b) swap(a, b);
    if(b == 0) return a;
    return gcd(b, a % b);
}

int n;
vector<pair<int, int>> res;
map<pair<ll, ll>, int> mp;
vector<pair<int, int>> g[400001];
int nodenum;
bool isend[400001];
bool isendedge[200001];

void ins(ll a, ll b, ll c, ll d, int idx)
{
    a += b;
    ll gc = gcd(c * b, a * d);
    pair<ll, ll> gi = { a * d / gc, c * b / gc };
    auto it = mp.find(gi);
    if(it == mp.end()) {
        it = mp.insert({ gi, nodenum }).first;
        nodenum++;
    }
    int node1 = it->second;

    a -= b;
    c += d;
    gc = gcd(c * b, a * d);
    gi = { a * d / gc, c * b / gc };
    it = mp.find(gi);
    if(it == mp.end()) {
        it = mp.insert({ gi, nodenum }).first;
        nodenum++;
    }
    int node2 = it->second;

    g[node1].push_back({ node2, idx });
    g[node2].push_back({ node1, idx });
}

int dfs(int cur, int par, int edge)
{
    isend[cur] = true;

    vector<int> edgelist;
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        int idx = nx.second;
        if(isendedge[idx] == true) continue;
        if(idx == edge) continue;
        if(isend[nxt] == true) {
            edgelist.push_back(idx);
            continue;
        }
        int r = dfs(nxt, cur, idx);
        if(r == 1) edgelist.push_back(idx);
    }
    if(edge != -1) edgelist.push_back(edge);
    for(int i = 1; i < edgelist.size(); i += 2) {
        res.push_back({ edgelist[i - 1], edgelist[i] });
        isendedge[edgelist[i - 1]] = true;
        isendedge[edgelist[i]] = true;
    }
    if(edgelist.size() % 2 == 1) return 1;
    else return 0;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;

        ins(a, b, c, d, i);
    }

    for(int i = 0; i < nodenum; ++i) {
        if(isend[i] == false) {
            dfs(i, -1, -1);
        }
    }

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i].first + 1 << " " << res[i].second + 1 << "\n";
    }

    return 0;
}