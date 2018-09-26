#include "2DArrays.h"
#include "norms.h"
#include <iostream>
#include <cmath>

//Los métodos nuevos están al final

d2DArray::d2DArray(){
	rows=-1;
}

d2DArray::d2DArray(std::string fileName){
	std::ifstream fin;
	fin.open(fileName);
	fin >> rows >> cols;
	A=new double* [rows];
	for(int i=0; i<rows; i++){
		A[i]=new double[cols];
		for(int j=0; j<cols; j++) fin >> A[i][j];
	}
	fin.close();
}

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
	if(rows!=-1) return false;
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
    X[0]=B[0];
    X[0]/=A[0][0];
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

int d2DArray::getrows(){ return rows;}

int d2DArray::getcols(){ return cols;}

void d2DArray::print(){
	for(int i=0; i<rows; i++){
		std::cout << A[i][0];
		for(int j=1; j<cols; j++) std::cout << " " << A[i][j];
		std::cout << "\n";
	}
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

void d2DArray::addOwnRows(int i, int j,double* B, double fact){
	B[j]+=B[i]*fact;//También se altera el valor del vector objetivo
	for(int k=0; k<cols; k++) {
		double aux=fact*A[i][k];
		A[j][k]+=aux;
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

void d2DArray::swapRows(int n, int m, double* B){
	double aux1=B[n];//También se alteran las posiciones del vector objetivo
	B[n]=B[m];
	B[m]=aux1;
	double* aux=A[n];
	A[n]=A[m];
	A[m]=aux;
}

void d2DArray::swapCols(int n, int m, int* pos){
	int auxint=pos[n];//Se tiene que llevar el estado actual de las posiciones del vector solución
	pos[n]=pos[m];
	pos[m]=auxint;
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

d2DArray* d2DArray::copy(){
	d2DArray *C=new d2DArray(rows, cols);
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			(*C)[i][j]=A[i][j];
		}
	}
	return C;
}

double*& d2DArray::operator[]( int d1) { return A[d1];}

d2DArray* d2DArray::operator+(d2DArray &B){
	int r=B.getrows();
	int c=B.getcols();
	d2DArray *C=new d2DArray(r, c);
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			(*C)[i][j]=A[i][j]+B[i][j];
		}
	}
	return C;
}

d2DArray* d2DArray::operator-(d2DArray &B){
	int r=B.getrows();
	int c=B.getcols();
	d2DArray *C=new d2DArray(r, c);
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			(*C)[i][j]=A[i][j]-B[i][j];
		}
	}
	return C;
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

d2DArray* d2DArray::operator*(d2DArray &B){
	int r=B.getrows(), c=B.getcols();
	d2DArray* C=new d2DArray(rows,c);
	for(int k=0; k<c; k++){
		for(int i=0; i<cols; i++){
			double sum=0;
			for(int j=0; j<rows; j++){
				sum+=A[i][j]*B[j][k];
			}
			(*C)[i][k]=sum;
		}
	}
	return C;
}

d2DArray* d2DArray::operator*(double fact){
	d2DArray* C=new d2DArray(rows,cols);
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			(*C)[i][j]=A[i][j]*fact;
		}
	}
	return C;
}

