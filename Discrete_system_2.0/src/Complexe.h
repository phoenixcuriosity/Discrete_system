/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version: 3.5
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

#ifndef Complexe_H
#define Complexe_H

#include "LIB.h"
#include "Polynome.h"

class Complexe
{
public:

	/* *********************************************************
	 *				constructeurs et destructeur			   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Complexe																	   */
	/* ROLE : Constructeur par d�faut													   */
	/* INPUT  PARAMETERS : void			 												   */
	/* OUTPUT PARAMETERS : Cr�ation d'un objet Complexe = 1 + i							   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Complexe();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Complexe																	   */
	/* ROLE : Constructeur par cast de la partie R�elle									   */
	/* INPUT  PARAMETERS : double Re : Partie R�elle			 						   */
	/* OUTPUT PARAMETERS : Cr�ation d'un objet Complexe = Re + 0 * i					   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Complexe
	(
		double Re
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Complexe																	   */
	/* ROLE : Constructeur avec partie R�elle et Imaginaire								   */
	/* INPUT  PARAMETERS : double Re : Partie R�elle				 					   */
	/* INPUT  PARAMETERS : double Im : Partie Imaginaire		 						   */
	/* OUTPUT PARAMETERS : Cr�ation d'un objet Complexe	= Re + Im						   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Complexe
	(
		double Re,
		double Im
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Complexe																	   */
	/* ROLE : Constructeur par Recopie													   */
	/* INPUT  PARAMETERS : void			 												   */
	/* OUTPUT PARAMETERS : Cr�ation d'un objet Complexe	recopie de l'entr�e				   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Complexe
	(
		const Complexe&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~Complexe																	   */
	/* ROLE : Destructeur de la classe Complexe											   */
	/* INPUT  PARAMETERS : void			 												   */
	/* OUTPUT PARAMETERS : Objet Complexe d�truit										   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	~Complexe();


public:

	/* *********************************************************
	 *			op�rations entre 2 objets Complexe 	     	   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator =																   */
	/* ROLE : Red�finition de l'op�rateur =												   */
	/* INPUT  PARAMETERS : const Complexe& C : objet permettant l'�galisation		 	   */
	/* OUTPUT PARAMETERS : this = C														   */
	/* RETURNED VALUE    : Complexe& : return this										   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Complexe& operator =
	(
		const Complexe&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator ==															       */
	/* ROLE : Red�finition de l'op�rateur ==											   */
	/* ROLE : Comparaison entre les 2 Complexe en Input						  			   */
	/* INPUT  PARAMETERS : const Complexe& a : un objet Complexe						   */
	/* INPUT  PARAMETERS : const Complexe& b : un objet Complexe						   */
	/* OUTPUT PARAMETERS : Comparaison													   */
	/* RETURNED VALUE    : bool : == -> true // != -> false								   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend bool operator ==
	(
		const Complexe& a,
		const Complexe& b
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator+																	   */
	/* ROLE : Red�finition de l'op�rateur +												   */
	/* ROLE : Addition entre les 2 Inputs												   */
	/* INPUT  PARAMETERS : const Complexe& a : un objet Complexe						   */
	/* INPUT  PARAMETERS : const Complexe& b : un objet Complexe						   */
	/* OUTPUT PARAMETERS : r�sultat de l'addition (a + b)								   */
	/* RETURNED VALUE    : Complexe : retourne un objet r�sultat de l'addition			   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend Complexe operator+
	(
		const Complexe&,
		const Complexe&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator-																	   */
	/* ROLE : Red�finition de l'op�rateur -												   */
	/* ROLE : Soustraction entre les 2 Inputs											   */
	/* INPUT  PARAMETERS : const Complexe& a : un objet Complexe 						   */
	/* INPUT  PARAMETERS : const Complexe& b : un objet Complexe						   */
	/* OUTPUT PARAMETERS : r�sultat de soustraction (a - b)								   */
	/* RETURNED VALUE    : Complexe : retourne un objet r�sultat de la soustraction		   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend Complexe operator-
	(
		const Complexe&,
		const Complexe&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator*																	   */
	/* ROLE : Red�finition de l'op�rateur *												   */
	/* ROLE : Multiplication entre les 2 Inputs											   */
	/* INPUT  PARAMETERS : const Complexe& a : un objet Complexe						   */
	/* INPUT  PARAMETERS : const Complexe& b : un objet Complexe						   */
	/* OUTPUT PARAMETERS : r�sultat de la multiplication (a * b)						   */
	/* RETURNED VALUE    : Complexe : retourne un objet r�sultat de la Multiplication	   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend Complexe operator*
	(
		const Complexe&,
		const Complexe&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator/																 	   */
	/* ROLE : Red�finition de l'op�rateur /												   */
	/* ROLE : Multiplication entre les 2 Inputs											   */
	/* INPUT  PARAMETERS : const Complexe& a : un objet Complexe						   */
	/* INPUT  PARAMETERS : const Complexe& b : un objet Complexe						   */
	/* OUTPUT PARAMETERS : r�sultat de la division (a / b)								   */
	/* RETURNED VALUE    : Complexe : retourne un objet r�sultat de la Multiplication	   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend Complexe operator/
	(
		const Complexe&,
		const Complexe&
	);


public:

	/* *********************************************************
	 *					op�rations sur l'objet				   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : module																	   */
	/* ROLE : Calcul du module du Complexe												   */
	/* INPUT  PARAMETERS : const Complexe a : un objet Complexe							   */
	/* OUTPUT PARAMETERS : sqrt(Re�+Im�)												   */
	/* RETURNED VALUE    : Module du Complexe											   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static double module
	(
		const Complexe&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : arg																		   */
	/* ROLE : Calcul de l'argument d'un Complexe										   */
	/* INPUT  PARAMETERS : const Complexe a : un objet Complex							   */
	/* OUTPUT PARAMETERS : (atan(Im / Re)) * (180 / Pi)									   */
	/* RETURNED VALUE    : Argument du Complexe											   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static double arg
	(
		const Complexe&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : tfReIm																	   */
	/* ROLE : Cr�ation d'un Complexe en fonction de son module et de son argument	  	   */
	/* INPUT  PARAMETERS : double module : Module du Complexe							   */
	/* INPUT  PARAMETERS : double arg : Argument du Complexe							   */
	/* OUTPUT PARAMETERS : Cr�ation d'un Complexe										   */
	/* RETURNED VALUE    : Complexe : l'objet cr��										   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static Complexe tfReIm
	(
		double module,
		double arg
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : power																		   */
	/* ROLE : Calcul du Complexe � la puissance power									   */
	/* INPUT  PARAMETERS : unsigned int power : puissance � appliquer au Complexe		   */
	/* OUTPUT PARAMETERS : Complexe � la puissance power								   */
	/* RETURNED VALUE    : Complexe														   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Complexe power
	(
		unsigned int power
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : tfPolynomeComplexe														   */
	/* ROLE : Transformation d'un objet Polynome en objet Complexe						   */
	/* ROLE : Calcul du complexe � partir du polynome et de Z transform� en complexe	   */
	/* INPUT  PARAMETERS : const Polynome& P : un objet Polynome						   */
	/* INPUT  PARAMETERS : Complexe& Z : un objet Complexe								   */
	/* OUTPUT PARAMETERS : objet Complexe image du Polynome en entr�					   */
	/* RETURNED VALUE    : Complexe														   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static Complexe tfPolynomeComplexe
	(
		const Polynome& P,
		Complexe& Z
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
	/* INPUT  PARAMETERS : const Complexe& s : Le Complexe � afficher					   */
	/* OUTPUT PARAMETERS : affichage textuelle du Complexe sur la console				   */
	/* RETURNED VALUE    : std::ostream& : std::cout, ...								   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend std::ostream& operator<<
	(
		std::ostream&,
		const Complexe&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : printOn																	   */
	/* ROLE : Cr�ation d'une repr�sentation visuelle du Complexe						   */
	/* INPUT  PARAMETERS : bool on = true : si true -> affichage direct ... 			   */
	/* INPUT  PARAMETERS : ... sur std::cout // sinon false								   */
	/* OUTPUT PARAMETERS : chaine de carat�res repr�sentant le Complexe					   */
	/* RETURNED VALUE    : std::string : chaine de carat�res							   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	const std::string printOn
	(
		bool on = true
	)const;

public:

	/* *********************************************************
	 *							Test						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : testComplexe																   */
	/* ROLE : For DEV only																   */
	/* ROLE : Test des m�thodes et fonctions de la classe Complexe						   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : Test de la classe											   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend void testComplexe();

public:

	/* *********************************************************
	 *						 assesseurs						   *
	 ********************************************************* */

	inline void SETRe(double Re) { _Re = Re; };
	inline void SETIm(double Im) { _Im = Im; };

	inline double GETRe()const { return _Re; };
	inline double GETIm()const { return _Im; };

private:

	/* *********************************************************
	 *						Attributs						   *
	 ********************************************************* */

	double _Re;
	double _Im;
};

#endif

/*
*	End Of File : Complexe.h
*/