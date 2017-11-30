#ifndef Polynome_H
#define Polynome_H

#include "LIB.h"

class Polynome {
public:
	Polynome();
	Polynome(unsigned int size);
	Polynome(unsigned int size, double tab[]);
	Polynome(const Polynome& P);
	~Polynome();


	Polynome& operator=(const Polynome&);
	double operator[](unsigned int index);
	friend bool operator==(const Polynome&, const Polynome&);
	friend Polynome operator+(const Polynome&, const Polynome&);
	friend Polynome operator-(const Polynome&, const Polynome&);
	friend Polynome operator*(const Polynome&, const Polynome&);
	
	void SETcoefTab(unsigned int index, double userValue);

	unsigned int GETsize() const;
	double GETcoefTab(unsigned int index) const;
	unsigned int GETstringSize() const;

	Polynome addition(const Polynome& a, const Polynome& b);
	Polynome soustraction(const Polynome& a, const Polynome& b);
	Polynome multiplication(const Polynome& a, const Polynome& b);
	void grow(double);
	void shrink();
	void ModifPolynome(unsigned int index, double userValue);

	void printOn() const;

	friend void testPolynome();
	

protected:
	virtual double* allocate(unsigned int) const;
	virtual double* allocate(unsigned int, double*) const;
	virtual double* allocate(const Polynome& P) const;
	

private:
	unsigned int _size;
	double* _tab;
	mutable unsigned int _stringSize;
};









template<class T>
T max(const T a, const T b){
	return (a>b) ? a : b;
}

template<class T>
T min(const T a, const T b){
	return (a<b) ? a : b;
}

#endif // !Polynome_H
