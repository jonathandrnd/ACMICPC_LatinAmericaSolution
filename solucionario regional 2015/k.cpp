#include<bits/stdc++.h>
#define N 100000
#define M 100000
#define INF 1000000100
#define pb push_back
using namespace std;

int L[ M+5 ], S[ M+5 ], C[ M+5 ], R[ M+5 ], E[ N+5 ], dp[ N+5 ], AC[ N+5 ];
int tree[4*N+5];
int n, m;
vector<int>adj[ N +5 ];

void init(int node, int a, int b ){
   if(a==b){
      tree[node]= 0;
      return;
   }
   init(2*node+1, a, (a+b)/2 );
   init(2*node+2, (a+b)/2+1, b );
   tree[node]=min( tree[2*node+1], tree[2*node+2] );
}

int query(int node, int a, int b, int p, int q){
   if(q<a || b<p)return INF;
   if(a>=p && b<=q) return tree[node];
   int v1=2*node+1;
   int v2=2*node+2;
   return min( query(v1, a, (a+b)/2, p, q), query(v2, (a+b)/2+1, b, p, q ) );
}

void update(int node,int a,int b,int p,int val){
   if(b<p || p<a)return;
   if(a==b){
      tree[node]=val;
      return;
   }
   update(2*node+1, a, (a+b)/2, p, val);
   update(2*node+2, (a+b)/2+1, b, p, val);
   tree[node] =min( tree[2*node+1], tree[2*node+2] );
}

bool check( int fin , int shop ){
	int ini = L[ shop ]-1;
	if( ini == 0 ) return S[ shop ] >= AC[ fin ];
	return S[ shop ] >= AC[ fin ] - AC[ ini-1 ];
}

int search( int shop){
	int lo = L[ shop ]-1 , hi = n-1;
	if( !check( lo , shop ) )return -1;
	if( check( hi , shop ) ) return hi;
	while( hi-lo >1 ){
		int mi = (lo + hi )/2;
		if( check( mi, shop) ) lo =mi;
		else hi = mi;
	}
	return lo;
}

void doit(){
	for( int i=0 ; i<n ; ++i ){
		scanf("%d", &E[ i ] );
		adj[ i ].clear();
	}
	AC[ 0 ] = E[ 0 ];
	for( int i=1 ; i<n ; ++i ) AC[ i ] = AC[ i-1 ] + E[ i ];
	for( int i=0 ; i<m ; ++i ){
		scanf("%d%d%d", &L[ i ], &S[ i ], &C[ i ] );
		R[ i ] = search( i );
		if( R[ i ] != -1 ) adj[ L[ i ] -1 ].pb( i );
	}

	init( 0 , 0 , n );
	dp[ n ] = 0;
	update( 0, 0, n, n, 0 );
	for( int i =n-1; i>=0; i-- ){
		dp[ i ] = INF;
		for( int j =0 ; j<adj[ i ].size() ; ++ j ){
			int shop = adj[ i ][ j ];
			dp[ i ] = min( dp[ i ] , C[ shop ] + query( 0, 0,  n, i+1, R[ shop ] +1 ) );
		}
		update( 0, 0, n, i, dp[ i ] );
	}
	if( dp[ 0 ] >= INF )puts("-1");
	else printf("%d\n" , dp[ 0 ] );
}

int main(){
	while( scanf("%d%d" ,&n,&m) ==2 ) doit();
}








