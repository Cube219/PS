#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    struct Node
    {
        ll v;
        int idx;
    };
    vector<Node> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i].v;
        a[i].idx = i;
    }


    sort(a.begin(), a.end(), [](const Node& l, const Node& r) {
        return l.v < r.v;
    });

    vector<ll> d(n);
    for(int i = 0; i < n; ++i) {
        d[i] = a[i].v;
    }

    auto dnc = [&](auto&& self, int l, int r, int curBit) -> void {
        if(l >= r) return;
        while((d[r] & (1LL << curBit)) == 0) curBit--;

        int m = l;
        for(; m <= r; ++m) {
            if(d[m] & (1LL << curBit)) break;
        }
        self(self, l, m - 1, curBit - 1);
        self(self, m, r, curBit - 1);

        int curl = l;
        ll mask = (1LL << (curBit)) - 1;
        for(int i = m; i <= r; ++i) {
            while((a[curl].v & mask) != (a[i].v & mask)) curl++;
            swap(d[curl], d[i]);
        }
    };
    dnc(dnc, 0, n - 1, 60);

    vector<ll> b(n);
    for(int i = 0; i < n; ++i) {
        b[a[i].idx] = d[i];
    }
    for(ll v : b) cout << v << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
