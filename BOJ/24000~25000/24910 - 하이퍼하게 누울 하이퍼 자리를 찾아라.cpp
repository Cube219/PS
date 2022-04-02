#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <array>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

#ifdef _WIN32
using l3 = ll;
#else
using l3 = __int128;
#endif

void solve()
{
    int n, k;
    cin >> n >> k;

    using Pos = array<int, 11>;

    vector<Pos> d(k);
    for(auto& v : d) {
        for(int i = 0; i < 11; ++i) {
            cin >> v[i];
            v[i]--;
        }
    }

    if(n == 1) {
        for(int i = 0; i < 11; ++i) {
            cout << 0 << "\n";
        }
        return;
    }

    l3 base = 1;
    for(int i = 0; i < 10; ++i) {
        base *= n;
    }

    auto getAreaNum = [&](vector<int> bPos) {
        int res = 0;
        int lastPos = 0;
        for(int pos : bPos) {
            if(pos - lastPos > 1) res++;
            lastPos = pos + 1;
        }
        if(n - lastPos > 1) res++;

        return res;
    };

    auto isSame = [&](Pos& l, Pos& r, int exceptI) {
        for(int i = 0; i < 11; ++i) {
            if(i == exceptI) continue;
            if(l[i] != r[i]) return false;
        }
        return true;
    };

    auto printl3 = [](l3 v) {
        string str;
        while(v > 0) {
            str.push_back(v % 10 + '0');
            v /= 10;
        }
        if(str.size() == 0) str.push_back('0');
        for(int i = str.size() - 1; i >= 0; --i) {
            cout << str[i];
        }
        cout << "\n";
    };

    for(int i = 0; i < 11; ++i) {
        sort(d.begin(), d.end(), [&i](const array<int, 11>& l, const array<int, 11>& r) {
            for(int j = 0; j < 11; ++j) {
                if(i == j) continue;
                if(l[j] < r[j]) return true;
                else if(l[j] > r[j]) return false;
            }
            return l[i] < r[i];
        });

        int offset = 0;
        vector<int> bPos;
        if(k > 0) {
            Pos lastPos = d[0];
            bPos.push_back(lastPos[i]);
            for(int j = 1; j < k; ++j) {
                if(isSame(lastPos, d[j], i) == false) {
                    int num = getAreaNum(bPos);
                    offset += num - 1;
                    bPos.clear();
                }
                lastPos = d[j];
                bPos.push_back(lastPos[i]);
            }
            int num = getAreaNum(bPos);
            offset += num - 1;
        }

        l3 res = base + offset;
        printl3(res);
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
