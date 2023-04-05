#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    const int INF = 101010;

    int t = 1;
    //cin>>t;
    for (int tt = 0; tt < t; ++tt)
    {
    	int n, m; cin>>n>>m;
    	vector<int> dp(20001, INF); // 2 times max bound
    	dp[n] = 0;
    	queue<int> q;
    	q.push(n);

    	while (!q.empty()) {
			int top = q.front();
			q.pop();
			if (top * 2 <= 2*m) {
				if (dp[top]+1 < dp[top*2]) {
					dp[top*2] = dp[top]+1;
					q.push(top*2);
				}
			}
			if (top - 1 > 0) {
				if (dp[top]+1 < dp[top-1]) {
					dp[top-1] = dp[top]+1;
					q.push(top-1);
				}
			}
    	}

    	cout<<dp[m]<<endl;
    }
    
    return 0;
}