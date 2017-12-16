/*
Discret_system
author : SAUTER Robin
2017 - 2018
version:0.17

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

	void SETA(const Matrice&);
	void SETB(const Matrice&);
	void SETC(const Matrice&);
	void SETD(const Matrice&);
	void SETnbech(unsigned int);
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
	unsigned int GETnbech()const;
	

	void calculABCD(const FCTDiscret&);
	void simulation(const std::string&);

	std::string printOn(bool on = true)const;


private:
	Matrice _A, _B, _C, _D;
	unsigned int _nbech;
};

#endif // !SYSETATDiscret_H
