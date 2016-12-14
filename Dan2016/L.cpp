#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

int n;
vpii pos, neg;
pii sz[1000000];

int main() {
    
    while (cin >> n) {
        for (int i=0; i<n; i++)
            cin >> sz[i].first >> sz[i].second;

        pos.clear();
        neg.clear();
        for (int i=0; i<n; i++)
            if (sz[i].first <= sz[i].second)
                pos.push_back(pii(sz[i].first,i));
            else
                neg.push_back(pii(-sz[i].second,i));

        sort(pos.begin(),pos.end());
        sort(neg.begin(),neg.end());

        ll extra=0,cur_extra=0;
        for (int i=0; i<pos.size(); i++) {
            pii cur = sz[pos[i].second];
            if (cur_extra < cur.first) {
                extra += cur.first-cur_extra;
                cur_extra = cur.first;
            }

            cur_extra += cur.second-cur.first;
        }

        for (int i=0; i<neg.size(); i++) {
            pii cur = sz[neg[i].second];
            if (cur_extra < cur.first) {
                extra += cur.first-cur_extra;
                cur_extra = cur.first;
            }
           
            cur_extra += cur.second-cur.first;
        }

        cout << extra << endl;
    }
}
