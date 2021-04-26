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
int d[101];
bool has[200001];
int idx[200001], idx2[200001];
int sum;
int lea[2001];

void solve()
{
    int s2 = sum / 2;
    int t = -1;
    int minf = 987654321;
    sort(d, d + n);
    for(int i = 0; i < n; ++i) {
        for(int j = 200000; j >= 0; --j) {
            if(has[j] == false) continue;

            has[j + d[i]] = true;
            if(j + d[i] == s2) {
                minf = min(minf, idx[j]);
            }
            idx[j + d[i]] = idx[j];
        }
        if(has[d[i]] == false) {
            has[d[i]] = true;
            idx[d[i]] = d[i];
            if(d[i] == s2) minf = min(minf, d[i]);
        }
    }
    if(has[s2] == false) {
        cout << "0";
        return;
    }
    if(minf == s2) {
        cout << "1\n";
        cout << lea[d[0]];
    } else {
        cout << "1\n";
        cout << lea[minf];
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        sum += d[i];
        if(lea[d[i]] == 0) {
            lea[d[i]] = i + 1;
        }
    }
    if(sum % 2 == 1) {
        cout << "0";
    } else {
        solve();
    }

    return 0;
}
