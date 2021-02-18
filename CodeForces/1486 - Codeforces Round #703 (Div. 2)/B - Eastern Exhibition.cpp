#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n;
int xx[1001], yy[1001];
vector<int> x, y;
 
ll xNum, yNum;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        x.clear();
        y.clear();
 
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> xx[i] >> yy[i];
        }
 
        sort(xx, xx + n);
        sort(yy, yy + n);
 
        x.push_back(xx[0]);
        for(int i = 1; i < n; ++i) {
            x.push_back(xx[i]);
        }
 
        y.push_back(yy[0]);
        for(int i = 1; i < n; ++i) {
            y.push_back(yy[i]);
        }
 
        if(x.size() % 2 == 1) xNum = 1;
        else {
            int mid = x.size() / 2;
            xNum = x[mid] - x[mid - 1] + 1;
        }
        if(y.size() % 2 == 1) yNum = 1;
        else {
            int mid = y.size() / 2;
            yNum = y[mid] - y[mid - 1] + 1;
        }
 
        cout << xNum * yNum << "\n";
    }
 
    return 0;
}
