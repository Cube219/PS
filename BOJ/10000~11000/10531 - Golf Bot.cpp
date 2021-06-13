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

int n, m;
int k[200001], d[200001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> k[i];
    }
    cin >> m;
    for(int i = 0; i < m; ++i) {
        cin >> d[i];
    }

    vector<int> co;
    co.resize(200001);
    co[0] = 1;
    for(int i = 0; i < n; ++i) {
        co[k[i]] = 1;
    }
    vector<int> res;
    mul(co, co, res);

    int r = 0;
    for(int i = 0; i < m; ++i) {
        if(res[d[i]] > 0) r++;
    }
    cout << r;

    return 0;
}
