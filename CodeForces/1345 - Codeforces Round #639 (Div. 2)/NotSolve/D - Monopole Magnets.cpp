#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int d[1001][1001];
int filled[1001][1001];

int qX[1000001];
int qY[1000001];
int qFront, qRear;

int top, bot, left, right;
vector<int> topY, botY, leftX, rightX;
bool isPossible = true;
int cnt;

void check(int x, int y)
{
    if(top == x) {
        topY.push_back(y);
    } else if(top > x) {
        top = x;
        topY.clear();
        topY.push_back(y);
    }

    if(bot == x) {
        botY.push_back(y);
    }
    else if(bot < x) {
        bot = x;
        botY.clear();
        botY.push_back(y);
    }

    if(left == y) {
        leftX.push_back(x);
    }
    else if(left > y) {
        left = y;
        leftX.clear();
        leftX.push_back(x);
    }

    if(right == y) {
        rightX.push_back(x);
    }
    else if(right < y) {
        right = y;
        rightX.clear();
        rightX.push_back(x);
    }
}

void BFS(int x, int y)
{
    qFront = 0;
    qRear = 0;
    qX[0] = x;
    qY[0] = y;
    filled[x][y] = 1;

    while(qFront <= qRear) {
        int cx = qX[qFront];
        int cy = qY[qFront];

        check(cx, cy);

        if(cy + 1 < m && d[cx][cy + 1] == 1 && filled[cx][cy + 1] == 0) {
            qX[++qRear] = cx;
            qY[qRear] = cy + 1;
            filled[cx][cy + 1] = 1;
        }
        if(cx + 1 < n && d[cx + 1][cy] == 1 && filled[cx + 1][cy] == 0) {
            qX[++qRear] = cx + 1;
            qY[qRear] = cy;
            filled[cx + 1][cy] = 1;
        }
        if(cy - 1 >= 0 && d[cx][cy - 1] == 1 && filled[cx][cy - 1] == 0) {
            qX[++qRear] = cx;
            qY[qRear] = cy - 1;
            filled[cx][cy - 1] = 1;
        }
        if(cx - 1 >= 0 && d[cx - 1][cy] == 1 && filled[cx - 1][cy] == 0) {
            qX[++qRear] = cx - 1;
            qY[qRear] = cy;
            filled[cx - 1][cy] = 1;
        }

        qFront++;
    }
}

void CheckIsPossible()
{
    if(topY.size() > 1) {
        sort(topY.begin(), topY.end());

        for(int i = 0; i < (int)(topY.size()) - 1; i++) {
            if(topY[i] + 1 != topY[i + 1]) {
                isPossible = false;
                return;
            }
        }
    }

    if(botY.size() > 1) {
        sort(botY.begin(), botY.end());

        for(int i = 0; i < (int)(botY.size()) - 1; i++) {
            if(botY[i] + 1 != botY[i + 1]) {
                isPossible = false;
                return;
            }
        }
    }

    if(leftX.size() > 1) {
        sort(leftX.begin(), leftX.end());

        for(int i = 0; i < (int)(leftX.size()) - 1; i++) {
            if(leftX[i] + 1 != leftX[i + 1]) {
                isPossible = false;
                return;
            }
        }
    }

    if(rightX.size() > 1) {
        sort(rightX.begin(), rightX.end());

        for(int i = 0; i < (int)(rightX.size()) - 1; i++) {
            if(rightX[i] + 1 != rightX[i + 1]) {
                isPossible = false;
                return;
            }
        }
    }
}

int main(void)
{
    char t[1001];
    bool hasBlack = false;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%s", t);

        for(int j = 0; j < m; j++) {
            if(t[j] == '#') {
                d[i][j] = 1;
                hasBlack = true;
            }
        }
    }

    if(hasBlack == false) {
        printf("0");
        return 0;
    }

    // Check rows
    for(int i = 0; i < n; i++) {
        bool t = false;
        for(int j = 0; j < m; j++) {
            if(d[i][j] == 1) {
                t = true;
                break;
            }
        }
        if(t == false) {
            isPossible = false;
            break;
        }
    }
    if(isPossible == false) {
        printf("-1");
        return 0;
    }

    // Check cols
    for(int j = 0; j < m; j++) {
        bool t = false;
        for(int i = 0; i < n; i++) {
            if(d[i][j] == 1) {
                t = true;
                break;
            }
        }
        if(t == false) {
            isPossible = false;
            break;
        }
    }
    if(isPossible == false) {
        printf("-1");
        return 0;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(d[i][j] == 1 && filled[i][j] == 0) {
                cnt++;

                top = n + 1;
                topY.clear();
                bot = -1;
                botY.clear();
                left = m + 1;
                leftX.clear();
                right = -1;
                rightX.clear();

                BFS(i, j);

                CheckIsPossible();
                if(isPossible == false) {
                    break;
                }
            }
        }

        if(isPossible == false) {
            break;
        }
    }

    if(isPossible == false) {
        printf("-1");
    }
    else {
        printf("%d", cnt);
    }

    return 0;
}
