// d1: ab c ba -> 00200
// d2: ab b a -> 0020
pair<vector<int>, vector<int>> manacher(const string& str)
{
    int n = str.size();
    vector<int> d1(n), d2(n);
    int l = 0, r = -1;
    for(int i = 0; i < n; ++i) {
        int k = 1;
        if(i <= r) {
            k = min(d1[l + r - i], r - i);
        }
        while(0 <= i - k && i + k < n && str[i - k] == str[i + k]) k++;
        d1[i] = --k;
        if(i + k > r) {
            r = i + k;
            l = i - k;
        }
    }

    l = 0;
    r = -1;
    for(int i = 0; i < n; ++i) {
        int k = 0;
        if(i <= r) {
            k = min(d2[l + r - i + 1], r - i);
        }
        while(0 <= i - k - 1 && i + k < n && str[i - k - 1] == str[i + k]) k++;
        d2[i] = k--;
        if(i + k > r) {
            r = i + k - 1;
            l = i - k;
        }
    }
    return { d1, d2 };
}
