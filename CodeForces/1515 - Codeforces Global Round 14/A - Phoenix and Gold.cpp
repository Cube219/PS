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
int n, x;
int d[101];
vector<int> res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> x;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        sort(d, d + n, [](const int& l, const int& r) {
            return l > r;
        });
        res.clear();
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            if(sum + d[i] == x) {
                if(i == n - 1) {
                    res.clear();
                    break;
                }
                res.push_back(d[n - 1]);
                n--;
            }
            sum += d[i];
            res.push_back(d[i]);
        }
        if(res.size() == 0) cout << "NO\n";
        else {
            cout << "YES\n";
            for(int i = 0; i < res.size(); ++i) {
                cout << res[i] << " ";
            }
            cout<<"\n";
        }
    }

    return 0;
}
