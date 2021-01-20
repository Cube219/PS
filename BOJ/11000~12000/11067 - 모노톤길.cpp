#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using lli = long long int;

int tNum;
vector<int> ys[100001];
int n, m;
int cafeX[100001], cafeY[100001];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        for(int i = 0; i <= 100000; i++) {
            ys[i].clear();
        }

        cin >> n;
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            ys[x].push_back(y);
        }

        for(int i = 0; i < 100000; i++) {
            if(ys[i].size() == 0) continue;
            sort(ys[i].begin(), ys[i].end());
        }

        int cx = 0, cy = 0;
        int cafeNum = 1;
        int dir = 0;
        for(int cx = 0; cx <= 100000; cx++) {
            if(ys[cx].size() == 0) continue;

            if(ys[cx][0] == cy) {
                for(int i = 0; i < ys[cx].size(); i++) {
                    cafeX[cafeNum] = cx;
                    cafeY[cafeNum] = ys[cx][i];
                    cafeNum++;
                }

                cy = *ys[cx].rbegin();
            } else {
                for(int i = ys[cx].size() - 1; i >= 0; i--) {
                    cafeX[cafeNum] = cx;
                    cafeY[cafeNum] = ys[cx][i];
                    cafeNum++;
                }
                
                cy = *ys[cx].begin();
            }
        }

        cin >> m;
        for(int i = 0; i < m; i++) {
            int a;
            cin >> a;
            cout << cafeX[a] << " " << cafeY[a] << "\n";
        }
    }

    return 0;
}
