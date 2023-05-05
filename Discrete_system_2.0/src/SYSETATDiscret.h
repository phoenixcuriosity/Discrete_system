/*

	Discrete_system
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	file version 4.2.2

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

/* *********************************************************
 *						Include							   *
 ********************************************************* */

#include "LIB.h"
#include "Matrice.h"
#include "FCTDiscret.h"
#include "Signal.h"

/* *********************************************************
 *					SYSETATDiscret						   *
 ********************************************************* */

class SYSETATDiscret
{
public:

	/* *********************************************************
	 *				constructeurs et destructeur			   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : SYSETATDiscret															   */
	/* ROLE : Constructeur par défaut													   */
	/* INPUT  PARAMETERS : void			 												   */
	/* OUTPUT PARAMETERS : Création d'un système d'état									   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	SYSETATDiscret();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : SYSETATDiscret															   */
	/* ROLE : Constructeur par Recopie													   */
	/* INPUT  PARAMETERS : const SYSETATDiscret& : objet à copier						   */
	/* OUTPUT PARAMETERS : Création d'un système d'état copie de l'entrée				   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	SYSETATDiscret
	(
		const SYSETATDiscret&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~SYSETATDiscret															   */
	/* ROLE : Destructeur de la classe SYSETATDiscret									   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : Objet SYSETATDiscret détruit									   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	~SYSETATDiscret();

public: 

	/* *********************************************************
	 *			opérations entre 2 objets SYSETATDiscret	   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator ==																   */
	/* ROLE : Redéfinition de l'opérateur ==											   */
	/* ROLE : Comparaison entre les 2 SYSETATDiscret en Input							   */
	/* INPUT  PARAMETERS : const SYSETATDiscret& a : un objet SYSETATDiscret 			   */
	/* INPUT  PARAMETERS : const SYSETATDiscret& b : un objet SYSETATDiscret			   */
	/* OUTPUT PARAMETERS : Comparaison													   */
	/* RETURNED VALUE    : bool : == -> true // != -> false								   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend bool operator ==
	(
		const SYSETATDiscret&,
		const SYSETATDiscret&
	);

public:

	/* *********************************************************
	 *					opérations sur l'objet				   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : calculABCD																   */
	/* ROLE : Calcul des matrices A, B, C et D à partir d'une FCTDiscret				   */
	/* INPUT  PARAMETERS : const FCTDiscret& fct : FCTDiscret prédéfini		 			   */
	/* OUTPUT PARAMETERS : Matrices A, B, C et D remplies								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void calculABCD
	(
		/* IN */
		const FCTDiscret* const fct
	);
		
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : simulation																   */
	/* ROLE : Simulation du système d'état avec un signal en entré et une matrice x0	   */
	/* ROLE : Calcul echantillon par echantillon le signal de sorti						   */
	/* INPUT  PARAMETERS : const std::string& namefile : fichier d'enregistrement		   */
	/* INPUT  PARAMETERS : Signal& signal : Signal en entrée du système					   */
	/* INPUT  PARAMETERS : Matrice& x0 : Matrice d'initialisation à t0		 			   */
	/* INPUT  PARAMETERS : double* yOut	: tableau de sortie	(index : t0, t1, t2, ...)	   */
	/* OUTPUT PARAMETERS : Réponse temporelle du système								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void simulation
	(
		const std::string& namefile,
		Signal& signal,
		Matrice& x0,
		double* yOut
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
	/* INPUT  PARAMETERS : const SYSETATDiscret& s : Le SYSETATDiscret à afficher		   */
	/* OUTPUT PARAMETERS : affichage textuelle de SYSETATDiscret sur la console			   */
	/* RETURNED VALUE    : std::ostream& : std::cout, ...								   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend std::ostream& operator<<
	(
		std::ostream&,
		const SYSETATDiscret&
		);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : printOn																	   */
	/* ROLE : Création d'une représentation visuelle de SYSETATDiscre					   */
	/* INPUT  PARAMETERS : bool on = true : si true -> affichage direct ... 			   */
	/* INPUT  PARAMETERS : ... sur std::cout // sinon false								   */
	/* OUTPUT PARAMETERS : chaine de caratères représentant de SYSETATDiscret			   */
	/* RETURNED VALUE    : std::string : chaine de caratères							   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	std::string printOn
	(
		bool on = true
	)const;

public:

	/* *********************************************************
	 *							Test						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : testSYSETATDiscret														   */
	/* ROLE : For DEV only																   */
	/* ROLE : Test des méthodes et fonctions de la classe SYSETATDiscret				   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : Test de la classe											   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void testSYSETATDiscret();

public:

	/* *********************************************************
	 *						 assesseurs						   *
	 ********************************************************* */


	inline void SETA(const Matrice* Z) { *_A = *Z; };
	inline void SETB(const Matrice* Z) { *_B = *Z; };
	inline void SETC(const Matrice* Z) { *_C = *Z; };
	inline void SETD(const Matrice* Z) { *_D = *Z; };
	inline void SETTe(unsigned int Te) { _Te = Te; };

	inline Matrice* GETA()const { return _A; };
	inline Matrice* GETB()const { return _B; };
	inline Matrice* GETC()const { return _C; };
	inline Matrice* GETD()const { return _D; };
	inline double GETTe()const	{ return _Te; };

private:

	/* *********************************************************
	 *						Attributs						   *
	 ********************************************************* */


	Matrice *_A,
			*_B,
			*_C,
			*_D;
	double _Te;
};

#endif // !SYSETATDiscret_H

/*
*	End Of File : SYSETATDiscret.h
*/
