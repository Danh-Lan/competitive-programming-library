#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    int t = 1;
    cin>>t;
    for (int tt = 0; tt < t; ++tt)
    {
        const int BOUND = 2e5;
        int n; cin>>n;
        set<int> s;
        int cnt[BOUND+1] = {0};
        for (int i = 0; i < n; ++i)
        {
            int num; cin>>num;
            cnt[num]++;
            s.insert(num);
        }

        int dp[BOUND+1] = {0};
        for (int it : s) { 
            dp[it] += cnt[it];
            for (int i = 2*it; i <= BOUND; i += it)
            {
                dp[i] = max(dp[i], dp[it]);
            }
        }

        /* N sqrt(N)
        for (int it : s) { 
            for (int i = 1; i <= sqrt(it); ++i)
            {
                if (it % i == 0) {
                    dp[it] = max(dp[it], dp[i]);
                    dp[it] = max(dp[it], dp[it/i]);
                }
            }
            dp[it] += cnt[it];
        }
        */

        int mx = 0;
        for (auto it : s) {
            mx = max(mx, dp[it]); 
        }
        cout<<n-mx<<endl;

    }

    return 0;
}