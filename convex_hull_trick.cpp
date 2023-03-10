const long long inf = 1e18;

bool Q = false;
struct line{
    mutable long long m, c;
    mutable double x;
    line(long long mm, long long cc){
        m = mm, c = cc;
        x = 0;
    }

    line(long long mm, long long cc, double xx){
        m = mm, c = cc, x = xx;
    }

    bool operator <(const line &oth) const{
        return Q ? x > oth.x : make_pair(m, c) < make_pair(oth.m, oth.c);
    }
};

struct line_container : multiset<line>{
    static double intersect(line a, line b){
        return (double)(b.c - a.c)/(a.m - b.m);
    }
    double get_x(iterator it){
        return it->x = (it == begin() ? (double)inf : intersect(*it, *prev(it)));
    }

    line_container(){
        Q = false;
    }

    void add(long long m, long long c){
        line l = line(m, c);
        auto it = insert(l);
        if (it != begin() && prev(it)->m == m){
            erase(it);
            return;
        }
        if (it != prev(end()) && next(it)->m == m){
            it = erase(next(it));
            it--;
        }
        while (it != begin() && get_x(prev(it)) <= get_x(it)){
            it = erase(prev(it));
        }
        if (it != prev(end()) && get_x(it) <= get_x(next(it))){
            it = erase(it);
            get_x(it);
            return;
        }
        get_x(it);
        while (it != prev(end()) && it != prev(prev(end())) && get_x(next(it)) <= get_x(next(next(it)))){
            it = erase(next(it));
            it--;
        }
        if (it != prev(end())) {
            get_x(next(it));
        }
    }

    long long query(long long x){
        if (empty()){
            return 0;
        }
        Q = true;
        auto it = upper_bound(line(0, 0, (double)x));
        it--;
        Q = false;
        return x*it->m + it->c;
    }
};