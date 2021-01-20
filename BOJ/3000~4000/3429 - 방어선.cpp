#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;

using ll = long long int;

int tNum;
int n, d[200001], d2[200001];
vector<int> m, group;
int res = 0;

int t[600001], lazy[600001], leafN;

void propagate(int node)
{
    if(lazy[node] == -1) return;

    if(node < leafN) {
        lazy[node * 2] = lazy[node];
        lazy[node * 2 + 1] = lazy[node];
    }
    t[node] = lazy[node];
    lazy[node] = -1;
}
void update(int cl, int cr, int l, int r, int node, int v)
{
    propagate(node);

    if(l <= cl && cr <= r) {
        if(t[node] < v) {
            lazy[node] = v;
            propagate(node);
        }
        return;
    }
    if(cr < l || r < cl) return;
    
    int m = (cl + cr) / 2;
    update(cl, m, l, r, node * 2, v);
    update(m + 1, cr, l, r, node * 2 + 1, v);
    if(t[node] < t[node * 2]) t[node] = t[node * 2];
    if(t[node] < t[node * 2 + 1]) t[node] = t[node * 2 + 1];
}
void update(int v, int cnt)
{
    auto it = lower_bound(m.begin(), m.end(), v);
    int idx = it - m.begin();
    update(0, leafN - 1, 0, idx, 1, cnt);
}
int find(int cl, int cr, int l, int r, int node)
{
    propagate(node);

    if(l <= cl && cr <= r) {
        return t[node];
    }
    if(cr < l || r < cl) return 0;

    int m = (cl + cr) / 2;
    int left = find(cl, m, l, r, node * 2);
    int right = find(m + 1, cr, l, r, node * 2 + 1);
    if(left < right) return right;
    else return left;
}
int find(int v)
{
    auto it = upper_bound(m.begin(), m.end(), v);
    if(it == m.end()) return 0;
    
    int idx = it - m.begin();
    return find(0, leafN - 1, idx, m.size() - 1, 1);
}
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        m.clear();
        group.clear();

        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> d[i];
            d2[i] = d[i];
        }
        sort(d2, d2 + n);
        m.push_back(d2[0]);
        for(int i = 1; i < n; i++) {
            if(d2[i - 1] != d2[i]) {
                m.push_back(d2[i]);
            }
        }

        group.push_back(1);
        for(int i = 1; i < n; i++) {
            if(d[i - 1] < d[i]) {
                group.back()++;
            } else {
                group.push_back(1);
            }
        }

        leafN = 1;
        while(leafN < m.size()) {
            leafN *= 2;
        }
        memset(t, 0, 4 * leafN * 2);
        memset(lazy, -1, 4 * leafN * 2);

        if(n == 1) {
            cout << "1\n";
            continue;
        }

        update(d[n - 1], 1);
        int ccnt = 1;
        res = group.back();
        group.back()--;
        for(int i = n - 2; i >= 0; i--) {
            if(d[i] < d[i + 1]) {
                int t = find(d[i]);
                if(group.back() + t > res) {
                    res = group.back() + t;
                }
                ccnt++;
            } else {
                group.pop_back();
                int t = find(d[i]);
                if(group.back() + t > res) {
                    res = group.back() + t;
                }
                ccnt = 1;
            }
            group.back()--;
            update(d[i], ccnt);
        }
        cout << res << "\n";
    }

    return 0;
}
