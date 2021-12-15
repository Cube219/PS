#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        ll x[2], p[2];
        cin >> x[0] >> p[0] >> x[1] >> p[1];

        int c[2] = { 0, 0 };
        for(int i = 0; i < 2; ++i) {
            int tmp = x[i];
            while(tmp > 0) {
                c[i]++;
                tmp /= 10;
            }
        }

        if(c[0] + p[0] > c[1] + p[1]) {
            cout << ">\n";
            continue;
        } else if(c[0] + p[0] < c[1] + p[1]) {
            cout << "<\n";
            continue;
        } else {
            if(c[0] - c[1] < 0) {
                for(int i = 0; i < c[1] - c[0]; ++i) {
                    x[0] *= 10;
                }
            } else {
                for(int i = 0; i < c[0] - c[1]; ++i) {
                    x[1] *= 10;
                }
            }

            if(x[0] < x[1]) {
                cout << "<\n";
            } else if(x[0] > x[1]) {
                cout << ">\n";
            } else {
                cout << "=\n";
            }
        }
    }

    return 0;
}
