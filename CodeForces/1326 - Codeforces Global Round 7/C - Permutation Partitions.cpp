#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, k;
pair<int, int> p[200001];
vector<int> idx;

const ll MOD = 998244353;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> p[i].first;
        p[i].second = i;
    }
    sort(p, p + n);
    ll res2 = 0;
    for(int i = 0; i < k; i++) {
        idx.push_back(p[n - 1 - i].second);
        res2 += p[n - 1 - i].first;
    }
    sort(idx.begin(), idx.end());

    ll res = 1;
    for(int i = 0; i < idx.size() - 1; i++) {
        res = (res * (idx[i + 1] - idx[i])) % MOD;
    }

    cout << res2 << " " << res;

    return 0;
}
