#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int main(){
	int n; cin>>n;
	multiset<int> s;
	multiset<int> history;
	for (int i=0; i<n; i++){
		string c; int x;
		cin>>c>>x;
		if (c=="add"){
			s.insert(x);
			history.insert(x);
			cout<<s.count(x)<<endl;
		}
		if (c=="del"){
			cout<<s.count(x)<<endl;
			s.erase(s.lower_bound(x),s.upper_bound(x));
		}
		if (c=="ask"){
			bool b = history.count(x);
			cout<<b<<' '<<s.count(x)<<endl;
		}
	}	
}