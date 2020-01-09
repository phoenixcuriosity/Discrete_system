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

#ifndef Matrice_H
#define Matrice_H

#include "LIB.h"

class Matrice{
public: // constructeurs et destructeur
	Matrice();
	Matrice(double); // cast d'un double vers un objet Matice
	Matrice(unsigned int lenght, unsigned int height);
	Matrice(double** tab, unsigned int length, unsigned int height);
	Matrice(const Matrice& M);
	~Matrice();

public: // opérations entre 2 Matrices
	Matrice& operator=(const Matrice&);
	friend bool operator==(const Matrice&, const Matrice&);
	friend Matrice operator+(const Matrice&, const Matrice&);
	friend Matrice operator-(const Matrice&, const Matrice&);
	friend Matrice operator*(const Matrice&, const Matrice&);

	friend Matrice addition(const Matrice&, const Matrice&);
	friend Matrice soustraction(const Matrice&, const Matrice&);
	friend Matrice multiplication(const Matrice&, const Matrice&);

public: // assesseurs
	void SETthiscoef(unsigned int i, unsigned int j, double userValue);
	double GETthiscoef(unsigned int i, unsigned int j)const;
	unsigned int GETlength()const;
	unsigned int GETheight()const;
	unsigned int GETstringSize() const;

public: // opérations sur la Matrice
	friend Matrice transposition(const Matrice&);
	void zero();
	void ones();
	void editsize(unsigned int length, unsigned int height);
	void growOneLOneC();

public: // affichage
	friend std::ostream& operator<<(std::ostream&, const Matrice&);
	const std::string printOn(bool on = true)const;

	virtual double** allocate(unsigned int length, unsigned int height) const;
	virtual double** allocate(unsigned int length, unsigned int height, double userValue) const;
	virtual double** allocate(const Matrice&) const;

	bool assertIndex(unsigned int length, unsigned int height)const;
	bool assertRange(unsigned int, unsigned int)const;
	static bool assertSize(unsigned int, unsigned int, unsigned int, unsigned int);

public:
	friend void testMatrice();

private:
	unsigned int _length;
	unsigned int _height;
	double** _tab;
	mutable unsigned int _stringSize;
};

#endif