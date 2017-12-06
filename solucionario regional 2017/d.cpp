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
set<pair<pair<int,int>,int> >S;
int f[100005];

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	int L,C,N;
	
	while(scanf("%d %d %d",&L,&C,&N)==3){
		int P,X,A,B;
		S.clear();
		
		memset(f,0,sizeof(f));
		
		S.insert(make_pair(make_pair(0,L-1),1) );
		f[1]=L;
		
		for(int caso=0;caso<N;caso++){
			scanf("%d %d %d %d",&P,&X,&A,&B);
			long long fp=f[P];
			long long LL=L;
			
			int M1= (A+fp*fp)%LL;
			int M2= (A+(fp+B)*(fp+B))%LL;
			
			if(M1>M2)swap(M1,M2);
			
			set<pair<pair<int,int>,int> >::iterator it=S.begin();
			it=S.lower_bound(make_pair(make_pair(M1+1,0),0));
			--it;
			set<pair<pair<int,int>,int> >::iterator aux=it;
			vector<pair<pair<int,int>,int> >del;
			vector<pair<pair<int,int>,int> >ins;
			
			while(true){
				if(it==S.end())break;
				pair<pair<int,int>,int> P=*it;
				if(P.first.first>M2)break;
				
				//S.erase(it);
				f[P.second]-=(P.first.second-P.first.first+1);
				
				if(P.first.first<M1){   //only once time
					//S.insert(make_pair(make_pair(P.first.first,M1-1),P.second ));
					ins.push_back(make_pair(make_pair(P.first.first,M1-1),P.second ));
					f[P.second]+=M1-1-P.first.first+1;
				}
				
				if(P.first.second>M2){ //only once time
					//S.insert(make_pair(make_pair(M2+1,P.first.second),P.second ));
					ins.push_back(make_pair(make_pair(M2+1,P.first.second),P.second ));
					f[P.second]+=P.first.second-(M2+1)+1;
				}
				
				//several
				del.push_back(P);
				f[X]+=min(M2,P.first.second)-max(M1,P.first.first)+1;
				++it;
			}
			
			// we update the values in the set in the end, because this could be affect the last iterator 
			for(int i=0;i<del.size();i++)
				S.erase(del[i]);
			for(int i=0;i<ins.size();i++)//at most twice
				S.insert(ins[i]);
			S.insert(make_pair(make_pair(M1,M2),X));
		}
		
		
		
		int maxi=0;
		for(int i=1;i<=C;i++)maxi=max(maxi,f[i]);
		cout<<maxi<<endl;
	}
	
	return 0;
}


