#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;

struct Node
{
    int x, y;
};

Node st[4];
Node ed[4];
Node cur[4];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
set<ll> mp;
bool pos;

bool has(int x, int y)
{
    for(int i = 0; i < 4; ++i) {
        if(cur[i].x == x && cur[i].y == y) return true;
    }
    return false;
}

ll getkey(Node* d)
{
    vector<int> tmp(4);
    for(int i = 0; i < 4; ++i) {
        tmp[i] = d[i].x * 8 + d[i].y;
    }
    sort(tmp.begin(), tmp.end());
    ll res = 0;
    for(int i = 0; i < 4; ++i) {
        res *= 64;
        res += tmp[i];
    }
    return res;
}

void bt(int idx)
{
    ll key = getkey(cur);
    mp.insert(key);

    if(idx == 4) {
        return;
    }

    for(int i = 0; i < 4; ++i) {
        int x = cur[i].x;
        int y = cur[i].y;
        for(int j = 0; j < 4; ++j) {
            int nx = x + dx[j];
            int ny = y + dy[j];
            if(nx < 0 || ny < 0 || nx >= 8 || ny >= 8) continue;
            if(has(nx, ny) == true) continue;
            cur[i].x = nx;
            cur[i].y = ny;
            bt(idx + 1);
            cur[i].x = x;
            cur[i].y = y;
        }
        for(int j = 0; j < 4; ++j) {
            int nx = x + dx[j] * 2;
            int ny = y + dy[j] * 2;
            if(nx < 0 || ny < 0 || nx >= 8 || ny >= 8) continue;
            if(has(x + dx[j], y + dy[j]) == false) continue;
            cur[i].x = nx;
            cur[i].y = ny;
            bt(idx + 1);
            cur[i].x = x;
            cur[i].y = y;
        }
    }
}

void bt2(int idx)
{
    ll key = getkey(cur);
    if(mp.find(key) != mp.end()) {
        pos = true;
        return;
    }

    if(idx == 4) {
        return;
    }

    for(int i = 0; i < 4; ++i) {
        int x = cur[i].x;
        int y = cur[i].y;
        for(int j = 0; j < 4; ++j) {
            int nx = x + dx[j];
            int ny = y + dy[j];
            if(nx < 0 || ny < 0 || nx >= 8 || ny >= 8) continue;
            if(has(nx, ny) == true) continue;
            cur[i].x = nx;
            cur[i].y = ny;
            bt2(idx + 1);
            if(pos == true) return;
            cur[i].x = x;
            cur[i].y = y;
        }
        for(int j = 0; j < 4; ++j) {
            int nx = x + dx[j] * 2;
            int ny = y + dy[j] * 2;
            if(nx < 0 || ny < 0 || nx >= 8 || ny >= 8) continue;
            if(has(x + dx[j], y + dy[j]) == false) continue;
            cur[i].x = nx;
            cur[i].y = ny;
            bt2(idx + 1);
            if(pos == true) return;
            cur[i].x = x;
            cur[i].y = y;
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

    for(int i = 0; i < 4; ++i) {
        cin >> st[i].x >> st[i].y;
        st[i].x--; st[i].y--;
        cur[i] = st[i];
    }
    for(int i = 0; i < 4; ++i) {
        cin >> ed[i].x >> ed[i].y;
        ed[i].x--; ed[i].y--;
    }

    bt(0);
    for(int i = 0; i < 4; ++i) {
        cur[i] = ed[i];
    }
    bt2(0);
    if(pos == true) cout << "YES";
    else cout << "NO";

    return 0;
}
