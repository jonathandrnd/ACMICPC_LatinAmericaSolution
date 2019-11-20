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
int c[1002][1002];


int main() {
	
	int R, C;	
	while( scanf("%d %d",&R, &C) == 2){
		char s[1002];
		for(int i = 0; i < R; i++){
			scanf("%s",s);	
			
			c[i][C-1] = 1;
			for(int j = C-2; j >=0 ;j--){
				if( s[j] == s[j+1] ){
					c[i][j] = 1 + c[i][j+1];
				}else{
					c[i][j] = 1;
				}
			}
		}
		
		int ans = 0;
		
		for(int j = 0; j < C; j++){
			vector<int> v(R);
			for(int i = 0;i < R;i++)
				v[i] = c[i][j]; 
			
			int right[R];
        	right[R - 1] = R;
        	
			int left[R];
        	left[0]=-1;
        
	        for(int i = R - 2;i >= 0;i--){
    	        int idx = i + 1;
        	    while( idx != R && v[idx] >= v[i])
            	    idx = right[idx];   
            	right[i] = idx;
        	}
        
	        for(int i = 1; i < R;i++){
    	        int idx = i - 1;
        	    while( idx != -1 && v[idx] >= v[i])
            	    idx = left[idx];
            	left[i] = idx;
        	}
			
			
	        for(int  i= 0;i < R;i++){
	        	int size = right[i] - left[i] - 1;
	        	ans = max(ans, min(size, v[i]) );
			}
		}
		
		cout<<ans*ans<<endl;	
	}		
	return 0;
}
