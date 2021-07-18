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
int n, a[200003];
vector<int> d[200005];
int res[200005], num, rev[200005];
bool comp[200005];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;

        for(int i = 0; i <= n; ++i) {
            d[i].clear();
            comp[i] = false;
            res[i] = 0;
        }
        num = 0;

        for(int i = 1; i <= n; ++i) {
            cin >> a[i];
            d[a[i]].push_back(i);
        }

        for(int i = 1; i <= n; ++i) {
            if(d[i].size() == 0) continue;
            res[d[i][0]] = i;
            rev[i] = d[i][0];
            comp[i] = true;
            num++;
        }

        vector<int> r1, r2;
        for(int i = 1; i <= n; ++i) {
            if(comp[i] == false) r2.push_back(i);
        }
        for(int i = 1; i <= n; ++i) {
            if(res[i] == 0) {
                res[i] = r2.back();
                r2.pop_back();
            }
        }

        vector<int> same;
        for(int i = 1; i <= n; ++i) {
            if(res[i] == i) {
                same.push_back(i);
            }
        }

        if(same.size()  == 1) {
            int t = same[0];
            int bf = d[a[t]][0];
            res[t] = a[t];
            res[bf] = t;
        } else if(same.size() > 0) {
            same.push_back(same[0]);
            for(int i = 0; i < same.size(); ++i) {
                res[same[i]] = same[i + 1];
            }
        }

        cout << num << "\n";
        for(int i = 1; i <= n; ++i) {
            cout << res[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
