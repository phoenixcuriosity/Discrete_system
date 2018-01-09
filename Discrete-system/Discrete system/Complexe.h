/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.21

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#ifndef Complexe_H
#define Complexe_H

#include "LIB.h"
#include "Polynome.h"

class Complexe{
public:
	Complexe();
	Complexe(double); // cast
	Complexe(double, double);
	~Complexe();

	Complexe& operator = (const Complexe&);
	friend bool operator ==(const Complexe& a, const Complexe& b);
	friend std::ostream& operator<<(std::ostream&, const Complexe&);
	friend Complexe operator+(const Complexe&, const Complexe&);
	friend Complexe operator-(const Complexe&, const Complexe&);
	friend Complexe operator*(const Complexe&, const Complexe&);
	friend Complexe operator/(const Complexe&, const Complexe&);


	friend double module(const Complexe&);
	friend double arg(const Complexe&);
	friend Complexe tfReIm(double module, double arg);
	Complexe power(unsigned int power);
	friend Complexe tfPolynomeComplexe(const Polynome& P, Complexe& Z);


	void SETRe(double);
	void SETIm(double);
	double GETRe()const;
	double GETIm()const;

	std::string printOn(bool on = true)const;

	friend void testComplexe();

private:
	double _Re;
	double _Im;
};




#endif