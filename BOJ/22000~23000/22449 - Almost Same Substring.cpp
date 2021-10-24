#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

struct ZFunc
{
    vector<int> z;

    void build(const string& s)
    {
        int n = (int)s.size();
        z.clear();
        z.resize(s.size());
        for(int i = 1, l = 0, r = 0; i < n; ++i) {
            if(i <= r) z[i] = min(r - i + 1, z[i - l]);
            while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
            if(i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
    }
};

string s, t;
ZFunc zf;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s >> t;

    string str1 = t + '!' + s;
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    string str2 = t + '!' + s;

    zf.build(str1);
    vector<int> pre = zf.z;
    zf.build(str2);
    vector<int> suf = zf.z;

    int res = 0;
    int tsz = t.size();
    for(int i = 0; i < s.size() - tsz + 1; ++i) {
        int prel = pre[tsz + 1 + i];
        int sufl = suf[str1.size() - i - tsz];
        if(prel + sufl == tsz - 1) res++;
    }

    cout << res;

    return 0;
}
