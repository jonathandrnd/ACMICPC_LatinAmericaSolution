#include <iostream>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;
int n,L,U;
long long c[100005];
long long rightP[100005][2];
long long rightPL[17][100005][2];

struct st{
    long long sum,maxpref,minpref;
    
    st(){}
    st(long long _sum, long long _maxpref ,long long _minpref){
        sum = _sum;
		maxpref = _maxpref;
		minpref = _minpref;  
    }
}tree[400005];

void init(int i , int j , int node ){
    if(i == j){
	   tree[node].sum = tree[node].maxpref = tree[node].minpref = c[i];
       return ;
    }
    
    int v1 = 2*node + 1;
    int v2 = 2*node + 2;
    init( i , (i+j)/2 ,v1);
    init( (i+j)/2 + 1 , j ,v2);
    
    tree[node].sum = tree[v1].sum +tree[v2].sum;
    tree[node].maxpref  = max(tree[v1].maxpref, tree[v1].sum +tree[v2].maxpref);
    tree[node].minpref  = min(tree[v1].minpref, tree[v1].sum +tree[v2].minpref);;
}

st query( int start , int end , int node , int i , int j ){
    if( i > end || j < start ) return st(-1LL<<60,-1,-1);
    if( i <= start && end <=j )return tree[node];
    
	int v1 = 2*node + 1;
    int v2 = 2*node + 2;
    
    st ret1 = query( start , (start+end)/2 , 2*node + 1 , i , j );
    st ret2 = query( (start+end)/2 + 1 , end , 2*node + 2, i , j );
    
	if( ret2.sum == (-1LL<<60) )return ret1;
    if( ret1.sum == (-1LL<<60) )return ret2;
    
    st ans;
	ans.sum = ret1.sum + ret2.sum;
	ans.maxpref = max(ret1.maxpref, ret1.sum + ret2.maxpref ); 
	ans.minpref = min(ret1.minpref, ret1.sum + ret2.minpref );
    return ans;
}


int main() {
	while(scanf("%d %d %d",&n, &L, &U) == 3){
		for(int i = 0 ; i < n; i++){
			int aux;scanf("%d",&aux);	
			c[i] =aux;
		}
		init(0,n-1,0);
		
		//right[i][0] starting with X = L find next position where X will be L
		//right[i][1] starting with X = U find next position where X will be U
		for(int i = 0; i< n;i++){
			int lo = i;
			int hi = n;
			
			//right[i][0]
			while(lo != hi){
				int me = (lo+hi)/2;
				st evaluate = query(0,n-1,0,i,me);
				if(L + evaluate.maxpref<= U && evaluate.minpref>=0  ){
					lo = me+1;
				}else{
					hi = me;
				}
			}
			
			if(lo == n){
				rightP[i][0]=1<<30;
			}else{
				st aux = query(0,n-1,0,i,lo);
				if(L + aux.maxpref> U ){
					rightP[i][0] = lo;
				}else{
					rightP[i][0] = -lo;
				}	
			}
			
			lo = i; hi=n;
			//right[i][1]
			while(lo != hi){
				int me = (lo+hi)/2;
				st evaluate = query(0,n-1,0,i,me);
				if(U + evaluate.minpref>= L && evaluate.maxpref<=0  ){
					lo = me+1;
				}else{
					hi = me;
				}
			}
			
			if(lo == n){
				rightP[i][1]= 1<<30;
			}else{
				st aux = query(0,n-1,0,i,lo);
				if(U + aux.minpref< L ){
					rightP[i][1] = -lo;
				}else{
					rightP[i][1] = lo;
				}	
			}
			
		}

		for(int i = 0;i<n;i++)rightPL[0][i][0] = rightP[i][0];
		for(int i = 0;i<n;i++)rightPL[0][i][1] = rightP[i][1];
		rightPL[0][n][0]=rightPL[0][n][1]=n;
		
		for(int L = 1; L <= 16; L++){
			rightPL[L][n][0]=rightPL[L][n][1]=n;
			
			for(int i = 0; i< n; i++){
				int nextval = rightPL[L-1][i][0];
				if(abs(nextval) < n){
					if(nextval <0 )
						rightPL[L][i][0] = rightPL[L-1][-nextval+1][0];
					else
						rightPL[L][i][0] = rightPL[L-1][nextval+1][1];
				}else{
					rightPL[L][i][0] = n;
				}
			}
			
			
			for(int i = 0; i< n; i++){
				int nextval = rightPL[L-1][i][1];
				if(abs(nextval) < n){
					if(nextval <0 )
						rightPL[L][i][1] = rightPL[L-1][-nextval+1][0];
					else
						rightPL[L][i][1] = rightPL[L-1][nextval+1][1];
				}else{
					rightPL[L][i][1] = n;
				}
			}
		}
		
		int q;
		scanf("%d",&q);
		
		for(int ncase = 1; ncase <= q; ncase++){
			int startMonth, endMonth, X;
			scanf("%d %d %d",&startMonth,&endMonth,&X);
			int f1 = startMonth,f2= endMonth, f3=X;
			
			startMonth--;
			endMonth--;
			
			st aux = query(0,n-1,0,startMonth,endMonth);
			
			
			if( X+ aux.maxpref <= U && X+aux.minpref>=L ){
				printf("%d\n", X+aux.sum);
				continue;
			}else{
				int lo = startMonth;
				int hi = endMonth+1;
				
				while(lo != hi){
					int me = (lo+hi)/2;
					st evaluate = query(0,n-1,0,startMonth,me);
					if(X + evaluate.maxpref<= U && X + evaluate.minpref>=L  ){
						lo = me+1;
					}else{
						hi = me;
					}
				}
				
				if(lo ==endMonth){
					st aux = query(0,n-1,0,startMonth,lo);
					if( X + aux.sum > U )printf("%d\n", U);
					else if(X + aux.sum < L )printf("%d\n", L);
					else {
						int result = (int)(X+aux.sum);
					}
					continue;
				}else{
					int nextMonth = lo + 1;
					int value = -1;
					int id =0;
					st aux = query(0,n-1,0,startMonth,lo);
					if(X + aux.maxpref>U ){
						value = U;
						id = 1;
					}else{
						id = 0;
						value = L;
					}
					
					for(int i=16;i>=0;i--){
						if( abs(rightPL[i][nextMonth][id]) >endMonth ){
							continue;
						}else{
							nextMonth = rightPL[i][nextMonth][id];
							if(nextMonth < 0){
								nextMonth = -nextMonth+1;
								value = L;
								id = 0;
							}else{
								nextMonth++;
								value = U;
								id = 1;
							}
						}
					}
					
					
					if(nextMonth > endMonth){
						printf("%d\n",(int)value );
					}else{
						long long done = value + query(0,n-1,0,nextMonth,endMonth).sum;
						
						if( done >U){
							printf("%d\n",U );
						}else{
							if(done < L){
								printf("%d\n",L );
							}else{
								printf("%d\n",done);
							}
						}
					}
				}
			}
		}	
	}
	
	return 0;
}
