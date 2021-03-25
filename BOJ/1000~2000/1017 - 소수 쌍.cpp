#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

bool isNotPrime[2001];
void init()
{
    for(int i = 2; i * i <= 2000; ++i) {
        int j = i * 2;
        if(isNotPrime[i] == true) continue;
        while(j <= 2000) {
            isNotPrime[j] = true;
            j += i;
        }
    }
}

int n;
vector<int> ld, rd;
int first;

vector<int> g[51];
int a[51], b[51];
bool isComp[51];
bool bp(int cur, int except)
{
    isComp[cur] = true;
    for(int nxt : g[cur]) {
        if(nxt == except) continue;
        if(b[nxt] == -1) {
            a[cur] = nxt;
            b[nxt] = cur;
            return true;
        } else if(isComp[b[nxt]] == false) {
            bool f = bp(b[nxt], except);
            if(f == true) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            }
        }
    }
    return false;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();

    cin >> n;
    cin >> first;
    for(int i = 1; i < n; ++i) {
        int d;
        cin >> d;
        if(d % 2 == 0) rd.push_back(d);
        else ld.push_back(d);
    }
    if(first % 2 == 0) {
        if(rd.size() + 1 != ld.size()) {
            cout << "-1";
            return 0;
        }
        swap(ld, rd);
    } else {
        if(rd.size() != ld.size() + 1) {
            cout << "-1";
            return 0;
        }
    }

    for(int i = 0; i < ld.size(); ++i) {
        for(int j = 0; j < rd.size(); ++j) {
            int v = ld[i] + rd[j];

            if(isNotPrime[v] == false) {
                g[i].push_back(j);
            }
        }
    }

    vector<int> res;
    for(int i = 0; i < rd.size(); ++i) {
        int v = first + rd[i];
        if(isNotPrime[v] == true) continue;

        for(int j = 0; j < ld.size(); ++j) {
            a[j] = -1;
        }
        for(int j = 0; j < rd.size(); ++j) {
            b[j] = -1;
        }

        int cnt = 0;
        for(int j = 0; j < ld.size(); ++j) {
            if(a[j] == -1) {
                for(int k = 0; k < rd.size(); ++k) {
                    isComp[k] = false;
                }
                if(bp(j, i) == true) cnt++;
            }
        }
        if(cnt == ld.size()) {
            res.push_back(rd[i]);
        }
    }
    sort(res.begin(), res.end());

    if(res.size() == 0) {
        cout << "-1";
    } else {
        for(int i = 0; i < res.size(); ++i) {
            cout << res[i] << " ";
        }
    }

    return 0;
}
