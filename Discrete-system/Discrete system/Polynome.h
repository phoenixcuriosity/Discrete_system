#ifndef Polynome_H
#define Polynome_H

#include "LIB.h"

class Polynome {
public:
	Polynome() {};
	Polynome(unsigned int size);
	Polynome(unsigned int size, double tab[]);
	Polynome(const Polynome& P);
	~Polynome();

	virtual void SETsize(unsigned int size);
	virtual void SETtab(double tab[]);
	virtual void SETcoefTab(unsigned int index, double userValue) const;

	virtual unsigned int GETsize() const;
	//virtual double* GETtab() const;
	virtual double GETcoefTab(unsigned int index) const;

	virtual void ModifPolynome(unsigned int coef, double userValue);

	friend void testPolynome();

protected:
	virtual double* allocate(unsigned int) const;
	virtual double* allocate(const Polynome& P) const;
	

private:
	unsigned int _size;
	double* _tab;
};





#endif // !Polynome_H
