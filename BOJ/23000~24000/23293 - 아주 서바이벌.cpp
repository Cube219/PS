#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int pos;
    int has[60];
    bool ban;
};

int t, n;
Node d[100005];
vector<int> lg;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t >> n;
    for(int i = 1; i <= n; ++i) {
        d[i].pos = 1;
    }

    for(int i = 0; i < t; ++i) {
        int lnum, p, v;
        char c;
        cin >> lnum >> p >> c >> v;
        if(c == 'M') {
            d[p].pos = v;
        } else if(c == 'F') {
            if(d[p].pos != v) {
                lg.push_back(lnum);
            }
            d[p].has[v]++;
        } else if(c == 'C') {
            int v2;
            cin >> v2;
            if(d[p].has[v] == 0) {
                lg.push_back(lnum);
            } else if(d[p].has[v2] == 0) {
                lg.push_back(lnum);
            }
            d[p].has[v] = max(0, d[p].has[v] - 1);
            d[p].has[v2] = max(0, d[p].has[v2] - 1);
        } else { // A
            if(d[p].pos != d[v].pos) {
                lg.push_back(lnum);
                d[p].ban = true;
            }
        }
    }

    sort(lg.begin(), lg.end());
    cout << lg.size() << "\n";
    for(int l : lg) {
        cout << l << " ";
    }
    if(lg.size() > 0) cout << "\n";

    int bnum = 0;
    for(int i = 1; i <= n; ++i) {
        if(d[i].ban == true) bnum++;
    }
    cout << bnum << "\n";
    for(int i = 1; i <= n; ++i) {
        if(d[i].ban == true) cout << i << " ";
    }

    return 0;
}
