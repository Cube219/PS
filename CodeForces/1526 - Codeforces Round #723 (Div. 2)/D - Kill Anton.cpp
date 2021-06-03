#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

template <int N>
class SegTree
{
public:
    int t[N * 3];
    int stLeaf, n;

    void init(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
    }
    void clear()
    {
        for(int i = 1; i <= stLeaf * 2; ++i) {
            t[i] = 0;
        }
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node];
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, node * 2) + findImpl(m + 1, cr, l, r, node * 2 + 1);
    }

    int find(int l, int r)
    {
        return findImpl(0, stLeaf - 1, l, r, 1);
    }

    void add(int idx)
    {
        int node = stLeaf + idx;
        t[node]++;
        node /= 2;
        while(node > 0) {
            t[node] = t[node * 2] + t[node * 2 + 1];
            node /= 2;
        }
    }
};

SegTree<100001> sg;
int tNum;
string str;
int nums[4];
int per[4];
ll res;
int resper[4];

char getch(int v)
{
    switch(v) {
        case 0: return 'A';
        case 1: return 'N';
        case 2: return 'O';
        case 3: return 'T';
        default: return 'A';
    }
}
int getchidx(char ch)
{
    switch(ch) {
        case 'A': return 0;
        case 'N': return 1;
        case 'O': return 2;
        case 'T': return 3;
        default: return -1;
    }
}

ll getnum(string& ss)
{
    vector<int> idxs[4];
    for(int i = str.size() - 1; i >= 0; --i) {
        int chidx = getchidx(str[i]);
        idxs[chidx].push_back(i);
    }
    sg.clear();

    ll ret = 0;
    int n = ss.size();
    for(int i = 0; i < ss.size(); ++i) {
        int chidx = getchidx(ss[i]);
        ret += sg.find(idxs[chidx].back(), n);
        sg.add(idxs[chidx].back());
        idxs[chidx].pop_back();
    }

    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> str;
        for(int i = 0; i < 4; ++i) {
            nums[i] = 0;
        }
        sg.init(str.size());
        for(int i = 0; i < str.size(); ++i) {
            if(str[i] == 'A') nums[0]++;
            else if(str[i] == 'N') nums[1]++;
            else if(str[i] == 'O') nums[2]++;
            else nums[3]++;
        }

        for(int i = 0; i < 4; ++i) {
            per[i] = i;
        }
        string cur;
        res = -1;
        for(int i = 0; i < 24; ++i) {
            cur.clear();
            for(int j = 0; j < 4; ++j) {
                int ch = per[j];
                for(int k = 0; k < nums[ch]; ++k) {
                    cur.push_back(getch(ch));
                }
            }
            ll r = getnum(cur);
            if(r > res) {
                res = r;
                for(int j = 0; j < 4; ++j) {
                    resper[j] = per[j];
                }
            }
            next_permutation(per, per + 4);
        }
        cur.clear();
        for(int j = 0; j < 4; ++j) {
            int ch = resper[j];
            for(int k = 0; k < nums[ch]; ++k) {
                cur.push_back(getch(ch));
            }
        }
        cout << cur <<"\n";
    }

    return 0;
}
