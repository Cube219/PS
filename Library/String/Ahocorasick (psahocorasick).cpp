struct AhoCorasick
{
    enum { BASE = 'a', NUM = 'z' - 'a' + 1 };
    struct Node
    {
        int nxt[NUM], fail = 0;
        int num = 0;
        Node()
        {
            fill(nxt, nxt + NUM, -1);
        }
    };
    vector<Node> t;

    AhoCorasick(vector<string>& pat) : t(1)
    {
        for(auto& str : pat) insert(str);

        queue<int> q; q.push(0);
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(int i = 0; i < NUM; ++i) {
                int nx = t[cur].nxt[i];
                if(nx == -1) continue;

                if(cur == 0) t[nx].fail = 0;
                else {
                    int pre = t[cur].fail;
                    while(pre != 0 && t[pre].nxt[i] == -1) pre = t[pre].fail;
                    if(t[pre].nxt[i] != -1) pre = t[pre].nxt[i];

                    t[nx].fail = pre;
                    t[nx].num += t[pre].num;
                }
                q.push(nx);
            }
        }
    }

    void insert(string& str)
    {
        int cur = 0;
        for(int i = 0; i < str.size(); ++i) {
            int ch = str[i] - BASE;
            if(t[cur].nxt[ch] == -1) {
                t[cur].nxt[ch] = t.size();
                t.emplace_back();
            }
            cur = t[cur].nxt[ch];
        }
        t[cur].num++;
    }

    int search(string& str)
    {
        int cur = 0, res = 0;
        for(int i = 0; i < str.size(); ++i) {
            int ch = str[i] - BASE;
            while(cur != 0 && t[cur].nxt[ch] == -1) cur = t[cur].fail;
            if(t[cur].nxt[ch] != -1) cur = t[cur].nxt[ch];

            if(cur != 0) res += t[cur].num;
        }
        return res;
    }
};
