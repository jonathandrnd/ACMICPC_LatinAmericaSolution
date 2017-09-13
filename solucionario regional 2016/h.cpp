#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<numeric>
#include<cmath>
#include<sstream>
#include<algorithm>
#include<set>
using namespace std;
int p[100005];
int n,k;


int main(){
	
	while(scanf("%d %d",&n,&k)==2){
		int sum=0;
		for(int i=0;i<n;i++){
			scanf("%d",&p[i]);
			sum+=p[i];
		}
		
		multiset<int>S;
		
		for(int i=0;i<n;i++){
			S.insert(p[i]);
			int tam=(i+1)/(k+1);
			
			while(S.size()>tam){
				S.erase(S.begin());
			}
		}
		
		vector<int>join(S.begin(),S.end());
		cout<<sum- (int)accumulate(join.begin(),join.end(),0)<<endl;
	}
	
    return 0;
}
