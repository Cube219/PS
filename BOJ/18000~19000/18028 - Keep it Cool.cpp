#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m, s, d;
pair<int, int> slot[101];
int res[101];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> s >> d;
    for(int i = 0; i < s; ++i) {
        int tmp;
        cin >> tmp;
        slot[i] = { tmp, i };
    }
    sort(slot, slot + s);
    int idx = 0;
    for(int i = 0; i < s; ++i) {
        int cap = d - slot[i].first;
        res[slot[i].second] = min(cap, n);
        n -= cap;
        if(n <= 0) {
            idx = i + 1;
            break;
        }
    }
    int sum = 0;
    for(int i = idx; i < s; ++i) {
        sum += slot[i].first;
    }
    if(sum < m) cout << "impossible";
    else {
        for(int i = 0; i < s; ++i) {
            cout << res[i] << " ";
        }
    }

    return 0;
}
