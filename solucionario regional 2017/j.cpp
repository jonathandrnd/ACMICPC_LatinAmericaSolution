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
int gcd[100005];

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	string s;
	
	while(cin>>s){
		int r=0,p=0;
		for(int i=0;i<s.size();i++)
			if(s[i]=='R'){
				r++;
			}else{
				p++;
			}
		
		if(p==0){
			cout<<s.size()-1<<endl;
			continue;
		}
		
		int n=s.size();
		vector<int>v;
		
		//O(sqrt(n), divisor of n
		for(int i=2;i*i<=n;i++){
			if(n%i==0){
				if(i*i==n){
					v.push_back(i);
					break;	
				}
				
				v.push_back(i);
				v.push_back(n/i);
			}
		}
		
		memset(gcd,0,sizeof(gcd));
		for(int i=2;i<n;i++)
			gcd[__gcd(i,n)]++;
		
		int count=0;
		
		for(int i=0;i<v.size();i++){
			//choose start [0-v[i]] 
			
			//O(n)
			bool yeah=0;
			for(int j=0;j<v[i];j++){
				bool ok=1;
				for(int k=j;k<n;k+=v[i]){
					if(s[k]=='P'){
						ok=0;
						break;
					}
				}
				
				if(ok){
					yeah=1;
					break;
				}
			}	
			
			if(yeah){
				count+=gcd[v[i]];
			}
		}
		
		cout<<count<<endl;
	}
	
	return 0;
}


