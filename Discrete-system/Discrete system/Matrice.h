#ifndef Matrice_H
#define Matrice_H

#include "LIB.h"

class Matrice{
public:
	Matrice();
	Matrice(double); // cast
	Matrice(unsigned int lenght, unsigned int height);
	Matrice(double** tab, unsigned int length, unsigned int height);
	Matrice(const Matrice& M);
	~Matrice();
	
	Matrice& operator=(const Matrice&);
	friend bool operator==(const Matrice&, const Matrice&);
	friend std::ostream& operator<<(std::ostream&, const Matrice&);
	friend Matrice operator+(const Matrice&, const Matrice&);
	friend Matrice operator-(const Matrice&, const Matrice&);
	friend Matrice operator*(const Matrice&, const Matrice&);
	friend Matrice operator*(double, const Matrice&);


	void SETthiscoef(unsigned int, unsigned int, double);
	double GETthiscoef(unsigned int, unsigned int)const;
	unsigned int GETlength()const;
	unsigned int GETheight()const;
	unsigned int GETstringSize() const;

	friend Matrice addition(const Matrice&, const Matrice&);
	friend Matrice soustraction(const Matrice&, const Matrice&);
	friend Matrice multiplication(const Matrice&, const Matrice&);
	friend Matrice multiplication(double, const Matrice&);

	friend Matrice transposistion(const Matrice&);
	void ones();
	void editsize(unsigned int, unsigned int);

	std::string printOn(bool on = true)const;

	friend void testMatrice();

protected:
	virtual double** allocate(unsigned int, unsigned int) const;
	virtual double** allocate(const Matrice&) const;

	bool assertIndex(unsigned int, unsigned int)const;
	friend bool assertSize(unsigned int, unsigned int, unsigned int, unsigned int);
private:
	unsigned int _length;
	unsigned int _height;
	double** _tab;
	mutable unsigned int _stringSize;
};


#endif