#include <iostream>
#include <vector>
#include <string>
#include <queue>
//#include <bitset>

using namespace std;

typedef vector<vector<int> > graph;
typedef pair<int,int> pii;

const int MAX_STATES = 9*9*4+5;

graph g;
string name;
int sr,sc,sd,gr,gc;
//Directions are NESW

int dir(char d)
{
    if (d == 'N')
        return 0;
    else if (d == 'E')
        return 1;
    else if (d == 'S')
        return 2;
    else if (d == 'W')
        return 3;
    else if (d == 'F')
        return 0;
    else if (d == 'L')
        return -1;
    else if (d == 'R')
        return 1;
}

vector<pii> solution;
bool seen[MAX_STATES];
int par[MAX_STATES];
queue<int> q;
int bfs(int start)
{
    q = queue<int>();
    q.push(start);
    seen[start] = true;
    par[start] = -1;
    
    while (q.size() > 0)
    {
        int cur = q.front();
        q.pop();
        
        if (cur/9/4 == gr && (cur/4)%9 == gc)
            return cur;
        
        for (auto x : g[cur])
        {
            if (!seen[x])
            {
                q.push(x);
                par[x] = cur;
                seen[x] = true;
            }
        }
    }
    
    return -1;
}

int main()
{
    while (1)
    {
        cin >> name;
        if (name == "END")
            return 0;
            
        char d;
        cin >> sr >> sc >> d >> gr >> gc;
        sr--; sc--; gr--; gc--;
        sd = dir(d);

        g = graph(MAX_STATES, vector<int>());
        if (sd == 0)
            g[9*4*sr + 4*sc + sd].push_back(9*4*(sr-1) + 4*sc + sd);
        else if (sd == 1)
            g[9*4*sr + 4*sc + sd].push_back(9*4*sr + 4*(sc+1) + sd);
        else if (sd == 2)
            g[9*4*sr + 4*sc + sd].push_back(9*4*(sr+1) + 4*sc + sd);
        else if (sd == 3)
            g[9*4*sr + 4*sc + sd].push_back(9*4*sr + 4*(sc-1) + sd);
        
        int r,c;
        cin >> r;
        while (r != 0)
        {
            cin >> c;
            r--; c--;
            
            string s;
            cin >> s;
            while (s != "*")
            {
                int cur_d = dir(s[0]);
                for (int i=1; i < s.size(); i++)
                {   
                    int new_d = (cur_d + dir(s[i]) + 4)%4;
                    if (new_d == 0)
                        g[9*4*r+4*c+cur_d].push_back(9*4*(r-1) + 4*c + new_d);
                    if (new_d == 1)
                        g[9*4*r+4*c+cur_d].push_back(9*4*r + 4*(c+1) + new_d);
                    if (new_d == 2)
                        g[9*4*r+4*c+cur_d].push_back(9*4*(r+1) + 4*c + new_d);
                    if (new_d == 3)
                        g[9*4*r+4*c+cur_d].push_back(9*4*r + 4*(c-1) + new_d);
                }
                
                cin >> s;
            }
            
            cin >> r;
        }
        
        for (int i=0; i<MAX_STATES; i++)
            seen[i] = false;
            
        int end;
        if ((end=bfs(9*4*sr+4*sc+sd)) >= 0)
        {
            cout << name;

            solution.clear();
            while (end != -1)
            {
                solution.push_back(pii(end/9/4, (end/4)%9));
                end = par[end];
            }
            
            for (int i = 0; i < solution.size(); i++)
            {
                if (i%10 == 0)
                    cout << endl << " ";
                cout << " (" << solution[solution.size()-i-1].first+1 << "," << solution[solution.size()-i-1].second+1 << ")";
            }
            cout << endl;
        }
        else
        {
            cout << name << endl << "  No Solution Possible" << endl;
        }
    }
    //cout << bitset<10>(939823) << "\n";
}
