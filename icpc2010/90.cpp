#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef long double ld;

int s,p,d,h;

ld o2(ld d) {
	return 1/(d*d);
}

ll tri(ll a) {
	return (a+1)*a/2;
}

ld solve(ll a, ll b, ll c) {
	if(b < a) swap(a,b);
	if(c < a) swap(a,c);
	if(c < b) swap(b,c);
	ld n = sqrt(o2(c-a) - 1.0/((c-a)*(b-a)) + o2(b-a));
	ld m = -sqrt(o2(b-c) - 1.0/((b-c)*(a-c)) + o2(a-c));
	ll o = h*(tri(b/h) - tri((a-1)/h)) - (b/h - (a-1)/h)*a;
	ll q = h*(tri(c/h) - tri((b-1)/h)) - (c/h - (b-1)/h)*c;
	ld r=0;
	if(b!=a) r+=n*o;
	if(b != c) r+=m*q;
	if(a!=b&&c!=b &&b%h==0){
		r-=n*(b-a);
	} 
	
	//cout << a << "," << b << "," << c << " -> " << r << endl;
	return r;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T = 1;
	while(1) {
		cin >> s >> p >> d >> h;
		if(!s) return 0;
		ll x[s][p+1];
		for(int i = 0; i < s; ++i) {
			for(int j = 0; j < p+1; ++j) {
				if(i%2==0 && j==p) continue;
				cin >> x[i][j];
				//cout << i <<"," << j << " : " << x[i][j] << endl;
			}
		}
		ld total = 0;
		for(int i = 0; i < s-1; ++i) {
			for(int j = 0; j < p; ++j) {
				
				//cout << i << " " << j << endl;
				if(i%2==0 || (j > 0 && j < p)){
					if(i%2==0)
						total += solve(x[i][j],x[i+1][j],x[i+1][j+1]);
					else
						total += solve(x[i][j],x[i+1][j-1],x[i+1][j]);
				}
				if(i%2==1 || (j < p-1))
					if(i%2==0)
						total += solve(x[i][j],x[i][j+1],x[i+1][j+1]);
					else
						total += solve(x[i][j],x[i][j+1],x[i+1][j]);
			}
		}
		
		for(int i=0; i<s-1; i++){
			if(i%2 == 0 && x[i][0] == x[i+1][0] && x[i][0] == x[i+1][1] && x[i][0] % h == 0) total += 1;
			if(i%2 == 1 && x[i][0] == x[i+1][0] && x[i][0] == x[i][1] && x[i][0] % h == 0) total += 1;
			if(i%2 == 0){
				if(x[i][p-1] == x[i+1][p] && x[i][p-1] == x[i+1][p-1]&&  x[i][p-1] % h == 0) total += 1;
			} else {
				if(x[i][p] == x[i+1][p-1] && x[i][p-1] == x[i+1][p-1] &&x[i][p] % h == 0) total += 1;
			}
		}
		for(int j=0; j<p+1; j++){
			if(j!=p)
				if(x[0][j] == x[0][j+1] && x[1][j+1] == x[0][j+1]&& x[0][j] % h == 0) total += 1;
			if(s%2 == 1)
				if(x[s-1][j] == x[s-1][j+1] && x[s-2][j+1] == x[s-1][j+1] && x[s-1][j] % h == 0) total += 1;
			if(s%2 == 0 && j!=p)
				if(x[s-1][j] == x[s-1][j+1] && x[s-2][j] == x[s-1][j+1] && x[s-1][j] % h == 0) total += 1;
			
		}
		for(int i = 0; i < s-1; ++i) {
			for(int j = 0; j < p; ++j) {
				if(i%2==0 && j != p-1){
					if(x[i][j+1] == x[i+1][j+1] && (x[i][j]-x[i][j+1])*(x[i][j+1]-x[i+1][j+2])!=0) total -=1;
				}
				else if (j!=p-1 && i%2==1){
					if(x[i][j+1] == x[i+1][j] && (x[i][j]-x[i][j+1])*(x[i][j+1]-x[i+1][j+1])!=0) total -=1;
				}
				if(i%2==0 && i<s-2){
					if(x[i+1][j] == x[i+1][j+1] && (x[i][j]-x[i+1][j])*(x[i+1][j]-x[i+2][j])!=0) total -=1;
				}
				else if(i%2==1 && j!=0 && i < s-2){
					if(x[i+1][j-1] == x[i+1][j] && (x[i][j]-x[i+1][j-1])*(x[i+1][j-1]-x[i+2][j])!=0) total -=1;
				}
				if(i%2==0 && j != p-1){
					if(x[i][j] == x[i+1][j+1] && (x[i+1][j]-x[i][j])*(x[i][j]-x[i][j+1])!=0) total -=1;
				}
				else if (j!=0 && i%2==1){
					if(x[i][j] == x[i+1][j] && (x[i+1][j-1]-x[i][j])*(x[i][j]-x[i][j+1])!=0) total -=1;
				}

			}
		}
		
		
		cout << "Case " << T++ << ": " << round(total*d) << "\n";
	}
	
	return 0;
}
