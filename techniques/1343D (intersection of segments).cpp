// idea : prefix sum with the notice that when we work
//        with segment [l,r], we can take pref[l]++, pref[r+1]--

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        
        int a[n];
        for (int i = 0; i < n; i++) { 
            cin>>a[i];
        }
        
        map<int,int> cnt;
        for (int i = 0; i < n/2; ++i) {
            cnt[a[i] + a[n - i - 1]]++;
        }
        
        int pref[2*k+2] = {0};
        for (int i = 0; i < n/2; ++i) {
            int l1 = 1 + a[i], r1 = k + a[i];
            int l2 = 1 + a[n - i - 1], r2 = k + a[n - i - 1];
            pref[min(l1, l2)]++;
            pref[max(r1, r2) + 1]--;
        }
        for (int i = 1; i <= 2 * k + 1; ++i) {
            pref[i] += pref[i - 1];
        }
        int ans = 2*n;
        for (int sum = 2; sum <= 2*k; ++sum) {
            ans = min(ans, (pref[sum] - cnt[sum]) + (n / 2 - pref[sum]) * 2);
        }
        cout<<ans<<endl;
    }
    
    return 0;
}