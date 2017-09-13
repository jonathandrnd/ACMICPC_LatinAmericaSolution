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

bool isprime(int n){
	
	for(int i=2;i*i<=n;i++)
		if(n%i==0)return 0;
	return 1;
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	int n;
	while(cin>>n){
		if(n==2){
			cout<<n<<endl;
			continue;
		}
		
		if(n%2==0)n--;
		
		while(!isprime(n)){
			n-=2;
		}
		
		cout<<n<<endl;
	}
	
    return 0;
}

