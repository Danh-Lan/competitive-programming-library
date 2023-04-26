#include<bits/stdc++.h>
 
using namespace std;

// the optimal solution is 1 2 4 8 16 ...
// we can generalize into a sort array,
// if a[i] > pref[i-1]+1 then pref[i-1]+1 is the answer
void solve() {
    int n;
    cin >> n;

    long long a[n+1];
    long long ans = 0LL;
    long long cur = 0LL;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    const long long INF = 1e17;
    a[n] = INF;
    sort(a, a+n);

    for (int i = 0; i <= n; ++i) {
        if (a[i] > cur + 1) {
            ans = cur+1;
            break;
        }

        cur += a[i];
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
 
    int tt = 1; 
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        solve();
    }
 
    return 0;
}
