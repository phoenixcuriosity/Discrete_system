#ifndef Matrice_H
#define Matrice_H

#include "LIB.h"

class Matrice{
public:
	Matrice(){};
	Matrice(unsigned int lenght, unsigned int height);
	Matrice(double** tab);
	Matrice(double** tab, unsigned int lenght, unsigned int height);
	~Matrice();

	void ones();

	void printOn();

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