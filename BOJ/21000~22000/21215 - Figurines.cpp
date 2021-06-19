#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

struct PST
{
    struct Node
    {
        int l = -1, r = -1;
        int v = 0;
    };

    vector<Node> t;
    int stLeaf;
    vector<int> root;

    void init(int n)
    {
        t.clear();
        root.clear();
        root.push_back(1);

        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        t.resize(stLeaf * 2 + 1);

        for(int i = 1; i < stLeaf; ++i) {
            t[i].l = i * 2;
            t[i].r = i * 2 + 1;
        }
    }

    int findImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node].v;
        else if(cr < l || r < cl) return 0;
        int m = (cl + cr) / 2;
        return findImpl(cl, m, l, r, t[node].l) + findImpl(m + 1, cr, l, r, t[node].r);
    }

    int find(int l, int r, int version)
    {
        return findImpl(0, stLeaf - 1, l, r, root[version]);
    }

    void update(int idx, int v)
    {
        int cl = 0, cr = stLeaf - 1;
        int node = root.back();

        int newnode = t.size();
        root.push_back(newnode);
        t.push_back(t[node]);

        while(cl != cr) {
            int m = (cl + cr) / 2;
            if(idx <= m) {
                cr = m;
                t[newnode].l = newnode + 1;
                newnode++;

                node = t[node].l;
                t.push_back(t[node]);
            } else {
                cl = m + 1;
                t[newnode].r = newnode + 1;
                newnode++;

                node = t[node].r;
                t.push_back(t[node]);
            }
        }
        t[newnode].v = v;
        newnode--;
        while(newnode >= root.back()) {
            t[newnode].v = t[t[newnode].l].v + t[t[newnode].r].v;
            newnode--;
        }
    }
};

int n;
PST pst;

pair<int, bool> getv(const string& str, int idx)
{
    bool neg = false;
    int a = 0;

    for(int i = idx + 1; i < str.size(); ++i) {
        if(str[i] == ' ') break;
        a *= 10;
        a += str[i] - '0';
    }
    if(str[idx] == '-') neg = true;

    return { a, neg };
}

int version[100001];
int curver;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    pst.init(100001);

    cin >> n;
    string str;
    getline(cin, str);
    for(int i = 0; i < n; ++i) {
        getline(cin, str);

        for(int j = 0; j < str.size(); ++j) {
            if(str[j] != '+' && str[j] != '-') continue;

            auto v = getv(str, j);
            if(v.second == false) {
                pst.update(v.first, 1);
            } else {
                pst.update(v.first, 0);
            }
            curver++;
        }
        version[i] = curver;
    }

    int x = 0;
    for(int i = 0; i < n; ++i) {
        int d;
        cin >> d;
        x += pst.find(x, n, version[d - 1]);
        x %= n;
    }

    cout << x;

    return 0;
}
