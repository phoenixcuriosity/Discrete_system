/*
Discrete_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.26

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#ifndef Matrice_H
#define Matrice_H

#include "LIB.h"

class Matrice{
public:
	Matrice();
	Matrice(double); // cast
	Matrice(unsigned int lenght, unsigned int height);
	Matrice(double** tab, unsigned int length, unsigned int height);
	Matrice(const Matrice& M);
	~Matrice();
	
	Matrice& operator=(const Matrice&);
	friend bool operator==(const Matrice&, const Matrice&);
	friend std::ostream& operator<<(std::ostream&, const Matrice&);
	friend Matrice operator+(const Matrice&, const Matrice&);
	friend Matrice operator-(const Matrice&, const Matrice&);
	friend Matrice operator*(const Matrice&, const Matrice&);


	void SETthiscoef(unsigned int i, unsigned int j, double userValue);
	double GETthiscoef(unsigned int i, unsigned int j)const;
	unsigned int GETlength()const;
	unsigned int GETheight()const;
	unsigned int GETstringSize() const;

	friend Matrice addition(const Matrice&, const Matrice&);
	friend Matrice soustraction(const Matrice&, const Matrice&);
	friend Matrice multiplication(const Matrice&, const Matrice&);

	friend Matrice transposistion(const Matrice&);
	void zero();
	void ones();
	void editsize(unsigned int length, unsigned int height);
	void growOneLOneC();

	const std::string printOn(bool on = true)const;

	friend void testMatrice();

protected:
	virtual double** allocate(unsigned int length, unsigned int height) const;
	virtual double** allocate(unsigned int length, unsigned int height, double userValue) const;
	virtual double** allocate(const Matrice&) const;

	bool assertIndex(unsigned int length, unsigned int height)const;
	bool assertRange(unsigned int, unsigned int)const;
	friend bool assertSize(unsigned int, unsigned int, unsigned int, unsigned int);
private:
	unsigned int _length;
	unsigned int _height;
	double** _tab;
	mutable unsigned int _stringSize;
};


template<class T>
T maxM(const T a, const T b){
	if (a > b)
		return a;
	else
		return b;
}
template<class T>
T minM(const T a, const T b){
	if (a < b)
		return a;
	else
		return b;
}




#endif