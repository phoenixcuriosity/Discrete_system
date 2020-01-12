/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:3.2
	file version 2.1

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

/* *********************************************************
 *						Include							   *
 ********************************************************* */

#include "LIB.h"

#include "Polynome.h"
#include "Matrice.h"

/* *********************************************************
 *					Class FCTDiscret					   *
 ********************************************************* */

class FCTDiscret
{
public:

	/* *********************************************************
	 *				constructeurs et destructeur			   *
	 ********************************************************* */

	FCTDiscret();
	FCTDiscret(double); // cast
	FCTDiscret(Polynome& num, Polynome& den, double deltaT);
	FCTDiscret(const FCTDiscret&);
	~FCTDiscret();

	/*
	 * NAME : allocate
	 * ROLE : Allocation de la mémoire pour _num, _den et _jury
	 * INPUT  PARAMETERS : Polynome num : Polynome numérateur de la FCTDiscret
	 * INPUT  PARAMETERS : Polynome den : Polynome dénominateur de la FCTDiscret
	 * OUTPUT PARAMETERS : new : _num, _den , _jury
	 * RETURNED VALUE    : void
	 */
	void allocate(Polynome num, Polynome den);


public:
	/* *********************************************************
	 *			opérations entre 2 objets FCTDiscret		   *
	 ********************************************************* */


	/*
	 * NAME : operator =
	 * ROLE : Redéfinition de l'opérateur =
	 * INPUT  PARAMETERS : const FCTDiscret& F : objet permettant l'égalisation
	 * OUTPUT PARAMETERS : this = F
	 * RETURNED VALUE    : FCTDiscret& : return this
	 */
	virtual FCTDiscret& operator = (const FCTDiscret& F);

	/*
	 * NAME : operator ==
	 * ROLE : Redéfinition de l'opérateur =
	 * ROLE : Comparaison entre les 2 FCTDiscret en Input
	 * INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret
	 * INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret 
	 * OUTPUT PARAMETERS : Comparaison
	 * RETURNED VALUE    : bool : == -> true // != -> false
	 */
	friend bool operator ==(const FCTDiscret& a, const FCTDiscret& b);

	/*
	 * NAME : operator+
	 * ROLE : Redéfinition de l'opérateur +
	 * ROLE : Addition entre les 2 Inputs
	 * INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret
	 * INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret
	 * OUTPUT PARAMETERS : résultat de l'addition (a + b)
	 * RETURNED VALUE    : FCTDiscret : retourne un objet résultat de l'addition 
	 */
	friend FCTDiscret operator+(const FCTDiscret& a, const FCTDiscret& b);

	/*
	 * NAME : operator-
	 * ROLE : Redéfinition de l'opérateur -
	 * ROLE : Soustraction entre les 2 Inputs
	 * INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret
	 * INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret
	 * OUTPUT PARAMETERS : résultat de la soustraction (a - b)
	 * RETURNED VALUE    : FCTDiscret : retourne un objet résultat de la soustraction 
	 */
	friend FCTDiscret operator-(const FCTDiscret& a, const FCTDiscret& b);

	/*
	 * NAME : operator*
	 * ROLE : Redéfinition de l'opérateur *
	 * ROLE : Multiplication entre les 2 Inputs
	 * INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret
	 * INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret
	 * OUTPUT PARAMETERS : résultat de la multiplication (a * b)
	 * RETURNED VALUE    : FCTDiscret : retourne un objet résultat de la Multiplication
	 */
	friend FCTDiscret operator*(const FCTDiscret& a, const FCTDiscret& b);


public:

	/* *********************************************************
	 *						 assesseurs						   *
	 ********************************************************* */

	inline void SETjuryPtr(const Matrice* J)			{ *_jury = *J; };
	inline void SETnumPtr(const Polynome* a)			{ *_num = *a; };
	inline void SETdenPtr(const Polynome* a)			{ *_den = *a; };
	inline void SETjury(const Matrice& J)				{ *_jury = J; };
	inline void SETnum(const Polynome& a)				{ *_num = a; };
	inline void SETden(const Polynome& a)				{ *_den = a; };
	inline void SETdeltaT(double deltaT)				{ _deltaT = deltaT; };
	inline void SETnumOrder(unsigned int order)			{ _num->SETorder(order); };
	inline void SETdenOrder(unsigned int order)			{ _den->SETorder(order); };
	inline void SETnumThisCoef(unsigned int index, double userValue) { _num->SETcoefTab(index, userValue); };
	inline void SETdenThisCoef(unsigned int index, double userValue) { _den->SETcoefTab(index, userValue); };

