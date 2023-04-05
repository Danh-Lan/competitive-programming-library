// DSU : if 2 node are already connected, we have a spare to connect 
// 2 differents connect components

#include <bits/stdc++.h>
 
using namespace std;

const int N = 1001;

vector<int> par(N);
vector<int> rnk(N, 1);
int spare = 0;

int find(int i) {
    return (par[i] == i ? i : (par[i] = find(par[i])));
}

void merge(int i, int j) {
    int x = find(i), y = find(j);
    if (x == y) {
        ++spare;
    } else {
        par[x] = y;
        rnk[y] += rnk[x];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
 
    int test = 1;
    //cin>>test;
    for (int tt = 0; tt < test; ++tt)
    {
        int n, d; cin>>n>>d;
        iota(par.begin(), par.end(), 0);

        for (int i = 0; i < d; ++i)
        {
            int x, y; cin>>x>>y;
            merge(x, y);
            
            priority_queue<int> pq;
            for (int j = 1; j <= n; ++j)
            {
                if (find(j) == j) pq.push(rnk[j]);
            }
            
            int ans = 0;
            for (int j = 0; j <= spare; ++j)
            {
                auto xx = pq.top();
                pq.pop();
                ans += xx;
            }
            
            cout<<ans-1<<endl;
        }
    }

    return 0;
}
