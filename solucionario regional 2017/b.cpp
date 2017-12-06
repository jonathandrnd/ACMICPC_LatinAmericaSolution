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

vector<int>v;
bool isvowel(char ch){
	if(ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u')
		return 1;
	return 0;
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	string s;
	
	while(cin>>s){
		int countvowel=0;
		for(int i=0;i<s.size();i++)
			if(isvowel(s[i]))
				countvowel++;
		
		if(countvowel==0){
			//all consonant
			cout<<1<<endl;
			continue;
		}
		
		if(!isvowel(s[0]) ){
			// the first character have to be vowel
			cout<<0<<endl;
			continue;
		}
		
		if(countvowel==1){
			//sample    accccccccccc=  cacccccccccc= ccaccccccccc= cccaccccccccc ....
			cout<<s.size()<<endl;
			continue;
		}
		
		v.clear();
		// O( size(s) )
		for(int i=0;i<s.size();i++){
			if(isvowel(s[i])){
				//check the next vowel and count consonants
				int count=0;
				i++;
				
				while(i<s.size() && !isvowel(s[i])){
					count++;
					i++;
				}
					
				if(i==s.size())break;// if does not exist vowel
				v.push_back(count);
				i--;
			}
		}
		
		cout<<v[v.size()/2]+1<<endl;
		
	}
		
	return 0;
}


