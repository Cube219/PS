#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int n;
        cin >> n;
        vector<ll> d(n);
        for(auto& v : d) cin >> v;
        sort(d.begin(), d.end());
        ll v = 1;
        for(int i = 0; i < n; ++i) {
            while(d[i] % 2 == 0) {
                v *= 2;
                d[i] /= 2;
            }
        }
        sort(d.begin(), d.end());
        d.back() *= v;
        v = 0;
        for(int i = 0; i < n; ++i) {
            v += d[i];
        }
        cout << v << "\n";
    }

    return 0;
}
