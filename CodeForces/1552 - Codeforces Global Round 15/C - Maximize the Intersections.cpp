#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

int tNum;
int n, k;
bool d[205];
int p[205];
int line[205][2];
int curcnt;
bool has[205];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;

        int res = 0;
        int remain = n * 2 - k * 2;
        for(int i = 0; i < remain / 2; ++i) {
            res += i;
        }
        n *= 2;
        for(int i = 0; i < n; ++i) {
            d[i] = false;
            p[i] = 0;
        }

        for(int i = 0; i < k; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            d[a] = true;
            d[b] = true;
            p[a] = i + 1;
            p[b] = i + 1;
            if(a > b) swap(a, b);
            line[i][0] = a;
            line[i][1] = b;
        }

        int cc = 0;
        for(int i = 0; i < k; ++i) {
            int a = line[i][0];
            int b = line[i][1];
            for(int j = 0; j < n; ++j) {
                has[j] = false;
            }
            curcnt = 0;
            for(int j = a + 1; j < b; ++j) {
                int v = p[j];
                if(v == 0) continue;
                if(has[v] == false) {
                    curcnt++;
                    has[v] = true;
                } else {
                    curcnt--;
                    has[v] = false;
                }
            }
            cc += curcnt;
        }
        res += cc / 2;

        for(int i = 0; i < k; ++i) {
            int cnt;
            int r = INF;
            int a = line[i][0];
            int b = line[i][1];

            cnt = 0;
            for(int j = a; j <= b; ++j) {
                if(d[j] == false) cnt++;
            }
            r = min(r, cnt);

            cnt = 0;
            for(int j = b; j != a; ) {
                if(d[j] == false) cnt++;

                j++;
                j %= n;
            }
            r = min(r, cnt);
            res += r;
        }
        cout << res << "\n";
    }

    return 0;
}
