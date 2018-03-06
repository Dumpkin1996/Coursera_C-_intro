#include <iostream>
using namespace std;

template<class T>  
class CArray3D  
{  
private:  
    T *** _array;  
    int _r,_c,_l;  
public:  
    CArray3D(int r, int c, int l)  
    {  
        _array = new T **[r];  
        for(int i = 0;i<r; i++)    
        {    
            _array[i] = new T*[c];    
        }    
        for(int i = 0;i<r; i++)    
        {    
            for(int j=0; j<c; j++)  
            {  
                _array[i][j] = new T[l];      
            }    
        }  
        _r = r; _c = c; _l = l;  
    }  
      
    int ** operator[] (int index)   
    {    
        return _array[index];    
    }   
      
}; 



// int main()
// {
//     CArray3D<int> a(3,4,5);
//     int No = 0;
//     for( int i = 0; i < 3; ++ i )
//         for( int j = 0; j < 4; ++j )
//             for( int k = 0; k < 5; ++k )
//                 a[i][j][k] = No ++;
//     for( int i = 0; i < 3; ++ i )
//         for( int j = 0; j < 4; ++j )
//             for( int k = 0; k < 5; ++k )
//                 cout << a[i][j][k] << ",";
//     return 0;
// }