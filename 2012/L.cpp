#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<ll> a[2];
vector<ll> b[2];

bool merge(vector<ll>& x) {
	if(x.size() > 1) {
		ll c = x.back();
		x.pop_back();
		x[x.size()-1] += c;
		return true;
	}
	return false;
}

bool take(vector<ll>& x, vector<ll>& y) {
	if(x.back() > y.back()) {
		y.pop_back();
		return true;
	}
	return false;
}

int winner(vector<ll>* a) {
	int i=1;
	while(a[i].size() && a[1-i].size()) {
		if(!take(a[i],a[1-i]) && !merge(a[i]))
			return 1-i;
		i = 1-i;
	}
	return 1-i;
}

int main() {
	ios::sync_with_stdio(0); cin.tie();
	int n,m;
	ll x;
	int T = 0;
	while(cin >> n >> m) {
		a[0].clear();
		a[1].clear();
		for(int i = 0; i < n; ++i) {
			cin >> x;
			a[0].push_back(x);
		}
		for(int i = 0; i < m; ++i) {
			cin >> x;
			a[1].push_back(x);
		}
		sort(a[0].begin(),a[0].end());
		sort(a[1].begin(),a[1].end());

		b[0] = a[0];
		b[1] = a[1];
		bool w = false;
		if(merge(a[0]))
			w |= winner(a) == 0;
		if(take(b[0],b[1]))
			w |= winner(b) == 0;


		cout << "Case " << ++T << ": ";
		if(w) cout << "Takeover Incorporated\n";
		else cout << "Buyout Limited\n";
	}
	return 0;
}