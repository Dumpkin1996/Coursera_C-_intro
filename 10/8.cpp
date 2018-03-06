#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int t; cin>>t;
	int n,i,j;
	while(t--){
		cin>>n>>i>>j;
		int x = pow(2,i);
		int a = n&x;
		int y = pow(2,j);
		int b = (n&y)^y;
		int result = a+b;
		for (int k = i+1; k<j; k++) result += pow(2,k);
		cout<<hex<<result<<endl;
	}
	return 0;
}