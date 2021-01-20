#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <queue>
#include <utility>

using lli = long long int;

constexpr int INF = 987654321;

int n, transTurn, dstX, dstY;
char m[501][501];
int d[501][501][2];

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

struct Info
{
    int x;
    int y;
    int turn;
    bool isTrans;
};
std::queue<Info> q;

void MoveNormal(int x, int y, int turn)
{
    int nextX;
    int nextY;

    for(int i = 0; i < 4; i++) {
        nextX = x + dx[i];
        nextY = y + dy[i];

        if(nextX < 0 || nextX >= n || nextY < 0 || nextY >= n) continue;

        if(turn + 1 < d[nextX][nextY][false]) {
            d[nextX][nextY][false] = turn + 1;
            q.push({ nextX, nextY, turn + 1, false });
        }
    }
}

void MoveTrans(int x, int y, int turn)
{
    int nextX;
    int nextY;

    for(int i = 0; i < 4; i++) {
        bool isPossible = true;
        nextX = x;
        nextY = y;
        do {
            nextX += dx[i];
            nextY += dy[i];

            if(nextX < 0 || nextX >= n || nextY < 0 || nextY >= n) {
                isPossible = false;
                break;
            }
        } while(m[nextX][nextY] != '#');

        if(isPossible == false) continue;

        if(turn + 1 < d[nextX][nextY][true]) {
            d[nextX][nextY][true] = turn + 1;
            q.push({ nextX, nextY, turn + 1, true });
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d %d %d %d", &n, &transTurn, &dstX, &dstY);
    dstX--;
    dstY--;
    for(int i = 0; i < n; i++) {
        scanf("%s", m[i]);

        for(int j = 0; j < n; j++) {
            d[i][j][0] = INF;
            d[i][j][1] = INF;
        }
    }

    d[0][0][0] = 0;
    d[0][0][1] = transTurn;
    q.push({0, 0, 0, false});
    while(q.empty() == false) {
        Info current = q.front();
        q.pop();

        // if(current.x == dstX && current.y == dstY) break;

        MoveNormal(current.x, current.y, current.turn);
        
        int tmp = current.turn;
        if(current.isTrans == false) {
            tmp += transTurn;
        }
        MoveTrans(current.x, current.y, tmp);
    }

    int res = d[dstX][dstY][0];
    if(res > d[dstX][dstY][1]) res = d[dstX][dstY][1];

    printf("%d", res);
                                               
    return 0;
}
