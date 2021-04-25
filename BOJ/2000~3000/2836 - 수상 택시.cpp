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
    int x;
    bool isright;
};

int n, m;
vector<Node> d;
ll res = 0;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        if(a < b) continue;
        d.push_back({ b, false });
        d.push_back({ a, true });
    }
    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        return l.x < r.x;
    });

    res = m;
    int cnt = 0, lastx = 0;
    for(int i = 0; i < d.size(); ++i) {
        if(d[i].isright == false) {
            if(cnt == 0) lastx = d[i].x;
            cnt++;
        } else {
            cnt--;
            if(cnt == 0) {
                res += 2ll * (d[i].x - lastx);
            }
        }
    }

    cout << res;

    return 0;
}
