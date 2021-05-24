#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;
constexpr ll INF = 9223372036854775800;

int n;
map<ll, vector<int>> mp[20];
ll d1[36], d2[36];

ll res = INF;
vector<vector<int>> r2;

vector<int> cur;
void bt(int idx, ll gap)
{
    if(idx == n / 2) {
        if(mp[cur.size()].find(gap) != mp[cur.size()].end()) return;
        mp[cur.size()].insert({ gap, cur });
        return;
    }
    cur.push_back(idx);
    bt(idx + 1, gap + d1[idx]);
    cur.pop_back();
    bt(idx + 1, gap - d2[idx]);
}

void bt2(int idx, ll gap)
{
    if(idx == n) {
        int num = n / 2 - cur.size();
        auto it = mp[num].lower_bound(-gap);
        if(it != mp[num].end()) {
            if(res >= abs(gap + it->first)) {
                if(res > abs(gap + it->first)) r2.clear();
                res = abs(gap + it->first);
                r2.push_back({});
                r2.back().assign(it->second.begin(), it->second.end());
                r2.back().insert(r2.back().end(), cur.begin(), cur.end());
            }
        }
        if(it != mp[num].begin()) {
            --it;
            if(res >= abs(gap + it->first)) {
                if(res > abs(gap + it->first)) r2.clear();
                res = abs(gap + it->first);
                r2.push_back({});
                r2.back().assign(it->second.begin(), it->second.end());
                r2.back().insert(r2.back().end(), cur.begin(), cur.end());
            }
        }
        return;
    }
    cur.push_back(idx);
    bt2(idx + 1, gap + d1[idx]);
    cur.pop_back();
    bt2(idx + 1, gap - d2[idx]);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d1[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> d2[i];
    }
    bt(0, 0);
    bt2(n / 2, 0);

    sort(r2.begin(), r2.end());

    r2.front().push_back(-1);
    int idx = 0;
    for(int i = 0; i < n; ++i) {
        if(r2.front()[idx] == i) {
            cout << "1 ";
            idx++;
        } else {
            cout << "2 ";
        }
    }

    return 0;
}
