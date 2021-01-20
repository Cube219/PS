#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stack>
#include <utility>
using namespace std;

int tNum;
int n, m;
int d[31][31];
int res;
bool isVisited[31][31];

stack<pair<int, int>> sq;
stack<pair<int, int>> eq;
stack<pair<int, int>> sqt;
stack<pair<int, int>> eqt;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        while(sq.empty() == false) sq.pop();
        while(eq.empty() == false) eq.pop();
        while(sqt.empty() == false) sqt.pop();
        while(eqt.empty() == false) eqt.pop();
        res = 0;

        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                scanf("%d", &d[i][j]);
                isVisited[i][j] = false;
            }
        }

        res = 0;
        
        int num0 = 0, num1 = 0;
        sq.push({ 0, 0 });
        eq.push({ n - 1, m - 1 });
        isVisited[0][0] = isVisited[n - 1][m - 1] = true;
        while(1) {
            num0 = num1 = 0;
            while(sq.empty() == false) {
                auto pos = sq.top();
                sq.pop();
                sqt.push(pos);

                if(d[pos.first][pos.second] == 0) num0++;
                else num1++;
            }
            while(eq.empty() == false) {
                auto pos = eq.top();
                eq.pop();
                eqt.push(pos);

                if(d[pos.first][pos.second] == 0) num0++;
                else num1++;
            }

            if(num0 < num1) res += num0;
            else res += num1;

            while(sqt.empty() == false) {
                auto pos = sqt.top();
                sqt.pop();

                if(pos.first + 1 < n && pos.second < m && isVisited[pos.first + 1][pos.second] == false) {
                    sq.push({ pos.first + 1, pos.second });
                    isVisited[pos.first + 1][pos.second] = true;
                }

                if(pos.first < n && pos.second +1 < m && isVisited[pos.first][pos.second + 1] == false) {
                    sq.push({ pos.first, pos.second + 1 });
                    isVisited[pos.first][pos.second + 1] = true;
                }
            }

            while(eqt.empty() == false) {
                auto pos = eqt.top();
                eqt.pop();

                if(pos.first - 1 >= 0 && isVisited[pos.first - 1][pos.second] == false) {
                    eq.push({ pos.first - 1, pos.second });
                    isVisited[pos.first - 1][pos.second] = true;
                }

                if(pos.second - 1 >= 0 && isVisited[pos.first][pos.second - 1] == false) {
                    eq.push({ pos.first, pos.second - 1 });
                    isVisited[pos.first][pos.second - 1] = true;
                }
            }

            if(sq.size() != eq.size()) break;
            if(sq.size() == 0) break;
        }

        printf("%d\n", res);
    }

    return 0;
}
