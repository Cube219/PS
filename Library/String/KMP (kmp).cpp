struct KMP
{
    vector<int> fail;

    void init_fail(const string& w)
    {
        int wn = w.size();
        fail.clear();
        fail.resize(wn, 0);

        int j = 0;
        for(int i = 1; i < wn; ++i) {
            while(j > 0 && w[i] != w[j]) {
                j = fail[j - 1];
            }
            if(w[i] == w[j]) {
                fail[i] = j + 1;
                j++;
            }
        }
    }

    void get(const string& s, const string& w, vector<int>& res)
    {
        init_fail(w);
        res.clear();

        int sn = s.size();
        int wn = w.size();

        int j = 0;
        for(int i = 0; i < sn; ++i) {
            while(j > 0 && s[i] != w[j]) {
                j = fail[j - 1];
            }
            if(s[i] == w[j]) {
                j++;
            }
            if(j == wn) {
                res.push_back(i - wn + 1);
                j = fail[j - 1];
            }
        }
    }
};
