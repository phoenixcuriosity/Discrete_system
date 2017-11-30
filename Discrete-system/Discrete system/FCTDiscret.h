#ifndef FCTDiscret_H
#define FCTDiscret_H

#include "LIB.h"
#include "Polynome.h"


class FCTDiscret{
public:
	FCTDiscret();
	FCTDiscret(Polynome&, Polynome&, double deltaT);
	~FCTDiscret();


	// virtual int& operator [] (unsigned int); 
	virtual FCTDiscret& operator = (const FCTDiscret&);
	friend bool operator ==(const FCTDiscret& a, const FCTDiscret& b);
	friend FCTDiscret operator+(const FCTDiscret&, const FCTDiscret&);
	friend FCTDiscret operator-(const FCTDiscret&, const FCTDiscret&);
	friend FCTDiscret operator*(const FCTDiscret&, const FCTDiscret&);

	FCTDiscret addition(const FCTDiscret& a, const FCTDiscret& b);
	FCTDiscret soustraction(const FCTDiscret& a, const FCTDiscret& b);
	FCTDiscret multiplication(const FCTDiscret& a, const FCTDiscret& b);

	void ModifFCT();

	void printOn() const;

	void SETnum(const Polynome &a);
	void SETden(const Polynome &a);

	Polynome GETnum() const;
	Polynome GETden() const;



	friend void testFCTDiscret();


private:
	Polynome _num;
	Polynome _den;
	double _deltaT;
};



#endif 
