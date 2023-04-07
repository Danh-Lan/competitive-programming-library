// height of a collection of trees in O(N^2)
// loop for every vertex, and loop from the vertex to the top to get the height of each path 

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
	//cin>>t;
	for (int tt = 1; tt <= t; tt++) {
	    int n; cin >> n;

	    vector<int> parent(n+1);
	    for (int i = 0; i < n; i++) {
	        cin>>parent[i+1];
	    }
	 
	    int ans = 1;
	    for (int i = 1; i <= n; i++) {
	        int height = 1;
	        int j = parent[i];
	        while(j != -1) {
	           j = parent[j];
	           ++height;
	        }
	        ans = max(ans, height);
	    }
	    cout << ans;
		}

	return 0;
}