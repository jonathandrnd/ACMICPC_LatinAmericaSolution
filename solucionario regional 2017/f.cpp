#include<iostream>
#include<cstring>
#include<map>
#include<cstdio>
#include<vector>
#include<cmath>
#include<sstream>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;
struct node{
	long long b,f,d;
	node(long long _b,long long _f,long long _d){
		b=_b;
		f=_f;
		d=_d;
	}
	node(){}
};

bool operator<(node a,node b){
	if(a.b!=b.b)return a.b<b.b;
	if(a.f!=b.f)return a.f>b.f;
	return a.d>b.d;
}

vector<node>v;


long long tree[100009];
long long MaxVal=100005;
long long read(int idx){
    if(idx==0)return 0;
	long long sum = 0;
	while (idx > 0){
		sum = max(sum,tree[idx]);
		idx -= (idx & -idx);
	}
	return sum;
}

void update(int idx ,long long val){
	while (idx <= MaxVal){
		tree[idx] = max(tree[idx],val);
		idx += (idx & -idx);
	}
}

int main(){
	
	int n;
	
	while(cin>>n){
		v.clear();
		
		map<pair<int,int>,long long>ac;
		
		for(int i=0;i<n;i++){
			int b,f,d;
			scanf("%d %d %d",&b,&f,&d);
			ac[make_pair(b,f)]+=d;
		}
		
		for(map<pair<int,int>,long long>::iterator it=ac.begin(); it!=ac.end(); ++it){
			pair<int,int>P=it->first;
			long long Q=it->second;
			v.push_back(node(P.first,P.second,Q));	
		}
		
		sort(v.begin(),v.end());
		n=v.size();		
		//coordinate compression f
		set<long long>S;
		for(int i=0;i<v.size();i++)S.insert(v[i].f);
		map<long long,long long>m;
		int cont=1;
		for(set<long long>::iterator it=S.begin(); it!=S.end(); ++it)m[*it]=cont++;
		
		for(int i=0;i<n;i++)v[i].f=m[v[i].f];
		
		memset(tree,0,sizeof(tree));
		long long last=v[0].b;
		long long maxi=0;
		
		
		//O(nlogn)
		for(int i=0;i<v.size();){
			while(i<v.size()){
				if(v[i].b!=last)break;
				
				long long value=read(v[i].f-1);
				long long ac=read(v[i].f);
				
				update(v[i].f,max(value+v[i].d,ac ));
				maxi=max(maxi,max(value+v[i].d, ac));	
				i++;
			}
			
			if(i==v.size())break;
			last=v[i].b;
		}
		
		cout<<maxi<<endl;
	}
		
			
	return 0;
}


