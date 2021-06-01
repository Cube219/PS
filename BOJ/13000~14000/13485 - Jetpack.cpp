#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

using ll = long long int;

int n;
char map[11][100005];
int rec[11][100005];

bool dfs(int x, int y)
{
    if(x == n - 1) {
        return true;
    }

    int nx, ny;
    bool res;
    nx = x + 1;

    // down
    ny = y + 1;
    if(ny >= 10) ny = 9;
    if(map[ny][nx] != 'X' && rec[ny][nx] != -1) {
        res = dfs(nx, ny);
        if(res == true) {
            rec[y][x] = 2;
            return true;
        }
    }

    // up
    ny = y - 1;
    if(ny < 0) ny = 0;
    if(map[ny][nx] != 'X' && rec[ny][nx] != -1) {
        res = dfs(nx, ny);
        if(res == true) {
            rec[y][x] = 1;
            return true;
        }
    }

    rec[y][x] = -1;
    return false;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < 10; ++i) {
        cin >> map[i];
    }
    dfs(0, 9);
    int y = 9;
    vector<int> pr;
    for(int x = 0; x < n - 1; ++x) {
        if(rec[y][x] == 1) {
            pr.push_back(x);
            y--;
        } else if(rec[y][x] == 2) {
            y++;
        } else {
            assert(false);
        }
        if(y < 0) y = 0;
        if(y >= 10) y = 9;
    }

    cout << pr.size() << "\n";
    for(int i = 0; i < pr.size(); ++i) {
        cout << pr[i] << " 1\n";
    }

    return 0;
}
