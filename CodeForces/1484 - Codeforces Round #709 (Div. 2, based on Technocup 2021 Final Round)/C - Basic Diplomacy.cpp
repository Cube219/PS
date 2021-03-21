#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
vector<int> a[100001];
int res[100001];
int cnt[100001], cnt2[100001];
bool pos;
vector<pair<vector<int>, int>> tmp;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        pos = true;
        cin >> n >> m;
        for(int i = 1; i <= n; ++i) {
            cnt[i] = 0;
            cnt2[i] = 0;
        }
        for(int i = 0; i < m; ++i) {
            int num;
            cin >> num;
            a[i].resize(num);
            for(int j = 0; j < num; ++j) {
                cin >> a[i][j];
                cnt[a[i][j]]++;
            }
            res[i] = 0;
        }
        int limit = m / 2;
        if(m % 2 == 1) limit++;

        tmp.clear();
        for(int i = 0; i < m; ++i) {
            bool f = false;
            for(int j = 0; j < a[i].size(); ++j) {
                int t = a[i][j];
                if(cnt[t] <= limit) {
                    res[i] = t;
                    f = true;
                    break;
                }
            }
            if(f == false) {
                tmp.push_back({ a[i], i });
            }
        }
        sort(tmp.begin(), tmp.end(), [](const auto& l, const auto& r) {
            return l.first.size() < r.first.size();
        });
        for(int i = 0; i < tmp.size(); ++i) {
            for(int j = 0; j < tmp[i].first.size(); ++j) {
                int v = tmp[i].first[j];
                if(cnt2[v] < limit) {
                    cnt2[v]++;
                    res[tmp[i].second] = v;
                    break;
                }
            }
            if(res[tmp[i].second] == 0) {
                pos = false;
                break;
            }
        }

        if(pos == true) {
            cout << "YES\n";
            for(int i = 0; i < m; ++i) {
                cout << res[i] << " ";
            }
            cout << "\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
