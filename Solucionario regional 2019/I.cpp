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
vector<int>v[2004];
int N, L;
set<int> uniq;
bool visited[2004];
int memo[2004];

void dfs(int list){
	visited[list] = 1;
	
	for(int i = 0;i <v[list].size();i++){
		int id = v[list][i];
		//its a list
		if( id <= L){
			if(!visited[id])
				dfs(id);		
		}else{
			//its a client
			uniq.insert(id);
		}
	}
	
}

int dp(int list){
	
	if(memo[list] != -1)return memo[list];
	int ans = 0;
	
	for(int i = 0;i < v[list].size(); i++){
		int id = v[list][i];
		
		if( id <= L){
			ans = (ans + dp(id) )%1000000007;
		}else{
			ans = (ans +1 )%1000000007;
		}		
	}
	
	memo[list] = ans;
	return ans;
}

int main() {
	
	while( scanf("%d %d",&N,&L) == 2){
		for(int i = 0; i <= N;i++)if(v[i].size() > 0)v[i].clear();
		
		for(int i = 0;i < L; i++){
			int k; scanf("%d",&k);
			for(int j = 0; j < k ;j++ ){
				int aux; scanf("%d",&aux);
				v[i + 1].push_back(aux);
			}
		}	
		
		uniq.clear();
		memset(visited,0,sizeof(visited));
		dfs(1);
		
		memset(memo,-1,sizeof(memo));
		cout<<dp(1)<<" "<<uniq.size()<<endl;
	}
	
		
	return 0;
}
