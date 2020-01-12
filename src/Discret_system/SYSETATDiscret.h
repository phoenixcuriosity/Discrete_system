/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:3.1
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

#ifndef SYSETATDiscret_H
#define SYSETATDiscret_H

#include "LIB.h"
#include "Matrice.h"
#include "FCTDiscret.h"
#include "Signal.h"


class SYSETATDiscret{
public: // constructeurs et destructeur
	SYSETATDiscret();
	SYSETATDiscret(const SYSETATDiscret&);
	~SYSETATDiscret();

public: // opérations entre 2 objets SYSETATDiscret
	friend bool operator ==(const SYSETATDiscret&, const SYSETATDiscret&);

public: // assesseurs
	void SETA(const Matrice*);
	void SETB(const Matrice*);
	void SETC(const Matrice*);
	void SETD(const Matrice*);
	void SETTe(unsigned int Te);
	void SETeditSizeA(unsigned int length, unsigned int height);
	void SETeditSizeB(unsigned int length, unsigned int height);
	void SETeditSizeC(unsigned int length, unsigned int height);
	void SETeditSizeD(unsigned int length, unsigned int height);
	void SETthisCoefA(unsigned int i, unsigned int j, double userValue);
	void SETthisCoefB(unsigned int i, unsigned int j, double userValue);
	void SETthisCoefC(unsigned int i, unsigned int j, double userValue);
	void SETthisCoefD(unsigned int i, unsigned int j, double userValue);
	Matrice* GETA()const;
	Matrice* GETB()const;
	Matrice* GETC()const;
	Matrice* GETD()const;
	double GETTe()const;
	
public: // affichage
	friend std::ostream& operator<<(std::ostream&, const SYSETATDiscret&);
	std::string printOn(bool on = true)const;

public: // opération sur l'objet
	void calculABCD(const FCTDiscret& fct);
	void simulation(const std::string& namefile, Signal& signal, Matrice& x0, double* yOut);
	
public:
	friend void testSYSETATDiscret();

private:
	Matrice *_A,
			*_B,
			*_C,
			*_D;
	double _Te;
};

#endif // !SYSETATDiscret_H
