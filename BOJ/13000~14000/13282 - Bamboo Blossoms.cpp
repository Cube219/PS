#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr int MAXR = 7369791;
int maxdv[MAXR + 1];
int n, m;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 2; i <= MAXR; ++i) {
        for(int j = i * 2; j <= MAXR; j += i) {
            maxdv[j] = i;
        }
    }

    while(1) {
        cin >> m >> n;
        if(n == 0) break;

        int cnt = n;
        for(int i = m; i <= MAXR; ++i) {
            if(maxdv[i] < m) {
                cnt--;
                if(cnt < 0) {
                    cout << i << "\n";
                    break;
                }
            }
        }
    }

    return 0;
}
