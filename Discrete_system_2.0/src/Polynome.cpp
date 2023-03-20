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

/* *********************************************************
 *						Include							   *
 ********************************************************* */

#include "Polynome.h"

/* *********************************************************
 *					Class FCTDiscret					   *
 ********************************************************* */


/* *********************************************************
 *				constructeurs et destructeur			   *
 ********************************************************* */

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Polynome																	   */
/* ROLE : Constructeur par défaut													   */
/* INPUT  PARAMETERS : void			 												   */
/* OUTPUT PARAMETERS : Création d'un objet Polynome	d'ordre 1 -> X + 1				   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Polynome::Polynome()
:
_order(1),
_tab(allocate(1)),
_stringSize(0)
{
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Polynome																	   */
/* ROLE : Constructeur / ordre du Polynome											   */
/* ROLE : Polynome a((unsigned int)2) est la seule façon de créer un polynome d'ordre 2*/
/* INPUT  PARAMETERS : unsigned int order : ordre du Polynome						   */
/* OUTPUT PARAMETERS : Création d'un objet Polynome	d'ordre order					   */
/* OUTPUT PARAMETERS : exemple : X^order + X^(order-1) + .... + X + 1				   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Polynome::Polynome
(
	unsigned int size
)
:
_order(size),
_tab(allocate(size)),
_stringSize(0)
{
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Polynome																	   */
/* ROLE : Constructeur / cast de la valeur en entrée (Polynome d'ordre 0)			   */
/* INPUT  PARAMETERS : double userValue : valeur du Polynome d'ordre 0				   */
/* OUTPUT PARAMETERS : Polynome d'ordre 0 / valeur = userValue						   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Polynome::Polynome
(
	double userValue
)
:
_order(0),
_tab(allocate(0, userValue)),
_stringSize(0)
{
}

/* ----------------------------------------------------------------------------------- */
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
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
Polynome::Polynome
(
	unsigned int size,
	double tab[]
)
:
_order(size),
_tab(allocate(size,tab)),
_stringSize(0)
{
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : Polynome																	   */
/* ROLE : Constructeur par recopie													   */
/* INPUT  PARAMETERS : const Polynome& P : Polynome à copier						   */
/* OUTPUT PARAMETERS : Recopie du Polynome en entrée								   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Polynome::Polynome
(
	const Polynome& P
)
:
_order(P._order),
_tab(allocate(P)),
_stringSize(0)
{
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : ~Polynome																	   */
/* ROLE : Destructeur de la classe Polynome											   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : Objet Polynome détruit										   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Polynome::~Polynome()
{
	clearPolynome();
}

/* *********************************************************
 *				 allocate et test d'index				   *
 ********************************************************* */

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : allocate																	   */
/* ROLE : Création d'un tableau de coefficents 1 de taille size 					   */
/* INPUT  PARAMETERS : unsigned int size : taille du tableau de coefficents			   */
/* OUTPUT PARAMETERS : Création d'un tableau de coefficents 1 de taille size		   */
/* RETURNED VALUE    : double* : tableau de coefficents								   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
double* Polynome::allocate
(
	unsigned int size
) const
{
	double* buffer(new double[size + ORDER_ZERO]);
	for (unsigned int i(0); i <= size; i++)
		buffer[i] = 1.0;
	return buffer;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : allocate																	   */
/* ROLE : Création d'un tableau de coefficents unique userValue de taille size 		   */
/* INPUT  PARAMETERS : unsigned int size : taille du tableau de coefficents			   */
/* INPUT  PARAMETERS : double userValue : valeur unique des coefficents				   */
/* OUTPUT PARAMETERS : Création d'un tableau de coefficents de taille size			   */
/* RETURNED VALUE    : double* : tableau de coefficents								   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
double* Polynome::allocate
(
	unsigned int size,
	double userValue
) const
{
	double* buffer(new double[size + ORDER_ZERO]);
	for (unsigned int i(0); i <= size; i++)
		buffer[i] = userValue;
	return buffer;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : allocate																	   */
/* ROLE : Création d'un tableau de coefficents tab[] de taille size 				   */
/* INPUT  PARAMETERS : unsigned int size : taille du tableau de coefficents			   */
/* INPUT  PARAMETERS : double* tab : tableau de coefficents							   */
/* OUTPUT PARAMETERS : Création d'un tableau de coefficents tab[] de taille size	   */
/* RETURNED VALUE    : double* : tableau de coefficents								   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
double* Polynome::allocate
(
	unsigned int size,
	double* tab
) const
{
	double* buffer(new double[size + ORDER_ZERO]);
	for (unsigned int i(0); i <= size; i++)
		buffer[i] = tab[i];
	return buffer;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : allocate																	   */
/* ROLE : Recopie et Création d'un tableau de coefficents							   */
/* INPUT  PARAMETERS : const Polynome& P : Polynome à recopier						   */
/* OUTPUT PARAMETERS : Recopie du Polynome											   */
/* RETURNED VALUE    : double* : tableau de coefficents								   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
double* Polynome::allocate
(
	const Polynome& P
) const
{
	double* buffer(new double[P._order + ORDER_ZERO]);
	for (unsigned int i(0); i <= P._order; i++)
		buffer[i] = P._tab[i];
	return buffer;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : assertIndex																   */
/* ROLE : Test si l'index en entrée est dans le range du tableau de coefficent		   */
/* ROLE : Min : 0 (implicite car unsigned int)									       */
/* ROLE : Max : L'ordre du Polynome													   */
/* INPUT  PARAMETERS : unsigned int index : index à tester							   */
/* OUTPUT PARAMETERS : In Range or Out Of Range										   */
/* RETURNED VALUE    : bool : false -> Out Of Range / true -> In Range				   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
bool Polynome::assertIndex
(
	unsigned int index
)const
{
	if (index <= _order)
		return true;
	else
	{
		std::cout << std::endl << "_______Polynome : assertIndex false : index = " << index;
		return false;
	}
}



/* *********************************************************
 *			 opérations sur 2 objets Polynome			   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : operator =																   */
/* ROLE : Redéfinition de l'opérateur =												   */
/* INPUT  PARAMETERS : const Polynome& P : objet permettant l'égalisation			   */
/* OUTPUT PARAMETERS : this = P														   */
/* RETURNED VALUE    : Polynome& : return this										   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Polynome& Polynome::operator=
(
	const Polynome& a
)
{
	if (this != &a)
	{
		if (nullptr != _tab)
			delete  _tab;
		_order = a._order;
		_tab = a.allocate(a);
	}
	return *this;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : operator ==																   */
/* ROLE : Redéfinition de l'opérateur ==											   */
/* ROLE : Comparaison entre les 2 Polynome en Input									   */
/* INPUT  PARAMETERS : const Polynome& a : un objet Polynome 						   */
/* INPUT  PARAMETERS : const Polynome& b : un objet Polynome						   */
/* OUTPUT PARAMETERS : Comparaison													   */
/* RETURNED VALUE    : bool : == -> true // != -> false								   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
bool operator==
(
	const Polynome& a,
	const Polynome& b
)
{
	if (b.GETorder() == a.GETorder())
	{
		for (unsigned int i(0); i < a.GETorder(); i++)
		{
			if (b.GETcoefTab(i) != a.GETcoefTab(i))
				return false;
		}
		return true;
	}
	else
		return false;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : operator+																	   */
/* ROLE : Redéfinition de l'opérateur +												   */
/* ROLE : Addition entre les 2 Inputs												   */
/* INPUT  PARAMETERS : const Polynome& a : un objet Polynome 						   */
/* INPUT  PARAMETERS : const Polynome& b : un objet Polynome						   */
/* OUTPUT PARAMETERS : résultat de l'addition (a + b)								   */
/* RETURNED VALUE    : Polynome : retourne un objet résultat de l'addition			   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Polynome operator+
(
	const Polynome& a,
	const Polynome& b
)
{
	/* ---------------------------------------------------------------------- */
	/* addition de 2 polynomes												  */
	/* en choisissant la nouvelle taille par le plus grand ordre			  */
	/* ---------------------------------------------------------------------- */
	unsigned int maxSize(std::max(a.GETorder(), b.GETorder()));
	unsigned int minSize(std::min(a.GETorder(), b.GETorder()));

	if (!checkNewOrder(a, b, &maxSize, opPolyn::Plus))
	{
		/* Case a - b = 0.0 */
		return 0.0;
	}

	if (maxSize == a.GETorder())
	{
		Polynome newPolynome(a);
		for (unsigned int i(0); i <= minSize; i++)
			newPolynome.SETcoefTab(i, newPolynome.GETcoefTab(i) + b.GETcoefTab(i));
		return newPolynome;
	}
	else
	{
		Polynome newPolynome(b);
		for (unsigned int i(0); i <= minSize; i++)
			newPolynome.SETcoefTab(i, newPolynome.GETcoefTab(i) + a.GETcoefTab(i));
		return newPolynome;
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : operator-																	   */
/* ROLE : Redéfinition de l'opérateur -												   */
/* ROLE : Soustraction entre les 2 Inputs											   */
/* INPUT  PARAMETERS : const Polynome& a : un objet Polynome 						   */
/* INPUT  PARAMETERS : const Polynome& b : un objet Polynome						   */
/* OUTPUT PARAMETERS : résultat de soustraction (a - b)								   */
/* RETURNED VALUE    : Polynome : retourne un objet résultat de la soustraction		   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Polynome operator-
(
	const Polynome& a,
	const Polynome& b
)
{
	/* ---------------------------------------------------------------------- */
	/* soustraction de 2 polynomes											  */
	/* en choisissant la nouvelle taille par le plus grand ordre			  */
	/* ---------------------------------------------------------------------- */
	unsigned int maxSize(std::max(a.GETorder(), b.GETorder()));
	unsigned int minSize(std::min(a.GETorder(), b.GETorder()));

	if (!checkNewOrder(a, b, &maxSize, opPolyn::Minus))
	{ 
		/* Case a - b = 0.0 */
		return 0.0;
	}

	Polynome newPolynome(maxSize);
	if (a.GETorder() == maxSize)
	{
		for (unsigned int i(0); i <= maxSize; i++)
			newPolynome.SETcoefTab(i, a.GETcoefTab(i));
		for (unsigned int i(0); i <= minSize; i++)
			newPolynome.SETcoefTab(i, newPolynome.GETcoefTab(i) - b.GETcoefTab(i));
	}
	else
	{
		for (unsigned int i(0); i <= maxSize; i++)
			newPolynome.SETcoefTab(i, b.GETcoefTab(i));
		for (unsigned int i(0); i <= minSize; i++)
			newPolynome.SETcoefTab(i, newPolynome.GETcoefTab(i) - a.GETcoefTab(i));
	}
	return newPolynome;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : operator*																	   */
/* ROLE : Redéfinition de l'opérateur *												   */
/* ROLE : Multiplication entre les 2 Inputs											   */
/* INPUT  PARAMETERS : const Polynome& a : un objet Polynome 						   */
/* INPUT  PARAMETERS : const Polynome& b : un objet Polynome						   */
/* OUTPUT PARAMETERS : résultat de la multiplication (a * b)						   */
/* RETURNED VALUE    : Polynome : retourne un objet résultat de la multiplication	   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
Polynome operator*
(
	const Polynome& a,
	const Polynome& b
)
{
	unsigned int maxSize(a.GETorder() + b.GETorder());

	Polynome newPolynome(maxSize);
	for (unsigned int i(0); i <= a.GETorder(); i++)
	{
		for (unsigned int j(0); j <= b.GETorder(); j++)
			newPolynome.SETcoefTab(i + j, newPolynome.GETcoefTab(i + j) + a.GETcoefTab(i) * b.GETcoefTab(j));
	}
	return newPolynome;
}

bool checkNewOrder
(
	const Polynome& a,
	const Polynome& b,
	unsigned int* maxSize,
	opPolyn operatorPoly
)
{
	unsigned int varSizeA(a.GETorder()), varSizeB(b.GETorder());

	while (varSizeA == varSizeB)
	{
		if	(
				(a.GETcoefTab(varSizeA) - b.GETcoefTab(varSizeB) == 0.0 && operatorPoly == opPolyn::Minus)
				||
				(a.GETcoefTab(varSizeA) + b.GETcoefTab(varSizeB) == 0.0 && operatorPoly == opPolyn::Plus)
			)
		{
			if (*maxSize == 0)
			{
				/* Case if a - b = 0.0 */
				/* Case if a + b = 0.0 */
				return false;
			}

			(*maxSize)--;
			varSizeA--;
			varSizeB--;
		}
		else
		{
			return true;
		}
	}
	return true;
}

