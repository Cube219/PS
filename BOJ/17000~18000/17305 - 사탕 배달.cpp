#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
ll w;
vector<ll> d3, d5;
ll d3sum[250001], d5sum[250001];
ll res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> w;
    for(int i = 0; i < n; i++) {
        int w, s;
        cin >> w >> s;
        if(w == 3) d3.push_back(s);
        else d5.push_back(s);
    }
    sort(d3.begin(), d3.end(), greater<ll>());
    sort(d5.begin(), d5.end(), greater<ll>());

    for(int i = 0; i < d3.size(); i++) {
        d3sum[i + 1] = d3[i] + d3sum[i];
    }
    for(int i = 0; i < d5.size(); i++) {
        d5sum[i + 1] = d5[i] + d5sum[i];
    }

    ll len5 = w / 5;
    len5 = min(len5, (ll)d5.size());
    for(ll i = 0; i <= len5; i++) {
        ll num3 = (w - i * 5) / 3;
        num3 = min(num3, (ll)d3.size());

        if(res < d3sum[num3] + d5sum[i]) {
            res = d3sum[num3] + d5sum[i];
        }
    }

    cout << res;

    return 0;
}
