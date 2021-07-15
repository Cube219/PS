#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, a[200001];
map<int, int> mp;

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
        }

        mp.clear();

        ll res = 0;
        int limit = -1;
        for(int i = 0; i < n; ++i) {
            res++;
            int l = -1;
            int r = 2000000000;
            for(int j = i - 1; j > limit; --j) {
                int cl = min(a[i], a[j]);
                int cr = max(a[i], a[j]);
                if(l < cl && cr < r) {
                    res++;
                    if(a[j] < a[i]) {
                        l = max(l, a[j]);
                    } else if(a[j] > a[i]) {
                        r = min(r, a[j]);
                    } else {
                        l = a[j];
                        r = a[j];
                    }
                } else {
                    limit = j;
                    break;
                }
            }
        }

        cout << res << "\n";
    }

    return 0;
}
