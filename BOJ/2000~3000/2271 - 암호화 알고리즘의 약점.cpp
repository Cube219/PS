#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;

int tNum;
int n, d[5001];
set<int> s;
bool pos;

bool ck()
{
    int curmax = -1;
    s.clear();
    s.insert(-d[0]);
    for(int i = 1; i < n - 2; ++i) {
        curmax = d[i + 1];
        for(int j = i + 2; j < n; ++j) {
            if(d[i] < d[j] && curmax > d[j]) {
                auto it = s.upper_bound(-curmax);
                if(it != s.end() && -(*it) > d[j]) {
                    return true;
                }
            }
            curmax = max(curmax, d[j]);
        }
        s.insert(-d[i]);
    }
    return false;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        s.clear();
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }

        pos = ck();
        if(pos == false) {
            for(int i = 0; i < n; ++i) {
                d[i] = -d[i];
            }
            pos = ck();
        }
        if(pos == true) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
