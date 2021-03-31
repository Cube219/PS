#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

int n, k;
ll except[1000001];
int nxt[1000001];
bool comp[1000001];
ll res;
int cycleNum, totalNum;
vector<int> st;
bool visit[1000001];

void dfs(int cur, int parent)
{
    if(comp[cur] == true) return;
    if(visit[cur] == true) {
        while(st.back() != cur) {
            st.pop_back();
            cycleNum++;
        }
        cycleNum++;
        return;
    }
    st.push_back(cur);
    visit[cur] = true;
    totalNum++;
    dfs(nxt[cur], -1);
    comp[cur] = true;
}

ll pw(ll a, ll b)
{
    ll ret = 1;
    while(b > 0) {
        if(b % 2 == 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        b /= 2;
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

    cin >> n >> k;
    for(int i = 1; i <= n; ++i) {
        cin >> nxt[i];
    }

    ll cnt = (k - 1);
    for(int i = 3; i <= n; ++i) {
        except[i] = (cnt - except[i - 1] + MOD) % MOD;
        cnt = (cnt * (k - 1)) % MOD;
    }

    res = 1;
    for(int i = 1; i <= n; ++i) {
        if(visit[i] == false) {
            cycleNum = 0;
            totalNum = 0;
            st.clear();
            dfs(i, -1);

            if(cycleNum > 0) {
                ll tmp = (pw(k - 1, cycleNum - 1) - except[cycleNum] + MOD) % MOD;
                res = (res * tmp) % MOD;
                res = (res * k) % MOD;
            }
            for(int j = 0; j < totalNum - cycleNum; ++j) {
                res = (res * (k - 1)) % MOD;
            }
        }
    }

    cout << res;

    return 0;
}