void fillOpPlus
(
	const Polynome& a,
	const Polynome& b,
	unsigned int maxSize,
	Polynome& outPlus
)
{
	for (unsigned int i(0); i <= maxSize; i++)
		outPlus.SETcoefTab(i, a.GETcoefTab(i));
	for (unsigned int i(0); i <= maxSize; i++)
		outPlus.SETcoefTab(i, outPlus.GETcoefTab(i) - b.GETcoefTab(i));
}

int Polynome::clearPolynome()
{
	if (nullptr != _tab)
	{
		delete   _tab;
		_tab = nullptr;
	}
	_order = 0;
	return 0;
}



/* *********************************************************
 *					opération sur l'objet				   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : operator[]																   */
/* ROLE : Redéfinition de l'opérateur []											   */
/* ROLE : Accède à la valeur index du tableau de coefficients						   */
/* INPUT  PARAMETERS : unsigned int index 											   */
/* OUTPUT PARAMETERS : valeur à l'index index du tableau de coefficients			   */
/* RETURNED VALUE    : double : valeur à l'index index du tableau de coefficients	   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
double Polynome::operator[]
(
	unsigned int index
)
{
	return GETcoefTab(index);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : grow																		   */
/* ROLE : Créer un nouveau tableau ayant une case de plus ... 						   */
/* ROLE : ... avec la nouvelle valeur de l'utilisateur userValue					   */
/* INPUT  PARAMETERS : double userValue : Valeur à ajouter au tableau 				   */
/* OUTPUT PARAMETERS : Agrandissement du tableau avec une nouvelle valeur			   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void Polynome::grow
(
	double userValue
)
{
	double* newTab(allocate(++_order));

	for (unsigned int i(0); i <= _order; i++)
		newTab[i] = _tab[i];

	newTab[_order] = userValue;
	delete[] _tab;

	_tab = newTab;
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
/* INPUT  PARAMETERS : const Polynome& s : Le Polynome à afficher					   */
/* OUTPUT PARAMETERS : affichage textuelle du Polynome sur la console				   */
/* RETURNED VALUE    : std::ostream& : std::cout, ...								   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
std::ostream& operator <<
(
	std::ostream& os,
	const Polynome& s
)
{
	return os << s.printOn(false);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : printOn																	   */
