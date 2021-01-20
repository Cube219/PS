#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

using lli = long long int;

int tNum;
int k;
vector<int> primes;
bool p[1001];

int res[3];
bool isPos;

void init()
{
    for(int i = 2; i <= 1000; i++) {
        for(int j = i*2; j <= 1000; j += i) {
            p[j] = true;
        }
    }

    for(int i = 2; i <= 1000; i++) {
        if(p[i] == false) {
            primes.push_back(i);
        }
    }
}

void pp(int index, int idx, int sum)
{
    if(index == 3) {
        if(sum == k) {
            isPos = true;
        }
        return;
    }

    for(int i = idx; i < primes.size(); i++) {
        res[index] = primes[i];
        sum += primes[i];
        if(sum > k) continue;

        pp(index + 1, i, sum);

        sum -= primes[i];

        if(isPos == true) return;
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
        cin >> k;

        isPos = false;

        pp(0, 0, 0);

        if(isPos == true) {
            cout << res[0] << " "<< res[1] << " " << res[2] << "\n";
        } else {
            cout << "0\n";
        }
    }

    return 0;
}
