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

	virtual void ModifFCT();

	virtual void affichageTextuel() const;

	virtual void SETnum();
	virtual void SETden();

	virtual Polynome GETnum() const;
	virtual Polynome GETden() const;


	friend void testFCTDiscret();


private:
	Polynome _num;
	Polynome _den;
	double _deltaT;
};



#endif 
