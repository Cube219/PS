using cpx = complex<double>;

void fft(vector<cpx>& f, cpx rt)
{
    int n = f.size();
    if(n == 1) return;

    vector<cpx> even(n/2), odd(n/2);
    for(int i = 0; i < n; ++i) {
        if(i & 1) odd[i / 2] = f[i];
        else even[i / 2] = f[i];
    }

    fft(even, rt*rt); fft(odd, rt*rt);

    cpx cur(1, 0);
    for(int i = 0; i < n / 2; ++i) {
        f[i] = even[i] + cur * odd[i];
        f[i + n / 2] = even[i] - cur * odd[i];
        cur *= rt;
    }
}

constexpr double PI = acos(-1);
vector<ll> conv(vector<ll>& a, vector<ll>& b)
{
    int n = 1;
    while(n <= a.size() || n <= b.size()) n *= 2;
    n *= 2;

    vector<cpx> aa(n), bb(n);
    copy(a.begin(), a.end(), aa.begin());
    copy(b.begin(), b.end(), bb.begin());

    cpx w(cos(2 * PI / n), sin(2 * PI / n));
    fft(aa, w);
    fft(bb, w);

    for(int i = 0; i < n; ++i) aa[i] *= bb[i];
    fft(aa, cpx(1, 0) / w);

    vector<ll> res(n);
    for(int i = 0; i < n; ++i) {
        res[i] = llround(aa[i].real() / n);
    }
    return res;
}

// NTT:
// p = c*2^k+1 -> w = (rt^c)^(2^k / n)
// p = 998244353 -> rt = 3
