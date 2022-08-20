#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <set>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    vector<int> d(n);
    vector<char> isPos(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i]; d[i]--;
        char ch; cin >> ch;
        if(ch == '+') isPos[i] = true;
        else isPos[i] = false;
    }

    struct State
    {
        vector<int> num;
        vector<char> pos;
        int v;
        bool operator<(const State& rhs) const
        {
            if(num == rhs.num) return pos < rhs.pos;
            return num < rhs.num;
        }
    };
    queue<State> q;
    q.push({ d, isPos, 0 });
    set<State> visit;
    visit.insert({ d, isPos, 0 });

    int res = 0;
    while(!q.empty()) {
        auto [num, pos, v] = q.front(); q.pop();

        bool finish = true;
        for(int i = 0; i < n; ++i) {
            if(num[i] != i) finish = false;
            if(pos[i] == false) finish = false;
        }
        if(finish) {
            res = v;
            break;
        }

        for(int i = 0; i < n; ++i) {
            reverse(num.begin(), num.begin() + i + 1);
            reverse(pos.begin(), pos.begin() + i + 1);
            for(int j = 0; j <= i; ++j) pos[j] = !pos[j];

            State nxt = { num, pos, v + 1 };
            if(visit.find(nxt) == visit.end()) {
                q.push(nxt);
                visit.insert(nxt);
            }

            for(int j = 0; j <= i; ++j) pos[j] = !pos[j];
            reverse(pos.begin(), pos.begin() + i + 1);
            reverse(num.begin(), num.begin() + i + 1);
        }
    }

    cout << res;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
