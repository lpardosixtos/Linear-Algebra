#include "2Darrays.h"
#include <iostream>
#include <cmath>

d2DArray::d2DArray(){}

d2DArray::d2DArray(int r, int c){
	rows=r;
	cols=c;
	A=new double* [r];
	for(int i=0; i<r; i++) A[i]=new double[c];
}
d2DArray::d2DArray(int r, int c, char f){
	rows=r;
	cols=c;
	A=new double* [r];
	for(int i=0; i<r; i++) A[i]=new double[c];
	form=f;
}

bool d2DArray::setShape(int r, int c){
	if(rows==-1) return false;
	rows=r;
	cols=c;
	A=new double* [r];
	for(int i=0; i<r; i++) A[i]=new double[c];
	return true;
}

d2DArray::~d2DArray(){
	for(int i=0; i<rows; i++) delete[] A[i];
	delete[] A;
}

bool d2DArray::solveD(double* B, double* X){
	bool aux=false;
	for(int i=0; i<rows; i++){
        if(fabs(A[i][i])<1e-8) return false;
        X[i]=B[i]/A[i][i];
    }
    return true;
}

bool d2DArray::solveL(double *B, double*X){
	if(fabs(A[0][0])<1e-8) return false;
    X[0]=B[0]/A[0][0];
    for(int i=1; i<rows; i++){
        if(fabs(A[i][i])<1e-8) return false;
        X[i]=B[i];
        double aux=0;
        for(int j=0; j<i; j++){
            aux+=A[i][j]*X[j];
        }
        X[i]-=aux;
        X[i]/=A[i][i];
    }
    return true;
}

bool d2DArray::solveU(double *B, double*X){
	if(fabs(A[rows-1][cols-1])<1e-8) return false;
    X[cols-1]=B[rows-1]/A[rows-1][cols-1];
    for(int i=cols-2; i>=0; i--){
        if(fabs(A[i][i])<1e-8) return false;
        X[i]=B[i];
        double aux=0;
        for(int j=cols-1; j>i; j--){
            aux+=A[i][j]*X[j];
        }
        X[i]-=aux;
        X[i]/=A[i][i];
    }
    return true;
}

void d2DArray::setform(char f){ form=f;}

char d2DArray::getform(){return form;}

double*& d2DArray::operator[]( int d1) { return A[d1];}

int d2DArray::getrows(){ return rows;}

int d2DArray::getcols(){ return cols;}

d2DArray d2DArray::copy(){
	d2DArray *C=new d2DArray(rows, cols);
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			(*C)[i][j]=A[i][j];
		}
	}
	return *C;
}

d2DArray d2DArray::operator+(d2DArray &B){
	int r=B.getrows();
	int c=B.getcols();
	d2DArray *C=new d2DArray(r, c);
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			(*C)[i][j]=A[i][j]+B[i][j];
		}
	}
	return *C;
}

d2DArray d2DArray::operator-(d2DArray &B){
	int r=B.getrows();
	int c=B.getcols();
	d2DArray *C=new d2DArray(r, c);
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			(*C)[i][j]=A[i][j]-B[i][j];
		}
	}
	return *C;
}

double* d2DArray::operator*(double* v){
	double *aux=new double[cols];
	for(int i=0; i<cols; i++) aux[i]=0;
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			aux[i]+=v[j]*A[i][j];
		}
	}
	return aux;
}

d2DArray d2DArray::operator*(d2DArray &B){
	int r=B.getrows(), c=B.getcols();
	d2DArray* C=new d2DArray(rows,c);
	for(int k=0; k<c; k++){
		for(int i=0; i<c; i++) (*C)[i][k]=0;
		for(int i=0; i<rows; i++){
			for(int j=0; j<cols; j++){
				(*C)[i][k]+=B[k][j]*A[i][k];
			}
		}
	}
	return *C;
}

void d2DArray::addOwnRows(int i, int j, double fact){ 
	for(int k=0; k<cols; k++) {
		double aux=fact*A[i][k];
		A[j][k]+=aux; 
	}
}
void d2DArray::addOwnCols(int i, int j, double fact){ 
	for(int k=0; k<rows; k++){
		double aux=fact*A[k][i];
		A[k][j]+=aux; 
	}
}

void d2DArray::swapRows(int n, int m){
	double* aux=A[n];
	A[n]=A[m];
	A[m]=aux;
}

void d2DArray::swapCols(int n, int m){
	double aux;
	for(int i=0; i<rows; i++){
		aux=A[i][n];
		A[i][n]=A[i][m];
		A[i][m]=aux;
	}
}

void d2DArray::multRow(int n, double fact){
	for(int i=0; i<cols; i++){
		A[n][i]*=fact;
	}
}
void d2DArray::multCol(int n, double fact){
	for(int i=0; i<rows; i++){
		A[i][n]*=fact;
	}
}
d2DArray d2DArray::operator*(double fact){
	d2DArray* C=new d2DArray(rows,cols);
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			(*C)[i][j]=A[i][j]*fact;
		}
	}
	return *C;
}

bool d2DArray::elimGaussFea(){
	for(int i=0; i<rows-1; i++){
		if(fabs(A[i][i])<1e-8) return false;
		for(int j=i+1; j<rows; j++){
			double fact=-(A[j][i]/A[i][i]);
			addOwnRows(i, j, fact);
		}
	}
	return true;
}

void d2DArray::toUpper(){
	for(int i=0; i<rows-1; i++){
		int indexR=i, indexC=i;
		double auxMax=fabs(A[i][i]);
		for(int k=i; k<rows; k++){
			for(int l=i; l<cols; l++){
				if(fabs(A[k][l])>auxMax){
					auxMax=fabs(A[k][l]);
					indexR=k;
					indexC=l;
				}
			}
		}
		swapRows(i, indexR);
		swapCols(i, indexC);
		if(fabs(A[i][i])<1e-8) break;
		for(int j=i+1; j<rows; j++){
			double fact=-(A[j][i]/A[i][i]);
			addOwnRows(i, j, fact);
		
		}
	}
}

bool d2DArray::elimGauss(double* B, double* X){
	toUpper();
	bool ind=solveU(B, X);
	return ind;
}

bool d2DArray::solve(double*B, double* X){
	if(form=='D') return solveD(B, X);
	if(form=='L') return solveL(B, X);
	if(form=='U') return solveU(B, X);
	return elimGauss(B, X);
}
