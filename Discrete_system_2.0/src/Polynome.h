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

#ifndef Polynome_H
#define Polynome_H

/* *********************************************************
 *						Include							   *
 ********************************************************* */

#include "LIB.h"

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

/* Définition d'un Polynome d'ordre 0 -> 1 coefficent  */
const Uint8 ORDER_ZERO = 1;

const double INVERSE_POLYNOME = -1.0;

const double INITIAL_VALUE_MULT = 0.0;


enum class opPolyn : bool 
{
	Plus = true,
	Minus = false
};

/* *********************************************************
 *					Class Polynome						   *
 ********************************************************* */

class Polynome
{
public:

	/* *********************************************************
	 *				constructeurs et destructeur			   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* NAME : Polynome																	   */
	/* ROLE : Constructeur par défaut													   */
	/* INPUT  PARAMETERS : void			 												   */
	/* OUTPUT PARAMETERS : Création d'un objet Polynome	d'ordre 1 -> (X + 1)			   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	Polynome();

	/* ----------------------------------------------------------------------------------- */
	/* NAME : Polynome																	   */
	/* ROLE : Constructeur / ordre du Polynome											   */
	/* ROLE : Polynome a((unsigned int)2) est la seule façon de créer un polynome d'ordre 2*/
	/* INPUT  PARAMETERS : unsigned int order : ordre du Polynome						   */
	/* OUTPUT PARAMETERS : Création d'un objet Polynome	d'ordre order					   */
	/* OUTPUT PARAMETERS : exemple : X^order + X^(order-1) + .... + X + 1				   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	Polynome
	(
		unsigned int order
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : Polynome																	   */
	/* ROLE : Constructeur / cast de la valeur en entrée (Polynome d'ordre 0)			   */
	/* INPUT  PARAMETERS : double userValue : valeur du Polynome d'ordre 0				   */
	/* OUTPUT PARAMETERS : Polynome d'ordre 0 / valeur = userValue						   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	Polynome
	(
		double userValue
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : Polynome																	   */
	/* ROLE : Constructeur / cast de la valeur en entrée (Polynome d'ordre 0)			   */
	/* INPUT  PARAMETERS : double userValue : valeur du Polynome d'ordre 0				   */
	/* OUTPUT PARAMETERS : Polynome d'ordre 0 / valeur = userValue						   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	Polynome
	(
		unsigned int order,
		double userValue
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : Polynome																	   */
	/* ROLE : Polynome d'ordre order avec les coefficents tab[]							   */
	/* INPUT  PARAMETERS : unsigned int order : ordre du Polynome						   */
	/* INPUT  PARAMETERS : double tab[] : tableau de coefficents						   */
	/* OUTPUT PARAMETERS : Polynome d'ordre order avec les coefficents tab[]			   */
	/* OUTPUT PARAMETERS : tab[order] * X^order + tab[order-1] * X^(order-1) + ...		   */
	/* OUTPUT PARAMETERS : .... + tab[1] * X + tab[0] * 1								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	Polynome
	(
		unsigned int order,
		double tab[]
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : Polynome																	   */
	/* ROLE : Constructeur par recopie													   */
	/* INPUT  PARAMETERS : const Polynome& P : Polynome à copier						   */
	/* OUTPUT PARAMETERS : Recopie du Polynome en entrée								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	Polynome
	(
		const Polynome& P
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~Polynome																	   */
	/* ROLE : Destructeur de la classe Polynome											   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : Objet Polynome détruit										   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	~Polynome();

protected:

	/* *********************************************************
	 *				 allocate et test d'index				   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* NAME : allocate																	   */
	/* ROLE : Création d'un tableau de coefficents 1 de taille size 					   */
	/* INPUT  PARAMETERS : unsigned int size : taille du tableau de coefficents			   */
	/* OUTPUT PARAMETERS : Création d'un tableau de coefficents 1 de taille size		   */
	/* RETURNED VALUE    : double* : tableau de coefficents								   */
	/* ------------------------------------------------------------------------------------*/
	virtual double* allocate
	(
		unsigned int size
	) const;

	/* ----------------------------------------------------------------------------------- */
	/* NAME : allocate																	   */
	/* ROLE : Création d'un tableau de coefficents unique userValue de taille size 		   */
	/* INPUT  PARAMETERS : unsigned int size : taille du tableau de coefficents			   */
	/* INPUT  PARAMETERS : double userValue : valeur unique des coefficents				   */
	/* OUTPUT PARAMETERS : Création d'un tableau de coefficents de taille size			   */
	/* RETURNED VALUE    : double* : tableau de coefficents								   */
	/* ------------------------------------------------------------------------------------*/
	virtual double* allocate
	(
		unsigned int size,
		double userValue
	) const;

