#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	
	int a,b,c,d;
	while(cin>>a>>b>>c>>d){
		cout<< abs( (a+d)-(b+c)) <<endl;
	}

    return 0;
}
