#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
ll n;
ll a[100001];
ll mx;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        ll s = 0;
        ll mx = -1;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            s += a[i];
            if(mx < a[i]) mx = a[i];
        }
        n--;

        ll al = mx * n;
        if(al - s < 0) {
            ll mul = (s - al) / n;
            if((s - al) % n != 0) mul++;
            mx += mul;
            al = mx * n;
        }
        cout << al - s << "\n";

    }

    return 0;
}
