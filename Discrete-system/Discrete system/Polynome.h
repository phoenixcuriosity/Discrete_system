/*
Discrete_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.31

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#ifndef Polynome_H
#define Polynome_H

#include "LIB.h"

class Polynome {
public:
	Polynome();
	Polynome(unsigned int order); // attention : Polynome a((unsigned int)2) est la seule fa�on de cr�er un polynome d'ordre 2
	Polynome(double userValue); // cast
	Polynome(unsigned int order, double tab[]);
	Polynome(const Polynome& P);
	~Polynome();

	Polynome& operator=(const Polynome&);
	double operator[](unsigned int index);
	friend std::ostream& operator<<(std::ostream& os, const Polynome&);
	friend bool operator==(const Polynome&, const Polynome&);
	friend Polynome operator+(const Polynome&, const Polynome&);
	friend Polynome operator-(const Polynome&, const Polynome&);
	friend Polynome operator*(const Polynome&, const Polynome&);

	void SETorder(unsigned int order);
	void SETcoefTab(unsigned int index, double userValue);

	unsigned int GETorder() const;
	double GETcoefTab(unsigned int index) const;
	unsigned int GETstringSize() const;

	friend Polynome addition(const Polynome& a, const Polynome& b);
	friend Polynome soustraction(const Polynome& a, const Polynome& b);
	friend Polynome multiplication(const Polynome& a, const Polynome& b);
	
	void grow(double userValue);
	std::string printOn(bool = true) const;

	friend void testPolynome();
	

protected:
	virtual double* allocate(unsigned int size) const;
	virtual double* allocate(unsigned int size, double userValue) const;
	virtual double* allocate(unsigned int size, double* tab) const;
	virtual double* allocate(const Polynome& P) const;

	bool assertIndex(unsigned int index) const;
private:
	unsigned int _order;
	double* _tab;
	mutable unsigned int _stringSize;
};


template<class T>
T max(const T a, const T b){
	return (a>b) ? a : b;
}

template<class T>
T min(const T a, const T b){
	return (a<b) ? a : b;
}



#endif // !Polynome_H
