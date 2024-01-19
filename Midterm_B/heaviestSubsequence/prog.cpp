#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
 void printVector(vector<int>& v)
 {
	for (int i=0; i<v.size(); i++)
	{
		cout << v[i]<<" ";
	}
	cout <<"\n";	
 }

int compute(vector<int>& seq, int n) {
    if (n == 0) return 0;
    if (n == 1) return seq[0];

    vector<int> dp(n, 0);
    dp[0] = seq[0];
    dp[1] = max(seq[0], seq[1]);

    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + seq[i]);
    }

    return dp[n - 1];
}

int main()
{
	vector<int> seq;	
	int z,n;
	cin >> z;
	while(z)
	{
		seq.clear();		
		cin >> n;
		for(int i=0; i<n; i++)
		{
			int x;
			cin >> x;
			seq.push_back(x);
		}
		int sol = compute(seq, n);
		cout << sol <<"\n";
		z--;
	}
	return 1;
}