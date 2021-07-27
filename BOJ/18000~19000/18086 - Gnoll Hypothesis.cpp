#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

using ll = long long int;

int n, k;
long double p[501];
long double res[501];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    for(int i = 0; i < n; ++i) {
        long double curp = p[i];
        long double curprob = (long double)(k * (k - 1)) / (long double)(n * (n - 1));
        res[i] += curp * curprob;
        int idx = i - 1;
        if(idx < 0) idx += n;

        for(int j = n - 3; j >= k - 2; --j) {
            curprob *= (long double)(j - k + 3) / (long double)(j + 1);
            curp += p[idx];
            res[i] += curprob * curp;

            idx--;
            if(idx < 0) idx += n;
        }
    }

    if(k == 1) {
        for(int i = 0; i < n; ++i) {
            res[i] = 100.0 / n;
        }
    }

    cout << fixed << setprecision(7);
    for(int i = 0; i < n; ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
