#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, m;
char s1[200002], s2[200002];
int last[200002][30];
int idx[200002];

constexpr int dis = 'z' - 'a' + 1;
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    cin >> s1 >> s2;

    for(int i = 0; i < dis; ++i) {
        last[0][i] = -1;
    }
    last[0][s1[0] - 'a'] = 0;

    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < dis; ++j) {
            last[i][j] = last[i - 1][j];
        }
        last[i][s1[i] - 'a'] = i;
    }

    int cur = 0;
    for(int i = 0; i < m; ++i) {
        while(1) {
            if(s1[cur] == s2[i]) {
                idx[i] = cur;
                cur++;
                break;
            }
            cur++;
        }
    }
    for(int i = 0; i < m - 1; ++i) {
        res = max(res, idx[i + 1] - idx[i]);
    }

    int end = n - 1;
    for(int i = m - 1; i >= 1; --i) {
        int newIdx = last[end][s2[i] - 'a'];
        if(newIdx == -1) break;
        idx[i] = newIdx;
        res = max(res, idx[i] - idx[i - 1]);
        end = newIdx - 1;
    }

    cout << res;

    return 0;
}
