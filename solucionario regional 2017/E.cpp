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
string s;
int k;
int memo[1001][1001];

bool ispossible(int pos,int mod){
	if(pos==s.size())return (mod==0);
	if(memo[pos][mod]!=-1)return memo[pos][mod];
	int dev=0;
	
	if(s[pos]=='?'){
		for(int i=0;i<10;i++){
			if(pos==0 && i==0)continue;
			dev=dev|ispossible(pos+1,(mod*10+i)%k); 
		}
	}else{
		dev=dev|ispossible(pos+1,(mod*10+(s[pos]-'0'))%k);
	}
	
	memo[pos][mod]=dev;
	return dev;
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	while(cin>>s>>k){
		memset(memo,-1,sizeof(memo));
			
		if(!ispossible(0,0)){
			cout<<"*"<<endl;
		}else{
			string dev="";
			int mod=0;
			
			for(int i=0;i<s.size();i++){
				if(s[i]=='?'){
					for(int j=0;j<10;j++){
						if(i==0 && j==0)continue;
						if(ispossible(i+1, (mod*10+j)%k )){
							mod=(mod*10+j)%k;
							dev+='0'+j;
							break;
						}
					}
				}else{
					dev+=s[i];
					mod=(mod*10+(s[i]-'0') )%k;
				}	
			}
				
			cout<<dev<<endl;
		}
		
	}
	
	return 0;
}
