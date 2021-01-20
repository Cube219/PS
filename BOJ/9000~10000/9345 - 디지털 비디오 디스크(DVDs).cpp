#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
using namespace std;

using lli = long long int;

int tNum;
int n, k;
pair<int, int> t[300001];
int stLeaf;
int book[300001];

void init()
{
    stLeaf = 1;
    while(stLeaf < n) {
        stLeaf *= 2;
    }

    for(int i = 1; i <= stLeaf * 2; i++) {
        t[i] = { -1, -1 };
    }
    for(int i = 0; i < n; i++) {
        book[i] = i;
    }

    for(int i = 0; i < n; i++) {
        int current = stLeaf + i;
        int r = i;
        while(current > 0) {
            if(t[current].first == -1 || t[current].first > r) {
                t[current].first = r;
            }
            if(t[current].second == -1 || t[current].second < r) {
                t[current].second = r;
            }

            current /= 2;
        }
    }
}

pair<int, int> p(int cl, int cr, int l, int r, int node)
{
    if(l <= cl && cr <= r) return t[node];
    else if(cr < l || r < cl) return { -1, -1 };

    int m = (cl + cr) / 2;

    auto left = p(cl, m, l, r, node * 2);
    auto right = p(m + 1, cr, l, r, node * 2 + 1);

    int min = left.first;
    if(min == -1) min = 987654321;
    if(right.first != -1 && min > right.first) min = right.first;
    else if(right.second != -1 && min > right.second) min = right.second;

    int max = left.second;
    if(right.second != -1 && max < right.second) max = right.second;
    else if(right.first != -1 && max < right.first) max = right.first;

    return { min, max };
}

void update(int node)
{
    while(node > 0) {
        auto left = t[node * 2];
        auto right = t[node * 2 + 1];

        int min = left.first;
        if(min == -1) min = 987654321;
        if(right.first != -1 && min > right.first) min = right.first;
        else if(right.second != -1 && min > right.second) min = right.second;

        int max = left.second;
        if(right.second != -1 && max < right.second) max = right.second;
        else if(right.first != -1 && max < right.first) max = right.first;

        t[node] = { min, max };

        node /= 2;
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;

        init();

        for(int i = 0; i < k; i++) {
            int q, a, b;
            cin >> q >> a >> b;

            if(q == 0) {
                int node = stLeaf + a;
                int aVal = t[node].first;

                node = stLeaf + b;
                int bVal = t[node].first;
                
                int tmp = aVal;
                aVal = bVal;
                bVal = tmp;

                node = stLeaf + a;
                t[node] = { aVal, aVal };
                update(node / 2);

                node = stLeaf + b;
                t[node] = { bVal, bVal };
                update(node / 2);
            } else {
                auto res = p(0, stLeaf - 1, a, b, 1);
                if(res.first == a && res.second == b) {
                    cout << "YES\n";
                } else {
                    cout << "NO\n";
                }
            }
        }
    }

    return 0;
}
