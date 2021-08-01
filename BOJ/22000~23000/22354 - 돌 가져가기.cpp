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
    int v;
    char ch;
    bool operator<(const Node& rhs)
    {
        return v < rhs.v;
    }
};

int n;
char str[300005];
int a[300005];
vector<Node> d;
vector<Node> black, white;
ll res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> str;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    d.push_back({ a[0], str[0] });
    for(int i = 1; i < n; ++i) {
        if(d.back().ch == str[i]) {
            d.back().v = max(d.back().v, a[i]);
        } else {
            d.push_back({ a[i], str[i] });
        }
    }

    for(int i = 1; i < d.size() - 1; ++i) {
        if(d[i].ch == 'B') black.push_back(d[i]);
        else white.push_back(d[i]);
    }
    sort(black.begin(), black.end());
    sort(white.begin(), white.end());

    if(d[0].ch == d.back().ch) {
        if(d.back().ch == 'B') {
            if(white.size() > 0) {
                res += white.back().v;
                white.pop_back();
            }
        } else {
            if(black.size() > 0) {
                res += black.back().v;
                black.pop_back();
            }
        }
    }
    vector<int> r;
    for(auto& v : black) {
        r.push_back(v.v);
    }
    for(auto& v : white) {
        r.push_back(v.v);
    }
    sort(r.begin(), r.end());
    for(int i = r.size() / 2; i < r.size(); ++i) {
        res += r[i];
    }

    cout << res;

    return 0;
}
