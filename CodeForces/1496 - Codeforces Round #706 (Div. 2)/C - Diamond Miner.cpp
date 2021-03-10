#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n;
vector<int> mine, miner;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        mine.clear();
        miner.clear();
 
        cin >> n;
        for(int i = 0; i < n * 2; ++i) {
            int a, b;
            cin >> a >> b;
            if(a == 0) {
                miner.push_back(abs(b));
            } else {
                mine.push_back(abs(a));
            }
        }
        sort(miner.begin(), miner.end());
        sort(mine.begin(), mine.end());
 
        long double res = 0.0;
        for(int i = 0; i < n; ++i) {
            long double r = (long double)mine[i] * (long double)mine[i] + (long double)miner[i] * (long double)miner[i];
            r = sqrt(r);
            res += r;
        }
        cout << fixed<<setprecision(10) << res << "\n";
    }
 
    return 0;
}
