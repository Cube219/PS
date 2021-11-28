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

    int n;
    cin >> n;
    vector<int> d(n);
    for(auto& v : d) cin >> v;
    sort(d.begin(), d.end());
    int res = 0;
    for(int i = (n + 1) / 2 - 1; i >= 0; --i) {
        int v = d[i];
        while(v > 1) {
            res++;
            v >>= 1;
        }
    }
    cout << res + 1;

    return 0;
}
