#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, q;
int a[300001];
int first[51];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        if(first[a[i]] == 0) first[a[i]] = i;
    }

    for(int i = 0; i < q; ++i) {
        int qu;
        cin >> qu;
        cout << first[qu] << " ";

        for(int j = 1; j <= 50; ++j) {
            if(first[j] < first[qu]) {
                first[j]++;
            }
        }
        first[qu] = 1;
    }

    return 0;
}
