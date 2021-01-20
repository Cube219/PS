#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, a[300001];
int res;
bool h;
int cnt, maxCnt;
 
int p(int x)
{
    int r = 0;
 
    if((a[x - 1] < a[x] && a[x] > a[x + 1]) || (a[x - 1] > a[x] && a[x] < a[x + 1])) r++;
    x++;
    if(x < n - 1) {
        if((a[x - 1] < a[x] && a[x] > a[x + 1]) || (a[x - 1] > a[x] && a[x] < a[x + 1])) r++;
    }
    x -= 2;
    if(x > 0) {
        if((a[x - 1] < a[x] && a[x] > a[x + 1]) || (a[x - 1] > a[x] && a[x] < a[x + 1])) r++;
    }
 
    return r;
}
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
 
        h = false;
        res = 0;
        maxCnt = 0;
 
        for(int i = 1; i < n - 1; i++) {
            if((a[i - 1] < a[i] && a[i] > a[i + 1]) || (a[i - 1] > a[i] && a[i] < a[i + 1])) res++;
        }
 
        for(int i = 1; i < n - 1; i++) {
            int old = p(i);
            int tmp = a[i];
            
            a[i] = a[i - 1];
            int ne = p(i);
            if(maxCnt < old - ne) maxCnt = old - ne;
 
            a[i] = a[i + 1];
            ne = p(i);
            if(maxCnt < old - ne) maxCnt = old - ne;
 
            a[i] = tmp;
        }
 
        cout << res - maxCnt << "\n";
    }
 
    return 0;
}
