#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

using ll = long long int;

int tNum;
deque<int> line[101];
vector<int> res[101];
int n, m;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            line[i].clear();
            for(int j = 0; j < m; ++j) {
                int a;
                cin >> a;
                line[i].push_back(a);
            }
            sort(line[i].begin(), line[i].end());
        }

        for(int i = 0; i < m; ++i) {
            res[i].clear();
            int minv = 987654321, minIdx = -1;
            for(int j = 0; j < n; ++j) {
                if(line[j].front() < minv) {
                    minv = line[j].front();
                    minIdx = j;
                }
            }
            for(int j = 0; j < n; ++j) {
                if(j == minIdx) {
                    res[i].push_back(line[j].front());
                    line[j].pop_front();
                } else {
                    res[i].push_back(line[j].back());
                    line[j].pop_back();
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                cout << res[j][i] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