	/* ----------------------------------------------------------------------------------- */
	/* NAME : allocate																	   */
	/* ROLE : Création d'un tableau de coefficents tab[] de taille size 				   */
	/* INPUT  PARAMETERS : unsigned int size : taille du tableau de coefficents			   */
	/* INPUT  PARAMETERS : double* tab : tableau de coefficents							   */
	/* OUTPUT PARAMETERS : Création d'un tableau de coefficents tab[] de taille size	   */
	/* RETURNED VALUE    : double* : tableau de coefficents								   */
	/* ------------------------------------------------------------------------------------*/
	virtual double* allocate
	(
		unsigned int size,
		double* tab
	) const;

	/* ----------------------------------------------------------------------------------- */
	/* NAME : allocate																	   */
	/* ROLE : Recopie et Création d'un tableau de coefficents							   */
	/* INPUT  PARAMETERS : const Polynome& P : Polynome à recopier						   */
	/* OUTPUT PARAMETERS : Recopie du Polynome											   */
	/* RETURNED VALUE    : double* : tableau de coefficents								   */
	/* ------------------------------------------------------------------------------------*/
	virtual double* allocate
	(
		const Polynome& P
	) const;

	/* ----------------------------------------------------------------------------------- */
	/* NAME : assertIndex																   */
	/* ROLE : Test si l'index en entrée est dans le range du tableau de coefficent		   */
	/* ROLE : Min : 0 (implicite car unsigned int)									       */
	/* ROLE : Max : L'ordre du Polynome													   */
	/* INPUT  PARAMETERS : unsigned int index : index à tester							   */
	/* OUTPUT PARAMETERS : In Range or Out Of Range										   */
	/* RETURNED VALUE    : bool : false -> Out Of Range / true -> In Range				   */
	/* ------------------------------------------------------------------------------------*/
	bool assertIndex
	(
		unsigned int index
	) const;

public:

