/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.21

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#ifndef FCTDiscret_H
#define FCTDiscret_H

#include "LIB.h"
#include "Polynome.h"
#include "Matrice.h"
#include "Complexe.h"


class FCTDiscret{
public:
	FCTDiscret();
	FCTDiscret(double); // cast
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

	std::string printOn(bool on = true) const;

	void SETnum(const Polynome &a);
	void SETden(const Polynome &a);
	void SETdeltaT(double);
	void SETnumOrder(unsigned int order);
	void SETdenOrder(unsigned int order);
	void SETnumThisCoef(unsigned int order, double userValue);
	void SETdenThisCoef(unsigned int order, double userValue);

	Polynome GETnum() const;
	Polynome GETden() const;
	double GETdeltaT() const;

	bool tabJury();
	bool Bode(double wMin, double wMax, unsigned int nbpoint);
	friend void closeLoop(const FCTDiscret& a, const FCTDiscret& b);

	friend void testFCTDiscret();

protected:
	virtual Polynome allocate(double order) const;

private:
	Polynome _num;
	Polynome _den;
	double _deltaT;
};



#endif 
