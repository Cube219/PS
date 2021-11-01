#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

template<int N>
struct SegTree
{
    int t[N * 2 + 1];
    int n;

    void init(int _n)
    {
        n = _n;
    }
    void build()
    {
        for(int i = n - 1; i >= 1; --i) {
            t[i] = min(t[i * 2], t[i * 2 + 1]);
        }
    }

    int find(int l, int r)
    {
        l += n;
        r += n + 1;
        int res = INF;
        while(l < r) {
            if(l & 1) res = min(res, t[l++]);
            if(r & 1) res = min(res, t[--r]);
            l >>= 1; r >>= 1;
        }
        return res;
    }

    void update(int idx, int v)
    {
        idx += n;
        t[idx] = min(t[idx], v);
        idx >>= 1;
        while(idx > 0) {
            t[idx] = min(t[idx * 2], t[idx * 2 + 1]);
            idx >>= 1;
        }
    }
};

int n, m;
int c[100001], pos[100001];
SegTree<100001> sg;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> m >> n;
    for(int i = 0; i < n; ++i) {
        cin >> pos[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    sg.init(n);
    for(int i = 0; i < n; ++i) {
        sg.t[i + n] = INF;
    }
    sg.build();
    int lastr = -1, curl = 0, lastl = -1;
    int curc = c[0];
    int lidx = -1, ridx = -1;

    for(int i = 0; i < n; ++i) {
        if(curc != c[i]) {
            lastr = i - 1;
            lastl = curl;
            curl = i;
            curc = c[i];

            lidx = i - 1;
            ridx = i - 1;
        }

        if(lastr == -1) {
            sg.update(i, 1);
            continue;
        }

        while(lidx >= lastl && pos[lastr] * 2 - pos[i] <= pos[lidx]) {
            lidx--;
        }
        while(ridx >= lastl && pos[ridx] > pos[curl] * 2 - pos[i]) {
            ridx--;
        }
        int res = sg.find(lidx + 1, ridx) + 1;
        res = min(res, sg.find(curl, i - 1) + 1);
        sg.update(i, res);
    }

    int res = sg.find(curl, n - 1);
    cout << res;

    return 0;
}
