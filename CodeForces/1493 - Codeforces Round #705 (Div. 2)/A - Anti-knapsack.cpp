#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, k;
vector<int> res;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res.clear();
 
        cin >> n >> k;
        for(int i = k + 1; i <= n; ++i) {
            res.push_back(i);
        }
 
        for(int i = (k + 1) / 2; i <= k - 1; ++i) {
            res.push_back(i);
        }
 
        cout << res.size() << "\n";
        for(int i = 0; i < res.size(); ++i) {
            cout << res[i] << " ";
        }
        cout << "\n";
    }
 
    return 0;
}
