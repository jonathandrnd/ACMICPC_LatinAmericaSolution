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
string s;
vector<long long>P;
int main() {
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	while(cin>>s){
		
		int id = 2;
		vector<long long>v;
		P.clear();
		
		for(int i = 0;i + 1 < s.size(); i++){
			if(s[i] != s[i+1])
				v.push_back(id+1);
			id += 2;
		}
		
		//(X-v[0])*(X-v[1]).....*(X-v[i])
		P.push_back(1);
		
		for(int i = 0; i < v.size(); i++){
			P.push_back(0);
			for(int j =P.size()-1; j >0 ;j--){
				P[j]-=P[j-1]*v[i];
			}
		}
		
		if( (v.size()%2 == 1 && s[0]=='H') || 
				(v.size()%2==0 && s[0]=='A')  ){
			for(int i = 0; i < P.size(); i++)
				P[i] = -P[i];
		}
		
		cout<<P.size() - 1<<endl;
		
		for(int i = 0; i < P.size() ;i++){
			cout<<P[i];
			if(i + 1 != P.size()){
				cout<<" ";
			}	
		}
		cout<<endl;
	}
		
	return 0;
}
