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

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	int k,n;
	
	while(cin>>k>>n){
		vector<int>f(k+1,0);
		
		for(int i=0;i<n;i++){
			int aux;
			scanf("%d",&aux);
			f[aux]++;
		}
		
		if(n%k==(k-1)){
			int num=0;
			for(int i=1;i<=k;i++)
				if( (n)/k==f[i])
					num=i;
			f[num]++;
			bool ok=1;
			for(int i=2;i<=k;i++)
				if(f[i]!=f[i-1])ok=0;
				
			if(ok)
				cout<<"+"<<num<<endl;
			else
				cout<<"*"<<endl;
		}else if(n%k==1){
			int num=0;
			for(int i=1;i<=k;i++)
				if( (n/k)+1==f[i]){
					num=i;
				}
			
			f[num]--;
			bool ok=1;
			for(int i=2;i<=k;i++)
				if(f[i]!=f[i-1])ok=0;
				
			if(ok)
				cout<<"-"<<num<<endl;
			else
				cout<<"*"<<endl;
			
		}else if(n%k==0){
			
			int num1=0;int num2=0;
			for(int i=1;i<=k;i++){
				if( (n/k)+1==f[i]){
					num1=i;
				}
				
				if( (n/k)-1==f[i]){
					num2=i;
				}
				
			}
			
			f[num1]--;f[num2]++;
			bool ok=1;
			for(int i=2;i<=k;i++)
				if(f[i]!=f[i-1])ok=0;
				
			if(ok)
				cout<<"-"<<num1<<" +"<<num2<<endl;
			else
				cout<<"*"<<endl;
			
			
		}else{
			cout<<"*"<<endl;
		}
		
	}
	
	
	return 0;
}
