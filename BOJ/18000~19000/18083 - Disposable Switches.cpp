#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 20000000000000;

struct CHT
{
    struct Line
    {
        ll a, b; // y = ax + b
        int idx;
    };

    struct R
    {
        ll u, d;

        bool operator<=(const R& rhs)
        {
            return u * rhs.d < rhs.u * d;
        }
    };

    vector<Line> d;
    int pos;

    void clear()
    {
        d.clear();
        pos = 0;
    }

    R cross(const Line& a, const Line& b)
    {
        return { b.b - a.b, a.a - b.a };
    }

    void insert(ll a, ll b, int idx)
    {
        Line cur = { a, b, idx };
        while(d.size() > 1) {
            Line& b1 = d[d.size() - 1];
            Line& b2 = d[d.size() - 2];
            if(cross(cur, b1) <= cross(b1, b2)) {
                d.pop_back();
            } else {
                break;
            }
        }
        d.push_back(cur);
    }

    pair<ll, int> get(ll x)
    {
        while(pos < d.size() - 1 && (d[pos].b - d[pos + 1].b) < x * (d[pos + 1].a - d[pos].a)) pos++;
        return { d[pos].a * x + d[pos].b, d[pos].idx };
    }
};

int n, m;
vector<pair<int, ll>> g[2001];
ll dp[2001][2001];
bool visit[2001][2001];
CHT cht;
bool use[2001];

void caldp()
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            dp[i][j] = INF;
        }
    }

    dp[0][0] = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n - 1; ++j) {
            for(auto& nx : g[j]) {
                int nxt = nx.first;
                ll cost = nx.second;

                dp[nxt][i + 1] = min(dp[nxt][i + 1], dp[j][i] + cost);
            }
        }
    }
}

void adduse(int k)
{
    queue<pair<int, int>> q;
    q.push({ n - 1, k });
    visit[n - 1][k] = true;
    while(q.empty() == false) {
        int cur = q.front().first;
        int curk = q.front().second;
        q.pop();
        if(curk == 0) {
            assert(cur == 0);
            continue;
        }

        use[cur] = true;

        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            ll cost = nx.second;
            if(visit[nxt][curk - 1] == false && dp[nxt][curk - 1] + cost == dp[cur][curk]) {
                q.push({ nxt, curk - 1 });
                visit[nxt][curk - 1] = true;
            }
        }
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

    caldp();

    for(int i = n - 1; i >= 1; --i) {
        if(dp[n - 1][i] == INF) continue;
        cht.insert(i, dp[n - 1][i], 0);
    }

    int st = 0;
    while(st < cht.d.size() - 1) {
        if(cht.d[st].b <= cht.d[st + 1].b) break;
        st++;
    }

    for(int i = st; i < cht.d.size(); ++i) {
        adduse(cht.d[i].a);
    }

    use[0] = true;
    int res = 0;
    for(int i = 0; i < n; ++i) {
        if(use[i] == false) res++;
    }
    cout << res << "\n";
    for(int i = 0; i < n; ++i) {
        if(use[i] == false) {
            cout << i + 1 << " ";
        }
    }

    return 0;
}
