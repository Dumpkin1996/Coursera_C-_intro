// #include <iostream>
// #include <cstring>
// using namespace std;
// 在此处补充你的代码
class Array2{
    int size1;
    int size2; 
    int * p;       
public:
    Array2(){p=NULL;};
    Array2(int m, int n);
    Array2(Array2 & a);
    Array2 & operator = (const Array2 &);
    int * operator[] (int i);
    int operator() (int i, int j);
    ~Array2(){if (p) delete [] p;};
};

Array2::Array2(int m, int n):size1(m), size2(n){
    p = new int[m*n];
}

Array2::Array2(Array2 & a){
    if (!a.p){
        p = NULL;
        size1 = 0; size2 = 0;
        return;
    }
    p = new int[a.size1*a.size2];
    memcpy(p, a.p, sizeof(int)*a.size1*a.size2);
    size1 = a.size1; size2 = a.size2;
}
    
Array2 & Array2::operator = (const Array2 & a){
    if (a.p==p) return *this;
    if (a.p == NULL){
        if (p) delete[] p;
        p = NULL; 
        size1 = 0; size2 = 0;
        return *this;
    }
    p = new int[a.size1*a.size2];
    memcpy(p, a.p, sizeof(int)*a.size1*a.size2);
    size1 = a.size1; size2 = a.size2;
    return *this;
}

int * Array2::operator[] (int i){
    return p+i*size2;
}

int  Array2::operator() (int i, int j){
    return * (p+i*size2+j);
}

// int main() {
//     Array2 a(3,4);
//     int i,j;
//     for(  i = 0;i < 3; ++i )
//         for(  j = 0; j < 4; j ++ )
//             a[i][j] = i * 4 + j;
//     for(  i = 0;i < 3; ++i ) {
//         for(  j = 0; j < 4; j ++ ) {
//             cout << a(i,j) << ",";
//         }
//         cout << endl;
//     }
//     cout << "next" << endl;
//     Array2 b;     b = a;
//     for(  i = 0;i < 3; ++i ) {
//         for(  j = 0; j < 4; j ++ ) {
//             cout << b[i][j] << ",";
//         }
//         cout << endl;
//     }
//     return 0;
// }