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

#define EPS 0.0000001
#define REAL_BIG 10000

struct pt {
	double x;
	double y;
	double z;

	public:
	pt():x(0),y(0),z(0) {};
	pt(double x, double y, double z):x(x),y(y),z(z) { };
	pt operator+(pt b) {
		return pt(x+b.x,y+b.y,z+b.z);
	}
	pt operator-(pt b) {
		return pt(x-b.x,y-b.y,z-b.z);
	}

	pt operator/(double sc) {
		return pt(x/sc,y/sc,z/sc);
	}

	pt operator*(double sc) {
		return pt(x*sc,y*sc,z*sc);
	}
};

double mag(pt a)
{
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

pt xprod(pt a, pt b)
{
	return pt(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}

double vol_pip(pt a, pt b, pt c)
{
	return a.x*b.y*c.z + a.y*b.z*c.x + a.z*b.x*c.y - a.z*b.y*c.x - a.y*b.x*c.z - a.x*b.z*c.y;
}

int side(pt a, pt b, pt test)
{
	pt zach = xprod(b-a, test-a);
	if (abs(zach.x) > EPS)
		return (zach.x > 0)?1:-1;
	if (abs(zach.y) > EPS)
		return (zach.y > 0)?1:-1;
	if (abs(zach.z) > EPS)
		return (zach.z > 0)?1:-1;
	return 0;
}

int side_plane(pt a, pt b, pt c, pt test)
{
	double v = vol_pip(test-a,b-a,c-a);
	if (v > EPS)
		return 1;
	if (v < -EPS)
		return -1;
	return 0;
}

bool in_tri(pt a, pt b, pt c, pt test)
{
	return (side(a,b,c) == side(a,b,test) && side(a,c,b) == side(a,c,test) && side(b,c,a) == side(b,c,test));
}

double dist_pt_line(pt a, pt b, pt test)
{
	return mag(xprod(test-a,b-a))/mag(b-a);
}

double dist_pt_plane(pt a, pt b, pt c, pt test)
{
	return abs(vol_pip(test-a,b-a,c-a)/mag(xprod(b-a,c-a)));
}

pt unit_norm(pt a, pt b, pt c)
{
	pt zach = xprod(b-a,c-a);
	return zach/mag(zach);
}

bool coplanar(pt a, pt b, pt c, pt d)
{
	return (abs(vol_pip(b-a,c-a,d-a)) <= EPS);
}

pt proj_plane(pt a, pt b, pt c, pt test)
{
	pt q = unit_norm(a,b,c)*dist_pt_plane(a,b,c,test);
	if (coplanar(a,b,c,test+q))
		return test+q;
	if (coplanar(a,b,c,test-q))
		return test-q;
	cout << "WAAH" << endl;
	return pt();
}

pt Q,F;

double solve(pt A, pt B, pt C) {
	pt P = proj_plane(A,B,C,Q);
	cout << dist_pt_plane(A,B,C,F) << endl;
	if (!in_tri(A,B,C,P)) return -1;
	if (dist_pt_line(A,B,P) < 0.2+EPS || dist_pt_line(A,C,P) < 0.2+EPS || dist_pt_line(B,C,P) < 0.2+EPS) return -2;
	return dist_pt_plane(A,B,C,F);
}

double solve4(pt a, pt b, pt c, pt d) {
	if (dist_pt_line(a,b,Q) < 0.2+EPS || dist_pt_line(b,c,Q) < 0.2+EPS || dist_pt_line(c,d,Q) < 0.2+EPS || dist_pt_line(d,a,Q) < 0.2+EPS) return -1;
	return dist_pt_plane(a,b,c,F);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout << setprecision(5) << fixed;

	int T=1;
	pt A,B,C,D,E;
	while (cin >> A.x >> A.y >> A.z >> B.x >> B.y >> B.z >> C.x >> C.y >> C.z >> D.x >> D.y >> D.z >> E.x >> E.y >> E.z >> F.x >> F.y >> F.z) {
		double v1=abs(vol_pip(A-E,B-E,C-E))/6, v2=abs(vol_pip(A-D,B-D,C-D))/6;
		pt l1=(A+B+C+E)/4, l2=(A+B+C+D)/4;
		Q = (l1*v1 + l2*v2)/(v1+v2);

		double a=solve(A,B,D),b=solve(A,C,D),c=solve(B,C,D);
		double d=solve(A,B,E),e=solve(A,C,E),f=solve(B,C,E);

		cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << endl;

		if (side_plane(D,A,C,E) != side_plane(D,A,C,B)) {
			b = -1;
			e = -1;
		}
		if (side_plane(D,A,B,E) != side_plane(D,A,B,C)) {
			a = -1;
			d = -1;
		}
		if (side_plane(D,B,C,E) != side_plane(D,B,C,A)) {
			c = -1;
			f = -1;
		}

		cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << endl;

		if (coplanar(A,B,D,E))
			a = solve4(A,B,D,E);
		if (coplanar(A,C,D,E))
			b = solve4(A,C,D,E);
		if (coplanar(B,C,D,E))
			c = solve4(B,C,D,E);

		cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << endl;

		double mx = max(max(max(a,b),c),max(max(d,e),f));
		double mi=REAL_BIG;
		if (a < mi && a > 0) mi = a;
		if (b < mi && b > 0) mi = b;
		if (c < mi && c > 0) mi = c;
		if (d < mi && d > 0) mi = d;
		if (e < mi && e > 0) mi = e;
		if (f < mi && f > 0) mi = f;

		cout << "Case " << T++ << ": " << mi << " " << mx << endl;
	}

	return 0;
}
