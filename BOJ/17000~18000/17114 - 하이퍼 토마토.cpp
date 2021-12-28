#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

vector<int> dimsz(11);

using hv = vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>>>>>;
hv arr;
int remain;
queue<pair<vector<int>, int>> q;

template <typename T>
void init(T& curarr, int dim, vector<int>& idx)
{
    curarr.resize(dimsz[dim]);
    for(int i = 0; i < dimsz[dim]; ++i) {
        idx.push_back(i);
        init(curarr[i], dim + 1, idx);
        idx.pop_back();
    }
}
template <>
void init(ll& curarr, int dim, vector<int>& idx)
{
    cin >> curarr;
    if(curarr == 0) remain++;
    else if(curarr == 1) {
        remain++;
        q.push({ idx, 0 });
    }
}

template <typename T>
bool ck(T& d, int dim, vector<int>& idx)
{
    return ck(d[idx[dim]], dim + 1, idx);
}
template <>
bool ck(ll& d, int dim, vector<int>& idx)
{
    if(d == 0) {
        d = 1;
        return true;
    }
    return false;
}

void solve()
{
    for(auto& v : dimsz) cin >> v;
    reverse(dimsz.begin(), dimsz.end());
    vector<int> idx;
    init(arr, 0, idx);

    int res = 0;
    while(q.empty() == false) {
        vector<int> cur = move(q.front().first);
        int cost = q.front().second;
        q.pop();

        res = max(res, cost);
        remain--;
        if(remain <= 0) break;

        vector<int> nxt = cur;
        for(int i = 0; i < 11; ++i) {
            nxt[i]++;
            if(nxt[i] < dimsz[i]) {
                if(ck(arr, 0, nxt)) {
                    q.push({ nxt, cost + 1 });
                }
            }
            nxt[i] -= 2;
            if(nxt[i] >= 0) {
                if(ck(arr, 0, nxt)) {
                    q.push({ nxt, cost + 1 });
                }
            }
            nxt[i]++;
        }
    }

    if(remain > 0) res = -1;
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
