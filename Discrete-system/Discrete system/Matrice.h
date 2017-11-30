#ifndef Matrice_H
#define Matrice_H

#include "LIB.h"

class Matrice{
public:
	Matrice(){};
	Matrice(unsigned int lenght, unsigned int height);
	Matrice(double** tab, unsigned int lenght, unsigned int height);
	Matrice(const Matrice& M);
	~Matrice();
	
	void SETthiscoef(unsigned int, unsigned int, double);
	double GETthiscoef(unsigned int, unsigned int)const;

	void ones();

	void printOn()const;

	friend void testMatrice();

protected:
	virtual double** allocate(unsigned int, unsigned int) const;
	virtual double** allocate(const Matrice&) const;

private:
	unsigned int _lenght;
	unsigned int _height;
	double** _tab;
};


#endif