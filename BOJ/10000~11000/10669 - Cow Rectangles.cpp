#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
struct Cow
{
    int x;
    int y;
    char ch;
};
Cow d[501];

struct Node
{
    int hNum;
    int gNum;

    int minY;
    int maxY;
    int minX;
    int maxX;
};
struct LRNode
{
    int hNum;
    int minY;
    int maxY;
    int minX;
    int maxX;
};
constexpr int ttt = sizeof(Node);
Node t[3001];
LRNode lt[3001], rt[3001];
int stLeaf;
int res, res2;
bool isComp[1001];

void up(int node)
{
    Node& cur = t[node];
    Node& left = t[node * 2];
    Node& right = t[node * 2 + 1];

    LRNode& cl = lt[node];
    LRNode& cr = rt[node];
    LRNode& ll = lt[node * 2];
    LRNode& lr = rt[node * 2];
    LRNode& rl = lt[node * 2 + 1];
    LRNode& rr = rt[node * 2 + 1];

    if(left.hNum > right.hNum) {
        cur = left;
    } else {
        cur = right;
    }
    cur.gNum = left.gNum + right.gNum;

    int midNum = lr.hNum + rl.hNum;
    if(cur.hNum < midNum) {
        cur.hNum = midNum;
        cur.minY = min(cur.minY, lr.minY);
        cur.minY = min(cur.minY, rl.minY);
        cur.maxY = max(cur.maxY, lr.maxY);
        cur.maxY = max(cur.maxY, rl.maxY);
        cur.minX = min(cur.minX, lr.minX);
        cur.minX = min(cur.minX, rl.minX);
        cur.maxX = max(cur.maxX, lr.maxX);
        cur.maxX = max(cur.maxX, rl.maxX);
    }

    cl = ll;
    cr = rr;
    if(left.gNum == 0) {
        cl.hNum += rl.hNum;
        cl.minY = min(cl.minY, rl.minY);
        cl.maxY = max(cl.maxY, rl.maxY);
        cl.minX = min(cl.minX, rl.minX);
        cl.maxX = max(cl.maxX, rl.maxX);
    }
    if(right.gNum == 0) {
        cr.hNum += lr.hNum;
        cr.minY = min(cr.minY, lr.minY);
        cr.maxY = max(cr.maxY, lr.maxY);
        cr.minX = min(cr.minX, lr.minX);
        cr.maxX = max(cr.maxX, lr.maxX);
    }
}

void updateLeaf(int idx)
{
    int tIdx = stLeaf + d[idx].y;
    if(d[idx].ch == 'H') {
        if(t[tIdx].gNum == 0) {
            t[tIdx].hNum++;
            lt[tIdx].hNum++;
            rt[tIdx].hNum++;
            t[tIdx].minX = min(t[tIdx].minX, d[idx].x);
            t[tIdx].maxX = max(t[tIdx].maxX, d[idx].x);
            t[tIdx].minY = d[idx].y;
            t[tIdx].maxY = d[idx].y;
            lt[tIdx].minX = t[tIdx].minX;
            lt[tIdx].maxX = t[tIdx].maxX;
            lt[tIdx].minY = d[idx].y;
            lt[tIdx].maxY = d[idx].y;

            rt[tIdx] = lt[tIdx];
        }
    } else {
        t[tIdx].gNum++;
        t[tIdx].hNum = 0;
        lt[tIdx].hNum = 0;
        lt[tIdx].minX = 1001;
        lt[tIdx].maxX = -1;
        lt[tIdx].minY = 1001;
        lt[tIdx].maxY = -1;
        rt[tIdx] = lt[tIdx];
    }
    tIdx /= 2;
    while(tIdx > 0) {
        up(tIdx);
        tIdx /= 2;
    }
}

void check()
{
    int area = (t[1].maxX - t[1].minX) * (t[1].maxY - t[1].minY);
    if(res < t[1].hNum) {
        res = t[1].hNum;
        res2 = area;
    } else if(res == t[1].hNum) {
        res2 = min(res2, area);
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].x >> d[i].y >> d[i].ch;
    }
    sort(d, d + n, [](auto& l, auto& r) {
        if(l.x == r.x)return l.y < r.y;
        else return l.x < r.x;
    });

    stLeaf = 1;
    while(stLeaf < 1001) stLeaf *= 2;

    for(int i = 0; i < n; ++i) {
        if(isComp[d[i].x] == true) continue;
        isComp[d[i].x] = true;

        for(int j = 0; j < stLeaf; ++j) {
            t[stLeaf + j] = { 0, 0, 1001, -1, 1001, -1 };
            lt[stLeaf + j] = { 0, 1001, -1, 1001, -1 };
            rt[stLeaf + j] = { 0, 1001, -1, 1001, -1 };
        }
        for(int j = stLeaf - 1; j > 0; --j) {
            up(j);
        }
        int lastX = d[i].x;
        for(int j = i; j < n; ++j) {
            if(lastX == d[j].x) {
                updateLeaf(j);
            } else {
                check();
                lastX = d[j].x;
                updateLeaf(j);
            }
        }
        check();
    }

    cout << res << "\n";
    cout << res2;

    return 0;
}
