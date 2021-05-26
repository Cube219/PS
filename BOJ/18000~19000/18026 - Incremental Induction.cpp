#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int indeg[5001];
ll res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 2; i <= n; ++i) {
        string str;
        cin >> str;
        for(int j = 1; j <= str.size(); ++j) {
            if(str[j - 1] == '0') {
                indeg[i]++;
            } else {
                indeg[j]++;
            }
        }
    }
    sort(indeg + 1, indeg + 1 + n);
    ll cur = indeg[1];
    res = cur;
    for(int i = 2; i <= n; ++i) {
        cur += indeg[i];
        ll minus = (ll)i * (i - 1) / 2;
        res = max(res, cur - minus);
    }

    cout << res;

    return 0;
}
