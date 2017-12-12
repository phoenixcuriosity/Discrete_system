#ifndef FCTDiscret_H
#define FCTDiscret_H

#include "LIB.h"
#include "Polynome.h"


class FCTDiscret{
public:
	FCTDiscret();
	FCTDiscret(Polynome&, Polynome&, double deltaT);
	FCTDiscret(const FCTDiscret&);
	~FCTDiscret();


	virtual FCTDiscret& operator = (const FCTDiscret&);
	friend bool operator ==(const FCTDiscret& a, const FCTDiscret& b);
	friend std::ostream& operator<<(std::ostream&, const FCTDiscret&);
	friend FCTDiscret operator+(const FCTDiscret&, const FCTDiscret&);
	friend FCTDiscret operator-(const FCTDiscret&, const FCTDiscret&);
	friend FCTDiscret operator*(const FCTDiscret&, const FCTDiscret&);

	friend FCTDiscret addition(const FCTDiscret& a, const FCTDiscret& b);
	friend FCTDiscret soustraction(const FCTDiscret& a, const FCTDiscret& b);
	friend FCTDiscret multiplication(const FCTDiscret& a, const FCTDiscret& b);

	void ModifFCT();

	std::string printOn(bool on = true) const;

	void SETnum(const Polynome &a);
	void SETden(const Polynome &a);
	void SETdeltaT(double);
	void SETnumOrder(unsigned int);
	void SETdenOrder(unsigned int);
	void SETnumThisCoef(unsigned int, double);
	void SETdenThisCoef(unsigned int, double);

	Polynome GETnum() const;
	Polynome GETden() const;
	double GETdeltaT() const;


	friend void testFCTDiscret();


private:
	Polynome _num;
	Polynome _den;
	double _deltaT;
};



#endif 
