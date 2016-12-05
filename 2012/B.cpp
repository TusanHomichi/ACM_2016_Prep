#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

#define PI 3.1415926535897
#define EPS 0.00001

double integ(const vector<double>& poly, double lo, double hi)
{
    double tot=0;
    for (int i=0; i<poly.size(); i++)
        tot += poly[i]*(pow(hi,i+1)-pow(lo,i+1))/(i+1);
   
    return tot;
}

double find_mark(const vector<double>& poly, double a, double b, double vol)
{
    double lo=a, hi=b;
    while (hi-lo > EPS)
    {
        double mid = (hi+lo)/2;
        if (PI*integ(poly,a,mid) < vol)
            lo = mid;
        else
            hi = mid;
    }

    return lo;
}

int main()
{
    int T=1,n;
    cout << setprecision(2) << fixed;
    while (cin >> n) {
        vector<double> poly;
        vector<double> psq = vector<double>(2*n+1,0);
        double d;
        for (int i=0; i<=n; i++)
        {
            cin >> d;
            poly.push_back(d);
        }

        for (int i=0; i<=n; i++)
            for (int j=0; j<=n; j++)
                psq[i+j] += poly[i]*poly[j];
        
        double lo,hi,inc;
        cin >> lo >> hi >> inc;

        cout << "Case " << T++ << ": " << PI*integ(psq,lo,hi) << "\n";
        if (PI*integ(psq,lo,hi) < inc)
        {
            cout << "insufficient volume\n";
        }
        else
        {
            for (int i=0; i<8; i++)
            {
                double m = find_mark(psq, lo, hi, (i+1)*inc);
                if (m+EPS > hi)
                    break;

                if (i > 0)
                    cout << " ";
                cout << m-lo;
            }
            cout << "\n";
        }
    }
}
