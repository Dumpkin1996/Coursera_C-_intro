//#include <iostream>
//using namespace std;
//class Sample{
//public:
//    int v;
//    Sample(int n):v(n) { }
// 在此处补充你的代码
    Sample (Sample & x):v(2*x.v) {}
//};
//int main() {
//    Sample a(5);
//    Sample b = a;
//    cout << b.v;
//    return 0;
//}