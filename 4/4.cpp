#include <iostream>
using namespace std;

class Longint{
private:
	bool is_neg;
	int length;
	int s[201];
public:
	Longint();
	Longint(string s);
	Longint & operator = (const Longint x);
	friend Longint operator + (Longint, Longint);
	friend Longint operator - (Longint, Longint);
	friend Longint operator * (Longint, Longint);
	friend Longint operator / (Longint, Longint);
	friend ostream & operator<< (ostream & os, const Longint);
	friend bool operator > (Longint, Longint);
};


Longint::Longint(){
	is_neg= 0;
	length = 0;
	for (int i = 0; i<201; i++){
		s[i]=0;
	}
}


Longint::Longint(string str){
	int l = str.length();
	length = l;
	if (str[0]=='-') is_neg = 1; else is_neg = 0;
	for (int i=0; i<l; i++){
		s[200-i]= (int)(str[l-1-i]) - (int)('0') ;
	}
}

bool operator > (Longint x, Longint y){
	if (x.length < y.length) return 0;
	else if (x.length > y.length) return 1;
	else {
		int l = x.length;
		for (int i= l; i>0; i--){
			if (x.s[201-i]>y.s[201-i]){
				return 1;
			}
			else if (x.s[201-i]<y.s[201-i]){
				return 0;
			}
		}
	}
	return 0;
}


Longint operator + (Longint x, Longint y){
	Longint result;
	for (int i = 200; i>0; i--){
		result.s[i] += (x.s[i]+y.s[i])%10;
		x.s[i-1] += (x.s[i]+y.s[i])/10;
	}
	int l = max(x.length, y.length);
	if (result.s[200-l]==0) result.length = l;
	else result.length = l+1;
	return result;
}


Longint operator - (Longint x, Longint y){
	Longint result;
	if (!(x>y) && !(y>x)) return result;
	else if (x>y){
		for (int i = 200; i>0; i--){
			if (x.s[i]-y.s[i]>=0) result.s[i] += x.s[i]-y.s[i];
			else {
				result.s[i] += x.s[i]-y.s[i]+10;
				x.s[i-1] -= 1;
			}
		}
	}
	else{
		result.is_neg = 1;
		for (int i = 200; i>0; i--){
			if (y.s[i]-x.s[i]>=0) result.s[i] += y.s[i]-x.s[i];
			else {
				result.s[i] += y.s[i]-x.s[i]+10;
				y.s[i-1] -= 1;
			}
		}
	}
	
	bool flag = 0;
	for(int i=0; i<201; i++){
		if (flag || result.s[i]!=0){
			flag = 1;
			result.length ++;
		}
	}

	return result;
}


Longint operator * (Longint x, Longint y){
	Longint result;
	for (int i=200; i>=0; i--){
		Longint temp;
		for (int j=0; j<y.s[i]; j++){
			temp = temp + x;
		}
		for (int j=0; j<=i ; j++){
			temp.s[j] = temp.s[j+(200-i)];
		}
		for (int j=0; j<200-i; j++){
		 	temp.s[200-j]=0;
		}
		result = result + temp;
	}

	bool flag = 0;
	for(int i=0; i<201; i++){
		if (flag || result.s[i]!=0){
			flag = 1;
			result.length ++;
		}
	}

	return result;
}


Longint operator / (Longint x, Longint y){
	Longint result;
	if (!(x>y)) return result;
	int lx = x.length;
	int ly = y.length;
	int power = lx-ly;

	Longint remainder;

	bool flag = 0;


	while (power >= 0){
		Longint temp;
		
		if (flag){
			for (int j = 0; j<ly+1; j++){
				temp.s[200-j] = x.s[200-power-j];
			}
			temp.length = ly+1;
		}
		else{
			for (int j = 0; j<ly; j++){
				temp.s[200-j] = x.s[200-power-j];
			}
			temp.length = ly;
		}
		
		while (y>temp) {
			result.s[200-power]=0;
//			cout<<"The number on the position "<<power<<" is 0."<<endl;
			power--;
			for (int j = 0; j<lx-power; j++){
				temp.s[200-j] = x.s[200-power-j];
			}
			temp.length++;
		}	
		
		int tempresult = 0;
		while (!(y>temp)){
			temp = temp - y;
			tempresult++;
		}

		result.s[200-power]=tempresult;
//		cout<<"The number on the position "<<power<<" is "<<tempresult<<endl;
		
		remainder = temp;
		for (int i=200-power; i>=0; i--){
			x.s[i]=remainder.s[i+power];
		}
		if (remainder.length==ly) flag=1; else flag=0;
//		cout<<"x is "<<x<<endl;
		power--;
	}
	return result;
}


Longint & Longint:: operator = (const Longint x){
	is_neg = x.is_neg;
	length = x.length;
	for(int i=0; i<201; i++){
		s[i] = x.s[i];
	}
	return *this;
}


ostream & operator<< (ostream & os, const Longint x){
	if (x.is_neg==1){
		os<<'-';
	}
	bool flag = 0;
	for(int i=0; i<201; i++){
		if (flag || x.s[i]!=0){
			flag = 1;
			os<<x.s[i];
		}
	}
	if (!flag) os<<'0';
	return os;
}


int main(){
	string sx,sy;
	char op;
	getline(cin,sx);
	cin>>op; cin.get();
	getline(cin,sy);

	Longint x = Longint(sx);
	Longint y = Longint(sy);

	switch(op){
		case'+':cout<<x+y<<endl; break;
		case'-':cout<<x-y<<endl; break;
		case'*':cout<<x*y<<endl; break;
		case'/':cout<<x/y<<endl; break;
		case'>':cout<<(x>y)<<endl; break;
	}
	return 0;
}