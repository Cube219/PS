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

vector<int> dimsz(11);
vector<int> cvtDim(11);
vector<int> invCvt(11);

using hv = vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<vector<ll>>>>>>>>>>>;
hv arr, tmp;

template<typename T>
void init(T& curarr, T& curtmp, int dim)
{
    curarr.resize(dimsz[dim]);
    curtmp.resize(dimsz[dim]);
    for(int i = 0; i < dimsz[dim]; ++i) {
        init(curarr[i], curtmp[i], dim + 1);
    }
}
template <>
void init(ll& curd, ll& curtmp, int idx)
{
    cin >> curd;
}

template<typename T>
void swap1(T& d1, T& d2, int dim, vector<int>& a1, vector<int>& a2, int swapDim, int x1, int x2)
{
    int cdim = invCvt[dim];
    if(cdim == swapDim) swap1(d1[x1], d2[x2], dim + 1, a1, a2, swapDim, x1, x2);
    else {
        for(int i = a1[cdim]; i <= a2[cdim]; ++i) {
            swap1(d1[i], d2[i], dim + 1, a1, a2, swapDim, x1, x2);
        }
    }
}
template <>
void swap1(ll& d1, ll& d2, int dim, vector<int>& a1, vector<int>& a2, int swapDim, int x1, int x2)
{
    swap(d1, d2);
}

void q1(vector<int>& a1, vector<int>& a2, int dim)
{
    int gap = a2[dim] - a1[dim] + 1;
    for(int i = 0; i < gap / 2; ++i) {
        swap1(arr, arr, 0, a1, a2, dim, a1[dim] + i, a2[dim] - i);
    }
}

template <typename T>
void cp(T& src, T& dst, int dim)
{
    for(int i = 0; i < dimsz[dim]; ++i) {
        cp(src[i], dst[i], dim + 1);
    }
}
template <>
void cp(ll& src, ll& dst, int dim)
{
    dst = src;
}

template <typename T>
void mv(T& src, T& dst, int dim, vector<int>& a1, vector<int>& a2, int rdim, int ddim, int r, int d, int dr, int dd)
{
    int cdim = invCvt[dim];
    if(cdim == rdim) {
        mv(src[r], dst[r + dr], dim + 1, a1, a2, rdim, ddim, r, d, dr, dd);
    } else if(cdim == ddim) {
        mv(src[d], dst[d + dd], dim + 1, a1, a2, rdim, ddim, r, d, dr, dd);
    } else {
        for(int i = a1[cdim]; i <= a2[cdim]; ++i) {
            mv(src[i], dst[i], dim + 1, a1, a2, rdim, ddim, r, d, dr, dd);
        }
    }
}
template <>
void mv(ll& src, ll& dst, int dim, vector<int>& a1, vector<int>& a2, int rdim, int ddim, int r, int d, int dr, int dd)
{
    dst = src;
}

void q2(vector<int>& a1, vector<int>& a2, int rdim, int ddim)
{
    int rst = a1[rdim], red = a2[rdim];
    int dst = a1[ddim], ded = a2[ddim];

    cp(arr, tmp, 0);

    while((rst < red && dst < ded)) {
        // down
        for(int i = dst; i < ded; ++i) {
            mv(arr, tmp, 0, a1, a2, rdim, ddim, rst, i, 0, 1);
        }
        // right
        for(int i = rst; i < red; ++i) {
            mv(arr, tmp, 0, a1, a2, rdim, ddim, i, ded, 1, 0);
        }
        // up
        for(int i = ded; i > dst; --i) {
            mv(arr, tmp, 0, a1, a2, rdim, ddim, red, i, 0, -1);
        }
        // left
        for(int i = red; i > rst; --i) {
            mv(arr, tmp, 0, a1, a2, rdim, ddim, i, dst, -1, 0);
        }

        rst++; red--;
        dst++; ded--;
    }

    swap(arr, tmp);
}

void q3(int dim1, int dim2)
{
    swap(cvtDim[dim1], cvtDim[dim2]);
    invCvt[cvtDim[dim1]] = dim1;
    invCvt[cvtDim[dim2]] = dim2;
}

pair<int, int> getdims(int num)
{
    pair<int, int> res = { 0, 0 };
    for(int i = 11 - 1; i >= 0; --i) {
        if(num < i) {
            res.second = res.first +  num + 1;
            break;
        }
        res.first++;
        num -= i;
    }

    return res;
}

template <typename T>
void init2(T& d1, int dim)
{
    d1.resize(dimsz[cvtDim[dim]]);
    for(int i = 0; i < dimsz[cvtDim[dim]]; ++i) {
        init2(d1[i], dim + 1);
    }
}
template <>
void init2(ll& d1, int dim)
{}

template <typename T>
void insert(T& d1, int dim, vector<int>& curi, ll v)
{
    int i = cvtDim[dim];
    insert(d1[curi[i]], dim + 1, curi, v);
}
template <>
void insert(ll& d1, int dim, vector<int>& curi, ll v)
{
    d1 = v;
}

template <typename T>
void get(T& d1, int dim, vector<int>& curi)
{
    for(int i = 0; i < dimsz[dim]; ++i) {
        curi.push_back(i);
        get(d1[i], dim + 1, curi);
        curi.pop_back();
    }
}
template <>
void get(ll& d1, int dim, vector<int>& curi)
{
    insert(tmp, 0, curi, d1);
}

template <typename T>
void print(T& d1, int dim)
{
    for(int i = 0; i < dimsz[cvtDim[dim]]; ++i) {
        print(d1[i], dim + 1);
    }
    if(dim == 10) cout << "\n";
}
template <>
void print(ll& d1, int dim)
{
    cout << d1 << " ";
}

void solve()
{
    iota(cvtDim.begin(), cvtDim.end(), 0);
    iota(invCvt.begin(), invCvt.end(), 0);

    for(auto& v : dimsz) cin >> v;

    init(arr, tmp, 0);

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int op;
        cin >> op;
        if(op <= 11) {
            vector<int> a1(11), a2(11);
            for(auto& v : a1) { cin >> v; v--; }
            for(auto& v : a2) { cin >> v; v--; }
            q1(a1, a2, op - 1);
        } else if(op <= 66) {
            auto r = getdims(op - 12);
            vector<int> a1(11), a2(11);
            for(auto& v : a1) { cin >> v; v--; }
            for(auto& v : a2) { cin >> v; v--; }
            q2(a1, a2, r.first, r.second);
        } else {
            auto r = getdims(op - 67);
            q3(r.first, r.second);
        }
    }

    tmp.clear();
    init2(tmp, 0);
    vector<int> curi;
    get(arr, 0, curi);

    for(int i = 0; i < 11; ++i) {
        cout << dimsz[cvtDim[i]] << " ";
    }
    cout << "\n";
    print(tmp, 0);
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
