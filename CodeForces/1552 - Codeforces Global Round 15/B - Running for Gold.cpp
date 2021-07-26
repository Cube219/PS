#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int r[5];
};

int tNum;
int n;
Node d[50001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < 5; ++j) {
                cin >> d[i].r[j];
            }
        }

        int cur = 0;
        for(int i = 1; i < n; ++i) {
            int cnt = 0;
            for(int j = 0; j < 5; ++j) {
                if(d[cur].r[j] < d[i].r[j]) cnt++;
            }
            if(cnt < 3) {
                cur = i;
            }
        }

        int res = cur;
        for(int i = 0; i < n; ++i) {
            if(res == i) continue;

            int cnt = 0;
            for(int j = 0; j < 5; ++j) {
                if(d[cur].r[j] < d[i].r[j]) cnt++;
            }
            if(cnt < 3) {
                res = -2;
                break;
            }
        }

        cout << res + 1 << "\n";
    }

    return 0;
}