/* ROLE : Création d'une représentation visuelle du Polynome						   */
/* INPUT  PARAMETERS : bool on = true : si true -> affichage direct ... 			   */
/* INPUT  PARAMETERS : ... sur std::cout // sinon false								   */
/* OUTPUT PARAMETERS : chaine de caratères représentant le Polynome					   */
/* RETURNED VALUE    : std::string : chaine de caratères							   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
std::string Polynome::printOn
(
	bool on
) const
{
	/* ---------------------------------------------------------------------- */
	/* affiche le polynome en z d'ordre décroissant							  */
	/* ---------------------------------------------------------------------- */
	std::string equation("");
	std::ostringstream stream;
	for (unsigned int i(_order); i >= 0; i--)
	{
		if (_tab[i] < 0)
		{
			stream << " - ";
			if (abs(_tab[i]) != 1 || i < 1)
				stream << std::fixed << std::setprecision(2) << abs(_tab[i]);
			if (i > 1)
				stream << "Z^" << i;
			else if (i == 1)
				stream << "Z";
		}
		else if (_tab[i] > 0)
		{
			if (i != _order)
				stream << " + ";
			if (_tab[i] != 1 || i < 1)
				stream << std::fixed << std::setprecision(2) <<_tab[i];
			if (i > 1)
				stream << "Z^" << i;
			else if (i == 1)
				stream << "Z";
		}
		if (i == 0)	break;
	}
	equation = stream.str();
	_stringSize = (unsigned int)equation.length();
	if (on)
		std::cout << equation;
	return equation;
}



