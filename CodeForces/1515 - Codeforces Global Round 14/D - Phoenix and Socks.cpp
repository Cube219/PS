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
int lnum[200001], rnum[200001];
int n, l, r;
int res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> l >> r;
        for(int i = 0; i < l; ++i) {
            int a;
            cin >> a;
            lnum[a]++;
        }
        for(int i = 0; i < r; ++i) {
            int a;
            cin >> a;
            rnum[a]++;
        }
        for(int i = 1; i <= n; ++i) {
            int gap = min(lnum[i], rnum[i]);
            lnum[i] -= gap;
            rnum[i] -= gap;
        }
        int lrgap = abs(l - r) / 2;
        bool isr = (r > l) ? true : false;
        for(int i = 1; i <= n; ++i) {
            if(isr == true) {
                if(rnum[i] <= 1) continue;
                if(lrgap <= 0) break;
                int cnt = rnum[i] / 2;
                cnt = min(cnt, lrgap);
                lrgap -= cnt;
                rnum[i] -= cnt * 2;
                res += cnt;
            } else {
                if(lnum[i] <= 1) continue;
                if(lrgap <= 0) break;
                int cnt = lnum[i] / 2;
                cnt = min(cnt, lrgap);
                lrgap -= cnt;
                lnum[i] -= cnt * 2;
                res += cnt;
            }
        }
        res += lrgap;
        int cnt = 0;
        for(int i = 1; i <= n; ++i) {
            cnt += lnum[i];
            cnt += rnum[i];
        }
        res += cnt / 2;

        cout << res << "\n";

        for(int i = 1; i <= n; ++i) {
            lnum[i] = 0;
            rnum[i] = 0;
        }
        res = 0;
    }

    return 0;
}
