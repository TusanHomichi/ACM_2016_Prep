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

#define x first
#define y second

double dp[105][105];
int last[105][105];
const double INF = 1e50;
int n,b1,b2;
pii p[105];

double mag(double a, double b) {
	return sqrt(a*a+b*b);
}

double dist(int i, int j) {
	return mag(p[i].x-p[j].x,p[i].y-p[j].y);
}

void solve() {
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			if(i==b2) dp[i][j] = INF;
			else if(j==b1) dp[i][j] = INF;
			else if(i==0 && j==0) dp[i][j] = 0;
			else if(i==j) dp[i][j] = INF;
			else  if(i==0 && j==1) {
				last[i][j] = 0;
				dp[i][j] = dist(0,1);
			} else if(i==1 && j == 0) {
				last[i][j] = 0;
				dp[i][j] = dist(0,1);
			} else if(j > i+1) {
				last[i][j] = j-1;
				dp[i][j] = dp[i][j-1] + dist(j-1,j);
			} else if(i > j+1) {
				last[i][j] = i-1;
				dp[i][j] = dp[i-1][j] + dist(i-1,i);
			} else if(i > j) {
				//i=j+1
				dp[i][j] = INF;
				for(int k = 0; k < j; ++k) {
					double d = dp[k][j]+dist(k,i);
					if(d < dp[i][j]) {
						last[i][j] = k;
						dp[i][j] = d;
					}
				}
			} else {
				//j=i+1
				dp[i][j] = INF;
				for(int k = 0; k < i; ++k) {
					double d = dp[i][k]+dist(k,j);
					if(d < dp[i][j]) {
						last[i][j] = k;
						dp[i][j] = d;
					}
				}
			}
		}
	}
}

vector<int> path1,path2;

void trace(int i, int j) {
	if(i==0 && j==0) {

	} else if(i > j) {
		path1.push_back(last[i][j]);
		trace(last[i][j],j);
	} else {
		path2.push_back(last[i][j]);
		trace(i,last[i][j]);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T = 1;
	cout << setprecision(2) << fixed;
	while(1) {
		cin >> n >> b1 >> b2;
		if(n==0)
			return 0;
		for(int i = 0; i < n; ++i)
			cin >> p[i].x >> p[i].y;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				dp[i][j] = -1;
		double best = INF;
		int q = 0;
		solve();
		for(int i = 0; i < n; ++i) {
			double d = dp[i][n-1]+dist(i,n-1);
			if(d < best) {
				best = d;
				q = i;
			}
		}
		path1.clear();
		path2.clear();
		path2.push_back(n-1);
		path1.push_back(n-1);
		path1.push_back(q);
		trace(q,n-1);
		cout << "Case " << T++ << ": " << best << "\n";
		if(path1[path1.size()-2] == 1) {
			for(int i = path1.size()-1; i > 0; --i)
				cout << path1[i] << " ";
			for(int i = 0; i < path2.size(); ++i)
				cout << path2[i] << ((path2.size()-1==i)?"\n":" ");
		} else {
			for(int i = path2.size()-1; i > 0; --i)
				cout << path2[i] << " ";
			for(int i = 0; i < path1.size(); ++i)
				cout << path1[i] << ((path1.size()-1==i)?"\n":" ");
		}
		
	}
	return 0;
}
