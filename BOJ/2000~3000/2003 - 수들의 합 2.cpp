#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n;
ll m;
ll d[10001];
ll res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> d[i];
    }
    int st = 0;
    int ed = 0;
    ll current = 0;
    while(st <= ed) {
        if(current >= m) {
            current -= d[st];
            st++;
        } else {
            if(ed == n) break;
            current += d[ed];
            ed++;
        }
        if(current == m) res++;
    }

    cout << res;

    return 0;
}
