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
ll c[100001];
ll res;
ll m1, m2;
ll s1, s2;
ll c1, c2;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> c[i];
        }
 
        m1 = c[0];
        m2 = c[1];
        s1 = m1;
        s2 = m2;
        res = m1 * n + m2 * n;
        c1 = 0;
        c2 = 0;
        for(int i = 2; i < n; i += 2) {
            m1 = min(m1, c[i]);
            s1 += c[i];
            c1++;
 
            ll t = m1 * (n - c1) + m2 * (n - c2) + (s1 - m1) + (s2 - m2);
            res = min(res, t);
 
            if(i + 1 == n) break;
 
            m2 = min(m2, c[i + 1]);
            s2 += c[i + 1];
            c2++;
            t = m1 * (n - c1) + m2 * (n - c2) + (s1 - m1) + (s2 - m2);
 
            res = min(res, t);
        }
 
        cout << res << "\n";
    }
 
    return 0;
}
