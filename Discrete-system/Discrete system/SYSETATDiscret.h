#ifndef SYSETATDiscret_H
#define SYSETATDiscret_H

#include "LIB.h"
#include "Matrice.h"
#include "Vecteur.h"


class SYSETATDiscret{
public:
	SYSETATDiscret() {};
	SYSETATDiscret(const SYSETATDiscret&);
	~SYSETATDiscret();


	void calculx();

protected:
	virtual double* allocate(unsigned int) const;
	virtual double* allocate(const double*) const;


private:
	Matrice _A;
	Vecteur _B, _C;
	double _D;
	double _deltaT;
	double* _x;
};

#endif // !SYSETATDiscret_H
