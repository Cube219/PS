#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
char map[1005][1005];
int ax, ay;
char res[1005][1005];
vector<pair<int, int>> d;
int minx[1005], maxx[1005];

struct Node
{
    int x, y;
    char ch;
};
constexpr char gap = 'a' - 'A';

void process(int left, int right, int top, int bottom)
{
    if(left < 0 || right >= m || top < 0 || bottom >= n) return;
    if(left > right || top > bottom) return;

    // cout << left << " " << right << " / " << top << " " << bottom << "\n";

    vector<Node> point;
    for(int i = top; i <= bottom; ++i) {
        for(int j = left; j <= right; ++j) {
            if(map[i][j] != '.') {
                point.push_back({ i, j, map[i][j] + gap });
            }
        }
    }

    if(point.size() == 0) return;
    else if(point.size() == 1) {
        for(int i = top; i <= bottom; ++i) {
            for(int j = left; j <= right; ++j) {
                res[i][j] = point[0].ch;
            }
        }
        return;
    }

    bool xdiff = false;
    int x = point[0].x;
    for(int i = 1; i < point.size(); ++i) {
        if(x != point[i].x) {
            xdiff = true;
            break;
        }
    }
    if(xdiff == false) {
        // y를 기준으로 나눔
        vector<int> yy;
        for(int i = 0; i < point.size(); ++i) {
            yy.push_back(point[i].y);
        }
        sort(yy.begin(), yy.end());
        yy.erase(unique(yy.begin(), yy.end()), yy.end());

        process(left, yy[0], top, bottom);
        for(int i = 1; i < yy.size() - 1; ++i) {
            process(yy[i - 1] + 1, yy[i], top, bottom);
        }
        process(yy[yy.size() - 2] + 1, right, top, bottom);
    } else {
        // x를 기준으로 나눔
        vector<int> xx;
        for(int i = 0; i < point.size(); ++i) {
            xx.push_back(point[i].x);
        }
        sort(xx.begin(), xx.end());
        xx.erase(unique(xx.begin(), xx.end()), xx.end());

        process(left, right, top, xx[0]);
        for(int i = 1; i < xx.size() - 1; ++i) {
            process(left, right, xx[i - 1] + 1, xx[i]);
        }
        process(left, right, xx[xx.size() - 2] + 1, bottom);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 'A') {
                ax = i;
                ay = j;
            } else if(map[i][j] != '.') {
                d.push_back({ i, j });
            }
        }
    }

    minx[ay] = 0, maxx[ay] = n - 1;
    for(int i = 0; i < d.size(); ++i) {
        if(d[i].second != ay) continue;

        if(d[i].first <= ax) minx[ay] = max(minx[ay], d[i].first + 1);
        if(d[i].first >= ax) maxx[ay] = min(maxx[ay], d[i].first - 1);
    }
    for(int i = ay - 1; i >= 0; --i) {
        minx[i] = minx[i + 1];
        maxx[i] = maxx[i + 1];
        for(int j = 0; j < d.size(); ++j) {
            if(d[j].second != i) continue;

            if(d[j].first <= ax) minx[i] = max(minx[i], d[j].first + 1);
            if(d[j].first >= ax) maxx[i] = min(maxx[i], d[j].first - 1);
        }
    }
    for(int i = ay + 1; i < m; ++i) {
        minx[i] = minx[i - 1];
        maxx[i] = maxx[i - 1];
        for(int j = 0; j < d.size(); ++j) {
            if(d[j].second != i) continue;

            if(d[j].first <= ax) minx[i] = max(minx[i], d[j].first + 1);
            if(d[j].first >= ax) maxx[i] = min(maxx[i], d[j].first - 1);
        }
    }

    int left = 0, right = m - 1, top = 0, bottom = n - 1;
    ll mx = 0;
    for(int i = 0; i <= ay; ++i) {
        for(int j = ay; j < m; ++j) {
            int t = max(minx[i], minx[j]);
            int b = min(maxx[i], maxx[j]);
            ll height = b - t + 1;
            ll cur = height * (j - i + 1);

            if(mx < cur) {
                mx = cur;
                left = i;
                right = j;
                top = max(minx[i], minx[j]);
                bottom = min(maxx[i], maxx[j]);
            }
        }
    }
    for(int i = top; i <= bottom; ++i) {
        for(int j = left; j <= right; ++j) {
            res[i][j] = 'a';
        }
    }

    process(0, left - 1, 0, bottom);
    process(left, m - 1, 0, top - 1);
    process(right + 1, m - 1, top, n - 1);
    process(0, right, bottom + 1, n - 1);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] != '.') cout << map[i][j];
            else cout << res[i][j];
            if(res[i][j] == 0 && map[i][j] == '.') cout << map[i][j];
        }
        cout << "\n";
    }

    return 0;
}
