void fwht(vector<ll> &a) {
    ll n = a.size();

    ll x, y;
    for (ll len = 2; len <= n; len <<= 1) {
        for (ll i = 0; i < n; i += len) {
            for (ll j = i; j < i + (len>>1); j++) {
                x = a[j], y = a[j+(len>>1)];
                a[j] = (x + y)%mod;
                a[j+(len>>1)] = (x - y)%mod;
            }
        }
    }
}