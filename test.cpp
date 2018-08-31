#include <iostream>
#include "2DArrays.h"

using namespace std;

int main(){
    int rows, cols;
    cin >> rows >> cols;
    d2DArray A(rows, cols);
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            A[i][j]=1;
        }
    }
    d2DArray B(rows, cols);

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            B[i][j]=-j;
        }
    }
    double v[cols];
    for(int i=0; i<cols; i++) v[i]=1;
    double* prod=A*v;
    for(int i=0; i<rows; i++){
        cout <<v[i] << " " << prod[i] << "\n";
    }
    /*d2DArray D=A+B;
    
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            cout << D[i][j] << " " ;
        }
        cout << "\n";
    }
    */




    return 0;
}
