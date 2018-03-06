// #include <iostream>
// using namespace std;
// 在此处补充你的代码
class CType{
public:
    int x;
    CType():x(0){}
    CType(int i):x(i){}
    void setvalue(int i){x=i;}
    CType operator++(int){
        CType tmp(*this); 
        x = x*x;
        return tmp;
    }
};

ostream & operator<<(ostream & o, const CType & c){
    o<<c.x;
    return o;
}

// int main(int argc, char* argv[]) {
//         CType obj;
//         int n;
//         cin>>n;
//         while ( n ) {
//                 obj.setvalue(n);
//                 cout<<obj++<<" "<<obj<<endl;
//                 cin>>n;
//         }
//         return 0;
// }