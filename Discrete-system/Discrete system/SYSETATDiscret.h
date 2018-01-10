/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.20

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#ifndef SYSETATDiscret_H
#define SYSETATDiscret_H

#include "LIB.h"
#include "Matrice.h"
#include "FCTDiscret.h"
#include "Signal.h"


class SYSETATDiscret{
public:
	SYSETATDiscret();
	SYSETATDiscret(const SYSETATDiscret&);
	~SYSETATDiscret();

	friend std::ostream& operator<<(std::ostream&, const SYSETATDiscret&);
	friend bool operator ==(const SYSETATDiscret&, const SYSETATDiscret&);

	void SETA(const Matrice&);
	void SETB(const Matrice&);
	void SETC(const Matrice&);
	void SETD(const Matrice&);
	void SETTe(unsigned int);
	void SETeditSizeA(unsigned int, unsigned int);
	void SETeditSizeB(unsigned int, unsigned int);
	void SETeditSizeC(unsigned int, unsigned int);
	void SETeditSizeD(unsigned int, unsigned int);
	void SETthisCoefA(unsigned int, unsigned int, double);
	void SETthisCoefB(unsigned int, unsigned int, double);
	void SETthisCoefC(unsigned int, unsigned int, double);
	void SETthisCoefD(unsigned int, unsigned int, double);
	Matrice GETA()const;
	Matrice GETB()const;
	Matrice GETC()const;
	Matrice GETD()const;
	double GETTe()const;
	

	void calculABCD(const FCTDiscret&);
	void simulation(const std::string&, const Signal&, Matrice&);

	std::string printOn(bool on = true)const;

	friend void testSYSETATDiscret();


private:
	Matrice _A, _B, _C, _D;
	double _Te;
};

#endif // !SYSETATDiscret_H
