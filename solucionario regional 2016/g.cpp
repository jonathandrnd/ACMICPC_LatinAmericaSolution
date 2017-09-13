#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define f(i,x,y) for(int i = x; i < y; ++ i)
typedef long long ll;

int KMP(const vector<int>& S, const vector<int>& K)
{
	int ans = 0;
	int n = S.size(), m = K.size();
	vector<int> T(m + 1);

	int j = T[0] = -1;
	f(i, 0, m)
	{
		while( ~j && K[i] != K[j] && (K[j] || K[i] <= j) ) j = T[j];
		T[i + 1] = ++ j;
	}

	j = 0;
	f(i, 0, n)
	{
		while( ~j && S[i] != K[j] && (K[j] || S[i] <= j) ) j = T[j];
		++ j;
		if( j == m ) ++ ans, j = T[j];
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	string w; cin >> w;
	int n = w.size();
	vector<int> s(n);

	vector<int> last(26, -1);
	f(i, 0, n)
	{
		char c = w[i] - 'a';
		s[i] = last[c] == -1? 0 : i - last[c];
		last[c] = i;
	}

	last.assign(26, -1);

	int m; cin >> m;
	vector<int> k(m);
	f(i, 0, m)
	{
		int x; cin >> x; -- x;
		k[i] = last[x] == -1? 0 : i - last[x];
		last[x] = i;
	}
	cout << KMP(s, k) << endl;
}

