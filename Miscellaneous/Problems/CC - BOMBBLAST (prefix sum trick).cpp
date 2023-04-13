/*
We separate the problem into 2 sub problem of calculate only the positive value from the right to left, 
and negative value from the left to right. 
For each bomb, we only memorize the extreme left and right side

Let's for example consider only the positive value after affected by the bomb. 
When we move from index i to i-1, each value decrease their value by 1. 
Since the sum of ( k*(k+1) - (k-1)k) is 2sum(k), if we can keep track the current sum, the problem is done. 
The problem is that some of the value can decrease to 0 and we have to remove them from the sum, 
so we have to consider the amount of value still being positive. 
To calculate this, we use the classic trick : 
  For each segment [pos, r] add 1 to r and add (-1) to pos, then calculate the suffix sum (or prefix sum for negative value)
*/

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
    	int n, m; 
    	cin >> n >> m;

    	vector<long long> ansPos(n, 0LL), ansNeg(n, 0LL);
    	vector<long long> sumPos(n, 0LL), sumNeg(n, 0LL); 
    	vector<int> cntPos(n, 0), cntNeg(n, 0);

    	for (int i = 0; i < m; ++i) {
    		int pos, range;
    		cin >> pos >> range;
    		--pos;
    		int l = max(0, pos-range);
    		int r = min(n-1, pos+range);
    		int distL = pos - l;
    		int distR = r - pos;

    		if (distL > 0) {
    			cntNeg[l]++;
    			cntNeg[pos]--;
    			ansNeg[l] += 1LL*distL*(distL+1);
    			sumNeg[l] += distL;
    		}

    		if (distR > 0) {
				cntPos[r]++; 
	    		cntPos[pos]--;
	    		ansPos[r] += 1LL*distR*(distR+1);
	    		sumPos[r] += distR;
    		}
    	}

    	for (int i = 1; i < n; ++i) {
    		ansNeg[i] += (ansNeg[i-1] - 2*sumNeg[i-1]);
    		cntNeg[i] += cntNeg[i-1];
    		sumNeg[i] += sumNeg[i-1] - cntNeg[i-1];
    	}

    	for (int i = n-2; i >= 0; --i) {
    		ansPos[i] += (ansPos[i+1] - 2*sumPos[i+1]);
			cntPos[i] += cntPos[i+1];
			sumPos[i] += sumPos[i+1] - cntPos[i+1];
    	}
    	
    	for (int i = 0; i < n; ++i) {
    		cout << (ansPos[i] - ansNeg[i]) << ' ';
    	} cout << '\n';
	}
 
    return 0;
}