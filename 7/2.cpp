#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	double x; cin>>x;
	cout<<fixed<<setprecision(5)<<x<<endl;
	cout<<setprecision(7)<<scientific<<x<<endl;
	return 0;
}