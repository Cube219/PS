struct KMP
{
    vector<int> fail;
    string w;
    KMP(string& _w) : w(_w), fail(_w.size(), 0)
    {
        int j = 0;
        for(int i = 1; i < w.size(); ++i) {
            while(j > 0 && w[i] != w[j]) j = fail[j - 1];
            if(w[i] == w[j]) fail[i] = ++j;
        }
    }

    vector<int> match(string& str)
    {
        vector<int> res;
        int j = 0;
        for(int i = 0; i < str.size(); ++i) {
            while(j > 0 && str[i] != w[j]) j = fail[j - 1];
            if(str[i] == w[j]) j++;
            if(j == w.size()) {
                res.push_back(i - j + 1);
                j = fail[j - 1];
            }
        }
        return res;
    }
};
