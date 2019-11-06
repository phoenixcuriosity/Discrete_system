/*

	Discrete_system
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version: 3.0
	file version 2.0

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

#ifndef Complexe_H
#define Complexe_H

#include "LIB.h"
#include "Polynome.h"

class Complexe{
public:
	Complexe();
	Complexe(double Re); // cast
	Complexe(double Re, double Im);
	Complexe(const Complexe&);
	~Complexe();

	Complexe& operator = (const Complexe&);
	friend bool operator ==(const Complexe& a, const Complexe& b);
	friend std::ostream& operator<<(std::ostream&, const Complexe&);
	friend Complexe operator+(const Complexe&, const Complexe&);
	friend Complexe operator-(const Complexe&, const Complexe&);
	friend Complexe operator*(const Complexe&, const Complexe&);
	friend Complexe operator/(const Complexe&, const Complexe&);


	static double module(const Complexe&);
	static double arg(const Complexe&);
	static Complexe tfReIm(double module, double arg);
	Complexe power(unsigned int power);
	static Complexe tfPolynomeComplexe(const Polynome& P, Complexe& Z);


	void SETRe(double Re);
	void SETIm(double Im);
	double GETRe()const;
	double GETIm()const;

	const std::string printOn(bool on = true)const;

	friend void testComplexe();

private:
	double _Re;
	double _Im;
};

#endif

/*
*	End Of File : Complexe.h
*/