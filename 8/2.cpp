#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main(){
	list<int> all_list[10001];
	int n; cin>>n;
	for (int i=0; i<n; i++){
		string s; cin>>s;
		if (s=="new"){
			int id; cin>>id;
		}
		if (s=="add"){
			int id,num; cin>>id>>num;
			all_list[id].push_back(num);
		}
		else if (s=="merge"){
			int id1, id2; cin>>id1>>id2;
			all_list[id1].merge(all_list[id2]);
		}
		else if (s=="unique"){
			int id; cin>>id;
			all_list[id].sort();
			all_list[id].unique();
		}
		else if (s=="out"){
			int id; cin>>id;
			list<int> copy = (all_list[id]);
			copy.sort();
			typename list<int>::const_iterator p;
			for (p = copy.begin(); p!= copy.end(); p++){
				cout<<*p<<' ';
			}
			cout<<endl;
		}
	}
	return 0;
}