/* *********************************************************
 *							TEST						   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : testPolynome																   */
/* ROLE : For DEV only																   */
/* ROLE : Test des méthodes et fonctions de la classe Polynome						   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : Test de la classe											   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void Polynome::testPolynome()
{
	std::string polynome("");
	std::ostringstream stream;


	stream << std::endl << "___TEST POLYNOME___";
	Polynome a((unsigned int)5);
	a.SETcoefTab(3, 1);
	a.SETcoefTab(1, 69.1);
	Polynome b(a);

	stream << std::endl << "taille de a = " + std::to_string(a.GETorder());
	b.SETcoefTab(2, 12.6);
	stream << std::endl << "valeur de l'index " << 2 << "= " + std::to_string(b.GETcoefTab(2));

	a.SETcoefTab(0, -0.9), a.SETcoefTab(4, -6534.69461354), a.grow(2.3);
	b.SETcoefTab(0, 96.36), b.SETcoefTab(1, -619);

	stream << std::endl << "taille de a = " + std::to_string(a.GETorder());
	stream << std::endl << "valeur de l'index " << 5 << "= " + std::to_string(a.GETcoefTab(5));
	stream << std::endl << "Polynome a = " << a;
	stream << std::endl << "Polynome b = " << b;
	if (a == b)
		stream << std::endl << "polynomes identique : a et b";
	else
		stream << std::endl << "polynomes different : a et b";
	
	
	Polynome addition = a + b;
	stream << std::endl << "addition de a + b = " << addition;
	Polynome soustraction1 = a - b;
	stream << std::endl << "soustraction de a - b = " << soustraction1;
	Polynome soustraction2 = addition - soustraction1;
	stream << std::endl << "addition de addition - soustraction1 = " << soustraction2;
	Polynome multiplication = a * b;
	stream << std::endl << "multiplication de a * b = " << multiplication;
	a = b;
	if (a == b)
		stream << std::endl << "polynomes identique : a et b";
	else
		stream << std::endl << "polynomes different : a et b";
	Polynome Z;
	stream << std::endl << std::endl << "taille de Z = " + std::to_string(Z.GETorder());
	Z.SETorder(6);
	stream << std::endl << "taille de Z = " + std::to_string(Z.GETorder());
	Z.SETorder(5);
	stream << std::endl << "taille de Z = " + std::to_string(Z.GETorder());
	Z.SETcoefTab(4, -3.2);
	stream << std::endl << "redefinition de l'operateur << ,  Z = " << Z;
	stream << std::endl << "Z * 2 = " << Z * 2.0;
	stream << std::endl << "Z + 2 = " << Z + 2.0;
	stream << std::endl << "Z - 2 = " << Z - 2.0 << std::endl << std::endl;

	polynome = stream.str();
	std::cout << polynome;

	Polynome xx{};
	xx.SETorder(4);
	xx.SETcoefTab(0, 2.0);
	xx.SETcoefTab(1, 1.0);
	xx.SETcoefTab(2, 2.0);
	xx.SETcoefTab(3, 1.0);
	xx.SETcoefTab(4, 0.5);
	Polynome yy{ -1.0 * xx };

	Polynome zz{ xx + yy };
}


/* *********************************************************
 *						 assesseurs						   *
 ********************************************************* */

