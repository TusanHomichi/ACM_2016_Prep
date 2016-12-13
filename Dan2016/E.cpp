#include <iostream>

using namespace std;

typedef long long ll;

const ll INF=2e18;

ll eval(ll l, ll b) {
    if (l < 10) return l;
    ll x = eval(l/10,b);
    if (x > INF/b) return INF;
    return b*x+l%10;
}

ll check(ll n, ll l) {
    ll lo=0,hi=n+1;
    while (hi-lo > 1) {
        ll mid = (lo+hi)/2;
        if (eval(l,mid) > n)
            hi = mid;
        else
            lo = mid;
    }

    if (eval(l,lo) == n)
        return lo;
    return INF;
}

ll get_l(ll n, ll b) {
    if (n == 0) return 0;
    if (n%b <= 9) {
        ll x = get_l(n/b,b);
        if (x == INF) return INF;
        return 10*x+n%b;
    }
    return INF;
}

ll go(ll n, ll l)
{
    for (ll i=l; i<=999; i++)
        if (check(n,i) < INF)
            return check(n,i);

    //cout << n << ", " << l << endl;
    ll last_ok=10;
    for (ll base=10; base<=1000000; base++) {
        ll x = get_l(n,base);
        //if (x < INF) cout << "Testing " << base << " " << x << endl;
        if (x < 1000 || x < l) break;
        if (x < INF) last_ok=base;
    }
    
    return last_ok;
}

int main()
{
    ll n, l;
    while (cin >> n >> l)
        cout << go(n,l) << "\n";
}
