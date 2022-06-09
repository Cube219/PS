#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    string str;
    cin >> str;

    vector<int> row(n * m, 0), col(n * m, 0);

    // row
    int empty = m + 1;
    vector<int> rowNum(m, 0);
    for(int i = 0; i < n * m; ++i) {
        if(i > 0) row[i] = row[i - 1];

        if(str[i] == '0') empty++;
        else {
            if(empty >= m) {
                rowNum[i % m]++;
            }
            empty = 0;
        }

        if(empty == m) {
            rowNum[i % m]--;
        }

        row[i] += rowNum[i % m];
    }

    // col
    vector<char> colVisit(m, false);
    for(int i = 0; i < n * m; ++i) {
        if(i > 0) col[i] = col[i - 1];

        if(str[i] == '0') continue;

        if(colVisit[i % m] == false) {
            colVisit[i % m] = true;
            col[i]++;
        }
    }

    for(int i = 0; i < n*m; ++i) {
        cout << row[i] + col[i] << " ";
    }
    cout << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
