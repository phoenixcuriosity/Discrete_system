/*
Discrete_system
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
	void SETTe(unsigned int Te);
	void SETeditSizeA(unsigned int length, unsigned int height);
	void SETeditSizeB(unsigned int length, unsigned int height);
	void SETeditSizeC(unsigned int length, unsigned int height);
	void SETeditSizeD(unsigned int length, unsigned int height);
	void SETthisCoefA(unsigned int i, unsigned int j, double userValue);
	void SETthisCoefB(unsigned int i, unsigned int j, double userValue);
	void SETthisCoefC(unsigned int i, unsigned int j, double userValue);
	void SETthisCoefD(unsigned int i, unsigned int j, double userValue);
	Matrice GETA()const;
	Matrice GETB()const;
	Matrice GETC()const;
	Matrice GETD()const;
	double GETTe()const;
	

	void calculABCD(const FCTDiscret& fct);
	void simulation(const std::string& namefile, Signal& signal, Matrice& x0, double* yOut);

	std::string printOn(bool on = true)const;

	friend void testSYSETATDiscret();


private:
	Matrice _A, _B, _C, _D;
	double _Te;
};

#endif // !SYSETATDiscret_H
