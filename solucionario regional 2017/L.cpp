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
int x[100005];
int y[100005];
int X[100005];
int Y[100005];
int rightx[100005];// where is number one
int leftx[100005];
int righty[100005];// where is number one
int lefty[100005];
int n;

int print(int x1,int y1,int x2,int y2){
	int dx=X[max(x1,x2)-1]-X[min(x1,x2)-1];
	int dy=Y[max(y1,y2)-1]-Y[min(y1,y2)-1];
	return dx+dy;
}

int solve(int x1,int y1,int x2,int y2){
	int ans=1<<30;
	int dx=abs(x1-x2);
	int dy=abs(y1-y2);
	
	if(dx>dy){
		int miss= dx-dy;
		int dir=1;
		if(x1>x2)dir=-1;
		int val=1<<30;
		
		if(y1<n){
		    val= 2*(miss/2)*y[y1]+abs(X[x1+dir*miss-1]-X[x1-1]) +print(x1+dir*miss,y1,x2,y2);
			ans=min(ans,val);
		}
		
		if(y1>1)
			val= 2*(miss/2)*y[y1-1]+abs(X[x1+dir*miss-1]-X[x1-1]) +print(x1+dir*miss,y1,x2,y2);
		ans=min(ans,val);
			
		return ans;
	}else{
		int miss= dy-dx;
		
		
		if(y1<y2){
			int val=1<<30;
			if(x1<n)
				val= 2*(miss/2)*x[x1]+Y[y1+miss-1]-Y[y1-1] +print(x1,y1+miss,x2,y2);
			
			ans=min(ans,val);
			if(x1>1)
				val= 2*(miss/2)*x[x1-1]+Y[y1+miss-1]-Y[y1-1] +print(x1,y1+miss,x2,y2);
			ans=min(ans,val);
		}else{
			int val=1<<30;
			if(x1<n)
				val= 2*(miss/2)*x[x1]+Y[y1-1]-Y[y1-miss-1]+  print(x1,y1-miss,x2,y2);
			
			ans=min(ans,val);
			if(x1>1)
				val= 2*(miss/2)*x[x1-1]+Y[y1-1]-Y[y1-miss-1]+print(x1,y1-miss,x2,y2);
			ans=min(ans,val);
		}
		
	}


	return ans;
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	
	while(scanf("%d",&n)==1){
		
		x[0]=0;y[0]=0;
		
		for(int i=0;i<n-1;i++)scanf("%d",&x[i+1]);
		for(int i=0;i<n-1;i++)scanf("%d",&y[i+1]);
		
		rightx[n]=righty[n]=-1;
		for(int i=n-1;i>=1;i--){
			if(x[i]==1)
				rightx[i]=i+1;
			else
				rightx[i]=rightx[i+1];
				
			if(y[i]==1)
				righty[i]=i+1;
			else
				righty[i]=righty[i+1];
		}
		
		leftx[1]=lefty[1]=-1;
		for(int i=1;i<n;i++){
			if(x[i]==1)
				leftx[i+1]=i;
			else
				leftx[i+1]=leftx[i];
				
			if(y[i]==1)
				lefty[i+1]=i;
			else
				lefty[i+1]=lefty[i];
		}
		
		
		X[0]=Y[0]=0;
		for(int i=1;i<n;i++)X[i]=X[i-1]+x[i];
		for(int i=1;i<n;i++)Y[i]=Y[i-1]+y[i];
		
		int q;
		scanf("%d",&q);
		
		while(q--){
			int x1,y1,x2,y2;
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			if(x1>x2){
				swap(x1,x2);
				swap(y1,y2);
			}
			
			int dx=abs(x1-x2);
			int dy=abs(y1-y2);
			
			if(dx==dy){
				int val=print(x1,y1,x2,y2);
				printf("%d\n",val);
				continue;
			}
			
			int ans= solve(x1,y1,x2,y2);
			
			if(dx>dy){
				int sum=0;
				if(righty[y1]!=-1 ){
					int miss= righty[y1]-y1;
					if(x1+miss<=n && y1+miss<=n){
						sum=X[x1+miss-1]-X[x1-1]+Y[y1+miss-1]-Y[y1-1];
						ans=min(ans,sum+solve(x1+miss,y1+miss,x2,y2));
					}
					
				}
					
				sum=0;
				if(lefty[y1]!=-1 ){
					int miss= y1 -lefty[y1];
					if(x1+miss<=n && y1-miss>=1){
						sum=X[x1+miss-1]-X[x1-1]+Y[y1-1]-Y[y1-miss-1];
						ans=min(ans,sum+solve(x1+miss,y1-miss,x2,y2));
					}
					
				}					
			}else{
				int sum=0;
				if(rightx[x1]!=-1 ){
					int miss= rightx[x1]-x1;
					
					
					if(y2>y1){
						if(x1+miss<=n && y1+miss<=n){
							sum=X[x1+miss-1]-X[x1-1]+Y[y1+miss-1]-Y[y1-1];
							ans=min(ans,sum+solve(x1+miss,y1+miss,x2,y2));
						}
					}else{
						if(x1+miss<=n && y1-miss>=1){
							sum=X[x1+miss-1]-X[x1-1]+Y[y1-1]-Y[y1-miss-1];
							ans=min(ans,sum+solve(x1+miss,y1-miss,x2,y2));
						}
					}
					
					
				}
						
					
				sum=0;
				if(leftx[x1]!=-1 ){
					int miss= x1 -leftx[x1];
					if(y2>y1){
						if(x1-miss>=1 && y1+miss<=n){
							sum=X[x1-1]-X[x1-miss-1]+Y[y1+miss-1]-Y[y1-1];
							ans=min(ans,sum+solve(x1-miss,y1+miss,x2,y2));
						}
					}else{
						if(x1-miss>=1 && y1-miss>=1){
							sum=X[x1-1]-X[x1-miss-1]+Y[y1-1]-Y[y1-miss-1];
							ans=min(ans,sum+solve(x1-miss,y1-miss,x2,y2));		
						}
					}
				}	
						
			}	
			
			printf("%d\n",ans);
		}
				
	}
		
	return 0;
}

