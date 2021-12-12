#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

const int LIM = 50001;
vector<int> pr; // prime set
int sp[LIM]; // minimum prime
int cnt[LIM]; // 2 ^ (prime_num)?
int mu[LIM]; // Mobius

void get_sieve()
{
	cnt[1] = 1;
	mu[1] = 1;
	for(int i = 2; i < LIM; ++i) {
		if(!sp[i]) pr.push_back(i), cnt[i] = 2, mu[i] = -1;
		for(auto& x : pr) {
			if(x * i >= LIM) break;
			sp[x * i] = x;
			cnt[x * i] = i % x == 0 ? cnt[i] : cnt[i] + 1;
			mu[x * i] = (i % x != 0) * (-mu[i]);
			if(i % x == 0) break;
		}
	}
}
int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    get_sieve();

    int n;
    cin >> n;

    int res = 0;
    for(int i = 1; i <= n; ++i) {
		res += mu[i] * (n / i) * (n / i);
    }
	cout << res / 2;

    return 0;
}
