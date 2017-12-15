/*
Discret_system
author : SAUTER Robin
2017 - 2018
version:0.16

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#ifndef Polynome_H
#define Polynome_H

#include "LIB.h"

class Polynome {
public:
	Polynome();
	Polynome(unsigned int);
	Polynome(unsigned int, double tab[]);
	Polynome(const Polynome& P);
	~Polynome();

	Polynome& operator=(const Polynome&);
	double operator[](unsigned int index);
	friend std::ostream& operator<<(std::ostream& os, const Polynome&);
	friend bool operator==(const Polynome&, const Polynome&);
	friend Polynome operator+(const Polynome&, const Polynome&);
	friend Polynome operator-(const Polynome&, const Polynome&);
	friend Polynome operator*(const Polynome&, const Polynome&);
	friend Polynome operator*(double, const Polynome&);

	void SETcoefTab(unsigned int index, double userValue);

	unsigned int GETorder() const;
	double GETcoefTab(unsigned int index) const;
	unsigned int GETstringSize() const;

	friend Polynome addition(const Polynome& a, const Polynome& b);
	friend Polynome soustraction(const Polynome& a, const Polynome& b);
	friend Polynome multiplication(const Polynome& a, const Polynome& b);
	friend Polynome multiplication(double, const Polynome&);
	void editsize(unsigned int);
	void grow(double);

	std::string printOn(bool on = true) const;

	friend void testPolynome();
	

protected:
	virtual double* allocate(unsigned int) const;
	virtual double* allocate(unsigned int, double*) const;
	virtual double* allocate(const Polynome& P) const;

	bool assertIndex(unsigned int) const;
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

template<class T>
T maxP(const T a, const T b){
	if (a > b)
		return a;
	else
		return b;
}
template<class T>
T minP(const T a, const T b){
	if (a < b)
		return a;
	else
		return b;
}

#endif // !Polynome_H
