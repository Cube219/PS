#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;
 
using ll = long long int;
 
constexpr int MAXN = 10000001;
int min_factor[MAXN + 1];
vector<pair<int, int>> fPrimes;
map<int, pair<int, int>> pp;
set<ll> has;
 
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
int n, k;
int d[200001];
int res = 0;
int cnt;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    init_primes();
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }
 
        cnt = 0;
        res = 0;
        has.clear();
        for(int i = 0; i < n; ++i) {
            get_f_primes(d[i]);
            ll v = 1;
            for(int j = 0; j < fPrimes.size(); ++j) {
                if(fPrimes[j].second % 2 == 0) continue;
                v *= fPrimes[j].first;
            }
            if(has.find(v) != has.end()) {
                res++;
                has.clear();
                has.insert(v);
                cnt = 1;
            } else {
                has.insert(v);
                cnt++;
            }
        }
        if(cnt > 0) res++;
        cout << res << "\n";
    }
 
    return 0;
}
