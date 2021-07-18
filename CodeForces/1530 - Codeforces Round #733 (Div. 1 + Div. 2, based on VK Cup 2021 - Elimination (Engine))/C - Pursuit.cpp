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
int n;
vector<int> a, b;

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
        a.clear();
        b.clear();
        a.resize(n);
        b.resize(n);
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for(int i = 0; i < n; ++i) {
            cin >> b[i];
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end(), [](const int& l, const int& r) {
            return l > r;
        });
        int cut = n / 4;
        ll asum = 0, bsum = 0;
        int aidx = cut, bidx = n - cut;
        for(int i = cut; i < n; ++i) {
            asum += a[i];
        }
        for(int i = 0; i < n - cut; ++i) {
            bsum += b[i];
        }
        int res = 0;
        
        while(asum < bsum) {
            a.push_back(100);
            asum += 100;
            b.push_back(0);
            n++;
            res++;
            if(n % 4 != 0) {
                bsum += b[bidx];
                bidx++;
            } else {
                asum -= a[aidx];
                aidx++;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
