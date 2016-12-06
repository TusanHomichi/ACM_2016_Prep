#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

string p;
int n;

string f[101];
ll m[101];

int tab[100005];
void build_tab()
{
    tab[0] = -1;
    tab[1] = 0;
    int i=2,j=0;
    while (i <= p.size())
    {
        if (p[i-1] == p[j]) {
            tab[i] = j+1;
            i++; j++;
        }
        else if (j > 0) j = tab[j];
        else {
            tab[i] = 0;
            i++;
        }
    }
}

//Count occurrences
int kmp(string s)
{
    int ret=0;
    int m=0,i=0;
    while (m+i < s.size())
    {
        if (p[i] == s[m+i])
        {
            i++;
            if (i == p.size()) {
                ret++;
                m += i - tab[i];
                i = tab[i];
            }
        }
        else
        {
            m += i-tab[i];
            if (i > 0) i = tab[i];
        }
    }
    
    return ret;
}

int main()
{
    int T=1;
    while (cin >> n >> p) {
        build_tab();
        
        f[0] = "0";
        f[1] = "1";
        f[2] = f[1] + f[0];
        f[3] = f[2] + f[1];
        
        m[0] = kmp(f[0]);
        m[1] = kmp(f[1]);
        m[2] = kmp(f[2]);
        m[3] = kmp(f[3]);
        
        int i=4;
        while (i <= n && f[i-4].size() < p.size())
        {
            f[i] = f[i-1] + f[i-2];
            m[i] = kmp(f[i]);
            i++;
        }
        
        while (i <= n)
        {
            m[i] = m[i-1] + 2*m[i-2] - m[i-3] - m[i-4];
            i++;
        }
        
        cout << "Case " << T++ << ": " << m[n] << endl;
    }
}
