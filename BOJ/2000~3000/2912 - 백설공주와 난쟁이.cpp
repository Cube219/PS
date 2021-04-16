#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, c, m;
vector<int> t[1050001];
int k[1050001];
int stLeaf;
vector<int> idx[10001];
vector<int> res;

void merge(int node)
{
    auto& cur = t[node];
    auto& lnode = t[node * 2];
    auto& rnode = t[node * 2 + 1];

    auto lit = lnode.begin();
    auto rit = rnode.begin();
    while(lit != lnode.end() && rit != rnode.end()) {
        if(*lit < *rit) {
            cur.push_back(*lit);
            ++lit;
        } else {
            cur.push_back(*rit);
            ++rit;
        }
    }
    cur.insert(cur.end(), lit, lnode.end());
    cur.insert(cur.end(), rit, rnode.end());
    if(cur.size() > 0) {
        k[node] = cur[cur.size() / 2];
    }
}

void construct()
{
    for(int i = stLeaf - 1; i >= 1; --i) {
        merge(i);
    }
}

void find(int cl, int cr, int l, int r, int node)
{
    if(cr < l || r < cl) return;
    else if(l <= cl && cr <= r) {
        res.push_back(k[node]);
        return;
    }
    int m = (cl + cr) / 2;
    find(cl, m, l, r, node * 2);
    find(m + 1, cr, l, r, node * 2 + 1);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> c;
    stLeaf = 1;
    while(stLeaf < n) stLeaf *= 2;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        t[stLeaf + i].push_back(a);
        k[stLeaf + i] = a;
        idx[a].push_back(i);
    }
    construct();

    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        res.clear();
        find(0, stLeaf - 1, a, b, 1);

        bool pos = false;
        int r = -1;
        int req = (b - a + 1) / 2;
        for(int cur : res) {
            auto left = lower_bound(idx[cur].begin(), idx[cur].end(), a);
            auto right = upper_bound(idx[cur].begin(), idx[cur].end(), b);
            int cnt = right - left;
            if(req < cnt) {
                pos = true;
                r = cur;
                break;
            }
        }

        if(pos == true) {
            cout << "yes " << r << "\n";
        } else {
            cout << "no\n";
        }
    }

    return 0;
}
