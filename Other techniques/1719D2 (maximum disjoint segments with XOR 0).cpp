#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int tt = 1; 
    cin>>tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin>>n;
        int a[n];
        for (int i = 0; i < n; ++i) {
            cin>>a[i];
        }
        
        int ans = 0;
        set<int> s;
        s.insert(0);
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            int nxt = (cur ^ a[i]);
            if (s.find(nxt) != s.end()) {
                ++ans;
                s.clear();
                s.insert(0);
                cur = 0;
            } else {
                s.insert(nxt);
                cur = nxt;
            }
        }

        cout<<n-ans<<endl;
    }

    return 0;
}