#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, d[100001], cn;
int idx[100001];
vector<int> res;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res.clear();
 
 
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
            idx[i + 1] = 0;
        }
 
        int cur = n;
        cn = n - 1;
        for(int i = n - 1; i >= 0; --i) {
            if(d[i] == cur) {
                for(int j = i; j <= cn; ++j) {
                    res.push_back(d[j]);
                    idx[d[j]] = 1;
                }
 
                for(int j = cur - 1; j >= 1; --j) {
                    if(idx[j] == 0) {
                        cur = j;
                        break;
                    }
                }
 
                cn = i - 1;
            }
        }
 
        for(int i = 0; i < n; ++i) {
            cout << res[i] << " ";
        }
        cout << "\n";
    }
 
    return 0;
}
