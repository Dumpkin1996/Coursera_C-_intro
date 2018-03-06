#include <iostream>
using namespace std;

class Student{
public:
	Student (string name, int age, string id, unsigned int gpa1, unsigned int gpa2, unsigned int gpa3, unsigned int gpa4);
	void display();

private:
	string _name, _id;
	int _age;
	unsigned int _gpa1, _gpa2, _gpa3, _gpa4;
	unsigned int _gpa;
};

Student::Student (string name, int age, string id, unsigned int gpa1, unsigned int gpa2, unsigned int gpa3, unsigned int gpa4){
	_name = name;
	_age = age;
	_id = id;
	_gpa1 = gpa1;
	_gpa2 = gpa2;
	_gpa3 = gpa3;
	_gpa4 = gpa4;
	_gpa = (gpa1+gpa2+gpa3+gpa4)/4;
}

void Student::display(){
	cout<<_name<<','<<_age<<','<<_id<<','<<_gpa<<endl;
}

int main(){
	char name[50]; 
	char id[50];  
	char comma; int age;
	unsigned int gpa1, gpa2, gpa3, gpa4;
	
	cin.getline(name, 50 , ',');
	cin>>age>>comma;
	cin.getline(id, 50 , ',');
	cin>>gpa1>>comma>>gpa2>>comma>>gpa3>>comma>>gpa4;
	
	Student student = Student(name, age, id, gpa1, gpa2, gpa3, gpa4);
	student.display();
	return 0;
}