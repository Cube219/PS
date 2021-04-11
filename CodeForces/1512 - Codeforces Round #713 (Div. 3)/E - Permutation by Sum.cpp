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
int n, l, r, s;
bool has[502];
int res[502];
bool pos;
int buf[502];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> l >> r >> s;

        for(int i = 1; i <= n; ++i) {
            has[i] = false;
            res[i] = 0;
        }
        pos = true;

        int cnt = r - l + 1;
        int cur = 0;
        for(int i = 0; i < cnt; ++i) {
            buf[i] = i + 1;
            cur += i + 1;
        }
        int gap = s - cur;
        if(gap >= 0) {
            for(int i = 0; i < cnt; ++i) {
                buf[i] += gap / cnt;
                cur += gap / cnt;
            }
            gap = gap % cnt;
            for(int i = cnt - 1; i >= 0; --i) {
                if(gap == 0) break;
                buf[i]++;
                gap--;
            }
            if(buf[cnt - 1] > n) pos = false;
            else {
                for(int i = 0; i < cnt; ++i) {
                    res[l + i] = buf[i];
                    has[buf[i]] = true;
                }
                int curIdx = 1;
                for(int i = 1; i <= n; ++i) {
                    if(res[i] != 0) continue;
                    while(has[curIdx] == true) curIdx++;
                    res[i] = curIdx;
                    has[curIdx] = true;
                }
            }
        } else {
            pos = false;
        }

        if(pos == false) {
            cout << "-1\n";
        } else {
            for(int i = 1; i <= n; ++i) {
                cout << res[i] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
