#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
ll pa, ph, n;
struct Monster
{
    ll a;
    ll h;
};
Monster m[100001];
bool res;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> pa >> ph >> n;
        for(int i = 0; i < n; ++i) {
            cin >> m[i].a;
        }
        for(int i = 0; i < n; ++i) {
            cin >> m[i].h;
        }
        sort(m, m + n, [](const Monster& l, const Monster& r) {
            if(l.a == r.a) return l.h < r.h;
            return l.a < r.a;
        });
 
        res = true;
 
        for(int i = 0; i < n; ++i) {
            int cnt = m[i].h / pa;
            if(m[i].h % pa != 0) cnt++;
 
            ph -= cnt * m[i].a;
 
            if(ph <= 0) {
                if(i == n - 1 && ph + m[i].a > 0) break;
                res = false;
                break;
            }
        }
 
        if(res == false) cout << "NO\n";
        else cout << "YES\n";
    }
 
    return 0;
}
