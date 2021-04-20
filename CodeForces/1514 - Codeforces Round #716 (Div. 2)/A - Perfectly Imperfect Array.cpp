#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr int MAXN = 20000;
int min_factor[MAXN + 1];
vector<pair<int, int>> fPrimes;

void init_primes()
{
    for(int i = 2; i <= MAXN; i++) {
        min_factor[i] = i;
    }

    for(int i = 2; i * i <= MAXN; i++) {
        if(min_factor[i] == i) {
            for(int j = i * i; j <= MAXN; j += i) {
                if(min_factor[j] == j) {
                    min_factor[j] = i;
                }
            }
        }
    }
}

void get_f_primes(int v)
{
    fPrimes.clear();

    while(v > 1) {
        int f = min_factor[v];
        if(fPrimes.size() == 0 || fPrimes.back().first != f) {
            fPrimes.push_back(make_pair(f, 0));
        }
        fPrimes.back().second++;
        v /= f;
    }
}


int tNum;
int n;
bool ispos;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_primes();

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        ispos = false;
        for(int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            get_f_primes(a);
            for(int i = 0; i < fPrimes.size(); ++i) {
                if(fPrimes[i].second % 2 == 1) {
                    ispos = true;
                    break;
                }
            }
        }
        if(ispos == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
