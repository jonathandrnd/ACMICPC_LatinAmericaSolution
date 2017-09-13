#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<sstream>
#include<algorithm>
#include<set>
#include<cassert>
#include<queue>
#include<map>
using namespace std;

int source, sink;
int N=105;
int residual[105][105];

int find_path(){
	bool visited[N];
	memset(visited, 0, sizeof(visited));
	
	int from[N];
	memset(from, -1, sizeof(from));
	
	queue <int> Q;
	Q.push(source);
	visited[source] = 1;
	
	int where;
	
	while(!Q.empty()){
		where = Q.front();
		Q.pop();
		
		if(where==sink) break;
		
		for(int i=0; i<N; i++){
			if(residual[where][i] > 0 && !visited[i]){
				Q.push(i);
				visited[i] = 1;
				from[i] = where;
			}
		}
	}
	
	int path_cap = 1<<30;
	where = sink;
	while(from[where] > -1){
		int prev = from[where];
		path_cap = min(path_cap, residual[prev][where]);
		where = prev;
	}
	
	where = sink;
	while(from[where] > -1){
		int prev = from[where];
		residual[prev][where] -= path_cap;
		residual[where][prev] += path_cap;
		where = prev;
	}
	
	if(path_cap == 1<<30) return 0;
	else return path_cap;
}

int max_flow(){
	int flow = 0;
	while(1){
		int path_cap = find_path();
		if(!path_cap) break;
		else flow += path_cap;
	}
	return flow;
}


int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	int n;
	
	while(scanf("%d",&n)==1){
		int a[n],b[n];
		
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
			scanf("%d",&b[i]);
			a[i]--;b[i]--;
		}
		
		int ans=0;
		for(int i=0;i<n;i++){
			memset(residual,0,sizeof(residual));
        	source=0;
        	sink=101;
			
			bool visited[n];
			memset(visited,0,sizeof(visited));
			visited[i]=1;
			
			int kill=0; // villagers  always choose the werewolf
			for(int j=0;j<n;j++){
				if(a[j]==i || b[j]==i){
					visited[j]=1;
					kill++;
				}
			}
			
			if(kill<=1){
				ans++;
				continue;
			}
			
			for(int j=0;j<n;j++){
				residual[source][j+1]=kill-1;
				if(a[i]==j || b[i]==j)
					residual[source][j+1]=kill-2;
			}
			
			int notvisited=0;
			
			for(int j=0;j<n;j++){
				if(!visited[j]){
					residual[a[j]+1][n+j+1]=1;
					residual[b[j]+1][n+j+1]=1;
					residual[n+j+1][sink]=1;
					notvisited++;
				}
			}
			
			//cout<<"maxflow "<<i<<" "<<notvisited<<" "<<max_flow()<<endl;
			if(max_flow()!=notvisited){
				ans++;
			}
		}
		
		cout<<ans<<endl;
	}
	
	
    return 0;
}