	inline Matrice* GETjuryPtr() const			{ return _jury; };
	inline Polynome* GETnumPtr() const			{ return _num; };
	inline Polynome* GETdenPtr() const			{ return _den; };
	inline Matrice& GETjury() const				{ return *_jury; };
	inline Polynome& GETnum() const				{ return *_num; };
	inline Polynome& GETden() const				{ return *_den; };
	inline double GETdeltaT() const				{ return _deltaT; };
	

public:

	/* *********************************************************
	 *						 affichage						   *
	 ********************************************************* */


	/*
	 * NAME : operator<<
	 * ROLE : Redéfinition de l'opérateur <<
	 * ROLE : Envoi sur le ostream (std::cout, ...) une forme textuelle ...
	 * ROLE : ... de l'objet créée par la fonction printOn
	 * INPUT  PARAMETERS : std::ostream& os : stream de sortie : std::cout, ...
	 * INPUT  PARAMETERS : const FCTDiscret& s : La FCT à afficher
	 * OUTPUT PARAMETERS : affichage textuelle de la FCTDiscret sur la console
	 * RETURNED VALUE    : std::ostream& : std::cout, ...
	 */
	inline friend std::ostream& operator<<(std::ostream& os, const FCTDiscret& s)
	{return os << s.printOn(false);};

	/*
	 * NAME : printOn
	 * ROLE : Création d'une représentation visuelle de la FCTDiscret
	 * INPUT  PARAMETERS : bool on = true : si true -> affichage direct ...
	 * INPUT  PARAMETERS : ... sur std::cout // sinon false 
	 * OUTPUT PARAMETERS : chaine de caratères représentant la FCTDiscret
	 * RETURNED VALUE    : std::string : chaine de caratères
	 */
	const std::string printOn(bool on = true) const;

public:

	/* *********************************************************
	 *				Possibilités d'initialisation			   *
	 ********************************************************* */

	/*
	 * NAME : interg
	 * ROLE : Initialisation de la FCTDiscret en integrateur
	 * ROLE : num : ordre 1 -> num = Z + 1
	 * ROLE : den : ordre 1 -> den = Z - 1
	 * INPUT  PARAMETERS : void
	 * OUTPUT PARAMETERS : La FCTDiscret est de type integrateur 
	 * RETURNED VALUE    : void
	 */
	void interg();

	/*
	 * NAME : secondOrdre
	 * ROLE : Initialisation de la FCTDiscret en second ordre
	 * ROLE : num : ordre 0 -> num = 1
	 * ROLE : den : ordre 2 -> den = Z² + 0.5Z - 1
	 * INPUT  PARAMETERS : void
	 * OUTPUT PARAMETERS : La FCTDiscret est de type second ordre
	 * RETURNED VALUE    : void
	 */
	void secondOrdre();

public:

	/* *********************************************************
	 *					opérations sur l'objet				   *
	 ********************************************************* */

	/*
	 * NAME : initPtrSysinfo
	 * ROLE : Initialisation du Ptr pour exitError
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : ptrSysinfo* = &sysinfo
	 * RETURNED VALUE    : void
	 */
	bool tabJury();

	/*
	 * NAME : initPtrSysinfo
	 * ROLE : Initialisation du Ptr pour exitError
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : ptrSysinfo* = &sysinfo
	 * RETURNED VALUE    : void
	 */
	bool Bode(double wMin, double wMax, unsigned int nbpoint, double** gainPhase);

	/*
	 * NAME : initPtrSysinfo
	 * ROLE : Initialisation du Ptr pour exitError
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : ptrSysinfo* = &sysinfo
	 * RETURNED VALUE    : void
	 */
	friend void closeLoop(const FCTDiscret& openLoop, const FCTDiscret& returnLoop);

public:

	/* *********************************************************
	 *							Test						   *
	 ********************************************************* */

	/*
	 * NAME : initPtrSysinfo
	 * ROLE : Initialisation du Ptr pour exitError
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : ptrSysinfo* = &sysinfo
	 * RETURNED VALUE    : void
	 */
	friend void testFCTDiscret();

private:

	/* *********************************************************
	 *						Attributs						   *
	 ********************************************************* */

	Matrice* _jury;
	Polynome* _num;
	Polynome* _den;
	double _deltaT;
};

#endif 
