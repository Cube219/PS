#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
ll a;
int b;

vector<pair<int, int>> fPrimes;

void pri()
{
    fPrimes.clear();

    int sb = sqrt(b);
    int cb = b;
    for(int i = 2; i <= sb; i++) {
        if(cb % i != 0) continue;

        pair<int, int> pri = { i, 0 };

        while(cb % i == 0) {
            pri.second++;
            cb /= i;
        }
        fPrimes.push_back(pri);
    }
    if(cb > 1) {
        fPrimes.push_back({ cb, 1 });
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> a >> b;
        if(a % (ll)b != 0) {
            cout << a << "\n";
            continue;
        }

        pri();
        ll minV = a;
        for(int i = 0; i < fPrimes.size(); i++) {
            ll ca = a;
            ll cb = 1;
            for(int j = 0; j < fPrimes[i].second; j++) {
                cb *= (ll)fPrimes[i].first;
            }
            ll prime = (ll)fPrimes[i].first;
            int cnt = 0;
            while(ca % cb == 0) {
                ca /= prime;
                cnt++;
            }

            ll tmp = 1;
            for(int j = 0; j < cnt; j++) {
                tmp *= prime;
            }
            if(minV > tmp) {
                minV = tmp;
            }
        }

        cout << a / minV << "\n";
    }

    return 0;
}
