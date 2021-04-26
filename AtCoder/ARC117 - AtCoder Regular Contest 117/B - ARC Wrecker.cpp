#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

int n;
vector<int> d;
ll res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    d.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sort(d.begin(), d.end());
    d.erase(unique(d.begin(), d.end()), d.end());

    res = d[0] + 1;
    for(int i = 1; i < d.size(); ++i) {
        res *= (d[i] - d[i - 1] + 1);
        res %= MOD;
    }
    cout << res;

    return 0;
}
