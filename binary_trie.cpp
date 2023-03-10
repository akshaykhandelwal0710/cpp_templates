struct trie{
    struct node{
        int val;
        node *on, *off;

        node(int vl){
            val = vl;
            on = off = nullptr;
        }
    };

    node *root;
    node *cur;
    trie(){
        root = new node(0);
        cur = root;
    }

    void start(){
        cur = root;
    }

    int cur_val(){
        return cur->val;
    }

    void change_val(int val){
        cur->val = val;
    }

    bool go_down(bool flg){
        if (flg){
            if (cur->on == nullptr){
                return false;
            }
            cur = cur->on;
        }
        else{
            if (cur->off == nullptr){
                return false;
            }
            cur = cur->off;
        }
        return true;
    }

    void add_next(int val, bool flg){
        if (flg){
            if (cur->on == nullptr){
                cur->on = new node(val);
            }
            else{
                cur->on->val = val;
            }
        }
        else{
            if (cur->off == nullptr){
                cur->off = new node(val);
            }
            else{
                cur->off->val = val;
            }
        }
    }
};