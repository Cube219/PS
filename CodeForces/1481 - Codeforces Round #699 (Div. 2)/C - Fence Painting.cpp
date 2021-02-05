#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, m;
int a[100001], b[100001], c[100001];
int req[100001];
int has[100001];
vector<int> reqPos[100001];
int res[100001];
bool pos;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for(int i = 1; i <= n; ++i) {
            req[i] = 0;
            reqPos[i].clear();
            has[i] = -1;
        }
        for(int i = 0; i < n; ++i) {
            cin >> b[i];
        }
        for(int i = 0; i < m; ++i) {
            cin >> c[i];
        }
 
        for(int i = 0; i < n; ++i) {
            if(a[i] != b[i]) {
                req[b[i]]++;
                reqPos[b[i]].push_back(i);
            }
            has[b[i]] = i;
        }
 
        pos = true;
        int tidx = -1;
        for(int i = m - 1; i >= 0; --i) {
            if(has[c[i]] == -1 && tidx == -1) {
                pos = false;
                break;
            }
 
            if(req[c[i]] > 0) {
                req[c[i]]--;
                res[i] = reqPos[c[i]].back();
                reqPos[c[i]].pop_back();
 
                if(tidx == -1) tidx = res[i];
            } else {
                if(tidx != -1) res[i] = tidx;
                else {
                    res[i] = has[c[i]];
                    tidx = res[i];
                }
            }
        }
 
        for(int i = 1; i <= n; ++i) {
            if(req[i] > 0) {
                pos = false;
                break;
            }
        }
 
        if(pos == false) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for(int i = 0; i < m; ++i) {
                cout << res[i] + 1 << " ";
            }
            cout << "\n";
        }
    }
 
    return 0;
}
