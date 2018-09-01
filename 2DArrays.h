#ifndef D2Arrays_H
#define D2Arrays_H
#include <utility>

class d2DArray{
private:
	double** A;
	int rows, cols;
	char form='0';
	bool solveD(double*, double*);
	bool solveL(double*, double*);
	bool solveU(double*, double*);
public:
	d2DArray();
	d2DArray(int, int);
	d2DArray(int, int, char);
	bool setShape(int, int);
	~d2DArray();
	void setform(char);
	char getform();
	int getrows();
	int getcols();
	void addOwnRows(int, int, double=1);
	void addOwnCols(int, int, double=1);
	void swapRows(int, int);
	void swapCols(int, int);
	void multRow(int, double);
	void multCol(int, double);
	d2DArray copy();
	double*& operator[](int);
	d2DArray operator+(d2DArray&);
	d2DArray operator-(d2DArray&);
	double* operator*(double*);
	d2DArray operator*(d2DArray&);
	d2DArray operator*(double);
	bool elimGaussFea();
	void toUpper();
	bool elimGauss(double*, double*);
	bool solve(double*, double*);

};

#endif
