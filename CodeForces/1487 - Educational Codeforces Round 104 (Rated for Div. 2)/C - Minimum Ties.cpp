#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, n2;
int wCnt[101], lCnt[101];
int last[101];
int res[101][101];
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        n2 = (n - 1) / 2;
 
        for(int i = 0; i < n; ++i) {
            last[i] = 0;
            wCnt[i] = 0;
            lCnt[i] = 0;
            for(int j = 0; j < n; ++j) {
                res[i][j] = 0;
            }
        }
 
        if(n % 2 == 0) {
            int tmp = n / 2;
            for(int i = 0; i < n / 2; i++) {
                res[i][i + tmp] = 2;
                res[i + tmp][i] = 2;
            }
        }
 
        int f = 1;
        for(int i = 1; i < n; ++i) {
            if(res[0][i] == 2) continue;
            res[0][i] = f;
            if(f == 1) lCnt[i]++;
            else wCnt[i]++;
            last[i] = f;
            f = f * (-1);
        }
 
        for(int i = 1; i < n - 1; ++i) {
            // Use win
            for(int j = i + 1; j < n && wCnt[i] < n2; ++j) {
                if(res[i][j] == 0 && wCnt[j] == n2) {
                    wCnt[i]++;
                    lCnt[j]++;
                    res[i][j] = 1;
                    last[j] = -1;
                }
            }
            for(int j = i + 1; j < n && wCnt[i] < n2; ++j) {
                if(res[i][j] == 0 && last[j] == 1) {
                    wCnt[i]++;
                    lCnt[j]++;
                    res[i][j] = 1;
                    last[j] = -1;
                }
            }
            for(int j = i + 1; j < n && wCnt[i] < n2; ++j) {
                if(res[i][j] == 0) {
                    wCnt[i]++;
                    lCnt[j]++;
                    res[i][j] = 1;
                    last[j] = -1;
                }
            }
            // Use lose
            for(int j = i + 1; j < n && lCnt[i] < n2; ++j) {
                if(res[i][j] == 0 && lCnt[j] == n2) {
                    lCnt[i]++;
                    wCnt[j]++;
                    res[i][j] = -1;
                    last[j] = 1;
                }
            }
            for(int j = i + 1; j < n && lCnt[i] < n2; ++j) {
                if(res[i][j] == 0 && last[j] == -1) {
                    lCnt[i]++;
                    wCnt[j]++;
                    res[i][j] = -1;
                    last[j] = 1;
                }
            }
            for(int j = i + 1; j < n && lCnt[i] < n2; ++j) {
                if(res[i][j] == 0) {
                    lCnt[i]++;
                    wCnt[j]++;
                    res[i][j] = -1;
                    last[j] = 1;
                }
            }
        }
        if(n == 2) res[0][1] = 0;
        for(int i = 0; i < n - 1; ++i) {
            for(int j = i + 1; j < n; ++j) {
                if(res[i][j] == 2) cout << "0 ";
                else cout << res[i][j] << " ";
            }
        }
        cout << "\n";
    }
 
    return 0;
}
