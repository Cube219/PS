#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int d;
ll res;

bool isNotPrime[200001];
vector<int> p;

void init()
{
    for(int i = 2; i <= 200000; i++) {
        for(int j = i * 2; j <= 200000; j += i) {
            isNotPrime[j] = true;
        }
    }

    for(int i = 2; i <= 200000; i++) {
        if(isNotPrime[i] == false) p.push_back(i);
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> d;

        res = 1;
        ll pre = 1;
        int cnt = 1;

        for(int i = 0; i < p.size(); i++) {
            ll cur = p[i];

            if(cur - pre >= d) {
                res *= cur;
                pre = cur;
                cnt++;

                if(cnt == 3) break;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
