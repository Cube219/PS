#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

vector<int> g[101];
int a[101], b[51];
bool isComp[101];
bool bp(int cur)
{
    isComp[cur] = true;
    for(int nxt : g[cur]) {
        if(b[nxt] == -1) {
            a[cur] = nxt;
            b[nxt] = cur;
            return true;
        } else if(isComp[b[nxt]] == false) {
            bool f = bp(b[nxt]);
            if(f == true) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            }
        }
    }
    return false;
}

struct Shark
{
    int a, b, c;
};
bool isSame(const Shark& l, const Shark& r)
{
    return l.a == r.a && l.b == r.b && l.c == r.c;
}
bool isGt(const Shark& l, const Shark& r)
{
    return l.a <= r.a && l.b <= r.b && l.c <= r.c;
}
void add(int a, int b)
{
    g[a * 2].push_back(b);
    g[a * 2 + 1].push_back(b);
}

int n;
Shark d[51];
bool match[51][51];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].a >> d[i].b >> d[i].c;
    }

    for(int i = 0; i < n - 1; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(isSame(d[i], d[j])) {
                if(match[j][i] == true) continue;
                match[i][j] = match[j][i] = true;

                add(i, j);
            } else if(isGt(d[i], d[j])) {
                add(j, i);
            } else if(isGt(d[j], d[i])) {
                add(i, j);
            }
        }
    }

    for(int i = 0; i < n * 2; ++i) {
        a[i] = -1;
        b[i] = -1;
    }

    int res = 0;
    for(int i = 0; i < n * 2; ++i) {
        if(a[i] == -1) {
            for(int j = 0; j < n * 2; ++j) {
                isComp[j] = false;
            }
            if(bp(i) == true) res++;
        }
    }

    cout << n - res;

    return 0;
}
