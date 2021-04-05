#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, k;
struct Node
{
    string str;
    bool isSame;
    string pre;
    string dummy;
    string suf;
};
Node d[501];
bool res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].str;
    }

    for(int i = 0; i < n - k + 1; ++i) {
        for(int j = 0; j < n; ++j) {
            d[j].pre = d[j].str.substr(0, i);
            d[j].dummy = d[j].str.substr(i, k);
            d[j].suf = d[j].str.substr(i + k);
            sort(d[j].dummy.begin(), d[j].dummy.end());
        }
        sort(d, d + n, [](const auto& l, const auto& r) {
            if(l.pre == r.pre) {
                if(l.suf == r.suf) return l.dummy < r.dummy;
                else return l.suf < r.suf;
            } else  return l.pre < r.pre;
        });
        for(int j = 0; j < n - 1; ++j) {
            if(d[j].pre == d[j+1].pre && d[j].suf == d[j+1].suf && d[j].dummy == d[j+1].dummy) {
                res = true;
                break;
            }
        }
        if(res == true) break;
    }

    if(res == true) cout << "DA";
    else cout << "NE";

    return 0;
}
