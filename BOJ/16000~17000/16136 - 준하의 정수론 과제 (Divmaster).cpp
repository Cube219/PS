#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr int MAXN = 1000000;
int min_factor[MAXN + 1];
vector<pair<int, int>> fPrimes;

void init_primes()
{
    for(int i = 2; i <= MAXN; i++) {
        min_factor[i] = i;
    }

    for(int i = 2; i * i <= MAXN; i++) {
        if(min_factor[i] == i) {
            for(int j = i * i; j <= MAXN; j += i) {
                if(min_factor[j] == j) {
                    min_factor[j] = i;
                }
            }
        }
    }
}

void get_f_primes(int v)
{
    fPrimes.clear();

    while(v > 1) {
        int f = min_factor[v];
        if(fPrimes.size() == 0 || fPrimes.back().first != f) {
            fPrimes.push_back(make_pair(f, 0));
        }
        fPrimes.back().second++;
        v /= f;
    }
}

ll process(ll v)
{
    get_f_primes(v);
    ll res = 1;
    for(int i = 0; i < fPrimes.size(); ++i) {
        res *= (fPrimes[i].second + 1);
    }
    return res;
}

template <int N>
class SegTree
{
public:
    ll t[N * 3];
    bool isComp[N * 3];
    int stLeaf, n;

    void init(int n, int* pData)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        for(int i = 0; i < n; ++i) {
            t[stLeaf + i] = pData[i];
            if(pData[i] == 1 || pData[i] == 2) {
                isComp[stLeaf + i] = true;
            } else {
                isComp[stLeaf + i] = false;
            }
        }
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = t[i * 2] + t[i * 2 + 1];
            isComp[i] = isComp[i * 2] && isComp[i * 2 + 1];
        }
    }

    ll findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    void addImpl(int cl, int cr, int l, int r, int node)
    {
        if(isComp[node] == true) {
            return;
        }
        if(cr < l || r < cl) return;
        if(cl == cr) {
            t[node] = process(t[node]);
            if(t[node] == 1 || t[node] == 2) {
                isComp[node] = true;
            }
            return;
        }
        
        int m = (cl + cr) / 2;
        addImpl(cl, m, l, r, node * 2);
        addImpl(m + 1, cr, l, r, node * 2 + 1);
        t[node] = t[node * 2] + t[node * 2 + 1];
        isComp[node] = isComp[node * 2] && isComp[node * 2 + 1];
    }

    ll find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int l, int r)
    {
        addImpl(0, stLeaf - 1, l, r, 1);
    }
};

int n, q;
SegTree<100001> sg;
int d[100001];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_primes();
    cin >> n >> q;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sg.init(n, d);
    for(int i = 0; i < q; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        if(a == 1) {
            sg.add(b - 1, c - 1);
        } else {
            cout << sg.find(b - 1, c - 1) << "\n";
        }
    }

    return 0;
}
