#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	int x; cin>>x;
	cout<<hex<<x<<endl;
	cout<<setfill('0')<<setw(10)<<dec<<x<<endl;
	return 0;
}