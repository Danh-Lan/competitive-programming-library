#include<bits/stdc++.h>
 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
 
    int tt = 1; 
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin >> n;
        bool repeat = false;
        vector<bool> vis(n, false);
        int b[n/2];
        map<int,int> pos;
        for (int i = 0; i < n/2; ++i) {
            int x; cin >> x;
            --x;
            b[i] = x;
            if (vis[x]) repeat = true;
            pos[x] = i;
            vis[x] = true;
        }

        if (repeat) {
            cout << -1 << '\n';
            continue;
        }

        bool possible = true;
        set<int> rest;
        set<int> s;
        int cntVis = 0, cntRest = 0;
        
        for (int i = 0; i < n; ++i) {
            if (vis[i]) {
                cntVis++;
            } else {
                cntRest++;
                rest.insert(i);
            }

            if (cntVis > cntRest) {
                possible = false;
            }
        }

        if (!possible) {
            cout << -1 << '\n';
        } else {
            vector<int> ans(n, -1);

            for (int i = n/2 - 1; i >= 0; --i) {
                int x = *prev(rest.lower_bound(b[i]));
                rest.erase(x);
                ans[2*i] = x;
                ans[2*i+1] = b[i];
            }

            for (int i = 0; i < n; ++i) {
                cout << ans[i]+1 << ' ';
            } cout << '\n';
        }
    }
 
    return 0;
}