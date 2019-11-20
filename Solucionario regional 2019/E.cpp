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
vector<int>nextEgg;
string s;

int main() {
	int t;
	
	while( cin >> s ){
		s += s;		
		cin >> t;
		int n = s.size();
		
		nextEgg = vector<int>(n+1);
		nextEgg[n]= -1;
		
		for(int i = n-1; i >= 0; i--){
			if(s[i] == 'E') nextEgg[i] = i;
			else nextEgg[i] = nextEgg[i+1];
		}
		
		long long ans = 0;
		
		for(int i = 0; i < n/2; i++){
			int index = nextEgg[i];
			if(index >= i + t || index == -1)continue;
			ans +=  (i+t-index);
		}
		
		cout<<ans<<endl;
	}
	
		
	return 0;
}
