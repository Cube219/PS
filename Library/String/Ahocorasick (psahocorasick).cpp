struct AhoCorasick
{
    constexpr static char BASE = 'A';
    constexpr static int NUM = 'Z' - 'A' + 1;

    AhoCorasick* nxt[NUM];
    AhoCorasick* fail;
    bool has;

    AhoCorasick()
    {
        for(int i = 0; i < NUM; ++i) {
            nxt[i] = nullptr;
        }
        fail = nullptr;
        has = false;
    }

    ~AhoCorasick()
    {
        for(int i = 0; i < NUM; ++i) {
            if(nxt[i] != nullptr) delete nxt[i];
        }
    }

    void insert(const string& str, int idx)
    {
        if(str.size() == idx) {
            has = true;
            return;
        }
        int ch = str[idx] - BASE;
        if(nxt[ch] == nullptr) nxt[ch] = new AhoCorasick();
        nxt[ch]->insert(str, idx + 1);
    }

    void build()
    {
        fail = this;
        queue<AhoCorasick*> q;
        q.push(this);
        while(q.empty() == false) {
            AhoCorasick* cur = q.front();
            q.pop();
            for(int i = 0; i < NUM; ++i) {
                if(cur->nxt[i] == nullptr) continue;
                AhoCorasick* nxt = cur->nxt[i];
                if(cur == this) nxt->fail = this;
                else {
                    AhoCorasick* k = cur->fail;
                    while(k != this && k->nxt[i] == nullptr) k = k->fail;
                    if(k->nxt[i] != nullptr) k = k->nxt[i];
                    nxt->fail = k;
                }
                q.push(nxt);
                if(nxt->fail->has == true) nxt->has = true;
            }
        }
    }

    bool process(const string& str)
    {
        AhoCorasick* cur = this;
        for(int i = 0; i < str.size(); ++i) {
            int ch = str[i] - BASE;
            while(cur != this && cur->nxt[ch] == nullptr) cur = cur->fail;
            if(cur->nxt[ch] != nullptr) cur = cur->nxt[ch];

            if(cur->has == true) return true;
        }
        return false;
    }
};
