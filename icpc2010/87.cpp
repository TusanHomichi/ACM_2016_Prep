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
typedef pair<ll,ll> pll;

int n,m,w;
vector<int> x1,x2,y;
set<int> ix,iy;

int grid[5000][5000];
map<int,int> cx,cy;
ll wx[5000],wy[5000];


int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T = 1;
	while(1) {
		cin >> n >> m >> w;
		if(n==0) return 0;
		x1.clear();
		x2.clear();
		y.clear();
		ix.clear();
		iy.clear();
		
		ix.insert(0);
		ix.insert(n);
		iy.insert(0);
		iy.insert(m);
		cx.clear();
		cy.clear();
		for(int i = 0; i < w; ++i) {
			int a,b,c,d;
			cin >> a >> b >> c >> d;
			x1.push_back(a);
			x2.push_back(c);
			y.push_back(b);
			
			ix.insert(a);
			ix.insert(c+1);
			
			iy.insert(b);
			iy.insert(b+1);
		}
		int ctr=0;
		for(auto a : ix) {
			cx[a] = ctr;
			wx[ctr++] = a;
		}
		ctr=0;
		for(auto a : iy) {
			cy[a] = ctr;
			wy[ctr++] = a;
		}

		
		for(int i=0; i < ix.size(); ++i)
			for(int j = 0; j < iy.size(); ++j)
				grid[i][j]=0;
		for(int i = 0; i < w; ++i) {
			int ed = cx[x2[i]+1];
			int ny = cy[y[i]];
			for(int j = cx[x1[i]]; j < ed; ++j)
				grid[j][ny] = 1;
		}
		int R = ix.size()-1;
		int C = iy.size()-1;
		
		for(int i = R-1; i >= 0; --i) {
			for(int j = C-1; j >= 0; --j) {
				if(grid[i][j] == 1) continue;
				if(i==R-1 && j==C-1) {
					grid[i][j] = 2;
				}
				if(i!=R-1) {
					if(grid[i+1][j] == 2)
						grid[i][j] = 2;
				}
				if(j!= C-1) {
					if(grid[i][j+1]==2)
						grid[i][j] = 2;
				}
			}
		}
		
		ll ans = 0;
		for(int i = 0; i < R; ++i) {
			for(int j = 0; j < C; ++j) {
				if(grid[i][j] != 0) continue;
				ans += (wx[i+1]-wx[i])*(wy[j+1]-wy[j]);
			}
		}
		cout << "Case " << T++ << ": " << ans << "\n";
	}

	return 0;
}
