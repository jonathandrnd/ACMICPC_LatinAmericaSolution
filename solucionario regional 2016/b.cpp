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
set<int>adj[100001];

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	int n,m,a,b;
	
	while(cin>>n>>m>>a>>b){
		for(int i=0;i<n;i++)
			if(adj[i].size()>0)adj[i].clear();
		
		set<pair<int,int> >size; // first value= size  , second value= node
		
		for(int i=0;i<m;i++){
			int p,q;
			scanf("%d %d",&p,&q);
			p--;q--;
			adj[p].insert(q);
			adj[q].insert(p);
		}
		
		for(int i=0;i<n;i++)
			if(adj[i].size()>0)
			size.insert(make_pair(adj[i].size(),i));
		
		
		while(size.size()>0){
			pair<int,int>P=*size.begin();
			pair<int,int>Q=*(--size.end());
			
			int totnode=((int)size.size());	
			
			if(P.first>=a && totnode-Q.first-1>=b)break;
			
			if(P.first<a){
				int id=P.second;
				//set<int>eliminar=adj[id];
				set<int>::iterator it=adj[id].begin();
				int sizeId=adj[id].size();
				size.erase(make_pair(sizeId,id));
				
				while(it!=adj[id].end()){
					int node= *it;
					int sizenode=adj[node].size();
					
					size.erase(make_pair(sizenode,node));
					if(sizenode>1){
						size.insert(make_pair(sizenode-1,node));
					}
					
					// id to node					
					adj[node].erase(id);
					it++;
				}
				
				adj[id].clear();		
				continue;
			}
			
			
			if( totnode-Q.first-1<b && P!=Q){
				int id=Q.second;
				set<int>::iterator it=adj[id].begin();
				int sizeId=adj[id].size();
				size.erase(make_pair(sizeId,id));
				
				while(it!=adj[id].end()){
					int node= *it;
					int sizenode=adj[node].size();
					size.erase(make_pair(sizenode,node));
					if(sizenode>1){
						size.insert(make_pair(sizenode-1,node));
					}
					
					// id to node					
					adj[node].erase(id);
					it++;
				}
				
				adj[id].clear();				
			}
			
		}
		
		cout<<size.size()<<endl;
	}

    return 0;
}

