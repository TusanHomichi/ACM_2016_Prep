#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool compare(vector<int> a, vector<int> b)
{
    if (a.size() != b.size()) return false;
    if (a.size() == 0) return true;

    vector<int> al, bl, ah, bh;
    for (int i=1; i < a.size(); i++)
    {
        if (a[i] < a[0])
            al.push_back(a[i]);
        else
            ah.push_back(a[i]);

        if (b[i] < b[0])
            bl.push_back(b[i]);
        else
            bh.push_back(b[i]);
    }

    return compare(al,bl) && compare(ah,bh);
}

vector<int> shapes[50];

int main()
{
    int n,k;
    while (cin >> n >> k) {
        int ct=0;
        for (int i=0; i<n; i++)
        {
            shapes[i] = vector<int>();
            int x;
            for (int j=0; j<k; j++)
            {
                cin >> x;
                shapes[i].push_back(x);
            }

            ct++;
            for (int j=0; j<i; j++)
            {
                if (compare(shapes[i],shapes[j])) {
                    ct--;
                    break;
                }
            }
        }

        cout << ct << endl;
    }
}
