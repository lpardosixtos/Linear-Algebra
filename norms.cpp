#include "norms.h"
#include <cmath>
#include <algorithm>

double norm_1(double* B, int sz){
	double sum=0.0;
	for(int i=0; i<sz; i++){
		sum+=fabs(B[i]);
	}
	return sum;
}

double norm_2(double* B, int sz){
	double sum=0;
	for(int i=0; i<sz; i++){
		sum+=B[i]*B[i];
	}
	return sqrt(sum);
}

double norm_inf(double*B, int sz){
	double maxi=0;
	for(int i=0; i<sz; i++){
		maxi=std::max(fabs(B[i]), maxi);
	}
	return maxi;
}
