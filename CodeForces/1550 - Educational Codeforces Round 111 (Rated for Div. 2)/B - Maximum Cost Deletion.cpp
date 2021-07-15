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
int n, a, b;
char str[201];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> a >> b >> str;

        ll res = 0;
        if(b >= 0) {
            res = n * b + n * a;
        } else {
            vector<int> cnt;
            int curcnt = 0;
            for(int i = 0; i < n; ++i) {
                if(str[i] == str[0]) {
                    if(curcnt != 0) cnt.push_back(curcnt);
                    curcnt = 0;
                } else {
                    curcnt++;
                }
            }
            if(curcnt != 0) cnt.push_back(curcnt);
            int sum = 0;
            for(int i = 0; i < cnt.size(); ++i) {
                res += a * cnt[i] + b;
                sum += cnt[i];
            }
            res += a * (n - sum) + b;
        }

        cout << res << "\n";
    }

    return 0;
}
