#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>

using lli = long long int;

int n;
struct Line
{
    int x1;
    int y1;
    int x2;
    int y2;
};
Line lines[3001];
int parent[3001];
int rank[3001];
int size[3001];

lli ccw(int lineX1, int lineY1, int lineX2, int lineY2, int pX, int pY)
{
    lli vec1X, vec1Y, vec2X, vec2Y;
    vec1X = lineX2 - lineX1;
    vec1Y = lineY2 - lineY1;

    vec2X = pX - lineX2;
    vec2Y = pY - lineY2;

    return vec1X * vec2Y - vec2X * vec1Y;
}

bool IsCross(int aIdx, int bIdx)
{
    Line a = lines[aIdx];
    Line b = lines[bIdx];

    lli accw = ccw(a.x1, a.y1, a.x2, a.y2, b.x1, b.y1) * ccw(a.x1, a.y1, a.x2, a.y2, b.x2, b.y2);
    lli bccw = ccw(b.x1, b.y1, b.x2, b.y2, a.x1, a.y1) * ccw(b.x1, b.y1, b.x2, b.y2, a.x2, a.y2);

    if(accw == 0 && bccw == 0) {
        if(a.x1 > a.x2) std::swap(a.x1, a.x2);
        if(a.y1 > a.y2) std::swap(a.y1, a.y2);
        if(b.x1 > b.x2) std::swap(b.x1, b.x2);
        if(b.y1 > b.y2) std::swap(b.y1, b.y2);

        if(a.x2 < b.x1) return false;
        if(a.y2 < b.y1) return false;
        if(b.x2 < a.x1) return false;
        if(b.y2 < a.y1) return false;

        return true;

        // return a.x2 >= b.x1 && a.x1 <= b.x2;
    }

    return accw <= 0 && bccw <= 0;
}

int findRoot(int i)
{
    if(parent[i] == i) return i;

    int res = findRoot(parent[i]);
    parent[i] = res;
    return res;
}

void merge(int a, int b)
{
    int aRoot = findRoot(a);
    int bRoot = findRoot(b);

    if(aRoot == bRoot) return;

    if(rank[aRoot] > rank[bRoot]) std::swap(aRoot, bRoot);
    parent[aRoot] = bRoot;
    size[bRoot] += size[aRoot];
    if(rank[aRoot] == rank[bRoot]) rank[bRoot]++;
}

int main(void)
{
   // freopen("input.txt", "r", stdin);

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        lines[i] = {x1, y1, x2, y2};
        parent[i] = i;
        rank[i] = 1;
        size[i] = 1;
    }

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(IsCross(i, j) == true) {
                merge(i, j);
            }
        }
    }
    int maxSize = -1, cnt = 0;
    for(int i = 0; i < n; i++) {
        if(parent[i] == i) {
            cnt++;
            if(maxSize < size[i]) {
                maxSize = size[i];
            }
        }
    }

    printf("%d\n%d", cnt, maxSize);

    return 0;
}
