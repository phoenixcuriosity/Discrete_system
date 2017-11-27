#ifndef FCTDiscret_H
#define FCTDiscret_H

#include "LIB.h"
#include "Factor.h"


class FCTDiscret{
public:
	FCTDiscret();
	FCTDiscret(Factor&, Factor&);
	~FCTDiscret();


	// virtual int& operator [] (unsigned int); 
	// virtual DynamicArray& operator = (const DynamicArray&);

	virtual void ModifFCT();

	virtual std::ostream& affichageTextuel(std::ostream&) const;

	virtual void SETnum();
	virtual void SETden();

	virtual Factor GETnum() const;
	virtual Factor GETden() const;


private:
	Factor _num;
	Factor _den;
};



#endif 
