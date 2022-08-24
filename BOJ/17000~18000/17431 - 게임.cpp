#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

vector<int> mem(300001, -1);

void solve()
{
    int n;
    cin >> n;

    if(mem[n] == -1) {
        int mn = INF, v = 0;
        for(int i = 1; i < n; ++i) {
            int a = i, b = n;
            int sum = 0;
            while(a > 1 && b % a != 0) {
                sum += b / a;
                b = b % a;
                swap(a, b);
            }
            if(a == 1) {
                sum += b - 1;
                if(mn > sum) {
                    mn = sum;
                    v = i;
                }
            }
        }
        mem[n] = v;
    }

    bool R = true;
    string res;
    int a = mem[n], b = n;
    while(a > 1) {
        int v = b / a;
        for(int i = 0; i < v; ++i) {
            res.push_back(R ? 'R' : 'B');
        }
        R = !R;
        b = b % a;
        swap(a, b);
    }
    for(int i = 0; i < b - 1; ++i) {
        res.push_back(R ? 'R' : 'B');
    }

    for(int i = res.size() - 1; i >= 0; --i) {
        cout << res[i];
    }
    cout << "\n";
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
