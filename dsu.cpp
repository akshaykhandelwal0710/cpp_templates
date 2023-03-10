struct dsu{
    vector<int> root, size;
    int lsta, lstb;

    dsu(int n){
        for (int i = 0; i < n; i++){
            root.push_back(i);
            size.push_back(1);
        }
    }

    int find(int a){
        while (a != root[a]){
            a = root[a];
        }
        return a;
    }

    bool unite (int a, int b){
        a = find(a);
        b = find(b);
        if (a == b){
            return false;
        }
        if (size[a] < size[b]){
            swap(a, b);
        }
        root[b] = a;
        size[a] += size[b];
        lsta = a, lstb = b;
        return true;
    }

    void revert_back(){
        size[lsta] -= size[lstb];
        root[lstb] = lstb;
    }
};