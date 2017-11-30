#include "SYSETATDiscret.h"

using namespace std;

SYSETATDiscret::SYSETATDiscret()
: _A(), _B(), _C(), _D(0), _deltaT(1), _x(allocate(2))
{
}
SYSETATDiscret::SYSETATDiscret(const SYSETATDiscret& a)
: _A(a._A), _B(a._B), _C(a._C), _D(a._D), _deltaT(a._deltaT), _x(allocate(a._x))
{
}
SYSETATDiscret::~SYSETATDiscret()
{
}


double* SYSETATDiscret::allocate(unsigned int size) const {
	/*
	alloue un tableau de taille size de type double initialisé à 0
	*/
	double* buffer = new double[size];
	for (unsigned int i = 0; i < size; i++)
		buffer[i] = 0;
	return buffer;
}
double* SYSETATDiscret::allocate(const double* P) const {
	double* buffer = new double[2];
	for (unsigned int i = 0; i < 2; i++)
		buffer[i] = P[i];
	return buffer;
}



void calculx();