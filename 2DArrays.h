#ifndef D2Arrays_H
#define D2Arrays_H


class d2DArray{
private:
	double** A;
	int rows, cols;
public:
	d2DArray();
	d2DArray(int, int);
	~d2DArray();
	int getrows();
	int getcols();
	void addOwnRows(int, int, double=1);
	void addOwnCols(int, int, double=1);
	double*& operator[](int);
	d2DArray operator+(d2DArray&);
	double* operator*(double*);
};

#endif
