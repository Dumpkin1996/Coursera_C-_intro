// #include <iostream>
// #include <set>
// #include <iterator>
// #include <algorithm>
// using namespace std;
// 在此处补充你的代码
class A{
public:
        int age;
        char type;
        A(int i):age(i){type='A';}
};

class B: public A{
public:
        B(int i):A(i){type='B';}
};

class Comp{
public:
        bool operator()(const A * p1, const A* p2){
                return p1->age<p2->age;
        }
};

void Print(A* p){
        cout<<p->type<<' '<<p->age<<endl;
}


// int main()
// {

//         int t;
//         cin >> t;
//         set<A*,Comp> ct;
//         while( t -- ) {
//                 int n;
//                 cin >> n;
//                 ct.clear();
//                 for( int i = 0;i < n; ++i)	{
//                         char c; int k;
//                         cin >> c >> k;

//                         if( c == 'A')
//                                 ct.insert(new A(k));
//                         else
//                                 ct.insert(new B(k));
//                 }
//                 for_each(ct.begin(),ct.end(),Print);
//                 cout << "****" << endl;
//         }
// }