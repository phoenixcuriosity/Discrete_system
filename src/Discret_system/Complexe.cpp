/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
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

#include "Complexe.h"

const double Pi = 3.14159265358979323846;


Complexe::Complexe() : _Re(0), _Im(0)
{
}
Complexe::Complexe(double Re) : _Re(Re), _Im(0)
{
}
Complexe::Complexe(const Complexe& a) : _Re(a._Re), _Im(a._Im)
{
}
Complexe::Complexe(double Re, double Im) : _Re(Re), _Im(Im)
{
}
Complexe::~Complexe()
{
}


Complexe& Complexe::operator = (const Complexe& a)
{
	if (this != &a){
		_Re = a.GETRe();
		_Im = a.GETIm();
	}
	return *this;
}
bool operator ==(const Complexe& a, const Complexe& b)
{
	if (a.GETRe() == b.GETRe() && a.GETIm() == b.GETIm())
		return true;
	else
		return false;
}
std::ostream& operator<<(std::ostream& os, const Complexe& c)
{
	return os << c.printOn(false);
}
Complexe operator+(const Complexe& a, const Complexe& b)
{
	Complexe resultat;
	resultat.SETRe(a.GETRe() + b.GETRe());
	resultat.SETIm(a.GETIm() + b.GETIm());
	return resultat;
}
Complexe operator-(const Complexe& a, const Complexe& b)
{
	Complexe resultat;
	resultat.SETRe(a.GETRe() - b.GETRe());
	resultat.SETIm(a.GETIm() - b.GETIm());
	return resultat;
}
Complexe operator*(const Complexe& a, const Complexe& b)
{
	Complexe resultat;
	resultat.SETRe(a.GETRe() * b.GETRe() - (a.GETIm() * b.GETIm()));
	resultat.SETIm(2 * a.GETRe() * b.GETIm());
	return resultat;
}
Complexe operator/(const Complexe& a, const Complexe& b)
{
	Complexe resultat;
	resultat.SETRe((a.GETRe() * b.GETRe() + a.GETIm() * b.GETIm()) / (pow(b.GETRe(), 2) + pow(b.GETIm(), 2)));
	resultat.SETIm((a.GETIm() * b.GETRe() + a.GETRe() * b.GETIm()) / (pow(b.GETRe(), 2) + pow(b.GETIm(), 2)));
	return resultat;
}



double Complexe::module(const Complexe& a)
{
	double module = sqrt(pow(a.GETRe(), 2) + pow(a.GETIm(), 2));
	return module;
}
double Complexe::arg(const Complexe& a)
{
	/*
		argument en degré
	*/
	double argument = 0;
	argument = atan(a.GETIm() / a.GETRe()) * (180 / Pi);
	if (a.GETRe() < 0)
		argument += Pi;
	return argument;
}
Complexe Complexe::tfReIm(double module, double arg)
{
	/*
		arg en degré en entré
	*/
	double Re = module * cos(arg * (Pi / 180));
	double Im = module * sin(arg * (Pi / 180));
	Complexe c(Re, Im);
	return c;
}
Complexe Complexe::power(unsigned int power)
{
	/*
		calcul du complexe puissance power
	*/
	if (power == 1)
		return *this;
	else if (power > 1)
	{
		Complexe c(*this);
		for (unsigned int i = 1; i < power; i++)
		{
			c = c * *this;
		}
		return c;
	}
	else
	{
		Complexe c(1, 0);
		return c;
	}
}
Complexe Complexe::tfPolynomeComplexe(const Polynome& P, Complexe& Z)
{
	/*
		calcul du complexe à partir du polynome et de Z transformé en complexe
	*/
	Complexe c;
	for (unsigned int j = 0; j <= P.GETorder(); j++)
		c = P.GETcoefTab(j) * Z.power(j) + c;
	return c;
}




void Complexe::SETRe(double Re)
{
	_Re = Re;
}
void Complexe::SETIm(double Im)
{
	_Im = Im;
}
double Complexe::GETRe()const
{
	return _Re;
}
double Complexe::GETIm()const
{
	return _Im;
}



const std::string Complexe::printOn(bool on)const
{
	std::string texte;
	std::ostringstream stream;

	if (_Re != 0)
		stream << _Re;
	if (_Im != 0){
		if (_Im < 0)
			stream << " - " << abs(_Im) << "j";
		else
			stream << " + " << _Im << "j";
	}
	texte = stream.str();
	if (on)
		std::cout << texte;
	return texte;
}




void testComplexe()
{
	std::string texte = "";
	std::ostringstream stream;

	stream << std::endl << "___TEST COMPLEXE___";

	Complexe a(2, 3);
	Complexe b(1, 1);
	Complexe c;


	stream << std::endl << "Complexe a = " << a;
	stream << std::endl << "Complexe b = " << b;
	stream << std::endl << "Complexe a + b = " << a + b;
	stream << std::endl << "Complexe a - b = " << a - b;
	stream << std::endl << "Complexe a * b = " << a * b;
	stream << std::endl << "Complexe a / b = " << a / b;
	stream << std::endl << "Module de a = " << Complexe::module(a);
	stream << std::endl << "arg de a = " << Complexe::arg(a);
	stream << std::endl << "Module de b = " << Complexe::module(b);
	stream << std::endl << "arg de b = " << Complexe::arg(b);
	stream << std::endl << "tfReIm du module et arg de b = " << Complexe::tfReIm(Complexe::module(b), Complexe::arg(b));
	stream << std::endl << "Puissance 3 de a = " << a.power(3) << std::endl << std::endl;

	texte = stream.str();
	std::cout << texte;
}

/*
*	End Of File : Complexe.cpp
*/