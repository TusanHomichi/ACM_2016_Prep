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

bool dp[40000][101];
int people[16];

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n;
	cin >> n;
	while (n != 0)
	{
		cin >> x >> y;
		for (int i=0; i<n; i++)
			cin >> people[i];
		
		cin >> n;
	}

	return 0;
}
