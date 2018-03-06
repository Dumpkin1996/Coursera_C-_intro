#include <iostream>
#include <map>
using namespace std;

typedef multimap<int, int> mm;

int main(){
	int n; cin>>n;
	mm book;
	book.insert(make_pair(1000000000, 1));
	for (int j=0; j<n; j++){
		int i,s; cin>>i>>s;
		book.insert(make_pair(s, i));
		cout<<i<<' ';
		mm::iterator p1 = book.lower_bound(s);
		mm::iterator p2 = book.upper_bound(s);
		int d1 = 1000000000;
		if (p1!=book.begin()){
			p1--;
			d1 = s - p1->first;
		}
		int d2 = 1000000000;
		if (p2!=book.end()) d2 = p2->first - s;
		if (d1 <= d2) cout<<p1->second<<endl;
		else cout<<p2->second<<endl;
	}

}