struct SuffixArray
{
    vector<int> sa, lcp;
    SuffixArray(string& str)
    {
        int n = str.size();
        sa.resize(n);
        vector<int> rnk(n), nxt(n);
        for(int i = 0; i < n; ++i) {
            sa[i] = i;
            rnk[i] = str[i];
        }

        for(int sz = 1; ; sz *= 2) {
            auto cmp = [&](int l, int r) {
                if(rnk[l] != rnk[r]) return rnk[l] < rnk[r];
                l += sz; r += sz;
                if(l < n && r < n) return rnk[l] < rnk[r];
                return l > r;
            };
            sort(sa.begin(), sa.end(), cmp);

            nxt[0] = 0;
            for(int i = 1; i < n; ++i) nxt[i] = nxt[i - 1] + cmp(sa[i - 1], sa[i]);
            for(int i = 0; i < n; ++i) rnk[sa[i]] = nxt[i];

            if(nxt[n - 1] == n - 1) break;
        }

        lcp.resize(n);
        vector<int> pos(n);
        for(int i = 0; i < n; ++i) pos[sa[i]] = i;
        for(int i = 0, k = 0; i < n; ++i, k = max(0, k - 1)) {
            if(pos[i] == 0) continue;
            for(int j = sa[pos[i] - 1]; i + k < n && j + k < n && str[i + k] == str[j + k]; k++) {}
            lcp[pos[i]] = k;
        }
    }
};
