#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef pair<int,int> pii;

int n;
vector<int> stacks[51];
vector<int> all;

int prv[2501], both[2501];
int ct[2501], pairs[2501], bottom[2501];

int main()
{
    int T=1;
    while (cin >> n)
    {
        int sz;
        all.clear();
        for (int i=0; i<n; i++)
        {
            cin >> sz;
            stacks[i].clear();
            for (int j=0; j<sz; j++)
            {
                int x;
                cin >> x;
                stacks[i].push_back(x);
                all.push_back(x);
            }
        }
        
        sort(all.begin(),all.end());
        
        map<int,int> m;
        int ctr=0;
        for (int i=0; i<all.size(); i++)
        {
            if (i && all[i] != all[i-1])
                ctr++;
            m[all[i]] = ctr;
        }
        
        for (int i=0; i<n; i++)
            for (int j=0; j<stacks[i].size(); j++)
                stacks[i][j] = m[stacks[i][j]];
                
        for (int i=0; i<=2500; i++)
        {
            prv[i] = both[i] = 0;
            ct[i] = pairs[i] = bottom[i] = 0;
        }
                
        for (int i=0; i<n; i++)
            for (int j=0; j<stacks[i].size()-1; j++)
                if (stacks[i][j] == stacks[i][j+1]-1)
                    prv[stacks[i][j+1]]++;
                    
        for (int i=0; i<n; i++)
        {
            int last = stacks[i][0];
            int last_ind = 0;
            for (int j=1; j<stacks[i].size()-1; j++)
            {
                if (stacks[i][j-1] != stacks[i][j])
                {
                    last = stacks[i][j-1];
                    last_ind = j-1;
                }
                
                if (last == stacks[i][j]-1 && stacks[i][j]+1 == stacks[i][j+1] &&
                    prv[stacks[i][j]] == 1 && prv[stacks[i][j]+1] == 1)
                    both[stacks[i][j]] = j-last_ind;
            }
        }
                    
        for (int i=0; i<n; i++)
            for (int j=0; j<stacks[i].size(); j++)
                ct[stacks[i][j]]++;
                
        for (int i=0; i<n; i++)
            for (int j=0; j<stacks[i].size()-1; j++)
                if (stacks[i][j] == stacks[i][j+1])
                    pairs[stacks[i][j]]++;
                    
        for (int i=0; i<n; i++)
            bottom[stacks[i].back()]++;
            
        int res = all.size() - n;
        for (int i=0; i<=2500; i++) {
            res -= pairs[i];
            if (prv[i])
                res--;
            if (ct[i] != both[i] && both[i])
                res++;
        }
        
        /*cout << " " << all.size() << " " << n << endl;
        for (int i=0; i<=ctr; i++)
            cout << prv[i] << " " << both[i] << " " << ct[i] << " " << pairs[i] << " " << bottom[i] << endl;*/
        
        res = 2*res + n-1;
        
        cout << "Case " << T++ << ": " << res << endl;
    }        
}
