#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<numeric>
#include<cmath>
#include<sstream>
#include<algorithm>
#include<set>
#include<queue>
#include<map>
#define MOD 1000000007
using namespace std;
int C[1001][1001];

void combinatoria(int n){
	C[0][0]=1;
	for(int i=1;i<=n;i++){
		C[i][0]=1;
		C[i][i]=1;
		for(int j=1;j<i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;	
		}
	}
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	long long x[1001],y[1001];
	int n;
	combinatoria(1000);
	
	while(scanf("%d",&n)==1){
		map<pair<long long,long long>,int >m;
		set<pair<long long,long long> >S;
	
		int a,b;
		for(int i=0;i<n;i++){
			scanf("%d %d",&a,&b);
			x[i]=2*a;
			y[i]=2*b;
			S.insert(make_pair(x[i],y[i]));
		}	
		
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++){
				pair<long long,long long>P= make_pair( (x[i]+x[j])/2, (y[i]+y[j])/2);
				m[P]++;
			}
		
		map< pair<long long,long long>,int>::iterator it=m.begin();
		long long ans[n+1];
		memset(ans,0,sizeof(ans));
		
		while(it!=m.end()){
			pair<long long,long long>P=it->first;
			int freq=it->second;
			
			bool ok=0;
			if(S.find(P)!=S.end())ok=1;
			
			if(freq>=1){
				for(int i=1;i<=freq;i++){
					ans[2*i]=(ans[2*i]+ C[freq][i] )%MOD;
					if(ok)
						ans[2*i+1]= (ans[2*i+1]+C[freq][i])%MOD;
				}
			}
							
			it++;
		}		
		
		ans[1]=n;
		ans[2]=(n*(n-1))/2;
		
		cout<<ans[1];
		for(int i=2;i<=n;i++)
			cout<<" "<<ans[i];
		cout<<endl;
	}
	
	
    return 0;
}
