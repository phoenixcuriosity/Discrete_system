/*

	Discrete_system
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	file version 4.1.0

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

const double COMPLEXE_UNIT_REAL = 1.0;

class Complexe
{
public:

	/* *********************************************************
	 *				constructeurs et destructeur			   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Complexe																	   */
	/* ROLE : Constructeur par défaut													   */
	/* INPUT  PARAMETERS : void			 												   */
	/* OUTPUT PARAMETERS : Création d'un objet Complexe = 1 + i							   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Complexe();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Complexe																	   */
	/* ROLE : Constructeur par cast de la partie Réelle									   */
	/* INPUT  PARAMETERS : double Re : Partie Réelle			 						   */
	/* OUTPUT PARAMETERS : Création d'un objet Complexe = Re + 0 * i					   */
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
	/* ROLE : Constructeur avec partie Réelle et Imaginaire								   */
	/* INPUT  PARAMETERS : double Re : Partie Réelle				 					   */
	/* INPUT  PARAMETERS : double Im : Partie Imaginaire		 						   */
	/* OUTPUT PARAMETERS : Création d'un objet Complexe	= Re + Im						   */
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
	/* OUTPUT PARAMETERS : Création d'un objet Complexe	recopie de l'entrée				   */
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
	/* OUTPUT PARAMETERS : Objet Complexe détruit										   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	~Complexe();


public:

	/* *********************************************************
	 *			opérations entre 2 objets Complexe 	     	   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator =																   */
	/* ROLE : Redéfinition de l'opérateur =												   */
	/* INPUT  PARAMETERS : const Complexe& C : objet permettant l'égalisation		 	   */
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
	/* ROLE : Redéfinition de l'opérateur ==											   */
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
	/* ROLE : Redéfinition de l'opérateur +												   */
	/* ROLE : Addition entre les 2 Inputs												   */
	/* INPUT  PARAMETERS : const Complexe& a : un objet Complexe						   */
	/* INPUT  PARAMETERS : const Complexe& b : un objet Complexe						   */
	/* OUTPUT PARAMETERS : résultat de l'addition (a + b)								   */
	/* RETURNED VALUE    : Complexe : retourne un objet résultat de l'addition			   */
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
	/* ROLE : Redéfinition de l'opérateur -												   */
	/* ROLE : Soustraction entre les 2 Inputs											   */
	/* INPUT  PARAMETERS : const Complexe& a : un objet Complexe 						   */
	/* INPUT  PARAMETERS : const Complexe& b : un objet Complexe						   */
	/* OUTPUT PARAMETERS : résultat de soustraction (a - b)								   */
	/* RETURNED VALUE    : Complexe : retourne un objet résultat de la soustraction		   */
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
	/* ROLE : Redéfinition de l'opérateur *												   */
	/* ROLE : Multiplication entre les 2 Inputs											   */
	/* INPUT  PARAMETERS : const Complexe& a : un objet Complexe						   */
	/* INPUT  PARAMETERS : const Complexe& b : un objet Complexe						   */
	/* OUTPUT PARAMETERS : résultat de la multiplication (a * b)						   */
	/* RETURNED VALUE    : Complexe : retourne un objet résultat de la Multiplication	   */
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
	/* ROLE : Redéfinition de l'opérateur /												   */
	/* ROLE : Multiplication entre les 2 Inputs											   */
	/* INPUT  PARAMETERS : const Complexe& a : un objet Complexe						   */
	/* INPUT  PARAMETERS : const Complexe& b : un objet Complexe						   */
	/* OUTPUT PARAMETERS : résultat de la division (a / b)								   */
	/* RETURNED VALUE    : Complexe : retourne un objet résultat de la Multiplication	   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend Complexe operator/
	(
		const Complexe&,
		const Complexe&
	);


public:

	/* *********************************************************
	 *					opérations sur l'objet				   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : module																	   */
	/* ROLE : Calcul du module du Complexe												   */
	/* INPUT  PARAMETERS : const Complexe a : un objet Complexe							   */
	/* OUTPUT PARAMETERS : sqrt(Re²+Im²)												   */
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
	/* ROLE : Création d'un Complexe en fonction de son module et de son argument	  	   */
	/* INPUT  PARAMETERS : double module : Module du Complexe							   */
	/* INPUT  PARAMETERS : double arg : Argument du Complexe							   */
	/* OUTPUT PARAMETERS : Création d'un Complexe										   */
	/* RETURNED VALUE    : Complexe : l'objet créé										   */
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
	/* ROLE : Calcul du Complexe à la puissance power									   */
	/* INPUT  PARAMETERS : unsigned int power : puissance à appliquer au Complexe		   */
	/* OUTPUT PARAMETERS : Complexe à la puissance power								   */
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
	/* ROLE : Calcul du complexe à partir du polynome et de Z transformé en complexe	   */
	/* INPUT  PARAMETERS : const Polynome& P : un objet Polynome						   */
	/* INPUT  PARAMETERS : Complexe& Z : un objet Complexe								   */
	/* OUTPUT PARAMETERS : objet Complexe image du Polynome en entré					   */
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
	/* ROLE : Redéfinition de l'opérateur <<											   */
	/* ROLE : Envoi sur le ostream (std::cout, ...) une forme textuelle ...				   */
	/* ROLE : ... de l'objet créée par la fonction printOn								   */
	/* INPUT  PARAMETERS : std::ostream& os : stream de sortie : std::cout, ...			   */
	/* INPUT  PARAMETERS : const Complexe& s : Le Complexe à afficher					   */
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
	/* ROLE : Création d'une représentation visuelle du Complexe						   */
	/* INPUT  PARAMETERS : bool on = true : si true -> affichage direct ... 			   */
	/* INPUT  PARAMETERS : ... sur std::cout // sinon false								   */
	/* OUTPUT PARAMETERS : chaine de caratères représentant le Complexe					   */
	/* RETURNED VALUE    : std::string : chaine de caratères							   */
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
	/* ROLE : Test des méthodes et fonctions de la classe Complexe						   */
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