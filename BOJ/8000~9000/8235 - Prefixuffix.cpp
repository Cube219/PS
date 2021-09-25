#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

using ll = long long int;

struct Manacher
{
    // d1: ab c ba -> 2
    // d2: ab b a -> 2
    vector<int> d1, d2;

    void build(const string& str)
    {
        int n = str.size();
        d1.clear();
        d2.clear();

        d1.resize(n);
        int l = 0, r = -1;
        /*for(int i = 0; i < n; ++i) {
            int k = 1;
            if(i <= r) {
                k = min(d1[l + r - i], r - i);
            }
            while(0 <= i - k && i + k < n && str[i - k] == str[i + k]) k++;
            d1[i] = --k;
            if(i + k > r) {
                r = i + k;
                l = i - k;
            }
        }*/

        d2.resize(n);
        l = 0;
        r = -1;
        for(int i = 0; i < n; ++i) {
            int k = 0;
            if(i <= r) {
                k = min(d2[l + r - i + 1], r - i);
            }
            while(0 <= i - k - 1 && i + k < n && str[i - k - 1] == str[i + k]) k++;
            d2[i] = k--;
            if(i + k > r) {
                r = i + k - 1;
                l = i - k;
            }
        }
    }
};

int n;
string str;
Manacher m;
set<int> pre;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> str;
    string str2;
    str2.resize(n);
    int l = 0, r = n - 1;
    for(int i = 0; i < n; ++i) {
        if((i & 1) == 0) {
            str2[i] = str[l];
            l++;
        } else {
            str2[i] = str[r];
            r--;
        }
    }
    m.build(str2);

    int res = 0;
    for(int i = 1; i < n; ++i) {
        if(m.d2[i] == 0) continue;

        l = i - m.d2[i];
        r = i + m.d2[i] - 1;
        auto it = pre.lower_bound(l - 1);
        if(it != pre.end()) {
            int offset = *it - l - 1;
            if(offset < m.d2[i]) {
                res = max(res, r - offset);
            }
        }

        if(l == 0) {
            res = max(res, r + 1);
            pre.insert(r);
        }
    }

    cout << res / 2;

    return 0;
}
    