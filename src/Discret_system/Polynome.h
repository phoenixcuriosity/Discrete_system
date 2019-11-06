/*

	Discrete_system
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:2.10

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef Polynome_H
#define Polynome_H

#include "LIB.h"

class Polynome {
public: // constructeurs et destructeur
	Polynome();
	Polynome(unsigned int order); // attention : Polynome a((unsigned int)2) est la seule façon de créer un polynome d'ordre 2
	Polynome(double userValue); // cast
	Polynome(unsigned int order, double tab[]);
	Polynome(const Polynome& P);
	~Polynome();

public: // opérations sur 2 objets Polynome
	Polynome& operator=(const Polynome&);
	friend bool operator==(const Polynome&, const Polynome&);
	friend Polynome operator+(const Polynome&, const Polynome&);
	friend Polynome operator-(const Polynome&, const Polynome&);
	friend Polynome operator*(const Polynome&, const Polynome&);
	friend Polynome addition(const Polynome& a, const Polynome& b);
	friend Polynome soustraction(const Polynome& a, const Polynome& b);
	friend Polynome multiplication(const Polynome& a, const Polynome& b);

public: // assesseurs
	void SETorder(unsigned int order);
	void SETcoefTab(unsigned int index, double userValue);

	unsigned int GETorder() const;
	double GETcoefTab(unsigned int index) const;
	unsigned int GETstringSize() const;

public: // opération sur l'objet
	double operator[](unsigned int index);
	void grow(double userValue);

public: // affichage
	friend std::ostream& operator<<(std::ostream& os, const Polynome&);
	std::string printOn(bool = true) const;

public:
	friend void testPolynome();
	
protected: // allocate et test d'index
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
