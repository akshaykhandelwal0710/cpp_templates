struct xor_basis{
    vector<int> *basis;
    int n;
    xor_basis(int n): n{n} {
        basis = new vector<int>(n, 0);
    }

    bool add(int x){
        for (int i = n - 1; i >= 0; i--) {
            if (x & (1 << i)) {
                if ((*basis)[i]){
                    x ^= (*basis)[i];
                }
                else {
                    (*basis)[i] = x;
                    return true;
                }
            }
        }
        
        return false;
    }
    
    bool check(int x){
        for (int i = n - 1; i >= 0; i--) {
            if (x & (1 << i)) x ^= (*basis)[i];
        }
        
        return (x == 0);
    }
};