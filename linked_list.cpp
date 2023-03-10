struct linked_list{
    struct node{
        int data;
        int left, right;

        node(int dat){
            data = dat;
            left = right = 0;
        }

        node(){
            data = left = right = 0;
        }
    };

    vector<node> nodes;
    int cur, sz;
    linked_list(){
        nodes.emplace_back(node());
        cur = 0;
        sz = 1;
    }

    int get(){
        return nodes[cur].data;
    }

    void add_to_left(int data){
        nodes.emplace_back(node(data));
        if (cur){
            int lft = nodes[cur].left;
            nodes[cur].left = sz;
            nodes.back().right = cur;
            nodes.back().left = lft;
            nodes[lft].right = sz;
        }
        cur = sz++;
    }

    void add_to_right(int data){
        nodes.emplace_back(node(data));
        if (cur){
            int rgt = nodes[cur].right;
            nodes[cur].right = sz;
            nodes.back().left = cur;
            nodes.back().right = rgt;
            nodes[rgt].left = sz;
        }
        cur = sz++;
    }

    bool move_left(){
        if (!cur || !nodes[cur].left){
            return false;
        }
        cur = nodes[cur].left;
        return true;
    }

    bool move_right(){
        if (!cur || !nodes[cur].right){
            return false;
        }
        cur = nodes[cur].right;
        return true;
    }
};