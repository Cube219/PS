#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;

vector<int> mst[300001];
int stLeaf;

void init()
{
    for(int i = stLeaf - 1; i > 0; --i) {
        auto& cur = mst[i];
        auto& left = mst[i * 2];
        auto& right = mst[i * 2 + 1];

        cur.clear();
        auto lit = left.begin();
        auto rit = right.begin();
        while(lit != left.end() && rit != right.end()) {
            if(*lit < *rit) {
                cur.push_back(*lit);
                ++lit;
            } else {
                cur.push_back(*rit);
                ++rit;
            }
        }
        cur.insert(cur.end(), lit, left.end());
        cur.insert(cur.end(), rit, right.end());
    }
}

int query(int cl, int cr, int l, int r, int node, int k)
{
    if(cr < l || r < cl) return 0;
    else if(l <= cl && cr <= r) {
        return mst[node].end() - upper_bound(mst[node].begin(), mst[node].end(), k);
    }
    int m = (cl + cr) / 2;
    return query(cl, m, l, r, node * 2, k) + query(m + 1, cr, l, r, node * 2 + 1, k);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    stLeaf = 1;
    while(stLeaf < n) stLeaf *= 2;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        mst[stLeaf + i].push_back(a);
    }
    init();
    cin >> m;
    int last = 0;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        int l = a ^ last;
        int r = b ^ last;
        int k = c ^ last;

        last = query(0, stLeaf - 1, l - 1, r - 1, 1, k);
        cout << last << "\n";
    }

    return 0;
}
