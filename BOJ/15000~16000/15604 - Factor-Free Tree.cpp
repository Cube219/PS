#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr int MAXN = 10000000;
int min_factor[MAXN + 1];
vector<pair<int, int>> fPrimes;

int n;
int d[1000001];
int table[10000001];
int pnum;
vector<int> pidx[1000001];
vector<int> cnt;
bool pos = true;
int parents[1000001];

void init()
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
    for(int i = 2; i <= MAXN; ++i) {
        if(i == min_factor[i]) {
            table[i] = pnum++;
        }
    }

    for(int i = 0; i < n; ++i) {
        int v = d[i];
        while(v > 1) {
            pidx[i].push_back(table[min_factor[v]]);
            v /= min_factor[v];
        }
        sort(pidx[i].begin(), pidx[i].end());
        pidx[i].erase(unique(pidx[i].begin(), pidx[i].end()), pidx[i].end());
    }

    cnt.resize(pnum, 0);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < pidx[i].size(); ++j) {
            cnt[pidx[i][j]]++;
        }
    }
}

void process(int l, int r, int p)
{
    if(l == r) {
        for(int i = 0; i < pidx[l].size(); ++i) {
            cnt[pidx[l][i]]--;
        }
        parents[l] = p;
    }
    if(l >= r) return;

    int root = -1;
    int left = l, right = r;
    while(left <= right) {
        bool f = true;
        for(int i = 0; i < pidx[left].size(); ++i) {
            if(cnt[pidx[left][i]] > 1) {
                f = false;
                break;
            }
        }
        if(f == true) {
            root = left;
            break;
        }

        f = true;
        for(int i = 0; i < pidx[right].size(); ++i) {
            if(cnt[pidx[right][i]] > 1) {
                f = false;
                break;
            }
        }
        if(f == true) {
            root = right;
            break;
        }
        left++;
        right--;
    }
    if(root == -1) {
        pos = false;
        return;
    }
    parents[root] = p;

    if(root - l < r - root) {
        for(int i = l; i <= root; ++i) {
            for(int j = 0; j < pidx[i].size(); ++j) {
                cnt[pidx[i][j]]--;
            }
        }
        process(root + 1, r, root);
        for(int i = l; i < root; ++i) {
            for(int j = 0; j < pidx[i].size(); ++j) {
                cnt[pidx[i][j]]++;
            }
        }
        process(l, root - 1, root);
    } else {
        for(int i = root; i <= r; ++i) {
            for(int j = 0; j < pidx[i].size(); ++j) {
                cnt[pidx[i][j]]--;
            }
        }
        process(l, root - 1, root);
        for(int i = root + 1; i <= r; ++i) {
            for(int j = 0; j < pidx[i].size(); ++j) {
                cnt[pidx[i][j]]++;
            }
        }
        process(root + 1, r, root);
    }
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
        cin >> d[i];
    }
    init();
    process(0, n - 1, -1);

    if(pos == false) {
        cout << "impossible";
    } else {
        for(int i = 0; i < n; ++i) {
            cout << parents[i] + 1 << " ";
        }
    }

    return 0;
}
