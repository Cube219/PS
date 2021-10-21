#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;

struct Query
{
    int idx, l, r;
};
int sq = 100;

struct Node
{
    int id, num;
};

int n, m;
int d[100001];
vector<int> vv;
Query q[100001];
int res[100001];
int cnt[100001];
Node cntsq[100001];
bool dirty[100001];

int getv(int v)
{
    return lower_bound(vv.begin(), vv.end(), v) - vv.begin();
}

void add(int v)
{
    cnt[v]++;
    int vsq = v / sq;
    if(cntsq[vsq].num < cnt[v]) {
        cntsq[vsq].num = cnt[v];
        cntsq[vsq].id = v;
    } else if(cntsq[vsq].num == cnt[v] && cntsq[vsq].id < v) {
        cntsq[vsq].id = v;
    }
}

void remove(int v)
{
    int vsq = v / sq;
    if(cntsq[vsq].id == v) {
        dirty[vsq] = true;
    }

    cnt[v]--;
}

int get()
{
    int num = 0;
    int res = 0;
    for(int i = (vv.size() - 1) / sq; i >= 0; --i) {
        if(dirty[i] == true) {
            cntsq[i].num = 0;
            for(int j = min((i + 1) * sq, (int)vv.size()) - 1; j >= i * sq; --j) {
                if(cntsq[i].num < cnt[j]) {
                    cntsq[i].num = cnt[j];
                    cntsq[i].id = j;
                }
            }
            dirty[i] = false;
        }
        if(num < cntsq[i].num) {
            num = cntsq[i].num;
            res = cntsq[i].id;
        }
    }

    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        vv.push_back(d[i]);
    }
    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());
    for(int i = 0; i < n; ++i) {
        d[i] = getv(d[i]);
    }

    sq = (int)sqrt(n);
    sq = max(sq, (int)sqrt(vv.size()));

    for(int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        q[i] = { i, l - 1, r - 1 };
    }
    sort(q, q + m, [](const Query& a, const Query& b) {
        if(a.l / sq != b.l / sq) return a.l < b.l;
        return a.l / sq & 1 ? a.r > b.r : a.r < b.r;
    });

    int cl = q[0].l, cr = q[0].l;
    add(d[q[0].l]);
    for(int i = 0; i < m; ++i) {
        int l = q[i].l, r = q[i].r;
        while(l < cl) {
            add(d[cl - 1]);
            cl--;
        }
        while(cr < r) {
            add(d[cr + 1]);
            cr++;
        }
        while(cl < l) {
            remove(d[cl]);
            cl++;
        }
        while(r < cr) {
            remove(d[cr]);
            cr--;
        }
        res[q[i].idx] = get();
    }

    for(int i = 0; i < m; ++i) {
        cout << vv[res[i]] << "\n";
    }

    return 0;
}
