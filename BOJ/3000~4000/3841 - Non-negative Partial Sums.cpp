#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

using ll = long long int;

int n;
ll d[1000001], sum[1000001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n;
        if(n == 0) break;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }

        sum[0] = d[0];
        for(int i = 1; i < n; ++i) {
            sum[i] = sum[i - 1] + d[i];
        }

        int res = 0;
        deque<pair<int, ll>> dq;
        ll offset = 0;
        for(int i = 0; i < n; ++i) {
            while(dq.size() > 0 && dq.back().second >= sum[i]) {
                dq.pop_back();
            }
            dq.push_back({ i, sum[i] });
        }
        for(int i = 0; i < n; ++i) {
            if(dq.front().second - offset >= 0) res++;
            if(dq.front().first == i) dq.pop_front();

            offset += d[i];

            ll nv = sum[n - 1] + offset;
            while(dq.size() > 0 && dq.back().second >= nv) {
                dq.pop_back();
            }
            dq.push_back({ n + 1, nv });
        }

        cout << res << "\n";
    }

    return 0;
}
