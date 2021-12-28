#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

vector<int> dimsz(11);

using hv = vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>>>>>;
hv arr, sum;

template<typename T>
void init(T& curarr, T& cursum, int dim)
{
    curarr.resize(dimsz[dim]);
    cursum.resize(dimsz[dim]);
    for(int i = 0; i < dimsz[dim]; ++i) {
        init(curarr[i], cursum[i], dim + 1);
    }
}
template <>
void init(ll& curarr, ll& cursum, int dim)
{
    cin >> curarr;
    cursum = curarr;
}

template <typename T>
void calsum(T& src, T& dst, int dim, int sumdim)
{
    if(dim == sumdim) {
        for(int i = 1; i < dimsz[dim]; ++i) {
            calsum(src[i - 1], dst[i], dim + 1, sumdim);
        }
    } else {
        for(int i = 0; i < dimsz[dim]; ++i) {
            calsum(src[i], dst[i], dim + 1, sumdim);
        }
    }
}
template <>
void calsum(ll& src, ll& dst, int dim, int sumdim)
{
    dst += src;
}

template <typename T>
ll bt(int dim, T& d, vector<int>& a1, vector<int>& a2, int cnt)
{
    ll res = 0;
    res += bt(dim + 1, d[a2[dim]], a1, a2, cnt);

    if(a1[dim] > 0) {
        res += bt(dim + 1, d[a1[dim] - 1], a1, a2, cnt + 1);
    }
    return res;
}
template <>
ll bt(int dim, ll& d, vector<int>& a1, vector<int>& a2, int cnt)
{
    if(cnt & 1) return -d;
    else return d;
}

ll query(vector<int>& a1, vector<int>& a2)
{
    return bt(0, sum, a1, a2, 0);
}

void solve()
{
    for(auto& v : dimsz) cin >> v;
    init(arr, sum, 0);
    for(int i = 0; i < 11; ++i) {
        calsum(sum, sum, 0, i);
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        vector<int> a1(11), a2(11);
        for(auto& v : a1) { cin >> v; v--; }
        for(auto& v : a2) { cin >> v; v--; }
        // query(a1, a2);
        cout << query(a1, a2) << "\n";
    }
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
