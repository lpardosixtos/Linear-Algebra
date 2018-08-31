#include "2Darrays.h"
#include <iostream>

d2DArray::d2DArray(){};

d2DArray::d2DArray(int r, int c){
	rows=r;
	cols=c;
	A=new double* [r];
	for(int i=0; i<r; i++) A[i]=new double[c];
}
d2DArray::~d2DArray(){
	for(int i=0; i<rows; i++) delete[] A[i];
	delete[] A;
}
double*& d2DArray::operator[]( int d1) { return A[d1];}

int d2DArray::getrows(){ return rows;}

int d2DArray::getcols(){ return cols;}

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

void d2DArray::addOwnRows(int i, int j, double fact){ for(int k=0; k<cols; k++) A[j][k]+=fact*A[i][k]; }
void d2DArray::addOwnCols(int i, int j, double fact){ for(int k=0; j<rows; k++) A[k][j]+=fact*A[i][k]; }

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

