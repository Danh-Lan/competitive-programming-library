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
    //cin>>tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin>>n;
        int a[n+1];
        for (int i = 1; i <= n; ++i) {
            cin>>a[i];
        }

        vector<int> dp(n+1, INT_MIN);
        map<int,int> m;
        int mx = 0;
        int mxVal = 0;
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            if (m.find(a[i]-1) != m.end()) {
                dp[i] = max(dp[i], dp[m[a[i]-1]] + 1);
            } else {
                dp[i] = 1;
            }

            m[a[i]] = i;
            if (dp[i] > mx) {
                mx = dp[i];
                mxVal = a[i];
            }
        }

        cout<<mx<<"\n";
        int cur = mxVal - mx + 1;
        for (int i = 1; i <= n; ++i) {
            if (cur > mxVal) break;
            if (a[i] == cur) {
                cout<<i<<" ";
                cur++;
            }
        } cout<<"\n";
    }

    return 0;
}