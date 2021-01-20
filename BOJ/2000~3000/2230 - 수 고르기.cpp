#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n;
ll m, a[100001];
ll res = 9999999999;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);

    int st = 0;
    int ed = 0;
    ll current = 0;
    while(1) {
        if(current >= m) {
            st++;
            current = a[ed - 1] - a[st];
        } else {
            if(ed == n) break;
            ed++;
            current = a[ed - 1] - a[st];
        }
        if(current >= m) {
            if(res > current) res = current;
        }
    }
    cout << res;

    return 0;
}
