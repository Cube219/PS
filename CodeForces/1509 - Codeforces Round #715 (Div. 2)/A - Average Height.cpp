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
int n, d[2002];
vector<int> odd, even;

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
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }

        odd.clear();
        even.clear();
        for(int i = 0; i < n; ++i) {
            if(d[i] % 2 == 0) odd.push_back(d[i]);
            else even.push_back(d[i]);
        }
        for(int i = 0; i < odd.size(); ++i) {
            cout << odd[i] << " ";
        }
        for(int i = 0; i < even.size(); ++i) {
            cout << even[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
