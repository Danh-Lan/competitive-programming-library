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
    	int n, m, k; cin >> n >> m >> k;
    	k++;
    	long long a[n][m];
    	vector<vector<long long>> pref(n, vector<long long>(m, 0LL));
    	long long total = 0LL;
    	for (int i = 0; i < n; ++i) {
    		for (int j = 0; j < m; ++j) {
    			cin >> a[i][j];
    			total += a[i][j];
    		}
    	}

    	if (total < k) {
    		cout << -1 << endl;
    		continue;
    	}

    	pref[0][0] = a[0][0];
    	for (int i = 1; i < n; ++i) {
    		pref[i][0] = pref[i-1][0] + a[i][0];
    	}
    	for (int j = 1; j < m; ++j) {
    		pref[0][j] = pref[0][j-1] + a[0][j];
    	}

    	for (int i = 1; i < n; ++i) {
    		for (int j = 1; j < m; ++j) {
    			pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1] + a[i][j];
    		}
    	}

    	int ans = 1e9;
    	for (int i = 0; i < n; ++i) {
    		for (int j = 0; j < m; ++j) {
    			if (a[i][j] == 0) continue;

    			int l = 0, r  = max(n,m);
    			while (l < r) {
    				int d = (l+r)/2;
    				pair<int,int> TL = {max(i-d, 0), max(j-d, 0)};
    				pair<int,int> BR = {min(i+d, n-1), min(j+d, m-1)};
    				long long sum = 0LL;
    				if (TL.first == 0 && TL.second == 0) {
    					sum = pref[BR.first][BR.second];
    				} else if (TL.first == 0) {
    					sum = pref[BR.first][BR.second] - pref[BR.first][TL.second-1];
    				} else if (TL.second == 0) {
    					sum = pref[BR.first][BR.second] - pref[TL.first-1][BR.second];
    				} else {
    					sum = pref[BR.first][BR.second] - pref[TL.first-1][BR.second] - pref[BR.first][TL.second-1] + pref[TL.first-1][TL.second-1];
    				}

    				if (sum >= k) {
						ans = min(ans, d);
						r = d;
					} else {
						l = d+1;
					}
    			}
    		}
    	}

    	cout << ans << endl;
	}
 
    return 0;
}