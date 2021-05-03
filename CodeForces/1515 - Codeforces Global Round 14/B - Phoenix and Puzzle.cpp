#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;

vector<pair<int, int>> fPrimes;

void get_f_primes(ll v)
{
    ll v2 = v;
    fPrimes.clear();
    if(v % 2 == 0) {
        fPrimes.push_back({ 2, 0 });
        while(v > 1 && v % 2 == 0) {
            fPrimes.back().second++;
            v /= 2;
        }
    }

    for(ll i = 3; i * i <= v2; i += 2) {
        if(v <= 1) break;
        if(v % i == 0) {
            fPrimes.push_back({ i, 0 });
            while(v > 1 && v % i == 0) {
                fPrimes.back().second++;
                v /= i;
            }
        }
    }
    if(v > 1) fPrimes.push_back({ v, 1 });
}


int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        get_f_primes(n);
        bool res = true;
        bool hastwo = false;
        for(int i = 0; i < fPrimes.size(); ++i) {
            if(fPrimes[i].first == 2) {
                hastwo = true;
            } else if(fPrimes[i].second % 2 == 1) {
                res = false;
                break;
            }
        }
        if(res == true && hastwo == false) res = false;

        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
