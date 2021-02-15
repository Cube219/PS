#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
int tNum;
ll n;
vector<ll> t;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    t.push_back(5);
    ll cur = 4;
    for(ll i = 3; i <= 54722; i += 2) {
        ll gap = (i + 2) * (i + 2) - i * i;
        cur = cur + gap / 2;
 
        t.push_back(cur + 1);
    }
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        if(n < 5) {
            cout << "0\n";
            continue;
        }
 
        for(int i = 0; i < t.size(); ++i) {
            if(n < t[i]) {
                cout << i << "\n";
                break;
            }
        }
    }
 
    return 0;
}
