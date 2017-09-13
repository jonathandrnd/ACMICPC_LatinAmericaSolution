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

int main(){

	int n;
	while(scanf("%d",&n)==1){
		int S[n];
		for(int i=0;i<n;i++)
			scanf("%d",&S[i]);
		
		sort(S,S+n);
		
		int S2[n];
		
		if(n%2==1){
			int pos=n-1;
			S2[n/2]=S[pos--];
			for(int i=1;i<=n/2;i++){
				S2[n/2-i]=S[pos--];
				S2[n/2+i]=S[pos--];
			}
		}else{
			int pos=n-1;
			for(int i=0;i<n/2;i++){
				S2[n/2-i-1]=S[pos--];
				S2[n/2+i]=S[pos--];
			}
		}
		
		
		double area=0;
		
		double pi=acos(-1);
		double angle=(pi*(n-2))/n;
		long long sarea=0;
		
		
		for(int i=0;i<n;i++)
			sarea+= (S2[i]*S2[(i+1)%n]); 			
		
		
		area=sarea;
		area*=sin(angle)/2;
		printf("%.3lf\n",area);
		
	}
	


    return 0;
}

// area   S1*S2*sin(angle)
		
