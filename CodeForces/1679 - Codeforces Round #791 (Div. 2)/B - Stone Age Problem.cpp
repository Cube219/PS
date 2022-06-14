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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    vector<char> changed(n, false);
    int base = 0;
    struct Node
    {
        int idx;
    };
    ll sum = 0;
    vector<int> rec;
    for(int i = 0; i < n; ++i) {
        changed[i] = true;
        rec.push_back(i);
        sum += a[i];
    }

    for(int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if(t == 1) {
            int pos, x;
            cin >> pos >> x;
            pos--;

            if(changed[pos] == false) {
                rec.push_back(pos);
                changed[pos] = true;
                sum -= base;
            } else {
                sum -= a[pos];
            }
            sum += x;
            a[pos] = x;
        } else {
            int x;
            cin >> x;
            base = x;
            sum = (ll)x * n;
            while(rec.size() > 0) {
                changed[rec.back()] = false;
                rec.pop_back();
            }
        }

        cout << sum << "\n";
    }
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
