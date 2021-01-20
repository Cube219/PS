#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

using lli = long long int;

int tNum;
int n;
vector<int> primes;
vector<int> pNum;
bool isPrime[40000];
vector<int> np;

vector<int> res;
int except;
int exceptIdx;

void init()
{
    for(int i = 2; i < 40000; i++) {
        for(int j = i * 2; j < 40000; j += i) {
            isPrime[j] = true;
        }
    }
    for(int i = 2; i < 40000; i++) {
        if(isPrime[i] == false) {
            primes.push_back(i);
        }
    }
}

void calc(int v)
{
    pNum.clear();
    np.clear();

    for(int i = 0; i < primes.size(); i++) {
        if(v % primes[i] == 0) {
            if(np.size() == 0 || np.back() != primes[i]) {
                np.push_back(primes[i]);
                pNum.push_back(0);
            }
            pNum.back()++;
            v /= primes[i];
            i--;
        }
    }
    if(v > 1) {
        np.push_back(v);
        pNum.push_back(1);
    }
}

int pw(int a, int b)
{
    int res = 1;
    for(int i = 0; i < b; i++) {
        res *= a;
    }
    return res;
}

void p(int idx, int v)
{
    if(idx == np.size()) {
        if(v != except) {
            res.push_back(v);
        } else {
            exceptIdx = res.size();
        }
        return;
    }

    for(int i = 0; i <= pNum[idx]; i++) {
        int tmp = pw(np[idx], i);
        if(tmp == 0) tmp = 1;
        p(idx + 1, v * tmp);
    }
}

int gcd(int a, int b)
{
    if(a > b) swap(a, b);
    if(a == 0) return b;
    while(a > 0) {
        int c = b % a;
        int d = a;
        
        a = c;
        b = d;
    }
    return b;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        calc(n);

        res.clear();

        if(np.size() > 1) {
            except = np[0] * np.back();
            res.push_back(except);
        } else {
            except = -1;
        }

        for(int i = 0; i < np.size(); i++) {
            for(int j = pNum[i]; j >= 1; j--) {
                int current = pw(np[i], j);
                if(current == 0) current = 1;
                p(i + 1, current);
            }
        }

        if(except != -1 && gcd(res[exceptIdx], res[exceptIdx - 1]) == 1)
        {
            int swapV = res[exceptIdx - 1];
            res.erase(res.begin() + (exceptIdx - 1));
            res.insert(res.begin() + 1, swapV);
        }

        for(int i = 0; i < res.size(); i++) {
            cout << res[i] << " ";
        }
        cout << "\n";

        if(np.size() == 2 && pNum[0] == 1 && pNum[1] == 1)
        {
            cout << "1\n"; // 이 경우만 1. 아니면 위에처럼 바꿔주면 됨
        } else {
            cout << "0\n";
        }
    }

    return 0;
}
