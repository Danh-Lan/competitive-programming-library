#include<bits/stdc++.h>
 
using namespace std;

int N = 1e3;
vector<int> prime;

void sieve() {
	vector<bool> vis(N+1, false);
	for (int i = 2; i <= N; ++i) {
		if (!vis[i]) {
			vis[i] = true;
			prime.push_back(i);
			for (int j = 2*i; j <= N; j += i) {
				vis[j] = true;
			}
		}
	}
}

queue<int> factor(int x) {
	queue<int> ans;
	for (int i = 0; i < prime.size(); ++i) {
		if (x % prime[i] == 0) ans.push(prime[i]);

		while (x % prime[i] == 0) {
			x /= prime[i];
		}

		if (prime[i] > x) break;
	}

	if (x > 1) ans.push(x);

	return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    sieve();

    int tt = 1; 
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
    	int n; cin >> n;
    	multiset<int> a;
    	for (int i = 0; i < n; ++i) {
    		int x; cin >> x;
    		a.insert(x);
    	}

    	map<int, multiset<int>> m;
    	for (int x : a) {
    		queue<int> q = factor(x);
    		while (!q.empty()) {
    			int top = q.front();
    			q.pop();
    			m[top].insert(x);
    		}
    	}

    	int query; cin >> query;
    	while (query--) {
    		int x; cin >> x;
    		queue<int> q = factor(x);
    		const int INF = 1e9;
    		int mn = INF;
    		while (!q.empty()) {
    			int top = q.front();
    			q.pop();
    			if (m.find(top) != m.end()) {
    				if (!m[top].empty()) mn = min(mn, *m[top].begin());
    			}
    		}

    		if (mn == INF) mn = *a.begin();
    		int val = mn;
			a.erase(a.find(val));

			queue<int> qq = factor(val);
			while (!qq.empty()) {
				int top = qq.front();
				qq.pop();
				if (m.find(top) != m.end()) {
					if (!m[top].empty()) m[top].erase(m[top].find(val));
				}

				if (m[top].empty()) {
					m.erase(top);
				}
			}

    		cout << val << ' ';
    	}

    	cout << '\n';
	}
 
    return 0;
}