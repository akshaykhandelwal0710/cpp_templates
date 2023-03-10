pair<long long, long long> extended_gcd(long long a, long long b){
    pair<long long, long long> aa = {1, 0}, bb = {0, 1};
    while (b){
        aa.first -= bb.first*(a/b);
        aa.second -= bb.second*(a/b);
        a %= b;
        swap(a, b);
        swap(aa, bb);
    }

    return aa;
}

pair<long long, long long> temp;
struct mint{
    int vl;
    mint(){
        vl = 0;
    }
    mint(long long v){
        if (v < 0){
            v += ((-v + mod - 1)/mod)*mod;
        }
        vl = (int)(v % mod);
    }

    mint operator +(mint oth){
        return mint((long long)vl + oth.vl);
    }

    mint operator -(mint oth){
        return mint((long long)vl - oth.vl);
    }

    mint operator *(mint oth){
        return mint((long long)vl*oth.vl);
    }

    mint powr(long long k){
        if (k == 0){
            return mint(1);
        }
        else if (k%2){
            return (*this)*powr(k - 1);
        }
        else{
            mint tmp = powr(k/2);
            return tmp*tmp;
        }
    }

    mint inv(){
        temp = extended_gcd(vl, mod);
        return mint(temp.first);
    }

    mint operator /(mint oth){
        return (*this)*oth.inv();
    }

    void operator +=(mint oth){
        (*this) = (*this) + oth;
    }

    void operator -=(mint oth){
        (*this) = (*this) - oth;
    }

    void operator *=(mint oth){
        (*this) = (*this) * oth;
    }

    void operator /=(mint oth){
        (*this) = (*this) / oth;
    }
};
ostream& operator<<(ostream& os, const mint& m)
{
    os << m.vl;
    return os;
}