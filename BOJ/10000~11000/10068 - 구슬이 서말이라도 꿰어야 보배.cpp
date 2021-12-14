#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = 0x3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vector<pair<int, ll>>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    // 0 : �ش� ��� ���� ����
    // 1 : �ڽ� �� �ش� ��� ���� (�����ϸ� �ڽĳ��� �Ķ��� 2���� ����)
    // 2 : �ڽ�-���-�θ�� �Ķ��� �����ϴµ�, �θ�->�ڽ�->���
    // 3 : �ڽ�-���-�θ�� �Ķ��� �����ϴµ�, �ڽ�->�θ�->���
    vector<vector<ll>> dp(n, vector<ll>(4, 0));
    auto dfs = [&](auto&& self, int cur, int par, ll lcost) -> void {
        ll inmx[2] = { -INF, -INF }, outmx[2] = { -INF, -INF }, innocost = 0;
        int inmx_child = -1, outmx_child = -2;
        ll sum = 0;
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            ll cost = nx.second;
            if(nxt == par) continue;

            self(self, nxt, cur, cost);

            ll mx = max(dp[nxt][0], dp[nxt][2]);
            sum += mx;

            innocost = max(innocost, max(dp[nxt][1], dp[nxt][3]) - mx);

            // child�� 0(out)���� �ٲٰ� �Ķ� �������� ����� ����� ����
            ll diff = dp[nxt][0] - mx + cost;

            if(outmx[0] < diff) {
                outmx[1] = outmx[0];
                outmx[0] = diff;
                outmx_child = nxt;
            } else if(outmx[1] < diff) {
                outmx[1] = diff;
            }

            // child�� 1(in)���� �ٲٰ� �Ķ� �������� ����� ����� ����
            diff = dp[nxt][1] - mx + cost;

            if(inmx[0] < diff) {
                inmx[1] = inmx[0];
                inmx[0] = diff;
                inmx_child = nxt;
            } else if(inmx[1] < diff){
                inmx[1] = diff;
            }
        }
        dp[cur][0] = sum;
        dp[cur][1] = sum + innocost;
        dp[cur][1] = max(dp[cur][1], sum + outmx[0] + outmx[1]);
        if(inmx_child == outmx_child) {
            dp[cur][1] = max(dp[cur][1], sum + inmx[0] + outmx[1]);
            dp[cur][1] = max(dp[cur][1], sum + inmx[1] + outmx[0]);
        } else {
            dp[cur][1] = max(dp[cur][1], sum + inmx[0] + outmx[0]);
        }
        dp[cur][2] = max(dp[cur][2], sum + outmx[0] + lcost);
        dp[cur][3] = max(dp[cur][3], sum + inmx[0] + lcost);
    };
    dfs(dfs, 0, -1, 0LL);

    cout << max(dp[0][0], dp[0][1]);

    return 0;
}
