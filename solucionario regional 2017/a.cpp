#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<sstream>
#include<algorithm>
#include<set>
#include<queue>
#define EPS 1e-8
using namespace std;
vector<pair<int,int> >v[15];
int h;
double dis[15][15];
int n;

inline bool area(pair<double,double> A, pair<double,double> B,pair<double,double> C) {	
	if( (B.first-A.first)*(C.second-A.second)>(B.second-A.second)* (C.first-A.first) )return 1;
	return 0;	
}


inline bool intersecta(pair<double,double> P1,pair<double,double> P2,pair<double,double>P3, pair<double,double>P4){
	bool A1 = area(P3, P4, P1);
    bool A2 = area(P3, P4, P2);
    bool A3 = area(P1, P2, P3);
    bool A4 = area(P1, P2, P4);
    
	if( ( ( A1 && !A2  ) || ( !A1  && A2) ) && 
		( ( A3 && !A4  ) || ( !A3  && A4 ) ) ) return 1;
            
	return false;
}

double f(int id1,int id2){
	vector<pair<int,int> >a=v[id1];//polygon 1
	vector<pair<int,int> >b=v[id2];//polygon 2
	
	double lo=a[1].first-a[0].first;double hi=2*1e+8;
	int tam1=a.size();
	int tam2=b.size();
	
	for(int caso=0;caso<50;caso++){
		double me=(lo+hi)/2;
		int pos1=1;// right
		int pos2=0;// left
					
		bool ok=1;
		bool fin=0;
		while(true){
			if(fin)break;
			int x1=a[pos1].first;
			int y1=a[pos1].second;
			int x2=a[(pos1+1)%tam1].first;
			int y2=a[(pos1+1)%tam1].second;
			
			int X1=b[pos2].first;
			int Y1=b[pos2].second;
			int X2=b[(pos2+tam2-1)%tam2].first;
			int Y2=b[(pos2+tam2-1)%tam2].second;
			
			if(y2==h && Y2==h){
				fin=1;
			}			
			
			if(Y1>y2){
				pos1++;
				continue;
			}
			
			if(y1>Y2){
				pos2=(pos2+tam2-1)%tam2;
				continue;
			}else{
				
				if(intersecta( make_pair(x1,y1),make_pair(x2,y2) ,make_pair(X1+me,Y1) ,make_pair(X2+me,Y2) )){
					ok=0;
					break;
				}else{	
					if(y2>Y2){
						pos2=(pos2+tam2-1)%tam2;
					}else{
						pos1++;		
					}
				
				}
				
			}
						
		}	
		
		
		if(ok==0){
			lo=me;
		}else{
			hi=me;
		}
			
	}
	
	return hi;
}

bool done[1<<15][15];
double memo[1<<15][15];
int g[15];

double dp(int mask,int last){
	if(__builtin_popcount(mask)==n){
		return g[last];	
	}
	
	if(done[mask][last])return memo[mask][last];
	double dev=1e+12;
	
	for(int i=0;i<n;i++)
		if( (mask&(1<<i))==0){
			dev=min(dev, dis[last][i]+dp(mask|(1<<i),i  )  );
		}
	
	
	memo[mask][last]=dev;
	done[mask][last]=1;
	return dev;
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	
	while(cin>>n){
		//cout<<"n "<<n<<endl;
		for(int i=0;i<n;i++)v[i].clear();
		h=0;
		
		for(int i=0;i<n;i++){
			vector<pair<int,int> >x;
			int size;
			scanf("%d",&size);	
			//cout<<"size "<<size<<endl;
			g[i]=0;
			
			for(int j=0;j<size;j++){
				int a,b;
				scanf("%d %d",&a,&b);
				//cout<<"j "<<a<<" "<<b<<endl;
				x.push_back(make_pair(a,b));
				h=max(h,b);
				g[i]=max(g[i],a);
			}
			
			v[i]=x;
		}
		
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(i==j)continue;
				dis[i][j]=f(i,j);
				//cout<<i<<" "<<j<<" "<<dis[i][j]<<endl;
			}
		
		memset(done,0,sizeof(done));
		double dev=1e+21;
		
		for(int i=0;i<n;i++){
			double w=0;
			for(int j=0;j<v[i].size();j++)
				if(v[i][j].first<0)w=max(w,abs(v[i][j].first)+0.0);
			
			
			dev=min(dev,w+dp(1<<i,i) );
		}
		
		
		printf("%.3lf\n",dev);
			
	}
		
	return 0;
}


