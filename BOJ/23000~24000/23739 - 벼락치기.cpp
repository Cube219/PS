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

    int res = 0;
    int cur = 0;
    for(int v : d) {
        int remain = 30 - cur;
        if(remain >= (v + 1) / 2) res++;
        cur += v;
        if(cur >= 30) cur = 0;
    }

    cout << res;

    return 0;
}
