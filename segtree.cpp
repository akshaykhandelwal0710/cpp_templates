struct Data{
    // data values
    
    Data(){
        // initialise
    }
};

Data idt = Data(); // additive identity
Data join_res = Data(); // store result of joining here
Data result = Data(); // any result from segtree gets stored here

void join(Data &left, Data &right){
    // function for joining
    
}

void assign(Data &from, Data &to){
    // copy all the data in 'from' to 'to'
    
}

struct segmentTree{
    int low, high;
    bool init;
    segmentTree *left;
    segmentTree *right;
    Data val;

    void update_val(){
        join(left->val, right->val);
        assign(join_res, val);
    }

    segmentTree(int l, int h, bool bl = true){
        low = l;
        high = h;
        val = Data();
        init = bl;
        if (l < h){
            int mid = (low + high)/2;
            left = (segmentTree *)malloc(sizeof(segmentTree));
            right = (segmentTree *)malloc(sizeof(segmentTree));
            *left = segmentTree(low, mid, false);
            *right = segmentTree(mid+1, high, false);
            update_val();
        }
    }

    void get(){
        assign(val, result);
    }

    void get_range(int l, int h){
        if (init){
            assign(idt, result);
        }
        
        if (low > h || high < l){
            return;
        }
        else if (low >= l && high <= h){
            join(result, val);
            assign(join_res, result);
        }
        else{
            left->get_range(l, h);
            right->get_range(l, h);
        }
    }

    void change_val(int k, Data &vl){
        if (low > k || high < k){
            return;
        }
        else if (low == high){
            assign(vl, val);
        }
        else{
            left->change_val(k, vl);
            right->change_val(k, vl);
            update_val();
        }
    }
};