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

	virtual FCTDiscret addition(const FCTDiscret& a, const FCTDiscret& b);
	virtual FCTDiscret soustraction(const FCTDiscret& a, const FCTDiscret& b);
	virtual FCTDiscret multiplication(const FCTDiscret& a, const FCTDiscret& b);

	virtual void ModifFCT();

	virtual void affichageTextuel() const;

	virtual void SETnum(const Polynome &a);
	virtual void SETden(const Polynome &a);

	virtual Polynome GETnum() const;
	virtual Polynome GETden() const;



	friend void testFCTDiscret();


private:
	Polynome _num;
	Polynome _den;
	double _deltaT;
};



#endif 
