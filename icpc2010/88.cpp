#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <iomanip>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef pair<int,pii> ppi;

int n;
pii node[102];
vvi gr;

pii dfs(int x, int p)
{
	vector<ppi> children = vector<ppi>();
	for (auto u : gr[x]) {
		if (u == p) continue;
		pii du = dfs(u,x);
		children.push_back(ppi(du.second-du.first,du));
	}
	sort(children.begin(),children.end());
	int a,b=0;
	for (auto u : children)
		b += u.second.second;

	a = b;
	for (auto u : children) {
		a = max(u.second.first,a);
		a -= u.second.second;
	}
	
	a += b;
	return pii(max(node[x].first,node[x].second+a),b+node[x].second);
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int T=1;
	cin >> n;
	while (n != 0) {
		int a,m,g;
		for (int i=1; i<=n; i++) {
			cin >> a >> m >> g;
			node[i] = pii(max(a,m+g), m+g);
		}

		gr = vvi(n+1, vi());
		int u,v;
		for (int i=0; i<n-1; i++) {
			cin >> u >> v;
			gr[u].push_back(v);
			gr[v].push_back(u);
		}

		int needed = 1000000;
		for (int i=1; i<=n; i++) {
			needed = min(needed,dfs(i,-1).first);
		}
		cout << "Case " << T++ << ": " << needed << endl;
		cin >> n;
	}

	return 0;
}
