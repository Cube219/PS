#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include <limits.h>
#include <unordered_set>
using namespace std;

using ll = long long int;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> distribution(0, INT_MAX);

int n;
ll ax, ay, bx, by;
vector<pair<ll, ll>> v;
unordered_set<ll> has;

bool cancatch(ll x1, ll y1, ll x2, ll y2)
{
    has.clear();
    has.insert(x1 * 100001 + y1);
    for(int i = 0; i < v.size(); ++i) {
        ll x = x1 + v[i].first;
        ll y = y1 + v[i].second;
        if(x <= 0 || x > n || y <= 0 || y > n) continue;
        ll key = x * 100001 + y;
        has.insert(key);
    }
    if(has.find(x2 * 100001 + y2) != has.end()) return true;
    for(int i = 0; i < v.size(); ++i) {
        ll x = x2 - v[i].first;
        ll y = y2 - v[i].second;
        if(x <= 0 || x > n || y <= 0 || y > n) continue;
        if(has.find(x * 100001 + y) != has.end()) return true;
    }
    return false;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    cin >> ax >> ay >> bx >> by;
    v.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
    }
    if(cancatch(ax, ay, bx, by) == true) {
        cout << "Alice wins";
    } else {
        bool f = false;
        for(int i = 0; i < 1000; ++i) {
            int x = distribution(rng) % n + 1;
            int y = distribution(rng) % n + 1;
            if(cancatch(bx, by, x, y) == false) {
                cout << "tie " << x << " " << y;
                f = true;
                break;
            }
        }
        if(f == false) cout << "Bob wins";
    }

    return 0;
}
