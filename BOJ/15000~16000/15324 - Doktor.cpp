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
    int l, r, cen2;
};

int n, d[500005], pos[500005], sum[500005];
vector<Node> ranges;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i];
        pos[d[i]] = i;
    }

    for(int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1];
        if(d[i] == i) sum[i]++;

        int l = i;
        int r = d[i];
        if(l > r) swap(l, r);
        ranges.push_back({ l, r, l + r });
    }
    ranges.push_back({ 1, n, 999999999 });
    sort(ranges.begin(), ranges.end(), [](const Node& l, const Node& r) {
        if(l.cen2 == r.cen2) return l.l > r.l;
        return l.cen2 < r.cen2;
    });

    int res = 0, rl = 1, rr = 1;
    int lastcen = -1;
    int curcnt = 0;
    for(Node& range : ranges) {
        if(lastcen != range.cen2) {
            lastcen = range.cen2;
            curcnt = sum[n];
        }
        curcnt++;
        int v = curcnt - (sum[range.r] - sum[range.l - 1]);
        if(res < v) {
            res = v;
            rl = range.l;
            rr = range.r;
        }
    }

    cout << d[rl] << " " << d[rr];

    return 0;
}
