// https://codeforces.com/contest/1154/problem/G

/* 
Linear sieve that compute the lowest prime factor of each number from
1 to 10^7. minPos store for each i 2 minimum number in the array 
that is divisible by i

We don't need to calculate the exact lcm in the end
Suppose number i has (a,b), gcd(a,b) = d --> d <= i, so a*b/i >= a*b/d
Since we loop from 1 to 10^7, we already calculate for d before reaching i
d either has (a,b) or some number smaller than (a,b), in which case the
lcm would be smaller than a*b/d

We need memoization to optimize the runtime
*/
#include<bits/stdc++.h>
 
using namespace std;

const int N = 1e7;
vector<int> lp(N+1); // lowest prime factor
vector<int> pr;

void linearSieve() {
    for (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < pr.size() && i * pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    } 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout); 
    #endif

    linearSieve();

    int tt = 1;
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n;
        cin >> n;

        int a[n];
        vector<pair<int,int>> minPos(N+1, {-1, -1});
        map<int, vector<int>> factor;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        for (int i = 0; i < n; ++i) {
            vector<int> fact = {1};
            if (factor.count(a[i])) {
                fact = factor[a[i]];
            } else {
                int cur = a[i];
                while (cur > 1) {
                    int curP = lp[cur];
                    int val = lp[cur];
                    vector<int> pow = {1};
                    while (curP == lp[cur]) {
                        pow.push_back(val);
                        val *= lp[cur];
                        cur /= lp[cur];
                    }

                    vector<int> newFact;
                    for (int f : fact) {
                        for (int p : pow) {
                            newFact.push_back(f*p);
                        }
                    }

                    fact = newFact;
                }

                factor[a[i]] = fact;
            }
            
            for (int f : fact) {
                int first = minPos[f].first, second = minPos[f].second;
                if (first == -1) {
                    minPos[f].first = i;
                } else if (second == -1) {
                    minPos[f].second = i;
                } else {
                    if (a[i] > a[first] && a[i] > a[second]) continue;
                    else {
                        if (a[first] <= a[second]) minPos[f].second = i;
                        else minPos[f].first = i;
                    }
                }
            }
        }

        long long mn = 1e15;
        pair<int,int> ans = {-1, -1};
        for (int i = 1; i <= N; ++i) {
            if (minPos[i].first != -1 && minPos[i].second != -1) {
                long long lcm = 1LL*a[minPos[i].first] / i * a[minPos[i].second];
                // not actually lcm but doesn't matter
                if (lcm < mn) {
                    mn = lcm;
                    ans = minPos[i];
                }
            }
        }

        if (ans.first > ans.second) swap(ans.first, ans.second);

        cout << ans.first + 1 << ' ' << ans.second + 1 << '\n';
    }

    return 0;
}