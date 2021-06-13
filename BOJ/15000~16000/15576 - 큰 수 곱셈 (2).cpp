#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <complex>
#include <vector>
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
    c.resize(n);
    for(int i = 0; i < n; i++) {
        c[i] = round(cc[i].real() / n);
    }
}

string s1, s2;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s1 >> s2;
    vector<int> co1, co2;
    for(int i = s1.size() - 1; i >= 0; --i) {
        co1.push_back(s1[i] - '0');
    }
    for(int i = s2.size() - 1; i >= 0; --i) {
        co2.push_back(s2[i] - '0');
    }
    vector<int> res;
    mul(co1, co2, res);

    for(int i = 0; i < res.size(); ++i) {
        if(res[i] >= 10) {
            if(i == res.size() - 1) res.push_back(0);
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
    }
    while(res.size() > 0 && res.back() == 0) res.pop_back();

    for(int i = res.size() - 1; i >= 0; --i) {
        cout << res[i];
    }
    if(res.size() == 0) cout << "0";

    return 0;
}
