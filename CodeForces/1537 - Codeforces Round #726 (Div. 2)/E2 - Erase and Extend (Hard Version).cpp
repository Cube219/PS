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
constexpr int MAXN = 1001001;

struct SANode
{
    int idx;
    int rank[2];
};
SANode sa[MAXN];
SANode saTmp[MAXN];
int idx[MAXN];
int cnt[MAXN];
int lcp[MAXN];
int n, m;
string str;

bool operator<(const SANode& l, const SANode& r)
{
    if(l.rank[0] == r.rank[0]) {
        return l.rank[1] < r.rank[1];
    }
    return l.rank[0] < r.rank[0];
}

void get_sa()
{
    for(int i = 0; i < n; i++) {
        sa[i].idx = i;
        sa[i].rank[0] = str[i];
        if(i + 1 < n) sa[i].rank[1] = str[i + 1];
        else sa[i].rank[1] = -1;
    }
    sort(sa, sa + n);

    for(int k = 4; k < 2 * n; k *= 2) {
        int rank0 = sa[0].rank[0];
        int rank1 = sa[0].rank[1];
        int cRank = 0;
        sa[0].rank[0] = 0;
        idx[sa[0].idx] = 0;

        for(int i = 1; i < n; i++) {
            if(sa[i].rank[0] == rank0 && sa[i].rank[1] == rank1) {
                rank0 = sa[i].rank[0];
                rank1 = sa[i].rank[1];
                sa[i].rank[0] = cRank;
            } else {
                rank0 = sa[i].rank[0];
                rank1 = sa[i].rank[1];
                sa[i].rank[0] = ++cRank;
            }
            idx[sa[i].idx] = i;
        }

        int maxRank = cRank + 1;
        // Counting sort, nextRank 기준으로 정렬(nextrank 구하면서 정렬)
        memset(cnt, 0, sizeof(int) * (maxRank + 1));
        for(int i = 0; i < n; i++) {
            int nextI = sa[i].idx + k / 2;
            sa[i].rank[1] = (nextI < n) ? sa[idx[nextI]].rank[0] : -1;
            cnt[sa[i].rank[1] + 1]++;
        }
        for(int i = 1; i < maxRank + 1; i++) {
            cnt[i] += cnt[i - 1];
        }
        for(int i = n - 1; i >= 0; i--) {
            saTmp[--cnt[sa[i].rank[1] + 1]] = sa[i];
        }
        // rank 기준으로 정렬
        memset(cnt, 0, sizeof(int) * (maxRank + 1));
        for(int i = 0; i < n; i++) {
            cnt[sa[i].rank[0] + 1]++;
        }
        for(int i = 1; i < maxRank + 1; i++) {
            cnt[i] += cnt[i - 1];
        }
        for(int i = n - 1; i >= 0; i--) {
            sa[--cnt[saTmp[i].rank[0] + 1]] = saTmp[i];
        }
    }
}

string strt;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> strt;
    while(str.size() < m) {
        str.append(strt);
    }
    n = str.size();
    get_sa();

    int st = 0;
    for(int i = 0; i < n; ++i) {
        if(sa[i].idx == 0) {
            st = i;
            break;
        }
    }
    int minv = n;
    for(int i = st + 1; i < n; ++i) {
        minv = min(minv, sa[i].idx);
    }

    string str2;
    for(int i = 0; i < minv; ++i) {
        str2.push_back(str[i]);
    }
    for(int i = 0; i < m; ++i) {
        cout << str2[i % minv];
    }

    return 0;
}
