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

struct Node
{
    string str;
    int y, m, d;
    bool operator<(const Node& rhs) const
    {
        if(y != rhs.y) return y < rhs.y;
        if(m != rhs.m) return m < rhs.m;
        return d < rhs.d;
    }
};

Node get(const string& str)
{
    Node res;
    res.y = 0;
    res.m = 0;
    res.d = 0;
    res.str = str;
    for(int i = 0; i < 4; ++i) {
        res.y *= 10;
        res.y += str[i] - '0';
    }
    for(int i =0; i < 2; ++i) {
        res.m *= 10;
        res.m += str[4 + i] - '0';
    }
    for(int i = 0; i < 2; ++i) {
        res.d *= 10;
        res.d += str[6 + i] - '0';
    }
    return res;
}

int n;
Node my;
Node d[1001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    cin >> str;
    my = get(str);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> str;
        d[i] = get(str);
        d[i].str = str;
    }
    sort(d, d + n);

    ll mx = 0;
    int res = 0;
    for(int i = 0; i < n; ++i) {
        ll yy = 0;
        for(int j = 0; j < 4; ++j) {
            ll gap = my.str[j] - d[i].str[j];
            yy += gap * gap;
        }
        ll mm = 0;
        for(int j = 4; j < 6; ++j) {
            ll gap = my.str[j] - d[i].str[j];
            mm += gap * gap;
        }
        ll dd = 0;
        for(int j = 6; j < 8; ++j) {
            ll gap = my.str[j] - d[i].str[j];
            dd += gap * gap;
        }

        ll v = yy *mm*dd;
        if(mx < v) {
            mx = v;
            res = i;
        }
    }
    cout << d[res].str;

    return 0;
}
