/*
Discrete_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:2.8

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#ifndef FCTDiscret_H
#define FCTDiscret_H

#include "LIB.h"

//#ifndef IHM_H
//#include "IHM.h"
//#endif

#include "Polynome.h"
#include "Matrice.h"
#include "Complexe.h"


class FCTDiscret{
public:
	FCTDiscret();
	FCTDiscret(double); // cast
	FCTDiscret(Polynome& num, Polynome& den, double deltaT);
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

	const std::string printOn(bool on = true) const;

	void SETjury(const Matrice& J);
	void SETnum(const Polynome &a);
	void SETden(const Polynome &a);
	void SETdeltaT(double);
	void SETnumOrder(unsigned int order);
	void SETdenOrder(unsigned int order);
	void SETnumThisCoef(unsigned int order, double userValue);
	void SETdenThisCoef(unsigned int order, double userValue);

	Matrice GETjury()const;
	Polynome GETnum() const;
	Polynome GETden() const;
	double GETdeltaT() const;

	void interg(); // modification de la fonction de transfert pour correspondre à un intégrateur
	void secondOrdre();// modification de la fonction de transfert pour correspondre à un second ordre

	bool tabJury();
	bool Bode(double wMin, double wMax, unsigned int nbpoint, double** gainPhase);
	friend void closeLoop(const FCTDiscret& openLoop, const FCTDiscret& returnLoop);

	friend void testFCTDiscret();

protected:
	virtual Polynome allocate(double order) const;

private:
	Matrice _jury;
	Polynome _num;
	Polynome _den;
	double _deltaT;
};



#endif 
