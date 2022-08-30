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
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> d(m);
    for(auto& v : d) {
        for(auto& v2 : v) cin >> v2;
        int tmp; cin >> tmp;
    }

    bool ck = false;
    for(auto& v : d) for(auto& v2 : v) if(v2 == 0) ck = true;
    if(ck) {
        cout << "INVALID: NULL RING\n";
        return;
    }
    ck = false;
    for(auto& v : d) for(auto& v2 : v) if(v2 < -n || n < v2) ck = true;
    if(ck) {
        cout << "INVALID: RING MISSING\n";
        return;
    }
    ck = false;
    for(auto& v : d) {
        for(int i = 0; i < 3; ++i) for(int j = i + 1; j < 3; ++j) {
            if(abs(v[i]) == abs(v[j])) ck = true;
        }
    }
    if(ck) {
        cout << "INVALID: RUNE CONTAINS A REPEATED RING\n";
        return;
    }

    bool res = false;
    for(int i = 0; i < 1 << n; ++i) {
        bool r2 = true;
        for(auto& v : d) {
            bool isTrue = false;
            for(int v2 : v) {
                int mask = 1 << (abs(v2) - 1);
                if(v2 < 0) {
                    // false
                    if((i & mask) == 0) {
                        isTrue = true;
                        break;
                    }
                } else {
                    // true
                    if(i & mask) {
                        isTrue = true;
                        break;
                    }
                }
            }
            if(!isTrue) {
                r2 = false;
                break;
            }
        }
        if(r2) {
            res = true;
            break;
        }
    }
    if(res) cout << "RUNES SATISFIED!\n";
    else cout << "RUNES UNSATISFIABLE! TRY ANOTHER GATE!\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
