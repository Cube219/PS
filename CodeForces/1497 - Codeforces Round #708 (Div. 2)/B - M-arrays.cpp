#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, m, d[100001];
int cnt[100001];
int res;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = 0;
        cin >> n >> m;
        for(int i = 0; i < m; ++i) {
            cnt[i] = 0;
        }
        for(int i = 0; i < n; ++i) {
            int dd;
            cin >> dd;
            d[i] = dd % m;
            cnt[d[i]]++;
        }
        sort(d, d + n);
        if(cnt[0] > 0) res++;
        for(int i = 1; i <= m / 2; ++i) {
            if(cnt[i] > 0 && cnt[m - i] > 0) {
                int a = cnt[i];
                int b = cnt[m - i];
                if(a > b) swap(a, b);
                b -= a;
                if(b > 0) b--;
                res += b + 1;
            } else {
                res += cnt[i];
                res += cnt[m - i];
            }
        }
 
        cout << res << "\n";
    }
 
    return 0;
}
