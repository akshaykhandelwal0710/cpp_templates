struct automaton{
    struct mp{
        set<pair<char, int>> st;

        int get(char c){
            auto it = st.lower_bound({c, -1});
            if (it == st.end() || (*it).first != c){
                return -1;
            }
            return (*it).second;
        }

        void add(char c, int vl){
            auto it = st.lower_bound({c, -1});
            if (it != st.end() && (*it).first == c){
                st.erase(it);
            }
            st.insert({c, vl});
        }
    };

    struct state{
        int len, link;
        vector<int> inv_link;
        int fpos;
        bool is_clone;
        mp next;
    };
    
    vector<state> states;
    int last, sz;

    automaton(int MAX){
        states.resize(2*MAX);
        last = 0;
        sz = 1;
        states[0].len = 0;
        states[0].link = -1;
    }

    void add(char c){
        int cur = sz++;
        int p = last;
        states[cur].len = states[last].len + 1;
        states[cur].fpos = states[cur].len - 1;
        states[cur].is_clone = false;
        while (p != -1 && states[p].next.get(c) == -1){
            states[p].next.add(c, cur);
            p = states[p].link;
        }

        if (p == -1){
            states[cur].link = 0;
        }
        else{
            int q = states[p].next.get(c);
            if (states[p].len + 1 == states[q].len){
                states[cur].link = q;
            }
            else{
                int clone = sz++;
                states[clone].len = states[p].len + 1;
                states[clone].next = states[q].next;
                states[clone].link = states[q].link;
                while (p != -1 && states[p].next.get(c) == q){
                    states[p].next.add(c, clone);
                    p = states[p].link;
                }
                states[q].link = states[cur].link = clone;
                states[clone].fpos = states[clone].len - 1;
                states[clone].is_clone = true;
            }
        }

        last = cur;
    }

    void create_inv(){
        for (int v = 1; v < sz; v++){
            states[states[v].link].inv_link.push_back(v);
        }
    }

    void give_all_occurences(int nd, vector<int> &v){
        if (!states[nd].is_clone){
            v.push_back(states[nd].fpos);
        }
        for (auto u: states[nd].inv_link){
            give_all_occurences(u, v);
        }
    }

    int find(string &p){
        int cur = 0;
        for (auto ch: p){
            cur = states[cur].next.get(ch);
            if (cur == -1){
                return 0;
            }
        }

        return cur;
    }
};