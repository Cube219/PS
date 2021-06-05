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
ll d[4];
ll res;

void bt(int cur)
{
    if(cur == 12 || d[3] == 0) {
        int maxidx = 0;
        ll maxv = 0;
        for(int i = 0; i < 3; ++i) {
            if(maxv < d[i]) {
                maxidx = i;
                maxv = d[i];
            }
        }
        d[maxidx] += d[3];

        ll minv = d[0];
        minv = min(minv, d[1]);
        minv = min(minv, d[2]);
        ll r = d[0] * d[0] + d[1] * d[1] + d[2] * d[2] + minv * 7;
        res = max(res, r);

        d[maxidx] -= d[3];
        return;
    }

    d[3]--;
    for(int i = 0; i < 3; ++i) {
        d[i]++;
        bt(cur + 1);
        d[i]--;
    }
    d[3]++;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 4; ++j) {
            cin >> d[j];
        }

        res = 0;
        bt(0);
        cout << res << "\n";
    }

    return 0;
}
