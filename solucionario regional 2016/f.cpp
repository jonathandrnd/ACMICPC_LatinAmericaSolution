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
	
	int N,C,S;
	
	while(cin>>N>>C>>S){
		int position=1;
		int count=(S==1);
		
		for(int i=0;i<C;i++){
			int command;
			scanf("%d",&command);
			
			if(command==-1){
				if(position==1)position=N;
				else position--;
			}else{
				if(position==N)position=1;
				else position++;
			}
			
			count+=(S==position);
		}
		
		cout<<count<<endl;
	}
	
    return 0;
}

