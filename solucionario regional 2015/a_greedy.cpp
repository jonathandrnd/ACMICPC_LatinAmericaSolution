#include <bits/stdc++.h>
#define all(v) v.begin(),v.end()
#define REP(i, a, b) \
for(int i = int(a); i < int(b); i++)
#define pb(v,e) v.push_back(e)
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef set<int> si;
typedef map<string, int> msi;
ll stois(string s){
	istringstream in(s);
	ll x;
	in>>x;
	return x;
}
int f(string s){
	vi v(10,2);
	int ind;
	REP(i,0,s.size()){
		if(v[s[i]-'0']>0){
			v[s[i]-'0']--;
			ind=i;
			continue;
		}
		break;
	}
	return ind;
}
int main(){
	string s;
	while(cin>>s){
		int pos=f(s);
	//	cout<<"posicion: "<<pos<<endl;
		if(pos+1==s.size() || s.size()<=2){
			cout<<s<<endl;
			continue;
		}
		for(int i=pos+1;i>=0;i--){
			vi v(10,2);
			string cad;
			REP(j,0,i)v[s[j]-'0']--;
			for(int j=s[i]-'0'-1; j>=0;j--){
				if(v[j]>0){
					v[j]--;
					cad=s.substr(0,i)+string(1,j+'0');
					int cont=0;
					for(int k=9;k>=0;k--){
						for(int l=0;l<v[k];l++){
							if(cont==s.size()-i-1){
								break;
							}
							cad+=string(1,'0'+k);
							cont++;
						}
					}
					break;
				}
			}
			if(cad.size()>0){
				cout<<stois(cad)<<endl;
				break;
			}
		}
	}
	return 0;
}

