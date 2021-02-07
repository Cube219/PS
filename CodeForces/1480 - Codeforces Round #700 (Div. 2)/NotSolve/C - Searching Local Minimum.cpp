#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
 
int n;
int st;
int ed;
int md;
int s, e;
int res;
int d[100011];
 
void qu(int x)
{
    if(d[x] != 0) return;
    cout << "? " << x << endl;
    cin >> d[x];
}
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
 
    cin >> n;
 
    s = 1;
    e = n;
 
    d[0] = 999999999;
    d[n + 1] = 999999999;
 
    cout << "? 1" << endl;
    cin >> st;
    d[1] = st;
    cout << "? " << n << endl;
    cin >> ed;
    d[n] = ed;
 
    while(1) {
        int m = (s + e) / 2;
 
        qu(m);
        md = d[m];
 
        int g1 = abs(md - st);
        int g2 = abs(md - ed);
 
 
        if(e - s <= 2) {
            break;
        }
 
        if(g1 < m - s) {
            e = m;
            ed = md;
        } else if(g2 < e - m) {
            s = m;
            st = md;
        } else {
            qu(m - 1);
            qu(m + 1);
            if(d[m-1] < d[m]) {
                e = m;
                ed = md;
            } else {
                s = m;
                st = md;
            }
        }
    }
    if(s > 1 && d[s-1] == 0) {
        qu(s - 1);
    }
    if(e < n && d[e+1] == 0) {
        qu(e + 1);
    }
 
    for(int i=s; i<=e; i++) {
        if(d[i-1] > d[i] && d[i] < d[i+1]) {
            res = i;
            break;
        }
    }
 
    cout <<"! "<< res;
 
    return 0;
}
