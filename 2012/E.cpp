#include <iostream>
#include <bitset>

using namespace std;
typedef long long ll;

ll ta, tb;

struct bits {
    ll a=0,b=0;
    
    void flip(int i) {
        if(i < 64) a ^= (1LL<<i);
        else b^= (1LL<<(i-64));
    }
    
    bool is_set(int i) {
        if(i < 64)  return a&(1LL<<i);
        return b&(1LL<<(i-64));
    }
    
    void init(string s) {
        for(int i = 0; i < s.size(); ++i) {
            if(s[i]=='1')
                flip(i);
        }
    }
    
    void bor(const bits& c) {
        a |= c.a;
        b |= c.b;
    }
    
    void reset() {
        a = b = 0;
    }
    
    bool ok() {
        return a==ta && b==tb;
    }
};

int n;
bits g[76];

bool used[76]={0};
int sofar[76];
bits b;
int best = 6;
int stored[76],stored_sz=6;

void go(int sz) {
    if(sz < 5) {
        for(int i = ((sz==0)?-1:sofar[sz-1])+1; i < n; ++i) {
            if(used[i]) continue;
            used[i] = true;
            sofar[sz] = i;
            go(sz+1);
            used[i] = false;
        }
    }

    b.reset();
    for(int i = 0; i < sz; ++i)
        b.bor(g[sofar[i]]);
    if(b.ok() && sz < best) {
        best = sz;
        for(int i = 0; i < sz; ++i)
            stored[i] = sofar[i];
        stored_sz = sz;
    }
}
void get6(int sz) {
    if(sz == 6) {
        stored_sz = 6;
        return;
    }
    int largest = -1;
    int lgsum = 0;
    for(int i = 0; i < n; ++i) {
        if(used[i]) continue;
        int sm = 0;
        for(int j = 0; j < n; ++j) {
            if(used[j]) continue;
            sm += g[i].is_set(j);
        }
        if(sm > lgsum) {
            largest = i;
            lgsum = sm;
        }
    }
    stored[sz] = largest;
    for(int i = 0; i < n; ++i) {
        if(g[largest].is_set(i))
            used[i] = 1;
    }
    get6(sz+1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T = 1;
    while(cin >> n) {
        if(n > 64) {
            ta = -1;
            tb = (1LL<<(n-64))-1;
        } else {
            ta = ((1LL<<(n))-1);
            tb = 0;
        }
        for(int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            s[i] = '1';
            g[i].reset();
            g[i].init(s);
        }
        best = 6;
        fill(used,used+n,0);
        fill(sofar,sofar+n,0);
        go(0);
        if(best == 6) {
            get6(0);
        }
        cout << "Case " << T++ << ": " << stored_sz;
        for(int i = 0; i < stored_sz; ++i)
            cout << " " << stored[i]+1;
        cout << "\n";
    }
    return 0;
}
