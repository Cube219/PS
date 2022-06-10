// https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/SuffixArray.h
struct SuffixArray
{
    vector<int> sa, lcp;
    vector<int> ori, lg2;
    vector<vector<int>> st;

    SuffixArray(string& s, int lim = 256)
    {
        // or basic_string<int>
        int n = s.size() + 1, k = 0, a, b;
        vector<int> x(s.begin(), s.end()), y(n), ws(max(n, lim)), rank(n);
        x.push_back(0);
        sa = lcp = y, iota(sa.begin(), sa.end(), 0);
        for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(y.begin(), y.end(), n - j);
            for(int i = 0; i < n; ++i) if(sa[i] >= j) y[p++] = sa[i] - j;
            fill(ws.begin(), ws.end(), 0);
            for(int i = 0; i < n; ++i) ws[x[i]]++;
            for(int i = 1; i < lim; ++i) ws[i] += ws[i - 1];
            for(int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            for(int i = 1; i < n; ++i) {
                a = sa[i - 1], b = sa[i];
                x[b] = (y[a] == y[b] && a + j < n && b + j < n && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
        }
        for(int i = 1; i < n; ++i) rank[sa[i]] = i;
        for(int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for(k && k--, j = sa[rank[i] - 1];
                i + k < n - 1 && j + k < n - 1 && s[i + k] == s[j + k]; k++);

        // lcp RMQ build
        lg2.resize(n + 1);
        lg2[0] = lg2[1] = 0;
        for(int i = 2; i <= n; ++i) {
            lg2[i] = lg2[i / 2] + 1;
        }

        ori.resize(n);
        int dep = lg2[n];
        st.resize(n);
        for(int i = 0; i < n; ++i) {
            ori[sa[i]] = i;
            st[i].resize(dep + 1);
            st[i][0] = lcp[i];
        }
        for(int j = 1; j <= dep; ++j) {
            for(int i = 0; i + (1 << (j - 1)) < n; ++i) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int get_lcp(int l, int r)
    {
        if(l == r) return sa.size() - l - 1;
        l = ori[l], r = ori[r];
        if(l > r) swap(l, r);
        int j = lg2[r - l];
        return min(st[l + 1][j], st[r - (1 << j) + 1][j]);
    }
};
// sa[0] = str.size(), sa.size() = str.size() + 1
// lcp[i] = lcp(sa[i - 1], sa[i]), lcp[0] = 0
