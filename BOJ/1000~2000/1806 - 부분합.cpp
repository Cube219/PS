#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n;
ll s;
ll d[100001];
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> s;
    for(int i = 0; i < n; i++) cin >> d[i];

    res = n + 1;
    int st = 0;
    int ed = 0;
    ll sum = 0;
    while(1) {
        if(sum >= s) {
            sum -= d[st];
            st++;
        } else {
            if(ed == n) break;
            sum += d[ed];
            ed++;
        }
        if(sum >= s) {
            if(res > ed - st) res = ed - st;
        }
    }
    
    if(res == n + 1) res = 0;
    cout << res;

    return 0;
}
