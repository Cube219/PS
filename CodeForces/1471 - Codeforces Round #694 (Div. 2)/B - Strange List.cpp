#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int tNum;
ll n, x;
vector<ll> d;
ll res;
queue<pair<ll, ll>> q;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> x;
        d.clear();
        d.resize(n);

        while(q.empty() == false) q.pop();

        res = 0;
        for(int i = 0; i < n; i++) {
            cin >> d[i];
            res += d[i];
            q.push({ d[i], 1 });
        }

        while(q.empty() == false) {
            ll c = q.front().first;
            ll cnt = q.front().second;
            q.pop();

            if(c % x == 0) {
                res += c * cnt;
                q.push({ c / x, cnt * x });
            } else {
                break;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
