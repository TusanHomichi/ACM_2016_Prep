#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

int n;
int d[151];
int wide[151];
int enc[151];
int T;

int weight(int x)
{
	if (x == 1)
		return 0;
	else if (x == 17)
		return 1;
	else if (x == 9)
		return 2;
	else if (x == 24)
		return 3;
	else if (x == 5)
		return 4;
	else if (x == 20)
		return 5;
	else if (x == 12)
		return 6;
	else if (x == 3)
		return 7;
	else if (x == 18)
		return 8;
	else if (x == 16)
		return 9;
	else if (x == 4)
		return 10;
	return -1;
}

void go()
{
	if (n%6 != 5) {
		cout << "Case " << T++ << ": bad code\n";
		return;
	}

	//Get code, using d[0] as threshold
	for (int i=0; i<n; i++)
	{
		double off = 1.0*d[i]/d[0];
		if (off >= 0.95/1.05 && off <= 1.05/0.95)
			wide[i] = false;
		else if (off >= 0.95*2/1.05 && off <= 1.05*2/0.95)
			wide[i] = true;
		else {
			cout << "Case " << T++ << ": bad code\n";
			return;
		}
	}

	double minw=200, maxw=1, minn=200, maxn=1;
	for (int i=0; i<n; i++)
	{
		if (wide[i]) {
			maxw = max(maxw,1.0*d[i]);
			minw = min(minw,1.0*d[i]);
		} else {
			maxn = max(maxn,1.0*d[i]);
			minn = min(minn,1.0*d[i]);
		}
	}

	if (maxn/1.05 > minn/0.95 || maxw/2/1.05 > minw/2/0.95 || minn/0.95 < maxw/2/1.05 || minw/2/0.95 < maxn/1.05) {
		cout << "Case " << T++ << ": bad code\n";
		return;
	}

	//cout << "Bars found" << endl;

	for (int i=0; i+4<n; i += 6)
	{
		enc[i/6] = 16*wide[i] + 8*wide[i+1] + 4*wide[i+2] + 2*wide[i+3] + wide[i+4];
		if (i+5 < n && wide[i+5] != 0) {
			cout << "Case " << T++ << ": bad code\n";
			return;
		}
	}

	//cout << "Chars found" << endl;

	string s = ""; int c=0; int k=0; int ct=(n+1)/6;

	if (enc[0] == 12 && enc[ct-1] == 12)
	{
		for (int i=0; i<ct; i++) {
			int x = 6*(ct-1-i);
			enc[i] = wide[x] + 2*wide[x+1] + 4*wide[x+2] + 8*wide[x+3] + 16*wide[x+4];
		}
	}

	//for (int i=0; i<ct; i++)
		//cout << enc[i] << " ";
	//cout << endl;

	if (enc[0] != 6 || enc[ct-1] != 6) {
		cout << "Case " << T++ << ": bad code\n";
		return;
	}

	//cout << "Start and stop ok" << endl;

	for (int i=1; i<ct-3; i++)
	{
		if (enc[i] == 1) {
			s += "0";
			c += ((ct-4-i)%10 + 1)*0;
			k += ((ct-3-i)%9 + 1)*0;
		}
		else if (enc[i] == 17) {
			s += "1";
			c += ((ct-4-i)%10 + 1)*1;
			k += ((ct-3-i)%9 + 1)*1;
		}
		else if (enc[i] == 9) {
			s += "2";
			c += ((ct-4-i)%10 + 1)*2;
			k += ((ct-3-i)%9 + 1)*2;
		}
		else if (enc[i] == 24) {
			s += "3";
			c += ((ct-4-i)%10 + 1)*3;
			k += ((ct-3-i)%9 + 1)*3;
		}
		else if (enc[i] == 5) {
			s += "4";
			c += ((ct-4-i)%10 + 1)*4;
			k += ((ct-3-i)%9 + 1)*4;
		}
		else if (enc[i] == 20) {
			s += "5";
			c += ((ct-4-i)%10 + 1)*5;
			k += ((ct-3-i)%9 + 1)*5;
		}
		else if (enc[i] == 12) {
			s += "6";
			c += ((ct-4-i)%10 + 1)*6;
			k += ((ct-3-i)%9 + 1)*6;
		}
		else if (enc[i] == 3) {
			s += "7";
			c += ((ct-4-i)%10 + 1)*7;
			k += ((ct-3-i)%9 + 1)*7;
		}
		else if (enc[i] == 18) {
			s += "8";
			c += ((ct-4-i)%10 + 1)*8;
			k += ((ct-3-i)%9 + 1)*8;
		}
		else if (enc[i] == 16) {
			s += "9";
			c += ((ct-4-i)%10 + 1)*9;
			k += ((ct-3-i)%9 + 1)*9;
		}
		else if (enc[i] == 4) {
			s += "-";
			c += ((ct-4-i)%10 + 1)*10;
			k += ((ct-3-i)%9 + 1)*10;
		}
		else {
			cout << "Case " << T++ << ": bad code\n";
			return;
		}

		//cout << c << " " << k << endl;
	}
	
	c = c%11;
	k = (k+c)%11;

	//cout << s << " " << c << " " << k << endl;

	if (weight(enc[ct-3]) != c) {
		cout << "Case " << T++ << ": bad C\n";
		return;
	}
	if (weight(enc[ct-2]) != k) {
		cout << "Case " << T++ << ": bad K\n";
		return;
	}
	cout << "Case " << T++ << ": " << s << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	T = 1;
	cin >> n;
	while (n != 0) {
		for (int i=0; i<n; i++)
			cin >> d[i];

		go();
		cin >> n;
	}

	return 0;
}
