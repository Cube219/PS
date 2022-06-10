struct Matrix
{
    vector<vector<ll>> d;
    int n;

    Matrix(int _n) : n(_n)
    {
        d.resize(n);
        for(int i = 0; i < n; ++i) {
            d[i].resize(n);
            for(int j = 0; j < n; ++j) {
                if(i == j) d[i][j] = 1;
                else d[i][j] = 0;
            }
        }
    }
    vector<ll>& operator[](int row) { return d[row]; }

    void mulself()
    {
        Matrix tmp(n);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                tmp.d[i][j] = 0;
                for(int k = 0; k < n; ++k) {
                    tmp.d[i][j] += (d[i][k] * d[k][j]) % MOD;
                    tmp.d[i][j] %= MOD;
                }
            }
        }
        d = move(tmp.d);
    }

    void mul(const Matrix& b)
    {
        Matrix tmp(n);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                tmp.d[i][j] = 0;
                for(int k = 0; k < n; ++k) {
                    tmp.d[i][j] += (d[i][k] * b.d[k][j]) % MOD;
                    tmp.d[i][j] %= MOD;
                }
            }
        }
        d = move(tmp.d);
    }

    void pow(ll p)
    {
        Matrix res(n);
        while(p > 0) {
            if(p & 1) res.mul(*this);
            mulself();
            p >>= 1;
        }
        d = move(res.d);
    }
};
