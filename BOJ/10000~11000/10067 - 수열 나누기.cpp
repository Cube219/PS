#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <fstream>
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 9223372036854775807;

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
        bool operator<(const R& rhs)
        {
            return u * rhs.d <= rhs.u * d;
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
            if(cross(cur, b1) < cross(b1, b2)) {
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

int n, k;
ll a[100001], sum[100001];
ll dp[100001][2];
int rec[100001][201];
CHT cht;

int main(int argc, char* argv[])
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sum[0] = a[0];
    for(int i = 1; i < n; ++i) {
        sum[i] = sum[i - 1] + a[i];
    }

    for(int j = 1; j <= k; ++j) {
        cht.clear();
        int cur = j % 2;
        int prev = 1 - cur;
        for(int i = 0; i < j; ++i) {
            dp[i][cur] = 0;
        }
        for(int i = j; i < n; ++i) {
            cht.insert(sum[i - 1], dp[i - 1][prev] - sum[i - 1] * sum[i - 1], i - 1);
            auto v = cht.get(sum[i]);
            dp[i][cur] = v.first;
            rec[i][j] = v.second;
        }
    }
    
    vector<int> res;
    int cur = n - 1;
    for(int i = k; i >= 1; --i) {
        res.push_back(rec[cur][i] + 1);
        cur = rec[cur][i];
    }
    cout << dp[n - 1][k % 2] << "\n";
    for(int i = res.size() - 1; i >= 0; --i) {
        cout << res[i] << " ";
    }


    return 0;
}
