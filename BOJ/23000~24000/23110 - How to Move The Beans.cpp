#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

bool has[5];
void ginit()
{
    for(int i = 0; i < 5; ++i) {
        has[i] = false;
    }
}
void gadd(int g)
{
    has[g] = true;
}
int gget()
{
    for(int i = 0; i < 5; ++i) {
        if(has[i] == false) return i;
    }
    return 4;
}

template <int N, bool left>
class SegTree
{
public:
    struct Node
    {
        int out[5];
    };

    Node t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

        for(int i = 0; i < stLeaf; ++i) {
            t[stLeaf + i] = { -1, -1, -1, -1, -1 };
        }
    }

    void initv(int idx, int v)
    {
        for(int i = 0; i < 5; ++i) {
            ginit();
            gadd(i);
            gadd(v);
            t[stLeaf + idx].out[i] = gget();
        }
    }

    Node merge(Node l, Node r)
    {
        Node res;
        if(l.out[0] == -1) return r;
        if(r.out[0] == -1) return l;
        for(int i = 0; i < 5; ++i) {
            if(left == true) {
                int lres = l.out[i];
                res.out[i] = r.out[lres];
            } else {
                int rres = r.out[i];
                res.out[i] = l.out[rres];
            }
        }
        return res;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    Node findImpl(int cl, int cr, int l, int r, int node)
    {
        if(cr < l || r < cl) return { -1, -1, -1, -1, -1 };
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return merge(findImpl(cl, m, l, r, node * 2), findImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    Node find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }
};

int w, h;
char map[1005][1005];
bool hasobs[1005];
int obsy[1005];
int gnum[2][1005], lg[1005], rg[1005];
SegTree<1005, true> lseg;
SegTree<1005, false> rseg;
int res;

void process(int x)
{
    int cur = x & 1;
    int pre = 1 - cur;

    for(int i = 0; i < w; ++i) {
        gnum[cur][i] = 4;
    }

    if(hasobs[x] == true) {
        for(int i = 0; i < w; ++i) {
            lg[i] = 4; rg[i] = 4;
        }

        for(int y = obsy[x] + 1; y < w; ++y) {
            if(map[x][y] == '#') continue;
            ginit();
            gadd(lg[y - 1]);
            gadd(gnum[pre][y]);
            lg[y] = gget();
        }
        for(int y = 0; y < obsy[x]; ++y) {
            if(map[x][y] == '#') continue;
            ginit();
            int yy = y - 1;
            if(yy < 0) yy += w;

            gadd(lg[yy]);
            gadd(gnum[pre][y]);
            lg[y] = gget();
        }

        for(int y = obsy[x] - 1; y >= 0; --y) {
            if(map[x][y] == '#') continue;
            ginit();
            gadd(rg[y + 1]);
            gadd(gnum[pre][y]);
            rg[y] = gget();
        }
        for(int y = w - 1; y > obsy[x]; --y) {
            if(map[x][y] == '#') continue;
            ginit();
            int yy = y + 1;
            if(yy >= w) yy -= w;

            gadd(rg[yy]);
            gadd(gnum[pre][y]);
            rg[y] = gget();
        }

        for(int y = 0; y < w; ++y) {
            if(map[x][y] == '#') continue;

            int l = (y - 1 + w) % w;
            int r = (y + 1) % w;

            ginit();
            gadd(lg[l]);
            gadd(rg[r]);
            gadd(gnum[pre][y]);
            gnum[cur][y] = gget();

            if(gnum[cur][y] != 4 && map[x][y] == 'B') res ^= gnum[cur][y];
        }
    } else {
        for(int i = 0; i < w; ++i) {
            lseg.initv(i, gnum[pre][i]);
            rseg.initv(i, gnum[pre][i]);
        }
        lseg.build();
        rseg.build();

        for(int y = 0; y < w; ++y) {
            ginit();
            gadd(gnum[pre][y]);

            if(w > 1) {
                int lend = (y + 1) % w;
                int st = gnum[pre][lend];
                if(y < w - 1) {
                    auto block = lseg.find(y + 1, w - 1);
                    st = block.out[st];
                }
                if(y > 0) {
                    auto block = lseg.find(0, y - 1);
                    st = block.out[st];
                }
                gadd(st);

                int rend = (y - 1 + w) % w;
                st = gnum[pre][rend];
                if(y > 0) {
                    auto block = rseg.find(0, y - 1);
                    st = block.out[st];
                }
                if(y < w - 1) {
                    auto block = rseg.find(y + 1, w - 1);
                    st = block.out[st];
                }
                gadd(st);
            }

            gnum[cur][y] = gget();
            if(gnum[cur][y] != 4 && map[x][y] == 'B') res ^= gnum[cur][y];
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

    cin >> h >> w;
    for(int i = 0; i < h; ++i) {
        cin >> map[i];
        for(int j = 0; j < w; ++j) {
            if(map[i][j] == '#') {
                hasobs[i] = true;
                obsy[i] = j;
            }
        }
    }

    lseg.init(w);
    rseg.init(w);

    int cur = h & 1;
    for(int i = 0; i < w; ++i) {
        gnum[cur][i] = 4;
    }
    for(int i = h - 1; i >= 0; --i) {
        process(i);
    }

    if(res == 0) cout << "Bob";
    else cout << "Alice";

    return 0;
}
