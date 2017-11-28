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

	virtual void SETcoefTab(unsigned int index, double userValue) const;

	virtual unsigned int GETsize() const;
	virtual double GETcoefTab(unsigned int index) const;
	virtual unsigned int GETstringSize() const;

	virtual void grow(double);
	virtual void shrink();
	virtual void ModifPolynome(unsigned int index, double userValue);

	virtual void printOn() const; // affiche de manière textuelle

	friend void testPolynome();

protected:
	virtual double* allocate(unsigned int) const;
	virtual double* allocate(const Polynome& P) const;
	

private:
	unsigned int _size;
	double* _tab;
	mutable unsigned int _stringSize;
};





#endif // !Polynome_H