bool d2DArray::elimGaussFea(double* B, double* X){
	for(int i=0; i<rows-1; i++){
		if(fabs(A[i][i])<1e-8) return false;//Si se encuentra un valor 0 no puede continuar
		for(int j=i+1; j<rows; j++){
			double fact=-(A[j][i]/A[i][i]);
			addOwnRows(i, j, B, fact);
		}
	}
	return solveU(B, X);
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

void d2DArray::toUpper(double* B, int* pos){
	for(int i=0; i<rows-1; i++){
		int indexR=i, indexC=i;
		double auxMax=fabs(A[i][i]);//Se calcula el máximo para reducir posibles error numéricos
		for(int k=i; k<rows; k++){
			for(int l=i; l<cols; l++){
				if(fabs(A[k][l])>auxMax){
					auxMax=fabs(A[k][l]);
					indexR=k;
					indexC=l;
				}
			}
		}
		swapRows(i, indexR, B);//Las operaciones de cambio toman en cuenta los vectores objetivo y solución
		swapCols(i, indexC, pos);
		if(fabs(A[i][i])<1e-8) break;
		for(int j=i+1; j<rows; j++){
			double fact=-(A[j][i]/A[i][i]);
			addOwnRows(i, j, B, fact);
		}
	}
}

bool d2DArray::elimGauss(double* B, double* X){
	int pos[cols];
	for(int i=0; i<cols; i++) pos[i]=i;
	toUpper(B, pos);
	double auxX[cols];
	bool ind=solveU(B, auxX);//El éxito del método depende del éxito del método solveU
	if(ind) for(int i=0; i<cols; i++) X[pos[i]]=auxX[i];
	return ind;
}

bool d2DArray::solve(double*B, double* X){//Manda a llamar al método correspondiente, no se pueden llamar individualmente
	if(form=='D') return solveD(B, X);
	if(form=='L') return solveL(B, X);
	if(form=='U') return solveU(B, X);
	if(pivoteo) return elimGauss(B, X);
	return elimGaussFea(B, X);
}

void d2DArray::setpivoteo(bool ind){pivoteo=ind;};

bool d2DArray::factLU(d2DArray&L, d2DArray& U){
	L.setShape(rows, cols);
	U.setShape(rows, cols);
	L.setform('L');
	U.setform('U');
	for(int l=0; l<rows; l++){
		double sum=0;
		for(int i=0; i<l; i++){
			for(int k=0; k<i; k++) sum+=L[i][k]*U[k][l];
			U[i][l]=A[i][l]-sum;
			L[i][l]=0.0;
		}
		sum=0;
		for(int j=0; j<l; j++){
			for(int k=0; k<j; k++) sum+=L[l][k]*U[k][j];
			L[l][j]=(A[l][j]-sum)/U[j][j];
			U[l][j]=0.0;
		}
		sum=0;
		for(int k=0; k<l; k++) sum+=L[l][k]*U[k][l];
		L[l][l]=1;
		U[l][l]=A[l][l]-sum;
		if(U[l][l]<1e-8) return false;
	}
	return true;
}

void d2DArray::transpose(){
	double aux;
	//Si la matriz tenía una forma dada también la cambia
	if(form=='L') form='U';
	else if(form=='U') form='L';
	for(int i=0; i<rows; i++){
		for(int j=0; j<i; j++){
			aux=A[i][j];
			A[i][j]=A[j][i];
			A[j][i]=aux;
		}
	}
}

bool d2DArray::choleskyFact(d2DArray& L, d2DArray& D){
	L.setShape(rows, cols);
	for(int i=0; i<rows; i++){
		L[i][i]=1; //Llena la diagonal de unos
		for(int j=0; j<i; j++){
			D[i][j]=0;
			D[j][i]=0;
			if(A[i][j]!= A[j][i] || fabs(D[j][j])<1e-8) return false; //Si la matriz no es simétrica o se divide entre 0 no se puede seguir
			else{
				L[j][i]=0;//Llena de ceros los elementos del triángulo superior
				L[i][j]=0;
				for(int k=0; k<j; k++){
					double prod;
					prod=L[i][k]*D[k][k]*L[j][k];
					L[i][j]+=prod;
				}
				L[i][j]=A[i][j]-L[i][j];
				L[i][j]/=D[j][j];
			}
		}
		D[i][i]=0;
		for(int j=0; j<i; j++){
			D[i][i]+=D[j][j]*L[i][j]*L[i][j];
		}
		D[i][i]=A[i][i]-D[i][i];
	}
	return true;
}

bool d2DArray::GaussSiedel(double*b, double*x, int iters){
	double* errorVect=new double[cols];
	double error;
	int cont=0;
	for(int i=1; i<cols; i++) x[i]=0;
	x[0]=1;
	do{
		for(int i=0; i<cols; i++){
			double sum=0;
			if(A[i][i]<1e-8) return false;
			for(int j=0; j<i; j++){
				sum+=A[i][j]*x[j];
			}
			for(int j=i+1; j<cols; j++){
				sum+=A[i][j]*x[j];
			}
			x[i]=(b[i]-sum)/A[i][i];
		}
		delete[] errorVect;
		errorVect=this->operator*(x);
		for(int i=0; i<cols; i++) errorVect[i]-=b[i];
		error=norm_2(errorVect, cols);
		cont++;
	}while(error>1e-5 && cont<iters);
	std::cout << cont << "\n";
	delete[] errorVect;
	return true;
}

bool d2DArray::Jacobi(double*b, double*x, int iters){
	double* errorVect=new double[cols];
	double error;
	int cont=0;
	double* xlast=new double[cols];
	for(int i=0; i<cols; i++) xlast[i]=0;
	xlast[cols-1]=1;
	do{
		for(int i=0; i<cols; i++){
			double sum=0;
			if(A[i][i]<1e-8) return false;
			for(int j=0; j<i; j++){
				sum+=A[i][j]*xlast[j];
			}
			for(int j=i+1; j<cols; j++){
				sum+=A[i][j]*xlast[j];
			}
			x[i]=(b[i]-sum)/A[i][i];
		}
		delete[] errorVect;
		errorVect=this->operator*(x);
		for(int i=0; i<cols; i++) errorVect[i]-=b[i];
		error=norm_2(errorVect, cols);
		double* auxPoint=xlast;
		xlast=x;
		x=auxPoint;
		cont++;
	}while(error>1e-5 && cont<iters);
	delete[] errorVect;
	return true;
}

double d2DArray::powerMax(){
	double* xlast=new double[1], *x=new double[cols];
	for(int i=0; i<cols; i++) x[i]=0;
	x[0]=1;
	double now=0;
	double last;
	do{
        double aux=0;
        for(int i=0; i<cols; i++) aux+=x[i]*x[i];
        aux=sqrt(aux);
        for(int i=0; i<cols; i++) x[i]/=aux;
		delete[] xlast;
        xlast=x;
        x=this->operator*(x);
        last=now;
        now=0;
        aux=0;
        for(int i=0; i<cols; i++){
            now+=x[i]*x[i];
            aux+=xlast[i]*x[i];
        }
        now/=aux;
    }while(fabs(now-last)>1e-5);
	delete[] x;
	delete[] xlast;
	return now;
}

double d2DArray::powerMin(){
	double* xlast=new double[cols], *x=new double[cols];
	double* xlastCopy=new double[cols];
	for(int i=0; i<cols; i++) x[i]=0;
	x[0]=1;
	double now=0;
	double last;
	do{
        double aux=0;
        for(int i=0; i<cols; i++) aux+=x[i]*x[i];
        aux=sqrt(aux);
        for(int i=0; i<cols; i++) x[i]/=aux;
		double* auxAp=xlast;
        xlast=x;
		for(int i=0; i<cols; i++)xlastCopy[i]=xlast[i];
		x=auxAp;
		d2DArray C;
		C=*(this->copy());
		C.setpivoteo(true);
        C.solve(xlastCopy, x);
		double *xans=this->operator*(x);
        last=now;
        now=0;
        aux=0;
        for(int i=0; i<cols; i++){
            now+=x[i]*x[i];
            aux+=xlast[i]*x[i];
        }
        now/=aux;
    }while(fabs(now-last)>1e-10);
	delete[] x;
	delete[] xlast;
	delete[] xlastCopy;
	return 1.0/now;
}
