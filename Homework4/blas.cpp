#include <iostream>
#include <cmath>
#include "blas.h"

int amax(const double* x, const unsigned int size) {
	int length = size;
	double max_value = 0;
	int element = 0;
	if (length == 0) {
		return -1;
	}
	for (int i = 0; i < length; i++) {
		if (abs(x[i]) > max_value) {
			max_value = abs(x[i]);
			element = i;
		}else{
			continue;
		}
	}
	return element;
}

double asum(const double* x, const unsigned int size) {
	int length = size;
	double sum = 0;
	for (int i = 0; i < length; i++) {
		sum += abs(x[i]);
	}
	return sum;
}

void axpy(const double a, const double* x, double* y, const unsigned int size) {
	int length = size;
  for (int i = 0; i < length; i++) {
		y[i] = a*x[i] + y[i];
	}
}

void copy(const double* src, double* dest, const unsigned int size) {
	int length = size;
  for (int i = 0; i < length; i++) {
		dest[i] = src[i];
	}
}

double dot(const double* x, const double* y, const unsigned int size) {
	int length = size;
	double sum = 0;
	for (int i = 0; i < length; i++) {
		sum += (x[i]*y[i]);
	}
    return sum;
}

double norm2(const double* x, const unsigned int size) {
	int length = size;
	double norm = 0;
	for (int i = 0; i < length; i++) {
		norm += pow(x[i],2);
	}
	norm = sqrt(norm);
  return norm;
}

void scale(const double a, double* x, const unsigned int size) {
	int length = size;
  for (int i = 0; i < length; i++) {
		x[i] *= a;
	}
}

void swap(double* x, double* y, const unsigned int size) {
	int length = size;
  double x_component = 0;
	double y_component = 0;
	for (int i = 0; i < length; i++) {
		x_component = x[i];
		y_component = y[i];
		x[i] = y_component;
		y[i] = x_component;
	}
}