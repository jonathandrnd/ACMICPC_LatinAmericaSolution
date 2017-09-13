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
using namespace std;
//http://codeforces.com/blog/entry/8219
int n,b,c;
long long h[6003];
long long dp[6003][2];
long long F[6003];
long long C[6003];
long long G[6003][6003];

void compute(int k,int L,int R,int optL,int optR){
	if(L>R)return ;
	int mid= (L+R)/2;
	dp[mid][k&1]=1LL<<62;
	int best=-1;
	int fin=min(optR,mid-1);
	
	for(int j=optL;j<= fin;j++){
		if(mid==n){
			long long val=dp[j][(k-1)&1]+G[j+1][n];
			if(dp[mid][k&1]> val){
				dp[mid][k&1]=val;
				best=j;
			}	
		}else{
			long long val=dp[j][(k-1)&1]+G[j+1][mid-1];
			if(dp[mid][k&1]> val){
				dp[mid][k&1]=val;
				best=j;
			}
		}			
	}

	compute(k,L,mid-1,optL,best);
	compute(k,mid+1,R,best,optR);
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);

	// Solucion en O(n^2*logn)
	while(scanf("%d %d %d",&n,&b,&c)==3){
		//cout<<n<<" "<<b<<" "<<c<<endl;
		F[0]=0;
		C[0]=0;
		
		memset(G,0,sizeof(G));
		
		
		for(int i=0;i<n;i++){
			int aux;
			scanf("%d",&aux);
			h[i]=aux;
			F[i+1]=F[i]+aux;
			C[i+1]=C[i]+(long long)aux*i;
		}
		
		for(int i=n-1;i>=0;i--){
			G[i][i]=h[i];
			for(int j=i+1;j<n;j++){
				G[i][j]=F[j+1]-F[i]+G[i+1][j-1];
			}
		}
			
		memset(dp,0,sizeof(dp));
		
		for(int i=0;i<n;i++)
			dp[i][0]=i*F[i]-C[i];
		
		for(int i=n-1;i>=0;i--)
			G[i][n]= (F[n]-F[i])+G[i+1][n];

	
		for(int k=1;k<=n;k++){
			compute(k, 0, n, k-1,n-1 );
			long long mini=dp[n][k&1]*c+(long long)k*b;
			
			cout<<mini;
			if(k!=n)cout<<" ";
		}
		
		cout<<endl;
	}

    return 0;
}

