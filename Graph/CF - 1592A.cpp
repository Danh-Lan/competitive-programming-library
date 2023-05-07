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
	for (int tt = 1; tt <= t; tt++) {
		int n; cin>>n;
		int num[n];

		// need book i to understand book j --> (i,j)
		vector<vector<int>> graph (n+1, vector<int>());
		vector<int> deg(n+1); // inner degree

		for (int i = 0; i < n; ++i)
		{
			cin>>num[i];
			deg[i+1] = num[i];
			for (int j = 0; j < num[i]; ++j)
			{
				int c; cin>>c;
				graph[c].push_back(i+1);
			}
		}

		vector<int> days (n+1, 0);
		priority_queue <int, vector<int>, greater<int>> pq;
		for (int i = 1; i <= n; ++i)
		{
			if (deg[i] == 0) {
				pq.push(i);
				days[i] = 1;
			}
		}

		while (!pq.empty()) {
			int top = pq.top();
			pq.pop();
			for (int i = 0; i < graph[top].size(); ++i)
			{
				int vertex = graph[top][i];
				--deg[vertex];
				if (deg[vertex] <= 0) {
					pq.push(vertex);
					if (top < vertex) {
						days[vertex] = days[top];
					} else {
						days[vertex] = days[top]+1;
					}
				}
			}
		}

		int ans = 0;
		for (int i = 1; i <= n; ++i)
		{
			if (days[i] == 0) {
				ans = -1;
				break;
			} else {
				ans = max(ans, days[i]);
			}
		}
		cout<<ans<<endl;
	}

	return 0;
}