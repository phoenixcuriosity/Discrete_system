/*

	Discrete_system
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	file version 4.0.1

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
 *						Constantes						   *
 ********************************************************* */

/* Nombre de conditions n�cessaires pour que la FCTDiscret soit stable  */
const Uint8 JURY_STABILITY_CONDITIONS = 4;

/* minimal order of the denominator to be process in Jury */
const Uint8 MIN_ORDER_DEN_TAB_JURY = 2;

/* *********************************************************
 *					Class FCTDiscret					   *
 ********************************************************* */

class FCTDiscret
{
public:

	/* *********************************************************
	 *				constructeurs et destructeur			   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : FCTDiscret																   */
	/* ROLE : Constructeur par d�faut													   */
	/* INPUT  PARAMETERS : void			 												   */
	/* OUTPUT PARAMETERS : Cr�ation d'un objet FCTDiscret : num = 1 / den = 1			   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	FCTDiscret();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : FCTDiscret																   */
	/* ROLE : Constructeur par cast du num�rateur										   */
	/* INPUT  PARAMETERS : double num : num�rateur										   */
	/* OUTPUT PARAMETERS : Cr�ation d'un objet FCTDiscret : num / 1						   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	FCTDiscret
	(
		double
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : FCTDiscret																   */
	/* ROLE : Constructeur par num et den avec deltaT sa p�riode						   */
	/* INPUT  PARAMETERS : Polynome& num : objet Polynome num�rateur					   */
	/* INPUT  PARAMETERS : Polynome& den : objet Polynome d�nominateur			 		   */
	/* INPUT  PARAMETERS : double deltaT			 									   */
	/* OUTPUT PARAMETERS : Cr�ation d'un objet FCTDiscret :	num / den					   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	FCTDiscret
	(
		Polynome& num,
		Polynome& den,
		double deltaT
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : FCTDiscret																   */
	/* ROLE : Constructeur par Recopie													   */
	/* INPUT  PARAMETERS : const FCTDiscret& : Objet � recopier		 					   */
	/* OUTPUT PARAMETERS : Cr�ation d'un objet FCTDiscret recopie de l'entr�e			   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	FCTDiscret
	(
		const FCTDiscret&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~FCTDiscret																   */
	/* ROLE : Destructeur de la classe FCTDiscret										   */
	/* INPUT  PARAMETERS : void			 												   */
	/* OUTPUT PARAMETERS : Objet FCTDiscret d�truit										   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	~FCTDiscret();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : allocate																	   */
	/* ROLE : Allocation de la m�moire pour _num, _den et _jury							   */
	/* INPUT  PARAMETERS : Polynome num : Polynome num�rateur de la FCTDiscret			   */
	/* INPUT  PARAMETERS : Polynome den : Polynome d�nominateur de la FCTDiscret		   */
	/* OUTPUT PARAMETERS : new : _num, _den , _jury										   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void allocate
	(
		Polynome num,
		Polynome den
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deallocate																   */
	/* ROLE : D�allocation de la m�moire pour _num, _den et _jury						   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : delete : _num, _den , _jury									   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void deallocate();


public:
	/* *********************************************************
	 *			op�rations entre 2 objets FCTDiscret		   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator =																   */
	/* ROLE : Red�finition de l'op�rateur =												   */
	/* INPUT  PARAMETERS : const FCTDiscret& F : objet permettant l'�galisation			   */
	/* OUTPUT PARAMETERS : this = F														   */
	/* RETURNED VALUE    : FCTDiscret& : return this									   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	virtual FCTDiscret& operator =
	(
		const FCTDiscret& F
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator ==																   */
	/* ROLE : Red�finition de l'op�rateur =												   */
	/* ROLE : Comparaison entre les 2 FCTDiscret en Input								   */
	/* INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret					   */
	/* INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret					   */
	/* OUTPUT PARAMETERS : Comparaison													   */
	/* RETURNED VALUE    : bool : == -> true // != -> false								   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend bool operator ==
	(
		const FCTDiscret& a,
		const FCTDiscret& b
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator+																	   */
	/* ROLE : Red�finition de l'op�rateur +												   */
	/* ROLE : Addition entre les 2 Inputs												   */
	/* INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret					   */
	/* INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret					   */
	/* OUTPUT PARAMETERS : r�sultat de l'addition (a + b)								   */
	/* RETURNED VALUE    : FCTDiscret : retourne un objet r�sultat de l'addition		   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend FCTDiscret operator+
	(
		const FCTDiscret& a,
		const FCTDiscret& b
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator-																	   */
	/* ROLE : Red�finition de l'op�rateur -												   */
	/* ROLE : Soustraction entre les 2 Inputs											   */
	/* INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret					   */
	/* INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret					   */
	/* OUTPUT PARAMETERS : r�sultat de la soustraction (a - b)							   */
	/* RETURNED VALUE    : FCTDiscret : retourne un objet r�sultat de la soustraction	   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend FCTDiscret operator-
	(
		const FCTDiscret& a,
		const FCTDiscret& b
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator*																	   */
	/* ROLE : Red�finition de l'op�rateur *												   */
	/* ROLE : Multiplication entre les 2 Inputs											   */
	/* INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret					   */
	/* INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret					   */
	/* OUTPUT PARAMETERS : r�sultat de la multiplication (a * b)						   */
	/* RETURNED VALUE    : FCTDiscret : retourne un objet r�sultat de la Multiplication	   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend FCTDiscret operator*
	(
		const FCTDiscret& a,
		const FCTDiscret& b
	);

	friend void getByCopyReversePolynomeOrder(const Polynome& src, Polynome& dest);


	friend void setFirstL
	(
		const Polynome* srcOrder,
		const Polynome* srcReverse,
		Matrice* dest
	);

public:

	/* *********************************************************
	 *						 affichage						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator<<																   */
	/* ROLE : Red�finition de l'op�rateur <<											   */
	/* ROLE : Envoi sur le ostream (std::cout, ...) une forme textuelle ...				   */
	/* ROLE : ... de l'objet cr��e par la fonction printOn								   */
	/* INPUT  PARAMETERS : std::ostream& os : stream de sortie : std::cout, ...			   */
	/* INPUT  PARAMETERS : const FCTDiscret& s : La FCT � afficher						   */
	/* OUTPUT PARAMETERS : affichage textuelle de la FCTDiscret sur la console			   */
	/* RETURNED VALUE    : std::ostream& : std::cout, ...								   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	inline friend std::ostream& operator<<
	(
		std::ostream& os,
		const FCTDiscret& s
	)
	{
		return os << s.printOn(false);
	};

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : printOn																	   */
	/* ROLE : Cr�ation d'une repr�sentation visuelle de la FCTDiscret					   */
	/* INPUT  PARAMETERS : bool on = true : si true -> affichage direct ...				   */
	/* INPUT  PARAMETERS : ... sur std::cout // sinon false 							   */
	/* OUTPUT PARAMETERS : chaine de carat�res repr�sentant la FCTDiscret				   */
	/* RETURNED VALUE    : std::string : chaine de carat�res							   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	const std::string printOn
	(
		bool on = true
	) const;

public:

	/* *********************************************************
	 *				Possibilit�s d'initialisation			   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : interg																	   */
	/* ROLE : Initialisation de la FCTDiscret en integrateur							   */
	/* ROLE : num : ordre 1 -> num = Z + 1												   */
	/* ROLE : den : ordre 1 -> den = Z - 1												   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : La FCTDiscret est de type integrateur						   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void interg();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : secondOrdre																   */
	/* ROLE : Initialisation de la FCTDiscret en second ordre							   */
	/* ROLE : num : ordre 0 -> num = 1													   */
	/* ROLE : den : ordre 2 -> den = Z� + 0.5Z - 1										   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : La FCTDiscret est de type second ordre						   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void secondOrdre();

public:

	/* *********************************************************
	 *					op�rations sur l'objet				   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : tabJury																	   */
	/* ROLE : Cr�ation du tableau de Jury (objet Matrice)								   */
	/* ROLE : Calcul du crit�re de Jury permettant de statuer sur la stabilit� du syst�me  */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : Matrice de Jury compl�t�e et status de la stabilit�			   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	bool tabJury(std::ostringstream& stream);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Bode																		   */
	/* ROLE : Repr�sentation visuelle de diagramme de Bode de la FCTDiscret				   */
	/* INPUT  PARAMETERS : double wMin : fr�quence min									   */
	/* INPUT  PARAMETERS : double wMax : fr�quence max									   */
	/* INPUT  PARAMETERS : unsigned int nbpoint : nombre de pts entre min et max		   */
	/* INPUT  PARAMETERS : double** gainPhase : Matrice des points du diagramme			   */
	/* OUTPUT PARAMETERS : diagramme de Bode											   */
	/* RETURNED VALUE    : bool															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	bool Bode
	(
		double wMin,
		double wMax,
		unsigned int nbpoint,
		BodeGraph& bodeGraph
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : closeLoop																	   */
	/* ROLE : Calcul de la Boucle Ferm�e												   */
	/* INPUT  PARAMETERS : const FCTDiscret& openLoop									   */
	/* INPUT  PARAMETERS : const FCTDiscret& returnLoop									   */
	/* OUTPUT PARAMETERS : Boucle Ferm�e												   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend void closeLoop
	(
		const FCTDiscret& openLoop,
		const FCTDiscret& returnLoop
	);

public:

	/* *********************************************************
	 *							Test						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : testFCTDiscret															   */
	/* ROLE : For DEV only																   */
	/* ROLE : Test des m�thodes et fonctions de la classe FCTDiscret					   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : Test de la classe											   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend void testFCTDiscret();

public:

	/* *********************************************************
	 *						 assesseurs						   *
	 ********************************************************* */

	inline void SETjury(const Matrice* J)	{ *_jury = *J; };
	inline void SETnum(const Polynome* a)	{ *_num = *a; };
	inline void SETden(const Polynome* a)	{ *_den = *a; };
	inline void SETdeltaT(double deltaT)	{ _deltaT = deltaT; };

	inline Matrice* GETjury() const { return _jury; };
	inline Polynome* GETnum() const { return _num; };
	inline Polynome* GETden() const { return _den; };
	inline double GETdeltaT() const { return _deltaT; };
	
	inline bool isInitialize()const { return m_isInitialize; };

private:

	/* *********************************************************
	 *						Attributs						   *
	 ********************************************************* */
	bool m_isInitialize;

	Matrice* _jury;
	Polynome* _num;
	Polynome* _den;
	double _deltaT;
};

#endif 

/*
*	End Of File : FCTDiscret.h
*/
