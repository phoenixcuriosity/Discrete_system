#ifndef FCTDiscret_H
#define FCTDiscret_H

#include "LIB.h"
#include "Polynome.h"


class FCTDiscret{
public:
	FCTDiscret();
	FCTDiscret(Polynome&, Polynome&);
	~FCTDiscret();


	// virtual int& operator [] (unsigned int); 
	// virtual DynamicArray& operator = (const DynamicArray&);

	virtual void ModifFCT();

	virtual void affichageTextuel() const;

	virtual void SETnum();
	virtual void SETden();

	virtual Polynome GETnum() const;
	virtual Polynome GETden() const;


private:
	Polynome _num;
	Polynome _den;
	double _deltaT;
};



#endif 
