#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include <limits>
using namespace std;

using ll = long long int;

int n;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> distribution(0, 999999999);

vector<int> ans;
int qnum;

int query(vector<int>& d)
{
#ifdef CUBE_PS
	if(qnum > n + 500) {
		cout << "Max query error";
		exit(0);
	}
	int num = 0;
	for(int i = 0; i < n; ++i) {
		if(d[i] == ans[i]) num++;
	}
	if(num != n && num != n / 2) num = 0;

	if(num == n) {
		cout << "Correct: ";
		for(int i = 0; i < n; i++) cout << d[i];
	}

	return num;
#else
	for(int i = 0; i < n; ++i) cout << d[i];
	cout << endl;

	int res;
	cin >> res;
	return res;
#endif
}

int main(void)
{
#ifdef CUBE_PS
	freopen("input.txt", "r", stdin);
#else
	// freopen("generators.in", "r", stdin);
	// freopen("generators.out", "w", stdout);
#endif

	cin >> n;
	vector<int> d(n, 0);

#ifdef CUBE_PS
	ans.resize(n);
	for(int i = 0; i < n; i++) {
		cin >> ans[i];
	}
#endif

	for(int i = 0; i < 499; i++) {
		for(int j = 0; j < n; ++j) {
			int v = distribution(rng) % 2;
			d[j] = v;
		}
		int res = query(d);
		if(res == n) return 0;
		else if(res == n / 2) break;
	}

	vector<int> d1(n, 0);
	vector<int> d2(n, 0);
	d2[0] = 1;

	for(int i = 1; i < n; i++) {
		d[i - 1] = 1 - d[i - 1];
		d[i] = 1 - d[i];
		int res = query(d);
		if(res == n) return 0;
		if(res == 0) {
			d1[i] = d1[i - 1];
			d2[i] = d2[i - 1];
		} else {
			d1[i] = 1 - d1[i - 1];
			d2[i] = 1 - d2[i - 1];
		}
		d[i - 1] = 1 - d[i - 1];
		d[i] = 1 - d[i];
	}

	vector<int> tmp = d;
	for(int i = 0; i < n; i++) {
		if(d1[i] == 1) tmp[i] = 1 - tmp[i];
	}
	int res = query(tmp);
	if(res != n) {
		tmp = d;
		for(int i = 0; i < n; i++) {
			if(d2[i] == 1) tmp[i] = 1 - tmp[i];
		}
		query(tmp);
	}

	return 0;
}