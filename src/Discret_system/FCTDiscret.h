/*

	Discrete_system
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
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

#ifndef FCTDiscret_H
#define FCTDiscret_H

#include "LIB.h"

#include "Polynome.h"
#include "Matrice.h"
#include "Complexe.h"


class FCTDiscret{
public: // constructeurs et destructeur
	FCTDiscret();
	FCTDiscret(double); // cast
	FCTDiscret(Polynome& num, Polynome& den, double deltaT);
	FCTDiscret(const FCTDiscret&);
	~FCTDiscret();

	void allocate(Polynome num, Polynome den);

public: // opérations entre 2 objets FCTDiscret
	virtual FCTDiscret& operator = (const FCTDiscret&);
	friend bool operator ==(const FCTDiscret& a, const FCTDiscret& b);
	friend FCTDiscret operator+(const FCTDiscret&, const FCTDiscret&);
	friend FCTDiscret operator-(const FCTDiscret&, const FCTDiscret&);
	friend FCTDiscret operator*(const FCTDiscret&, const FCTDiscret&);

public: // assesseurs
	void SETjuryPtr(const Matrice* J);
	void SETnumPtr(const Polynome* a);
	void SETdenPtr(const Polynome* a);
	void SETjury(const Matrice& J);
	void SETnum(const Polynome& a);
	void SETden(const Polynome& a);
	void SETdeltaT(double);
	void SETnumOrder(unsigned int order);
	void SETdenOrder(unsigned int order);
	void SETnumThisCoef(unsigned int order, double userValue);
	void SETdenThisCoef(unsigned int order, double userValue);

	Matrice* GETjuryPtr()const;
	Polynome* GETnumPtr() const;
	Polynome* GETdenPtr() const;
	Matrice& GETjury()const;
	Polynome& GETnum() const;
	Polynome& GETden() const;
	double GETdeltaT() const;

public: // affichage
	friend std::ostream& operator<<(std::ostream&, const FCTDiscret&);
	const std::string printOn(bool on = true) const;

public:
	void interg(); // modification de la fonction de transfert pour correspondre à un intégrateur
	void secondOrdre();// modification de la fonction de transfert pour correspondre à un second ordre

public: // opérations sur l'objet
	bool tabJury();
	bool Bode(double wMin, double wMax, unsigned int nbpoint, double** gainPhase);
	friend void closeLoop(const FCTDiscret& openLoop, const FCTDiscret& returnLoop);

public:
	friend void testFCTDiscret();

private:
	Matrice* _jury;
	Polynome* _num;
	Polynome* _den;
	double _deltaT;
};



#endif 
