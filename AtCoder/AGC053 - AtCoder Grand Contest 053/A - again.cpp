#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
char str[104];
int a[105];
int gap[105];
int res[105];
vector<vector<int>> pr;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> str;
    n++;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int minGap = 987654321;
    for(int i = 0; i < n - 1; ++i) {
        gap[i] = abs(a[i] - a[i + 1]);
        minGap = min(minGap, gap[i]);
    }
    for(int i = 0; i < minGap; ++i) {
        pr.push_back({});
        pr.back().resize(n);
        for(int j = 0; j < n; ++j) {
            pr.back()[j] = (a[j] + i) / minGap;
        }
    }

    cout << pr.size() << "\n";
    for(int i = 0; i < pr.size(); ++i) {
        for(int j = 0; j < n; ++j) {
            cout << pr[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
