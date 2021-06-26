#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;

int n, k;
int d[100005];
int sum[100005][31];
map<vector<int>, int> mp;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        int dd = d[i];
        for(int j = 0; j < k; ++j) {
            sum[i][j] = dd % 2;
            dd /= 2;
        }
    }
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < k; ++j) {
            sum[i][j] += sum[i - 1][j];
        }
    }

    vector<int> hs(k, 0);
    mp.insert({ hs, -1 });

    int res = 0;
    for(int i = 0; i < n; ++i) {
        int base = sum[i][0];
        for(int j = 0; j < k; ++j) {
            hs[j] = sum[i][j] - base;
        }
        auto it = mp.find(hs);
        if(it == mp.end()) {
            mp.insert({ hs, i });
        } else {
            res = max(res, i - it->second);
        }
    }

    cout << res;

    return 0;
}
