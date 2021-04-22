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
ll k;
bool has[1000001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    ll sum = 0;
    for(int i = 1; i < n - 1; ++i) {
        has[i] = true;
        sum += i;
    }
    sum -= k;
    for(int i = n - 2; i >= 1; --i) {
        if(sum - i < 0) continue;
        sum -= i;
        has[n - i - 1] = false;
        if(sum == 0) break;
    }
    if(sum > 0 || sum < 0) {
        cout << "-1";
    } else {
        cout << n << " ";
        for(int i = 1; i < n - 1; ++i) {
            if(has[i] == true) cout << i << " ";
        }
        cout << n - 1 << " ";
        for(int i = n - 2; i >= 1; --i) {
            if(has[i] == false) cout << i << " ";
        }
    }

    return 0;
}
