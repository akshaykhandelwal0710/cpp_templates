// fft
const double PI = acos(-1);

void fft(vector<complex<double>> &a, bool invert){
    int n = (int)a.size();

    for (int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for (; j & bit; bit >>= 1){
            j ^= bit;
        }
        j ^= bit;

        if (i < j){
            swap(a[i], a[j]);
        }
    }

    for (int len = 2; len <= n; len <<= 1){
        double angle = 2*PI/len*(invert ? -1 : 1);
        complex<double> wlen(cos(angle), sin(angle));
        for (int i = 0; i < n; i += len){
            complex<double> w(1);
            for (int j = 0; j < len/2; j++){
                complex<double> u = a[i + j], v = a[i + j + len/2]*w;
                a[i + j] = u + v;
                a[i + j + len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert){
        for (int i = 0; i < n; i++){
            a[i] /= n;
        }
    }
}

// ntt
vector<mint> v;

void ntt(vector<mint> &a, mint w){
    int n = (int)a.size();
    int nn = n;

    for (int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for (; j & bit; bit >>= 1){
            j ^= bit;
        }
        j ^= bit;

        if (i < j){
            swap(a[i], a[j]);
        }
    }

    v.clear();
    while (nn != 1){
        v.push_back(w);
        w = w * w;
        nn >>= 1;
    }

    for (int len = 2; len <= n; len <<= 1){
        for (int i = 0; i < n; i += len){
            w = 1;
            for (int j = 0; j < len/2; j++, w = w * v.back()){
                mint one = a[i + j], two = a[i + j + len/2]*w;
                a[i + j] = one + two;
                a[i + j + len/2] = one - two;
            }
        }
        v.pop_back();
    }
}

// convolution (polynomial multiplication)
vector<mint> convolution(vector<mint> a, vector<mint> b){
    int n = a.size(), m = b.size();
    int len = n + m - 1;
    int p = 1;
    while (p < len){
        p <<= 1;
    }

    mint w = mint(r).powr((mod - 1) / p);
    mint w_inv = w.inv();
    mint len_inv = mint(p).inv();
    while (a.size() < p) a.push_back(0);
    while (b.size() < p) b.push_back(0);
    ntt(a, w);
    ntt(b, w);
    for (int i = 0; i < p; i++){
        a[i] *= b[i];
    }
    ntt(a, w_inv);
    for (int i = 0; i < p; i++){
        a[i] *= len_inv;
    }
    while (a.size() > len){
        a.pop_back();
    }
    return a;
}

// polynomial inverse
void poly_inverse(vector<mint> &a){
    int n = (int)a.size();
    if (n == 1){
        a = {a[0].inv(), 0};
        return;
    }
    mint w = r.powr((mod - 1) / (2 * n));
    mint iv = mint(2 * n).inv();

    vector<mint> a_(2 * n, 0), t(2 * n, 0);
    for (int i = 0; i < n; i++){
        a_[i] = a[i];
        t[i] = a[i];
        if (i % 2){
            a_[i] *= -1;
        }
    }

    ntt(t, w);
    ntt(a_, w);
    for (int i = 0; i < 2 * n; i++){
        t[i] *= a_[i];
    }
    ntt(t, w.inv());
    for (int i = 0; i < 2 * n; i++){
        t[i] *= iv;
    }

    vector<mint> tt(n / 2, 0);
    for (int i = 0; i < n / 2; i++){
        tt[i] = t[i * 2];
        assert(t[i * 2 + 1].vl == 0);
    }
    poly_inverse(tt);
    for (int i = 0; i < 2 * n; i++){
        if (i % 2 == 0 && i < n){
            t[i] = tt[i / 2];
        }
        else{
            t[i] = 0;
        }
    }
    ntt(t, w);
    for (int i = 0; i < 2 * n; i++){
        a_[i] *= t[i];
    }
    ntt(a_, w.inv());
    for (int i = 0; i < 2 * n; i++){
        a_[i] *= iv;
    }
    a = a_;
}