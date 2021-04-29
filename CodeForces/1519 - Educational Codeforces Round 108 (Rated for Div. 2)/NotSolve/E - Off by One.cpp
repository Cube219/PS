#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;
using lll = ll;

lll gcd(lll a, lll b)
{
    if(a < b) swap(a, b);
    if(b == 0) return a;
    return gcd(b, a % b);
}

int n;
vector<pair<int, int>> res;
map<pair<ll, ll>, vector<int>> mp;
bool isend[200001];

void ins(ll a, ll b, ll c, ll d, int idx)
{
    ll g = gcd(c * b, a * d);
    pair<ll, ll> gi = { a * d / g, c * b / g };
    auto it = mp.find(gi);
    if(it == mp.end()) {
        it = mp.insert({ gi, {} }).first;
    }
    it->second.push_back(idx + 1);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;

        a += b;
        ins(a, b, c, d, i);
        a -= b;
        c += d;
        ins(a, b, c, d, i);
    }

    for(auto it = mp.begin(); it != mp.end(); ++it) {
        vector<int>& v = it->second;
        int a = -1, b = -1;
        for(int i = 0; i < v.size(); ++i) {
            if(isend[v[i]] == true) continue;

            if(a == -1) {
                a = v[i];
            } else {
                b = v[i];
                res.push_back({ a, b });
                isend[a] = true;
                isend[b] = true;
                a = -1;
                b = -1;
            }
        }
    }

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i].first << " " << res[i].second << "\n";
    }

    return 0;
}
