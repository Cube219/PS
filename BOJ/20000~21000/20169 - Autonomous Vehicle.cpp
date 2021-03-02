#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, t;
struct Line
{
    int x1;
    int y1;
    int x2;
    int y2;
    int lineIdx;
};
vector<Line> vl, hl;

struct Point
{
    int x;
    int y;
    int lineIdx;
    bool isIntersect;
};
vector<Point> pv, ph;
vector<pair<Point, ll>> pTime;
vector<int> pDir;
Point st;
int stDir;

constexpr int LEFT = 0;
constexpr int RIGHT = 1;
constexpr int UP = 2;
constexpr int DOWN = 3;

bool intersect(const Line& v, const Line& h, Point& res)
{
    if(v.x1 == h.x1 && v.y1 == h.y1) {
        res = { v.x1, v.y1, 0, true };
        return true;
    }
    if(v.x2 == h.x2 && v.y2 == h.y2) {
        res = { v.x2, v.y2, 0, true };
        return true;
    }

    if(h.x1 <= v.x1 && v.x1 <= h.x2 && v.y1 <= h.y1 && h.y1 <= v.y2) {
        res = { v.x1, h.y1, 0, true };
        return true;
    }
    return false;
}

auto search(Point p, int dir)
{
    if(dir == UP || dir == DOWN) {
        auto stIt = lower_bound(pv.begin(), pv.end(), p.x, [](const Point& l, int v) {
            return l.x < v;
        });
        auto edIt = upper_bound(pv.begin(), pv.end(), p.x, [](int v, const Point& l) {
            return v < l.x;
        });
        auto curIt = lower_bound(stIt, edIt, p.y, [](const Point& l, int v) {
            return l.y < v;
        });
        return curIt;
    } else {
        auto stIt = lower_bound(ph.begin(), ph.end(), p.y, [](const Point& l, int v) {
            return l.y < v;
        });
        auto edIt = upper_bound(ph.begin(), ph.end(), p.y, [](int v, const Point& l) {
            return v < l.y;
        });
        auto curIt = lower_bound(stIt, edIt, p.x, [](const Point& l, int v) {
            return l.x < v;
        });
        return curIt;
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> t;
    for(int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if(i == 0) {
            st = { x1, y1 };
            if(x1 == x2) {
                if(y1 < y2) {
                    stDir = UP;
                } else {
                    stDir = DOWN;
                }
            } else {
                if(x1 < x2) {
                    stDir = RIGHT;
                } else {
                    stDir = LEFT;
                }
            }
        }

        if(x1 == x2) {
            if(y1 > y2) swap(y1, y2);
            vl.push_back({ x1, y1, x2, y2, i });
        } else {
            if(x1 > x2) swap(x1, x2);
            hl.push_back({ x1, y1, x2, y2, i });
        }
        pv.push_back({ x1, y1, i, false });
        pv.push_back({ x2, y2, i, false });
        ph.push_back({ x1, y1, i, false });
        ph.push_back({ x2, y2, i, false });
    }

    Point tmp;
    for(int i = 0; i < vl.size(); ++i) {
        for(int j = 0; j < hl.size(); ++j) {
            bool r = intersect(vl[i], hl[j], tmp);
            if(r == true) {
                pv.push_back({ tmp.x, tmp.y, vl[i].lineIdx, true });
                ph.push_back({ tmp.x, tmp.y, hl[j].lineIdx, true });
            }
        }
    }

    sort(pv.begin(), pv.end(), [](const Point& l, const Point& r) {
        if(l.x == r.x) return l.y < r.y;
        return l.x < r.x;
    });
    sort(ph.begin(), ph.end(), [](const Point& l, const Point& r) {
        if(l.y == r.y) return l.x < r.x;
        return l.y < r.y;
    });

    ll cTime = 0;
    pTime.push_back({ st, 0 });
    pDir.push_back(stDir);
    Point cur = st;
    int dir = stDir;
    auto curIt = search(cur, dir);
    while(1) {
        switch(dir) {
            case UP:
                ++curIt;
                if(curIt == pv.end() || curIt->x != cur.x || curIt->lineIdx != cur.lineIdx) {
                    dir = DOWN;
                    --curIt;
                    pDir.back() = dir;
                } else {
                    cTime += curIt->y - cur.y;
                    cur = *curIt;
                    pTime.push_back({ cur, cTime });

                    if(curIt->isIntersect == true) {
                        dir = LEFT;
                        curIt = search(cur, dir);
                        cur.lineIdx = curIt->lineIdx;
                    }

                    pDir.push_back(dir);
                }
                break;
            case DOWN:
            {
                if(curIt == pv.begin()) {
                    dir = UP;
                    pDir.back() = dir;
                } else {
                    --curIt;
                    if(curIt->x != cur.x || curIt->lineIdx != cur.lineIdx) {
                        dir = UP;
                        pDir.back() = dir;
                        ++curIt;
                    } else {
                        cTime += cur.y - curIt->y;
                        cur = *curIt;
                        pTime.push_back({ cur, cTime });

                        if(curIt->isIntersect == true) {
                            dir = RIGHT;
                            curIt = search(cur, dir);
                            cur.lineIdx = curIt->lineIdx;
                        }

                        pDir.push_back(dir);
                    }
                }
                break;
            }
            case LEFT:
            {
                if(curIt == ph.begin()) {
                    dir = RIGHT;
                    pDir.back() = dir;
                } else {
                    --curIt;
                    if(curIt->y != cur.y || curIt->lineIdx != cur.lineIdx) {
                        dir = RIGHT;
                        pDir.back() = dir;
                        ++curIt;
                    } else {
                        cTime += cur.x - curIt->x;
                        cur = *curIt;
                        pTime.push_back({ cur, cTime });

                        if(curIt->isIntersect == true) {
                            dir = DOWN;
                            curIt = search(cur, dir);
                            cur.lineIdx = curIt->lineIdx;
                        }

                        pDir.push_back(dir);
                    }
                }
                break;
            }
            case RIGHT:
            {
                ++curIt;
                if(curIt == ph.end() || curIt->y != cur.y || curIt->lineIdx != cur.lineIdx) {
                    dir = LEFT;
                    pDir.back() = dir;
                    --curIt;
                } else {
                    cTime += curIt->x - cur.x;
                    cur = *curIt;
                    pTime.push_back({ cur, cTime });

                    if(curIt->isIntersect == true) {
                        dir = UP;
                        curIt = search(cur, dir);
                        cur.lineIdx = curIt->lineIdx;
                    }

                    pDir.push_back(dir);
                }
                break;
            }
        }
        if(cur.x == st.x && cur.y == st.y) break;
    }

    t %= pTime.back().second;
    auto it = upper_bound(pTime.begin(), pTime.end(), t, [](ll v, const pair<Point, ll>& l) {
        return v < l.second;
    });
    --it;
    t -= it->second;
    int idx = it - pTime.begin();
    Point res = it->first;
    switch(pDir[idx]) {
        case UP:
            res.y += t;
            break;
        case DOWN:
            res.y -= t;
            break;
        case LEFT:
            res.x -= t;
            break;
        case RIGHT:
            res.x += t;
            break;
    }

    cout << res.x << " " << res.y;

    return 0;
}
