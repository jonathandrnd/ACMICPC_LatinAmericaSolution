#include <iostream>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;
long long memo[5002][5002];

long long dp(int S, int B){
	if( S <= 0) return ( B == 0);
	if( B < 0 || S < 0) return 0; 
	if(memo[S][B] != -1)return memo[S][B];
	
	long long ans = 2*dp(S - 1, B) - dp(S - 2, B) + dp(S, B - S);
	ans = ans%1000000007;
	if(ans<0) ans += 1000000007;
	memo[S][B] = ans;
	return ans;
}

int main(){
   	memset(memo,-1,sizeof(memo));
	int S,B;
   	
   	while(cin>>S>>B){
   		cout<<dp(S,B-S)<<endl;
	}
   	
   	return 0;
}
