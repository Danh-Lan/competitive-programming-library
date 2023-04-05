#include <bits/stdc++.h>

using namespace std;

struct node {
    int a, b, c;
};

// only max query of type [0; k]
struct MaxFenwick {
    int n;
    vector<int> Fen;
    MaxFenwick(int n): N(n), Fen(n+1, -1) { }

    void update (int i, int val) {
        while (i <= n) {
            Fen[i] = max(Fen[i], val);
            i += i & -i;
        }
    }

    int query (int i) {
        int ans = 0;
        while (i > 0) {
            ans = max(ans, Fen[i]);
            i -= i & -i;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    int tt = 1; 
    //cin>>tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin>>n;
        node stats[n];
        vector<int> bVal(n);
        for (int i = 0; i < n; ++i) {
            cin>>stats[i].a;
        }
        for (int i = 0; i < n; ++i) {
            cin>>stats[i].b;
            bVal[i] = stats[i].b;
        }
        for (int i = 0; i < n; ++i) {
            cin>>stats[i].c;
        }

        // reverse the comparative value order of b
        sort(bVal.begin(), bVal.end());
        bVal.resize(unique(bVal.begin(), bVal.end()) - bVal.begin());
        int val = bVal.size();
        map<int,int> reduce;
        for (int x : bVal) {
            reduce[x] = val;
            val--;
        }
        for (int i = 0; i < n; ++i) {
            stats[i].b = reduce[stats[i].b];
        }

        sort(stats, stats+n, [&] (node n1, node n2) {
            return (n1.a > n2.a);
        });

        int ans = 0;
        MaxFenwick Fen(n);
        for (int i = 0; i < n;) {
            // iterate through each block of equal value of a
            int j;
            for (j = i; j < n; ++j) {
                if (stats[j].a != stats[i].a) break;
                if (stats[j].c < Fen.query(stats[j].b-1)) ++ans;
            }

            while (i < j) {
                Fen.update(stats[i].b, stats[i].c);
                ++i;
            }
        }

        cout<<ans<<"\n";
    }

    return 0;
}