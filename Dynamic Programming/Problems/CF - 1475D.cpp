#include<bits/stdc++.h>
using namespace std;
typedef long long ll;



int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll  a;
	cin >> a;
	for (ll i = 0; i < a; i++) {
		ll b, c;
		cin >> b >> c;
		vector<ll> x, y;
		ll sum = 0;
		ll num = 0;
		for (ll j = 0; j < b; j++) {
			ll k;
			cin >> k;
			x.push_back(k);
			sum += k;
		}
		for (ll j = 0; j < b; j++) {
			ll k;
			cin >> k;
			y.push_back(k);
			num += k;
		}
		if (sum < c) {
			cout << -1 << "\n";
			continue;
		}
		vector<ll> o, t;
		for (ll j = 0; j < b; j++) {
			if (y[j] == 1) {
				o.push_back(x[j]);
			}
			else {
				t.push_back(x[j]);
			}
		}
		sort(o.begin(), o.end(), greater<ll>());
		sort(t.begin(), t.end(), greater<ll>());
		pair<ll, pair<ll, ll>> dp[num + 3];
		if (o.size() != 0) {
			dp[1] = {o[0], {1, 0}};
		}
		else {
			dp[1] = { -1, {0, 0}};
		}
		if (t.size() != 0) {
			dp[0] = {0, {0, 0}};
		}
		else {
			dp[0] = { -1, {0, 0}};
		}
		for (ll i = 2; i <= num + 2; i++) {
			pair<ll, pair<ll, ll> > p = dp[i - 1], q = dp[i - 2];
			if (p.second.first != o.size()) {
				dp[i] = {p.first + o[p.second.first], {p.second.first + 1, p.second.second}};
			}
			if (q.second.second != t.size()) {
				if (dp[i].first < q.first + t[q.second.second]) {
					// cout << q.second.second << " " << q.first << " s\n";
					dp[i] = {q.first + t[q.second.second] , {q.second.first, q.second.second + 1}};
				}
			}
			// cout << i << " " << dp[i].first << " " << dp[i].second.first << " " << dp[i].second.second << "\n";

		}
		ll  ans = 0;
		for (ll i = 1; i <= num + 2; i++) {
			// cout << i << " " << dp[i].first << " " << dp[i].second.first << " " << dp[i].second.second << "\n";
			if (dp[i].first >= c) {
				ans = i;
				break;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}