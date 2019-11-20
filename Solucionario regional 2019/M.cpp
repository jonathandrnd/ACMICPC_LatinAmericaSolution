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

int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	int n, x;
	
	while(cin>>n>>x){
		
		vector<int>v(n,-1);
		for(int i = 0; i < n; i++)
			cin>>v[i];
		
		int ans = 0;
		
		for(int i=  0; i < n;){
			int cnt = 0;
			int last = v[i];
			
			while(i <n && last + x >= v[i] ){
				last = v[i];
				cnt++;
				i++;
			}
			
			ans = max(ans, cnt);
		}
		
		cout<<ans<<endl;
	}
		
	return 0;
}
