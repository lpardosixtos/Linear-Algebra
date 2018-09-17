#ifndef D2Arrays_H
#define D2Arrays_H
#include <utility>

class d2DArray{
private:
	double** A;
	int rows, cols;
	char form='0'; //Guarda si la matriz es diagonal, TSUP, TINF
	bool solveD(double*, double*);//Resuelve el sistema si la matriz es diagonal
	bool solveL(double*, double*);//Resuelve el sistema si la matriz es triangular inferior
	bool solveU(double*, double*);//Resuelve el sistema si la matriz es triangular superior
	bool pivoteo;//Indica si se va a pivotear para la eliminación Gaussiana
public:
	d2DArray();
	d2DArray(int, int);//Constructor con dimensiones
	d2DArray(int, int, char);//Constructor con dimensiones y forma
	bool setShape(int, int);//Establece las dimensiones de una matriz sin dimensiones
	~d2DArray();//Destructor, borra la memoria creada, no solo los punteros
	void setform(char);//Cambia el parámetro form
	char getform();//Devuelve el parámetro form
	int getrows();//Devuelve el parámetro rows
	int getcols();//Devuelve el parámetro cols
	void addOwnRows(int, int, double=1);//Suma un renglón multiplicado por un factor a otro renglón
	void addOwnCols(int, int, double=1);//Suma una columna multiplicada por un factor a otra columna
	void addOwnRows(int, int, double*, double=1);//Suma un renglón multiplicado por un factor a otro renglón, en la matriz extendida
	void swapRows(int, int);//Intercambia dos renglones
	void swapCols(int, int);//Intercambia dos columnas
	void swapRows(int, int, double*);//Intercambia dos renglones de la matr	iz extendida
	void swapCols(int, int, int*);//Intercambia dos columnas de la matriz extendida, guarda los cambios del vector solución
	void multRow(int, double);//Multiplica un renglón por un factor
	void multCol(int, double);//Multiplica una columna por un factor
	d2DArray* copy();//Crea una copia de esta matriz
	double*& operator[](int);//Accede a los elementos de la matriz
	d2DArray* operator+(d2DArray&);
	d2DArray* operator-(d2DArray&);
	double* operator*(double*);//Multiplicación por vector
	d2DArray* operator*(d2DArray&);
	d2DArray* operator*(double);
	bool elimGaussFea(double*, double*);//Eliminación Gaussiana sin pivoteo
	void toUpper();//Convierte a matriz triangular superior
	void toUpper(double*, int*);//Convierte la matriz extendida a triangular superior
	bool elimGauss(double*, double*);//Eliminación Gaussiana con pivoteo
	bool solve(double*, double*);//Resuelve el sistema, internamente depende del tipo
	void setpivoteo(bool);//Cambia el valor pivoteo
	void transpose();
	bool choleskyFact(d2DArray&, d2DArray&);

};

#endif
