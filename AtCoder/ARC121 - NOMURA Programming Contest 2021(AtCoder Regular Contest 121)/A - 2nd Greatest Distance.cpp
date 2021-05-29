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
    int x, y, idx;
};

int n;
Node d[200001];
vector<pair<ll, pair<int, int>>> res;

bool has(int a, int b)
{
    if(a > b) swap(a, b);
    for(int i = 0; i < res.size(); ++i) {
        if(res[i].second.first == a && res[i].second.second == b) return true;
    }
    return false;
}

void add(int a, int b, int idxa, int idxb, bool isx)
{
    if(a == b) return;
    int dx = abs(d[a].x - d[b].x);
    int dy = abs(d[a].y - d[b].y);
    if(dx > dy) {
        if(has(idxa, idxb) == false) {
            if(idxa > idxb) swap(idxa, idxb);
            res.push_back({ dx, { idxa, idxb } });
        }
    } else {
        if(has(idxa, idxb) == false) {
            if(idxa > idxb) swap(idxa, idxb);
            res.push_back({ dy, { idxa, idxb } });
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].x >> d[i].y;
        d[i].idx = i;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.x < r.x;
    });
    for(int i = 0; i <= 2; ++i) {
        for(int j = n - 1; j >= n - 3; --j) {
            add(i, j, d[i].idx, d[j].idx, true);
        }
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.y < r.y;
    });
    for(int i = 0; i <= 2; ++i) {
        for(int j = n - 1; j >= n - 3; --j) {
            add(i, j, d[i].idx, d[j].idx, false);
        }
    }

    sort(res.begin(), res.end(), [](const auto& l, const auto& r) {
        return l.first > r.first;
    });

    cout << res[1].first;


    return 0;
}