	/* *********************************************************
	 *			 opérations sur 2 objets Polynome			   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator =																   */
	/* ROLE : Redéfinition de l'opérateur =												   */
	/* INPUT  PARAMETERS : const Polynome& P : objet permettant l'égalisation			   */
	/* OUTPUT PARAMETERS : this = P														   */
	/* RETURNED VALUE    : Polynome& : return this										   */
	/* ------------------------------------------------------------------------------------*/
	Polynome& operator=
	(
		const Polynome&
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator ==																   */
	/* ROLE : Redéfinition de l'opérateur ==											   */
	/* ROLE : Comparaison entre les 2 Polynome en Input									   */
	/* INPUT  PARAMETERS : const Polynome& a : un objet Polynome 						   */
	/* INPUT  PARAMETERS : const Polynome& b : un objet Polynome						   */
	/* OUTPUT PARAMETERS : Comparaison													   */
	/* RETURNED VALUE    : bool : == -> true // != -> false								   */
	/* ------------------------------------------------------------------------------------*/
	friend bool operator==
	(
		const Polynome&,
		const Polynome&
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME: operator+																	   */
	/* ROLE: Redéfinition de l'opérateur +												   */
	/* ROLE: Addition entre les 2 Inputs												   */
	/* RVALUE: retourne un objet résultat de l'addition	a + b 							   */
	/* ------------------------------------------------------------------------------------*/
	friend Polynome operator+
	(
		/* IN */
		const Polynome& a,
		const Polynome& b
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME: operator-																	   */
	/* ROLE: Redéfinition de l'opérateur -												   */
	/* ROLE: Soustraction entre les 2 Inputs											   */
	/* RVALUE: un objet résultat de la soustraction	a - b								   */
	/* ------------------------------------------------------------------------------------*/
	friend Polynome operator-
	(
		/* IN */
		const Polynome& a,
		const Polynome& b
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator*																	   */
	/* ROLE : Redéfinition de l'opérateur *												   */
	/* ROLE : Multiplication entre les 2 Inputs											   */
	/* RVALUE: résultat de la multiplication (a * b)									   */
	/* ------------------------------------------------------------------------------------*/
	friend Polynome operator*
	(
		/* IN */
		const Polynome& a,
		const Polynome& b
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME: checkNewOrder																   */
	/* ROLE: Check the real size of a Polynome											   */
	/* RVALUE: false: No diff ; true: the order has been reduced						   */
	/* ------------------------------------------------------------------------------------*/
	friend bool checkNewOrder
	(
		/* INOUT */
		Polynome& newPolynome
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME: clearPolynome																   */
	/* ROLE: Clear and delete the Polynome, to zero										   */
	/* RVALUE: 0 : NO_ERROR																   */
	/* ------------------------------------------------------------------------------------*/
	int clearPolynome();

	/* ----------------------------------------------------------------------------------- */
	/* NAME: getByCopyReversePolynomeOrder												   */
	/* ROLE: Set dest value in inverse order than src									   */
	/* RVALUE: void																		   */
	/* ------------------------------------------------------------------------------------*/
	friend void getByCopyReversePolynomeOrder
	(
		/* IN */
		const Polynome& src,
		/* OUT */
		Polynome& dest
	);

public: 

	/* *********************************************************
	 *					opération sur l'objet				   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator[]																   */
	/* ROLE : Operator redifinition []													   */
	/* ROLE : Access Polynome's values with []											   */
	/* RVALUE: Value at the index														   */
	/* ------------------------------------------------------------------------------------*/
	double& operator[]
	(
		/* IN */
		const unsigned int index
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator[]																   */
	/* ROLE : Operator redifinition []													   */
	/* ROLE : Access Polynome's values with []											   */
	/* RVALUE: Value at the index														   */
	/* ------------------------------------------------------------------------------------*/
	const double& operator[]
	(
		/* IN */
		const unsigned int index
	)const;

	/* ----------------------------------------------------------------------------------- */
	/* NAME: grow																		   */
	/* ROLE: Grow the actual Polynome by 1 order with userValue 						   */
	/* RVALUE: void																		   */
	/* ------------------------------------------------------------------------------------*/
	void grow
	(
		/* IN */
		const double userValue
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME: Shrink																		   */
	/* ROLE: Shrink the actual Polynome by 1 order										   */
	/* RVALUE: void																		   */
	/* ------------------------------------------------------------------------------------*/
	void shrink();


public:

	/* *********************************************************
	 *						Utilitaire						   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* NAME: isNegative																	   */
	/* ROLE: Check if the last order is negative										   */
	/* RVALUE: true if negative ; false if positive										   */
	/* ------------------------------------------------------------------------------------*/
	bool isNegative()const;

	/* ----------------------------------------------------------------------------------- */
	/* NAME: inverseSign																   */
	/* ROLE: Inverse the sign for each order of the Polynome							   */
	/* RVALUE: None																		   */
	/* ------------------------------------------------------------------------------------*/
	void inverseSign();


public:

	/* *********************************************************
	 *						 affichage						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* NAME : operator<<																   */
	/* ROLE : Redéfinition de l'opérateur <<											   */
	/* ROLE : Envoi sur le ostream (std::cout, ...) une forme textuelle ...				   */
	/* ROLE : ... de l'objet créée par la fonction printOn								   */
	/* INPUT  PARAMETERS : std::ostream& os : stream de sortie : std::cout, ...			   */
	/* INPUT  PARAMETERS : const Polynome& s : Le Polynome à afficher					   */
	/* OUTPUT PARAMETERS : affichage textuelle du Polynome sur la console				   */
	/* RETURNED VALUE    : std::ostream& : std::cout, ...								   */
	/* ------------------------------------------------------------------------------------*/
	friend std::ostream& operator<<
	(
		std::ostream& os,
		const Polynome&
	);

	/* ----------------------------------------------------------------------------------- */
	/* NAME : printOn																	   */
	/* ROLE : Création d'une représentation visuelle du Polynome						   */
	/* INPUT  PARAMETERS : bool on = true : si true -> affichage direct ... 			   */
	/* INPUT  PARAMETERS : ... sur std::cout // sinon false								   */
	/* OUTPUT PARAMETERS : chaine de caratères représentant le Polynome					   */
	/* RETURNED VALUE    : std::string : chaine de caratères							   */
	/* ------------------------------------------------------------------------------------*/
	std::string printOn
	(
		bool = true
	) const;

public:

	/* *********************************************************
	 *							TEST						   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* NAME : testPolynome																   */
	/* ROLE : For DEV only																   */
	/* ROLE : Test des méthodes et fonctions de la classe Polynome						   */
	/* INPUT  PARAMETERS : void															   */
	/* OUTPUT PARAMETERS : Test de la classe											   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	static void testPolynome();

public:

	/* *********************************************************
	 *						 assesseurs						   *
	 ********************************************************* */

	void SETorder		(unsigned int order);
	void SETcoefTab		(unsigned int index, double userValue);

	unsigned int GETorder() const;
	double& GETcoefTab(unsigned int index) const;
	unsigned int GETstringSize() const;

private:

	/* *********************************************************
	 *						 Attributs						   *
	 ********************************************************* */

	unsigned int _order;
	double* _tab;
	mutable unsigned int _stringSize;
};

/* Polynome to transform negative Polynome to Positive */
const Polynome NEGATIVE_2_POSITIVE_COEF = -1.0;

#endif // !Polynome_H

/*
*	End Of File : Polynome.h
*/