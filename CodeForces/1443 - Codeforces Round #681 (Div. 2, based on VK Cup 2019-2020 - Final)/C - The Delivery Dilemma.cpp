#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n;
pair<ll, ll> d[200001];

ll res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            int a;
            cin >> a;
            d[i].first = a;
        }
        for(int i = 0; i < n; i++) {
            int b;
            cin >> b;
            d[i].second = b;
        }
        sort(d, d + n, [](const pair<ll, ll>& l, const pair<ll, ll>& r) {
            if(l.first == r.first) return l.second < r.second;
            return l.first > r.first;
        });

        res = d[0].first;
        ll sum = 0;
        for(int i = 0; i < n - 1; i++) {
            sum += d[i].second;
            
            ll tt = sum;
            if(tt < d[i + 1].first) tt = d[i + 1].first;
            if(res > tt) {
                res = tt;
            }
        }
        sum += d[n - 1].second;
        if(res > sum) res = sum;

        cout << res << "\n";
    }

    return 0;
}
