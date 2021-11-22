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
int n, a, b;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> a >> b;
        vector<int> has(n + 1, 0), res(n);
        int i1 = 0, i2 = n / 2;

        has[a] = 1;
        has[b] = 1;
        res[i1++] = a;
        res[i2++] = b;

        bool pos = true;
        for(int i = a - 1; i >= 1; --i) {
            if(has[i] == 1) continue;
            if(i2 == n) {
                pos = false;
                break;
            }
            if(i >= b) {
                pos = false;
                break;
            }
            res[i2++] = i;
            has[i] = 1;
        }

        for(int i = b + 1; i <= n; ++i) {
            if(has[i] == 1) continue;
            if(i1 == n / 2) {
                pos = false;
                break;
            }
            if(i <= a) {
                pos = false;
                break;
            }
            res[i1++] = i;
            has[i] = 1;
        }

        for(int i = 1; i <= n; ++i) {
            if(has[i] == 1) continue;
            if(i1 < n / 2) {
                res[i1++] = i;
            } else {
                if(i2 == n) {
                    pos = false;
                    break;
                }
                res[i2++] = i;
            }
        }

        if(pos == false) {
            cout << "-1\n";
        } else {
            for(int i = 0; i < res.size() - 1; ++i) {
                cout << res[i] << " ";
            }
            cout << res.back() << "\n";
        }
    }

    return 0;
}