void Polynome::SETorder
(
	unsigned int order
)
{
	/* ---------------------------------------------------------------------- */
	/* Copie de l'ancien tableau dans un nouveau en fonction de sa taille	  */
	/* ---------------------------------------------------------------------- */
	double* newTab(allocate(order));
	unsigned int minSize(std::min(order, _order));

	for (unsigned int i(0); i <= minSize; i++)
		newTab[i] = _tab[i];

	if (order > _order)
	{
		for (unsigned int i(_order); i <= order; i++)
			newTab[i] = 0;
	}

	delete[] _tab;
	_tab = nullptr;

	_order = order;
	_tab = newTab;
}
void Polynome::SETcoefTab
(
	unsigned int index,
	double userValue
)
{
	if (assertIndex(index))
	{
		_tab[index] = userValue;
	}
}


unsigned int Polynome::GETorder() const
{
	return _order;
}
double Polynome::GETcoefTab
(
	unsigned int index
) const
{
	if (assertIndex(index))
		return _tab[index];
	return 0;
}
unsigned int Polynome::GETstringSize() const
{
	/* ---------------------------------------------------------------------- */
	/* calcul la place en byte (= nombre de caractère)						  */
	/* pour afficher le polynome sur la console								  */
	/* ---------------------------------------------------------------------- */
	std::string equation("");
	equation = this->printOn(false);
	_stringSize = (unsigned int)equation.length();
	return _stringSize;
}



/*
*	End Of File : Polynome.cpp
*/