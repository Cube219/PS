#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
int parent[100001];
vector<int> child[100001];
ll d[100001];

int find(int a)
{
    if(parent[a] != a) a = parent[a];
    return a;
}

void add(int a, int b, ll c)
{
    int ar = find(a);
    int br = find(b);

    if(ar == br) return;

    if(child[ar] < child[br]) {
        swap(ar, br);
        swap(a, b);
        c = -c;
    }

    c -= d[b];
    c += d[a];

    d[br] = c;
    parent[br] = ar;
    child[ar].push_back(br);

    for(int ch : child[br]) {
        d[ch] += c;
        parent[ch] = ar;
        child[ar].push_back(ch);
    }
    child[br].clear();
}

bool search(int a, int b, ll& res)
{ 
    int ar = find(a);
    int br = find(b);
    if(ar != br) return false;

    res = d[b] - d[a];
    return true;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n >> m;
        if(n == 0 && m == 0) break;

        for(int i = 1; i <= n; ++i) {
            parent[i] = i;
            d[i] = 0;
            child[i].clear();
        }

        for(int i = 0; i < m; ++i) {
            char ch;
            int a, b;
            ll c;
            cin >> ch;
            if(ch == '!') {
                cin >> a >> b >> c;
                add(a, b, c);
            } else {
                cin >> a >> b;
                ll res = 0;
                if(search(a, b, res) == false) {
                    cout << "UNKNOWN\n";
                } else {
                    cout << res << "\n";
                }
            }
        }
    }

    return 0;
}
