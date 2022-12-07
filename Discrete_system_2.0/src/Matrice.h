/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	file version 4.0

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

/* *********************************************************
 *						Include							   *
 ********************************************************* */

#include "LIB.h"

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

/* Valeur arbitraire maximal pour �viter des probl�mes de m�moires */
const Uint16 MAX_MATRICE_SIZE = 10000;

/* Valeur d'agrandissement de 1 ligne et de 1 colonne*/
const Uint8 GROW1L1C = 1;

/* *********************************************************
 *						Class Matrice					   *
 ********************************************************* */

class Matrice
{
public:

	/* *********************************************************
	 *				constructeurs et destructeur			   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Matrice																	   */
	/* ROLE : Constructeur par d�faut													   */
	/* ROLE : ( 0 | 0 )																	   */
	/* ROLE : ( 0 | 0 )																	   */
	/* INPUT  : void					 												   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Matrice();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Matrice																	   */
	/* ROLE : Constructeur cast d'un double vers un objet Matice						   */
	/* ROLE : ( Value | Value )															   */
	/* ROLE : ( Value | Value )															   */
	/* INPUT : double Value : Valeur unique des coefficients de la Matrice				   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Matrice
	(
		double Value
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Matrice																	   */
	/* ROLE : Constructeur par taille													   */
	/* ROLE : ( 0 | ... | 0 )															   */
	/* ROLE : ( . | ... | . )															   */
	/* ROLE : ( 0 | ... | 0 )															   */
	/* INPUT  : unsigned int lenght : nombre de colonnes								   */
	/* INPUT  : unsigned int height : nombre de lignes									   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Matrice
	(
		unsigned int lenght,
		unsigned int height
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Matrice																	   */
	/* ROLE : Constructeur par taille et par valeur	de tab								   */
	/* ROLE : (    tab[0][0]   | ... |   tab[lenght][0]    )							   */
	/* ROLE : ( .............. | ... | ................... )							   */
	/* ROLE : ( tab[0][height] | ... | tab[lenght][height] )							   */
	/* INPUT : double** tab : tableau de valeur											   */
	/* INPUT : unsigned int lenght : nombre de colonnes									   */
	/* INPUT : unsigned int height : nombre de lignes									   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Matrice
	(
		double** tab,
		unsigned int length,
		unsigned int height
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Matrice																	   */
	/* ROLE : Constructeur par Recopie													   */
	/* INPUT  : const Matrice& M : Matrice � copier						 				   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Matrice
	(
		const Matrice& M
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~Matrice																	   */
	/* ROLE : Destructeur de la classe Matrice											   */
	/* INPUT  : void																	   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	~Matrice();

public:

	/* *********************************************************
	 *					assert and allocate					   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : allocate																	   */
	/* ROLE : Alloue un tableau de taille length et height de type double initialis� � 0   */
	/* INPUT  : unsigned int lenght : Nombre de colonnes								   */
	/* INPUT  : unsigned int height : Nombre de lignes									   */
	/* OUTPUT : Matrice de taille length et height contenant les 0						   */
	/* RETURNED VALUE    : double** : matrice de taille length et height contenant les 0   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	virtual double** allocate
	(
		unsigned int length,
		unsigned int height
	)const;

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : allocate																	   */
	/* ROLE : Alloue un tableau de tableau de taille length et height ...				   */
	/* ROLE : ... de type double initialis� � Value										   */
	/* INPUT  PARAMETERS : unsigned int lenght : Nombre de colonnes						   */
	/* INPUT  PARAMETERS : unsigned int height : Nombre de lignes						   */
	/* INPUT  PARAMETERS : double Value : Valeur d'initialisation						   */
	/* OUTPUT PARAMETERS : Matrice de taille length et height contenant les Value		   */
	/* RETURNED VALUE    : double** : matrice de taille length et height				   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	virtual double** allocate
	(
		unsigned int length,
		unsigned int height,
		double Value
	) const;

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : allocate																	   */
	/* ROLE : Recopie de l'attribut _tab de la Matrice en entr�e						   */
	/* INPUT  PARAMETERS : const Matrice& : Matrice de recopie							   */
	/* OUTPUT PARAMETERS : Matrice de taille length et height contenant la recopie 		   */
	/* RETURNED VALUE    : double** : matrice de taille length et height				   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	virtual double** allocate
	(
		const Matrice&
	) const;

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deAllocate																   */
	/* ROLE : D�truit l'allocation dynamique de tab										   */
	/* INPUT  PARAMETERS : unsigned int lenght : Nombre de colonnes						   */
	/* INPUT  PARAMETERS : double** tab : tableau de valeur								   */
	/* OUTPUT PARAMETERS : delete tab													   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void deAllocate
	(
		unsigned int length,
		double** tab
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : assertIndex																   */
	/* ROLE : Test in range pour length et height compar� � ceux dans la Matrice		   */
	/* INPUT  PARAMETERS : unsigned int lenght : Nombre de colonnes						   */
	/* INPUT  PARAMETERS : unsigned int height : Nombre de lignes						   */
	/* OUTPUT PARAMETERS : Validation Out Of Range ou In Range							   */
	/* RETURNED VALUE    : bool : false -> length and/or height Out Of Range of Matrice	   */
	/* RETURNED VALUE    : bool : true -> length and height In Range of Matrice			   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	bool assertIndex
	(
		unsigned int length,
		unsigned int height
	)const;

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : assertRange																   */
	/* ROLE : Test in range > 0 et MAX_MATRICE_SIZE										   */
	/* INPUT  PARAMETERS : unsigned int lenght : Nombre de colonnes						   */
	/* INPUT  PARAMETERS : unsigned int height : Nombre de lignes						   */
	/* OUTPUT PARAMETERS : Validation Out Of Range ou In Range							   */
	/* RETURNED VALUE    : bool : false -> length and/or height Out Of Range of Matrice	   */
	/* RETURNED VALUE    : bool : true -> length and height In Range of Matrice			   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	bool assertRange
	(
		unsigned int length,
		unsigned int height
	)const;

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : assertSize																   */
	/* ROLE : Test le premier couple == deuxi�me couple									   */
	/* INPUT  PARAMETERS : unsigned int lenghtA : Nombre de colonnes Matrice A			   */
	/* INPUT  PARAMETERS : unsigned int heightA : Nombre de lignes Matrice A			   */
	/* INPUT  PARAMETERS : unsigned int lenghtB : Nombre de colonnes Matrice B			   */
	/* INPUT  PARAMETERS : unsigned int heightB : Nombre de lignes Matrice B			   */
	/* OUTPUT PARAMETERS : Validation si meme taille									   */
	/* RETURNED VALUE    : bool : false -> length and/or height Out Of Range of Matrice	   */
	/* RETURNED VALUE    : bool : true -> length and height In Range of Matrice			   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static bool assertSize
	(
		unsigned int lenghtA,
		unsigned int heightA,
		unsigned int lenghtB,
		unsigned int heightB
	);

public: 

	/* *********************************************************
	 *			op�rations entre 2 objets Matrice			   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator =																   */
	/* ROLE : Red�finition de l'op�rateur =												   */
	/* INPUT  PARAMETERS : const Matrice& P : objet permettant l'�galisation			   */
	/* OUTPUT PARAMETERS : this = P														   */
	/* RETURNED VALUE    : Matrice& : return this										   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Matrice& operator=
	(
		const Matrice&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator ==																   */
	/* ROLE : Red�finition de l'op�rateur ==											   */
	/* ROLE : Comparaison entre les 2 Polynome en Input									   */
	/* INPUT  PARAMETERS : const Matrice& a : un objet Matrice 							   */
	/* INPUT  PARAMETERS : const Matrice& b : un objet Matrice							   */
	/* OUTPUT PARAMETERS : Comparaison													   */
	/* RETURNED VALUE    : bool : == -> true // != -> false								   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend bool operator==
	(
		const Matrice&,
		const Matrice&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator+																	   */
	/* ROLE : Red�finition de l'op�rateur +												   */
	/* ROLE : Addition entre les 2 Inputs												   */
	/* INPUT  PARAMETERS : const Matrice& a : un objet Matrice 							   */
	/* INPUT  PARAMETERS : const Matrice& b : un objet Matrice							   */
	/* OUTPUT PARAMETERS : r�sultat de l'addition (a + b)								   */
	/* RETURNED VALUE    : Matrice : retourne un objet r�sultat de l'addition			   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend Matrice operator+
	(
		const Matrice&,
		const Matrice&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator-																	   */
	/* ROLE : Red�finition de l'op�rateur -												   */
	/* ROLE : Soustraction entre les 2 Inputs											   */
	/* INPUT  PARAMETERS : const Matrice& a : un objet Matrice 							   */
	/* INPUT  PARAMETERS : const Matrice& b : un objet Matrice							   */
	/* OUTPUT PARAMETERS : r�sultat de soustraction (a - b)								   */
	/* RETURNED VALUE    : Matrice : retourne un objet r�sultat de la soustraction		   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend Matrice operator-
	(
		const Matrice&,
		const Matrice&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator*																	   */
	/* ROLE : Red�finition de l'op�rateur *												   */
	/* ROLE : Multiplication entre les 2 Inputs											   */
	/* INPUT  PARAMETERS : const Matrice& a : un objet Matrice	 						   */
	/* INPUT  PARAMETERS : const Matrice& b : un objet Matrice							   */
	/* OUTPUT PARAMETERS : r�sultat de la multiplication (a * b)						   */
	/* RETURNED VALUE    : Matrice : retourne un objet r�sultat de la multiplication	   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend Matrice operator*
	(
		const Matrice&,
		const Matrice&
	);

public:

	/* *********************************************************
	 *					op�rations sur l'objet				   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : fillTabLoop																   */
	/* ROLE : Rempli la Matrice de taille length * height de valeur value				   */
	/* INPUT  PARAMETERS : unsigned int length : Nombre de colonnes						   */
	/* INPUT  PARAMETERS : unsigned int height : Nombre de lignes						   */
	/* INPUT  PARAMETERS : double*** tab : Ptr Matrice � remplir						   */
	/* INPUT  PARAMETERS : double value : Valeur � appliquer							   */
	/* OUTPUT PARAMETERS : Matrice remplie de value										   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void fillTabLoop
	(
		unsigned int length,
		unsigned int height,
		double** tab,
		double value
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : transposition																   */
	/* ROLE : Transpose la Matrice en entr�e											   */
	/* INPUT  PARAMETERS : const Matrice& : Matrice � transposer						   */
	/* OUTPUT PARAMETERS : Transpos� de la Matrice en entr�e							   */
	/* RETURNED VALUE    : Matrice														   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend Matrice transposition
	(
		const Matrice&
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : zero																		   */
	/* ROLE : Rempli la Matrice de taille length * height de 0							   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : Matrice remplie de 0											   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void zero();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ones																		   */
	/* ROLE : Rempli la Matrice de taille length * height de 1							   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : Matrice remplie de 1											   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void ones();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : editSize																	   */
	/* ROLE : Changement de taille de la Matrice 										   */
	/* ROLE : Si plus grand remplissage 0, si plus petit suppression des derniers		   */
	/* INPUT  PARAMETERS : unsigned int length : Nombre de colonnes						   */
	/* INPUT  PARAMETERS : unsigned int height : Nombre de lignes						   */
	/* OUTPUT PARAMETERS : Matrice agrandie ou rapetissie								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void editSize
	(
		unsigned int length,
		unsigned int height
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : growOneLOneC																   */
	/* ROLE : Agrandie de 1 le nombre colonnes et de lignes de la Matrice  				   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : Matrice agrandie de 1 remplie de 0							   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	void growOneLOneC();

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
	/* INPUT  PARAMETERS : const Matrice& s : La Matrice � afficher						   */
	/* OUTPUT PARAMETERS : affichage textuelle de la Matrice sur la console				   */
	/* RETURNED VALUE    : std::ostream& : std::cout, ...								   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend std::ostream& operator<<
	(
		std::ostream&,
		const Matrice&
	);


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : printOn																	   */
	/* ROLE : Cr�ation d'une repr�sentation visuelle de la Matrice						   */
	/* INPUT  PARAMETERS : bool on = true : si true -> affichage direct ... 			   */
	/* INPUT  PARAMETERS : ... sur std::cout // sinon false								   */
	/* OUTPUT PARAMETERS : chaine de carat�res repr�sentant de la Matrice				   */
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
	/* NAME : testMatrice																   */
	/* ROLE : For DEV only																   */
	/* ROLE : Test des m�thodes et fonctions de la classe Matrice						   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : Test de la classe											   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	friend void testMatrice();

public:

	/* *********************************************************
	 *						 assesseurs						   *
	 ********************************************************* */

	void SETthiscoef(unsigned int i, unsigned int j, double userValue);
	double GETthiscoef(unsigned int i, unsigned int j)const;
	unsigned int GETlength()const;
	unsigned int GETheight()const;

private:

	/* *********************************************************
	 *						Attributs						   *
	 ********************************************************* */

	unsigned int _length;
	unsigned int _height;
	double** _tab;
};

#endif

/*
*	End Of File : Matrice.h
*/