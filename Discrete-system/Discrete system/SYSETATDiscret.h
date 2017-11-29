#ifndef SYSETATDiscret_H
#define SYSETATDiscret_H

#include "LIB.h"
#include "Matrice.h"


class SYSETATDiscret{
public:
	SYSETATDiscret();
	SYSETATDiscret(Matrice&, Matrice&, Matrice&);
	SYSETATDiscret(Matrice&, Matrice&, Matrice&, double);
	SYSETATDiscret(Matrice&, Matrice&, Matrice&, Matrice&, double, double[]);
	~SYSETATDiscret();


protected:
	virtual double* allocate(unsigned int) const;
	virtual double* allocate(const double*) const;


private:
	Matrice _A, _B, _C, _D;
	double _deltaT;
	double* _x;
};

#endif // !SYSETATDiscret_H
