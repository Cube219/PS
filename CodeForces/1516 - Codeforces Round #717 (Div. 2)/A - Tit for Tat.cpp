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
int n, k;
int d[101];
bool isend;

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
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        int curidx = 0;
        isend = false;
        for(int i = 0; i < k; ++i) {
            while(d[curidx] == 0) {
                curidx++;
                if(curidx == n - 1) {
                    isend = true;
                    break;
                }
            }
            if(isend == true) break;
            d[curidx]--;
            d[n - 1]++;
        }
        for(int i = 0; i < n; ++i) {
            cout << d[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
