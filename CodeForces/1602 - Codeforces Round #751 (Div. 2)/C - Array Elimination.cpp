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
int n, a[200007];
int cnt[40];
bool res[200007];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
            int aa = a[i];
            for(int j = 0; j < 40 && aa > 0; ++j) {
                if((aa & 1) == 1) cnt[j]++;
                aa >>= 1;
            }
        }

        for(int i = 1; i <= n; ++i) {
            res[i] = true;
        }

        for(int i = 0; i < 40; ++i) {
            if(cnt[i] == 0) continue;

            for(int j = 1; j <= n; ++j) {
                if(cnt[i] % j != 0) res[j] = false;
            }
        }

        for(int i = 1; i <= n; ++i) {
            if(res[i] == true) cout << i << " ";
        }
        cout << "\n";

        for(int i = 0; i < 40; ++i) {
            cnt[i] = 0;
        }
    }

    return 0;
}
