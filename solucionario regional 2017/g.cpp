#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<sstream>
#include<algorithm>
#include<set>
#include<queue>
#define MOD 1000000007LL
using namespace std;
int izq[100005];
int der[100005];
int op[100005];
long long memo[100005][2][2];

// how many ways to get correct value u in the gate node but the output is v
long long dp(int node,int u,int v){
	
	if(memo[node][u][v]!=-1)return memo[node][u][v];
	// 0 0 |1
	// 0 1 |1
	// 1 0 |1
	// 1 1 |0	
	long long a=(izq[node]==-1?1:dp(izq[node],0,0));
	long long b=(izq[node]==-1?0:dp(izq[node],0,1));
	long long c=(izq[node]==-1?0:dp(izq[node],1,0));
	long long d=(izq[node]==-1?1:dp(izq[node],1,1));
		
	long long e=(der[node]==-1?1:dp(der[node],0,0));
	long long f=(der[node]==-1?0:dp(der[node],0,1));
	long long g=(der[node]==-1?0:dp(der[node],1,0));
	long long h=(der[node]==-1?1:dp(der[node],1,1));
	
	long long dev=0;
	
	if(op[node]==-1){
		if(u==0 && v==0)dev=(d*h)%MOD;
		if(u==0 && v==1)dev=(c*h+d*g+c*g)%MOD;
		if(u==1 && v==0)dev=(b*f+b*h+d*f)%MOD;
		if(u==1 && v==1)dev= (a*e+a*f+a*g+a*h+b*e+b*g+c*e+c*f+d*e)%MOD;
	}
	
	if(op[node]==1){
		if(u==0 && v==1)dev=( (c+d)*(g+h))%MOD;
		if(u==1 && v==1)dev= (((  ((a+b+c+d)%MOD)*((e+f+g+h)%MOD) - (c+d)*(g+h)%MOD    ) %MOD)+MOD)%MOD;
	}
	
	if(op[node]==0){
		if(u==0 && v==0)dev=( (c+d)*(g+h))%MOD;
		if(u==1 && v==0)dev= (((  ((a+b+c+d)%MOD)*((e+f+g+h)%MOD) - (c+d)*(g+h)%MOD    ) %MOD)+MOD)%MOD;
	}
	
	memo[node][u][v]=dev;
	return dev;
}


int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	int n;
	
	while(cin>>n){
		memset(izq,-1,sizeof(izq));
		memset(der,-1,sizeof(der));
		
		for(int i=1;i<=n;i++){
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			op[i]=c;
			if(a==0)
				izq[i]=-1;
			else{
				izq[i]=a;
			}
			
			if(b==0)
				der[i]=-1;
			else {
				der[i]=b;
			}
		}	
		
		
		memset(memo,-1,sizeof(memo));
		cout<< (dp(1,0,1)+dp(1,1,0))%MOD<<endl;
	}
	
	return 0;
}
