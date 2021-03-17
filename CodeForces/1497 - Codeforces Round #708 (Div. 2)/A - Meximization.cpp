#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, d[101];
vector<int> res, r2;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res.clear();
        r2.clear();
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        sort(d, d + n);
        res.push_back(d[0]);
        for(int i = 1; i < n; ++i) {
            if(res.back() != d[i]) {
                res.push_back(d[i]);
            } else {
                r2.push_back(d[i]);
            }
        }
 
        for(int i = 0; i < res.size(); ++i) {
            cout << res[i] << " ";
        }
        for(int i = 0; i < r2.size(); ++i) {
            cout << r2[i] << " ";
        }
        cout << "\n";
    }
 
    return 0;
}
