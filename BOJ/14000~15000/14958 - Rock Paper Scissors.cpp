#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <complex>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

using cpx = complex<double>;
const double PI = acos(-1);

void fft(vector<cpx>& poly, cpx w)
{
    int n = poly.size();
    if(n == 1) return;

    vector<cpx> even(n >> 1), odd(n >> 1);
    for(int i = 0; i < n; i++) {
        if(i & 1) odd[i >> 1] = poly[i];
        else even[i >> 1] = poly[i];
    }
    fft(even, w * w);
    fft(odd, w * w);
    cpx wp(1, 0);
    for(int i = 0; i < (n >> 1); i++) {
        poly[i] = even[i] + wp * odd[i];
        poly[i + n / 2] = even[i] - wp * odd[i];
        wp = wp * w;
    }
}

void mul(vector<int>& a, vector<int>& b, vector<int>& c)
{
    vector<cpx> ca(a.begin(), a.end());
    vector<cpx> cb(b.begin(), b.end());
    vector<cpx> cc;
    int n = 1;
    while(n <= a.size() || n <= b.size()) n <<= 1;
    n <<= 1;
    ca.resize(n);
    cb.resize(n);
    cc.resize(n);

    cpx w(cos(2 * PI / n), sin(2 * PI / n));
    fft(ca, w);
    fft(cb, w);

    for(int i = 0; i < n; i++) {
        cc[i] = ca[i] * cb[i];
    }

    fft(cc, cpx(w.real(), -w.imag()));
    c.clear();
    c.resize(n);
    for(int i = 0; i < n; i++) {
        c[i] = round(cc[i].real() / n);
    }
}

int n, m;
string s1, s2;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> s1 >> s2;
    vector<int> a, b, res, tmp;
    // R -> S
    for(int i = 0; i < n; ++i) {
        if(s1[i] == 'S') a.push_back(1);
        else a.push_back(0);
    }
    for(int i = m - 1; i >= 0; --i) {
        if(s2[i] == 'R') b.push_back(1);
        else b.push_back(0);
    }
    mul(a, b, tmp);
    res = tmp;
    // S -> P
    a.clear(); b.clear();
    for(int i = 0; i < n; ++i) {
        if(s1[i] == 'P') a.push_back(1);
        else a.push_back(0);
    }
    for(int i = m - 1; i >= 0; --i) {
        if(s2[i] == 'S') b.push_back(1);
        else b.push_back(0);
    }
    mul(a, b, tmp);
    for(int i = 0; i < tmp.size(); ++i) {
        res[i] += tmp[i];
    }
    // P -> R
    a.clear(); b.clear();
    for(int i = 0; i < n; ++i) {
        if(s1[i] == 'R') a.push_back(1);
        else a.push_back(0);
    }
    for(int i = m - 1; i >= 0; --i) {
        if(s2[i] == 'P') b.push_back(1);
        else b.push_back(0);
    }
    mul(a, b, tmp);
    for(int i = 0; i < tmp.size(); ++i) {
        res[i] += tmp[i];
    }

    int r = 0;
    for(int i = m - 1; i < res.size(); ++i) {
        r = max(r, res[i]);
    }
    cout << r;

    return 0;
}
