#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
ll k;
ll p2[100001];
int res[100001];
bool pos;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    p2[1] = 1;
    for(int i = 2; i <= 100000; ++i) {
        p2[i] = p2[i - 1] * 2;
        if(p2[i] >= 1000000000000000000) {
            p2[i] = 1000000000000000000;
        }
    }

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;
        pos = true;

        int curIdx = 0, cur = 1;
        for(int i = 0; i < n; ++i) {
            if(k > p2[n - i - 1]) {
                k -= p2[n - i - 1];
            } else {
                for(int j = i; j >= curIdx; --j) {
                    res[j] = cur++;
                }
                curIdx = i + 1;
            }
        }
        if(k != 1) pos = false;
        else {
            for(int i = n - 1; i >= curIdx; --i) {
                res[i] = cur++;
            }
        }

        if(pos == false) {
            cout << "-1\n";
        } else {
            for(int i = 0; i < n; ++i) {
                cout << res[i] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
