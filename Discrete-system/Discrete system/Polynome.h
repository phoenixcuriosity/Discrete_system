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


	Polynome& operator=(const Polynome&);
	friend bool operator==(const Polynome&, const Polynome&);
	friend Polynome operator+(const Polynome&, const Polynome&);
	friend Polynome operator-(const Polynome&, const Polynome&);
	friend Polynome operator*(const Polynome&, const Polynome&);
	
	virtual void SETcoefTab(unsigned int index, double userValue);

	virtual unsigned int GETsize() const;
	virtual double GETcoefTab(unsigned int index) const;
	virtual unsigned int GETstringSize() const;

	virtual Polynome addition(const Polynome& a, const Polynome& b);
	virtual Polynome soustraction(const Polynome& a, const Polynome& b);
	virtual Polynome multiplication(const Polynome& a, const Polynome& b);
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









template<class T>
T max(const T a, const T b){
	return (a>b) ? a : b;
}

template<class T>
T min(const T a, const T b){
	return (a<b) ? a : b;
}

#endif // !Polynome_H
