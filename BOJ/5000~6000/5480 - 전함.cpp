#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, k, l;

#define NO_LASER 987654321
struct Craft
{
    int x1;
    int y1;
    int x2;
    int y2;
    int w;
};
bool operator<(const Craft& l, const Craft& r)
{
    return l.w > r.w;
}
Craft d[100001];
int res[100001];

vector<int> xIdx;
vector<int> yIdx;

struct Laser
{
    int pos;
    int flag;
};
Laser lasers[100001];

int xt[400001], yt[400001];
int xLeafStart, yLeafStart;

int getXIdx(int v)
{
    return lower_bound(xIdx.begin(), xIdx.end(), v) - xIdx.begin();
}

int getYIdx(int v)
{
    return lower_bound(yIdx.begin(), yIdx.end(), v) - yIdx.begin();
}

int search(int cl, int cr, int l, int r, int node, int* tree)
{
    if(l <= cl && cr <= r) return tree[node];
    if(cr < l || r < cl) return NO_LASER;

    int m = (cl + cr) / 2;

    int a = search(cl, m, l, r, node * 2, tree);
    int b = search(m + 1, cr, l, r, node * 2 + 1, tree);

    if(a < b) return a;
    else return b;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        xIdx.clear();
        yIdx.clear();

        cin >> n >> k >> l;
        for(int i = 0; i < k; i++) {
            int x1, y1, x2, y2, w;
            cin >> x1 >> y1 >> x2 >> y2 >> w;

            if(x1 > x2) swap(x1, x2);
            if(y1 > y2) swap(y1, y2);

            d[i] = { x1, y1, x2, y2, w };
        }
        sort(d, d + k);

        for(int i = 0; i < l; i++) {
            int flag, pos;
            cin >> pos >> flag;
            if(flag == 0) {
                yIdx.push_back(pos);
            } else {
                xIdx.push_back(pos);
            }
            lasers[i] = { pos, flag };
            res[i] = 0;
        }
        sort(xIdx.begin(), xIdx.end());
        xIdx.erase(unique(xIdx.begin(), xIdx.end()), xIdx.end());
        sort(yIdx.begin(), yIdx.end());
        yIdx.erase(unique(yIdx.begin(), yIdx.end()), yIdx.end());

        xLeafStart = 1;
        while(xLeafStart < xIdx.size()) {
            xLeafStart *= 2;
        }
        for(int i = 0; i < xLeafStart; i++) {
            xt[xLeafStart + i] = NO_LASER;
        }
        for(int i = 0; i < l; i++) {
            if(lasers[i].flag == 0) continue;
            int idx = getXIdx(lasers[i].pos);
            if(xt[xLeafStart + idx] > i) {
                xt[xLeafStart + idx] = i;
            }
        }
        for(int i = xLeafStart - 1; i >= 1; i--) {
            xt[i] = min(xt[i * 2], xt[i * 2 + 1]);
        }

        yLeafStart = 1;
        while(yLeafStart < yIdx.size()) {
            yLeafStart *= 2;
        }
        for(int i = 0; i < yLeafStart; i++) {
            yt[yLeafStart + i] = NO_LASER;
        }
        for(int i = 0; i < l; i++) {
            if(lasers[i].flag == 1) continue;
            int idx = getYIdx(lasers[i].pos);
            if(yt[yLeafStart + idx] > i) {
                yt[yLeafStart + idx] = i;
            }
        }
        for(int i = yLeafStart - 1; i >= 1; i--) {
            yt[i] = min(yt[i * 2], yt[i * 2 + 1]);
        }

        for(int i = 0; i < k; i++) {
            auto xLeft = lower_bound(xIdx.begin(), xIdx.end(), d[i].x1);
            auto xRight = upper_bound(xIdx.begin(), xIdx.end(), d[i].x2);

            int xMin = NO_LASER;
            if(xRight != xIdx.begin() && xLeft != xIdx.end()) {
                xMin = search(0, xLeafStart - 1, xLeft - xIdx.begin(), xRight - xIdx.begin() - 1, 1, xt);
            }

            auto yLeft = lower_bound(yIdx.begin(), yIdx.end(), d[i].y1);
            auto yRight = upper_bound(yIdx.begin(), yIdx.end(), d[i].y2);

            int yMin = NO_LASER;
            if(yRight != yIdx.begin() && yLeft != yIdx.end()) {
                yMin = search(0, yLeafStart - 1, yLeft - yIdx.begin(), yRight - yIdx.begin() - 1, 1, yt);
            }

            int r = min(xMin, yMin);
            if(r == NO_LASER) continue;

            if(res[r] == 0) {
                res[r] = d[i].w;
            }
        }


        for(int i = 0; i < l; i++) {
            cout << res[i] << "\n";
        }
    }

    return 0;
}
