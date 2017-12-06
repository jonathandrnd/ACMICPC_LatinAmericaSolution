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
#define MAXN 1000005  
int n,t;  //n es el tamaño de la cadena
int p[MAXN],r[MAXN];
//p es el inverso del suffix array, no usa indices del suffix array ordenado
int s[MAXN];

void fix_index(int *b, int *e) {  
    int pkm1, pk, np, i, d, m;  
    pkm1 = p[*b + t];  
    m = e - b; d = 0;  
    np = b - r;  
    for(i = 0; i < m; i++) {  
        if (((pk = p[*b+t]) != pkm1) && !(np <= pkm1 && pk < np+m)) {  
            pkm1 = pk;  
            d = i;  
        }  
        p[*(b++)] = np + d;  
    }  
}  

bool comp(int i, int j) {  
    return p[i + t] < p[j + t];  
}  

void suff_arr() {  
    int i, j, bc[305];  
    t = 1;  
    for(i = 0; i < 305; i++) bc[i] = 0;  //alfabeto    
    for(i = 0; i < n; i++) ++bc[int(s[i])]; //counting sort inicial del alfabeto  
    for(i = 1; i < 305; i++) bc[i] += bc[i - 1];  
    for(i = 0; i < n; i++) r[--bc[int(s[i])]] = i;  
    for(i = n - 1; i >= 0; i--) p[i] = bc[int(s[i])];  
    for(t = 1; t < n; t *= 2) {  
        for(i = 0, j = 1; i < n; i = j++) {  
            while(j < n && p[r[j]] == p[r[i]]) ++j;  
            if (j - i > 1) {  
                sort(r + i, r + j, comp);  
                fix_index(r + i, r + j);  
            }  
        }  
    } 
}

int size[100005];
int position[100005];
vector<int>id[100005];
int whicharray[MAXN];

set<int>S;

long long pot(long long a,long long b){
	if(b==0)return 1;
	long long dev=pot(a,b/2);
	dev=(dev*dev)%1000000007LL;
	if(b%2==1)dev=(dev*a)%1000000007LL;
	return dev;	
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	int cant;
	while(scanf("%d",&cant)==1){
		n=0;
		int D=0;
		memset(position,0,sizeof(position));
		
		for(int i=0;i<cant;i++){
			int val;
			scanf("%d",&val);
			size[i]=val;
			D+=val;
			id[i].clear();
			for(int j=0;j<val;j++){
				int aux;
				scanf("%d",&aux);
				id[i].push_back(n);
				whicharray[n]=i;
				s[n++]=aux;
			}
			
			s[n++]=304;
		}
		
		suff_arr();
		
		S.clear();
		for(int i=0;i<cant;i++){
			S.insert(p[id[i][position[i]++]]);
		}
		
		// 2  1 3 ->  6
		long long dev=0;
		
		while(D!=0){
			int aux=*S.begin();//this is min_value in p
			int idx=r[aux]; //position in s
			dev=(dev+ (long long)s[idx]*pot(365,D))%1000000007LL;
			
			
			S.erase(S.begin());
			int idarray=whicharray[idx];
			
			if( position[idarray] <size[idarray]){
				S.insert( p[id[idarray][position[idarray]++]]);
			}
			
			D--;
		}
		
		cout<<dev<<endl;
	}
	
	// 2 5 7 $ 1 4 6 10 $ 3 2 1 $ 2 4 1 $
	
	return 0;
}


