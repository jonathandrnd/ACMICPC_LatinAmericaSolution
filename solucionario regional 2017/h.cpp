#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<sstream>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int ca,ba,pa;
	int cr,br,pr;
	
	while(cin>>ca>>ba>>pa>>cr>>br>>pr){
		cout<<max(cr-ca,0)+max(br-ba,0)+max(pr-pa,0)<<endl;
	}
	
	return 0;
}


