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
#define MAXN 200005
int n,t;  //n es el tamaño de la cadena
int p[MAXN],r[MAXN],h[MAXN];
int RMQ[MAXN][18];
int L[MAXN];

//p es el inverso del suffix array, no usa indices del suffix array ordenado
//h el el tamaño del lcp entre el i-esimo y el i+1-esimo elemento de suffix array ordenado
string s;

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
   int i, j, bc[256];
   t = 1;
   for(i = 0; i < 256; i++) bc[i] = 0;  //alfabeto
   for(i = 0; i < n; i++) ++bc[int(s[i])]; //counting sort inicial del alfabeto
   for(i = 1; i < 256; i++) bc[i] += bc[i - 1];
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
 
int main(){
	
	while(cin>>s){
		s += "$";
   		n = s.size();
   		suff_arr();
   		
   		int querys;
   		cin>>querys;
   		
   		while(querys--){
   			string q;
   			cin >> q;
   			
   			int ans = 0;
   			
			while(true){
				int lo = 0;
	  			int hi = n;
	  			
	  			for(int i = 0; i < 18; i++){
	  				int me = (lo+hi)/2;
	  				int start = r[me];
	  				
					int cnt = 0;
	  				bool greater = 0;
	  				
					for(int j = start;j<n;j++){
	  					if(s[j]==q[j - start]){
	  						cnt++;
						}else{
							if(s[j] > q[ j - start] ){
								greater = 1;
							}
							break;
						}
						
						if(cnt==q.size())break;
					}
	  				
	  				if(greater){
	  					hi = me;
					}else{
						lo = me;
					}
	  				
				}
	  			
	  			int coincidence = 0;
	  			int start = r[lo];
	  			
	  			for(int i = start;i < n;i++)
	  				if(s[i] == q[i - start]){
	  					coincidence++;	
	  					if(coincidence ==q.size())break;
					}else{
						break;
					}
	   			
	   			if(lo+1<n){
	   				start = r[lo+1];
	  				int cnt = 0;
					for(int i = start;i < n;i++)
	  					if(s[i] == q[i - start]){
	  						cnt++;	  						
		  					if(cnt ==q.size())break;
						}else{
							break;
						}
	   				
	   				coincidence = max(coincidence, cnt);
				}
				
	   			ans++;
	   			if(coincidence == 0){
	   				ans = -1;
	   				break;
				}
	   			
				if(coincidence == q.size()){
					break;
				}	
				
				q = q.substr(coincidence);
			}
			cout<<ans<<endl;
		}
   		
	}
   	return 0;
}
