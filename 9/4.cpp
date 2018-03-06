#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

string ss[21];

int getint(string & s);
string getstring(string & s);
int find(string & rest);
int rfind(string & rest);
string copy(string & rest);
string add(string & rest);

int getint(string & s){
	int pos = s.find(' ');
	if (pos==string::npos) return atoi(s.c_str());
	else{
		string func = s.substr(0, pos);
		s = s.substr(pos+1);
		if (func=="find") return find(s);
		if (func=="rfind") return rfind(s);
		else return atoi(func.c_str());
	}
}

string getstring(string & s){
	int pos = s.find(' ');
	if (pos==string::npos) return s;
	else{
		string func = s.substr(0, pos);
		s = s.substr(pos+1);
		if (func=="copy") return copy(s);
		if (func=="add") return add(s);
		else return func;
	}
}

bool isnumber(string s){
	int l = s.length();
	if (l>5) return false;
	else{
		for (int i=0; i<l; i++)
			if ( s[i]-(int)('0')<0 || s[i]-(int)('0')>9 )
				return false;
	}
	return true;
}

int find(string & rest){
	string s = getstring(rest);
	int n = getint(rest);
	int result = ss[n].find(s);
	if (result==string::npos) return s.length();
	else return result;
}

int rfind(string & rest){
	string s = getstring(rest);
	int n = getint(rest);
	int result = ss[n].rfind(s);
	if (result==string::npos) return s.length();
	else return result;
}

string copy(string & rest){
	int n = getint(rest);
	int x = getint(rest);
	int l = getint(rest);
	return ss[n].substr(x, l);
}

string add(string & rest){
	string s1 = getstring(rest);
	string s2 = getstring(rest);
	if (isnumber(s1) && isnumber(s2))
		return to_string(atoi(s1.c_str())+atoi(s2.c_str()));
	return s1+s2;
}

void insert(string & rest){
	string s = getstring(rest);
	int n = getint(rest);
	int x = getint(rest);
	ss[n].insert(x, s);
}

void reset(string & rest){
	string s = getstring(rest);
	int n = getint(rest);
	ss[n] = s;
}

void print(string & rest){
	int n = getint(rest);
	cout<<ss[n]<<endl;
}

int main(){
	int n; cin>>n;
	for (int i=1; i<n+1; i++) cin>>ss[i];

	while (true){
		string command; getline(cin,command);

		if (command == "printall") for (int i=1; i<n+1; i++) cout<<ss[i]<<endl;
		
		if (command == "over")  break;

		else{
			int pos = command.find(' ');
			string func = command.substr(0, pos);
			string rest = command.substr(pos+1);
			if (func=="find") find(rest);
			if (func=="rfind") rfind(rest);
			if (func=="copy") copy(rest);
			if (func=="add") add(rest);
			if (func=="insert") insert(rest);
			if (func=="reset") reset(rest);
			if (func=="print") print(rest);

		}
	}
	return 0;
}