/*

	Discrete_system
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
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

/* *********************************************************
 *						Includes						   *
 ********************************************************* */

#include "Complexe.h"

const double Pi = 3.14159265358979323846;

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
Complexe::Complexe()
:
_Re(1),
_Im(1)
{
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Complexe																	   */
/* ROLE : Constructeur par cast de la partie Réelle									   */
/* INPUT  PARAMETERS : double Re : Partie Réelle			 						   */
/* OUTPUT PARAMETERS : Création d'un objet Complexe = Re + 0 * i					   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Complexe::Complexe
(
	double Re
) 
:
_Re(Re),
_Im(0)
{
}

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
Complexe::Complexe
(
	double Re,
	double Im
)
:
_Re(Re),
_Im(Im)
{
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Complexe																	   */
/* ROLE : Constructeur par Recopie													   */
/* INPUT  PARAMETERS : void			 												   */
/* OUTPUT PARAMETERS : Création d'un objet Complexe	recopie de l'entrée				   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Complexe::Complexe
(
	const Complexe& a
)
:
_Re(a._Re),
_Im(a._Im)
{
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : ~Complexe																	   */
/* ROLE : Destructeur de la classe Complexe											   */
/* INPUT  PARAMETERS : void			 												   */
/* OUTPUT PARAMETERS : Objet Complexe détruit										   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Complexe::~Complexe()
{
}

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
Complexe& Complexe::operator =
(
	const Complexe& a
)
{
	if (this != &a)
	{
		_Re = a.GETRe();
		_Im = a.GETIm();
	}
	return *this;
}

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
bool operator ==
(
	const Complexe& a,
	const Complexe& b
)
{
	if	(
			(a.GETRe() == b.GETRe())
			&&
			(a.GETIm() == b.GETIm())
		)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

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
Complexe operator+
(
	const Complexe& a,
	const Complexe& b
)
{
	Complexe resultat
	(
		a.GETRe() + b.GETRe(),
		a.GETIm() + b.GETIm()
	);
	return resultat;
}

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
Complexe operator-
(
	const Complexe& a,
	const Complexe& b
)
{
	Complexe resultat
	(
		a.GETRe() - b.GETRe(),
		a.GETIm() - b.GETIm()
	);
	return resultat;
}

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
Complexe operator*
(
	const Complexe& a,
	const Complexe& b
)
{
	Complexe resultat
	(
		a.GETRe() * b.GETRe() - (a.GETIm() * b.GETIm()),
		2 * a.GETRe() * b.GETIm()
	);
	return resultat;
}

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
Complexe operator/
(
	const Complexe& a,
	const Complexe& b
)
{
	Complexe resultat
	(
		(a.GETRe() * b.GETRe() + a.GETIm() * b.GETIm()) / (pow(b.GETRe(), 2) + pow(b.GETIm(), 2)),
		(a.GETIm() * b.GETRe() + a.GETRe() * b.GETIm()) / (pow(b.GETRe(), 2) + pow(b.GETIm(), 2))
	);
	return resultat;
}


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
double Complexe::module
(
	const Complexe& a
)
{
	return sqrt(pow(a.GETRe(), 2) + pow(a.GETIm(), 2));
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : arg																		   */
/* ROLE : Calcul de l'argument d'un Complexe										   */
/* INPUT  PARAMETERS : const Complexe a : un objet Complex							   */
/* OUTPUT PARAMETERS : (atan(Im / Re)) * (180 / Pi)									   */
/* RETURNED VALUE    : Argument du Complexe											   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
double Complexe::arg
(
	const Complexe& a
)
{
	/* ---------------------------------------------------------------------- */
	/* argument en degrés													  */
	/* ---------------------------------------------------------------------- */
	double argument(atan(a.GETIm() / a.GETRe()) * (180 / Pi));
	if (a.GETRe() < 0)
		argument += Pi;
	return argument;
}

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
Complexe Complexe::tfReIm
(
	double module,
	double arg
)
{
	/* ---------------------------------------------------------------------- */
	/* argument en degrés													  */
	/* ---------------------------------------------------------------------- */
	Complexe c
	(
		module * cos(arg * (Pi / 180)),
		module * sin(arg * (Pi / 180))
	);
	return c;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : power																		   */
/* ROLE : Calcul du Complexe à la puissance power									   */
/* INPUT  PARAMETERS : unsigned int power : puissance à appliquer au Complexe		   */
/* OUTPUT PARAMETERS : Complexe à la puissance power								   */
/* RETURNED VALUE    : Complexe														   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Complexe Complexe::power
(
	unsigned int power
)
{
	if (power == 1)
	{
		return *this;
	}
	else if (power > 1)
	{
		Complexe c(*this);
		for (unsigned int i(1); i < power; i++)
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
Complexe Complexe::tfPolynomeComplexe
(
	const Polynome& P,
	Complexe& Z
)
{
	Complexe c;
	for (unsigned int j(0); j <= P.GETorder(); j++)
		c = P.GETcoefTab(j) * Z.power(j) + c;
	return c;
}


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
std::ostream& operator<<
(
	std::ostream& os,
	const Complexe& c
)
{
	return os << c.printOn(false);
}

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
const std::string Complexe::printOn
(
	bool on
)const
{
	std::string texte("");
	std::ostringstream stream;

	if (_Re != 0)
		stream << _Re;
	if (_Im != 0)
	{
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
void testComplexe()
{
	std::string texte("");
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

/* *********************************************************
 *						 assesseurs						   *
 ********************************************************* */

 /* Define in Complexe.h */

/*
*	End Of File : Complexe.cpp
*/