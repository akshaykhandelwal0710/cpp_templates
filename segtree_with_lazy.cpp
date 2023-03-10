struct segmentTree{
    int low, high;
    segmentTree *left;
    segmentTree *right;
    $type$ val, lazy;

    void update_val(){
        val = left->val + right->val;
    }

    segmentTree(int l, int h, $type$ default_val){
        low = l;
        high = h;
        lazy = 0;
        if (l < h){
            int mid = (low + high)/2;
            left = (segmentTree *)malloc(sizeof(segmentTree));
            right = (segmentTree *)malloc(sizeof(segmentTree));
            *left = segmentTree(low, mid, default_val);
            *right = segmentTree(mid+1, high, default_val);
            update_val();
        }
        else{
            val = default_val;
        }
    }

    segmentTree(int l, int h, vector<$type$> &arr){
        low = l;
        high = h;
        lazy = 0;
        if (l < h){
            int mid = (low + high)/2;
            left = (segmentTree *)malloc(sizeof(segmentTree));
            right = (segmentTree *)malloc(sizeof(segmentTree));
            *left = segmentTree(low, mid, arr);
            *right = segmentTree(mid+1, high, arr);
            update_val();
        }
        else{
            val = arr[l];
        }
    }

    void push_down(){
        val += lazy*(high-low+1);
        if (low < high){
            left->lazy += lazy;
            right->lazy += lazy;
        }
        lazy = 0;
    }

    $type$ get(){
        push_down();
        return val;
    }

    $type$ get_range(int l, int h){
        push_down();
        if (low > h || high < l){
            return 0;
        }
        else if (low >= l && high <= h){
            return val;
        }
        else{
            return left->get_range(l, h) + right->get_range(l, h);
        }
    }

    void update_range(int l, int h, $type$ diff){
        push_down();
        if (low > h || high < l){
            return;
        }
        if (low >= l && high <= h){
            lazy += diff;
            push_down();
        }
        else{
            left->update_range(l, h, diff);
            right->update_range(l, h, diff);
            update_val();
        }
    }

    void change_val(int k, $type$ vl){
        push_down();
        if (low > k || high < k){
            return;
        }
        else if (low == high){
            val = vl;
        }
        else{
            left->change_val(k, vl);
            right->change_val(k, vl);
            update_val();
        }
    }
};