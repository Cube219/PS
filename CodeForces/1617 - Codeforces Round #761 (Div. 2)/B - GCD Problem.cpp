#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        ll n;
        cin >> n;

        n--;
        ll a, b, c;
        if(n % 2 == 1) {
            a = n / 2;
            b = n - a;
            c = 1;
        } else {
            a = n / 2 - 1;
            b = n / 2 + 1;
            if(a % 2 == 0) {
                a = n / 2 - 2;
                b = n / 2 + 2;
            }
            c = 1;
        }
        cout << a << " " << b << " " << c << "\n";

        assert(gcd(a, b) == c);
        assert(a + b + c == n + 1);
    }

    return 0;
}
