/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version: 3.5
	file version 2.2

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

#include "FCTDiscret.h"

#include "Complexe.h"
#include "IHM.h"

/* *********************************************************
 *					Class FCTDiscret					   *
 ********************************************************* */

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
FCTDiscret::FCTDiscret() 
:
_jury(nullptr),
_num(nullptr),
_den(nullptr),
_deltaT(1)
{
	allocate((Polynome)1.0, (Polynome)1.0);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : FCTDiscret																   */
/* ROLE : Constructeur par cast du num�rateur										   */
/* INPUT  PARAMETERS : double num : num�rateur										   */
/* OUTPUT PARAMETERS : Cr�ation d'un objet FCTDiscret : num / 1						   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
FCTDiscret::FCTDiscret
(
	double num
)
:
_jury(nullptr),
_num(nullptr),
_den(nullptr),
_deltaT(1)
{
	allocate((Polynome)num, (Polynome)1.0);
}

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
FCTDiscret::FCTDiscret
(
	Polynome& num,
	Polynome& den,
	double deltaT
)
:
_jury(nullptr),
_num(nullptr),
_den(nullptr),
_deltaT(deltaT)
{
	allocate(num, den);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : FCTDiscret																   */
/* ROLE : Constructeur par Recopie													   */
/* INPUT  PARAMETERS : const FCTDiscret& : Objet � recopier		 					   */
/* OUTPUT PARAMETERS : Cr�ation d'un objet FCTDiscret recopie de l'entr�e			   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
FCTDiscret::FCTDiscret
(
	const FCTDiscret& F
)
: 
_jury(nullptr),
_num(nullptr),
_den(nullptr), 
_deltaT(F.GETdeltaT())
{
	allocate(*F.GETnum(), *F.GETden());
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : ~FCTDiscret																   */
/* ROLE : Destructeur de la classe FCTDiscret										   */
/* INPUT  PARAMETERS : void			 												   */
/* OUTPUT PARAMETERS : Objet FCTDiscret d�truit										   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
FCTDiscret::~FCTDiscret()
{
	deallocate();
}

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
void FCTDiscret::allocate
(
	Polynome num,
	Polynome den
)
{
	_jury = new Matrice;
	_num = new Polynome(num);
	_den = new Polynome(den);
}


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : deallocate																   */
/* ROLE : D�allocation de la m�moire pour _num, _den et _jury						   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : delete : _num, _den , _jury									   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void FCTDiscret::deallocate()
{
	if (nullptr != _jury)
	{
		delete _jury;
		_jury = nullptr;
	}
	else
	{
		IHM::logfileconsole("[ERROR]___: FCTDiscret::~FCTDiscret : _jury == nullptr");
	}

	if (nullptr != _num)
	{
		delete _num;
		_num = nullptr;
	}
	else
	{
		IHM::logfileconsole("[ERROR]___: FCTDiscret::~FCTDiscret : _num == nullptr");
	}

	if (nullptr != _den)
	{
		delete _den;
		_den = nullptr;
	}
	else
	{
		IHM::logfileconsole("[ERROR]___: FCTDiscret::~FCTDiscret : _den == nullptr");
	}
}


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
FCTDiscret& FCTDiscret::operator=
(
	const FCTDiscret& F
)
{
	if (this != &F)
	{
		_num = F._num;
		_den = F._den;
		_deltaT = F._deltaT;
	}
	return *this;
}

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
bool operator==
(
	const FCTDiscret& a,
	const FCTDiscret& b
)
{
	if	(
			(a.GETnum() == b.GETnum())
			&&
			(a.GETden() == b.GETden())
		)
	{
		return true;
	}
	return false;
}

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
FCTDiscret operator+
(
	const FCTDiscret& a,
	const FCTDiscret& b
)
{
	Polynome num(*a.GETnum() * *b.GETden() + *b.GETnum() * *a.GETden());
	Polynome den(*a.GETden() * *b.GETden());
	FCTDiscret resultat(num, den, a.GETdeltaT());
	return resultat;
}

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
FCTDiscret operator-
(
	const FCTDiscret& a,
	const FCTDiscret& b
)
{
	Polynome num(*a.GETnum() * *b.GETden() - *b.GETnum() * *a.GETden());
	Polynome den(*a.GETden() * *b.GETden());
	FCTDiscret resultat(num, den, a.GETdeltaT());
	return resultat;
}

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
FCTDiscret operator*
(
	const FCTDiscret& a,
	const FCTDiscret& b
)
{
	Polynome num(*a.GETnum() * *b.GETnum());
	Polynome den(*a.GETden() * *b.GETden());
	FCTDiscret resultat(num, den, a.GETdeltaT());
	return resultat;
}

/* *********************************************************
 *						 affichage						   *
 ********************************************************* */

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
const std::string FCTDiscret::printOn
(
	bool on
) const
{

	/*
	 *	affiche sur la console : en haut le num, puis la barre de fraction et enfin le den
	 *	affichage selon la taille de la chaine de caratere la plus longue
	 */
	unsigned int stringSize(0);
	std::string equation("");
	std::stringstream stream;

	if (_num->GETstringSize() > _den->GETstringSize())
	{
		stringSize = _num->GETstringSize();
		stream << _num->printOn(false) << std::endl;
		for (unsigned int i(0); i < stringSize; i++)
			stream << "-";
		stream << std::endl;
		for (unsigned int i(0); i < ((_num->GETstringSize() / 2) - (_den->GETstringSize() / 2)); i++)
			stream << " ";
		stream << _den->printOn(false);
		equation = stream.str();
	}
	else if (_num->GETstringSize() < _den->GETstringSize())
	{
		stringSize = _den->GETstringSize();
		for (unsigned int i(0); i < ((_den->GETstringSize() / 2) - (_num->GETstringSize() / 2)); i++)
			stream << " ";
		stream << _num->printOn(false) << std::endl;
		for (unsigned int i(0); i < stringSize; i++)
			stream << "-";
		stream << std::endl << _den->printOn(false);
		equation = stream.str();
	}
	else
	{
		stringSize = _num->GETstringSize();
		stream << _num->printOn(false) << std::endl;
		for (unsigned int i(0); i < stringSize; i++)
			stream << "-";
		stream << std::endl << _den->printOn(false);
		equation = stream.str();
	}
	if (on)
		std::cout << equation;
	return equation;
}

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
void FCTDiscret::interg()
{
	_num->SETorder(1);
	_den->SETorder(1);
	_num->SETcoefTab(0, 0);
	_num->SETcoefTab(1, 1);
	_den->SETcoefTab(0, -1);
	_den->SETcoefTab(1, 1);
}

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
void FCTDiscret::secondOrdre()
{
	_num->SETorder(0);
	_den->SETorder(2);
	_num->SETcoefTab(0, 1);
	_den->SETcoefTab(0, -0.1);
	_den->SETcoefTab(1, 0.5);
	_den->SETcoefTab(2, 1);
}

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
bool FCTDiscret::tabJury()
{
	std::string tableauJury("");
	std::ostringstream stream;

	/* ---------------------------------------------------------------------- */
	/* 1ere Partie															  */
	/* Remplissage du tableau de Jury										  */
	/* ---------------------------------------------------------------------- */

	Polynome den(_den->GETorder());
	for (unsigned int i(0), j(_den->GETorder()); i <= _den->GETorder(), j >= 0; i++, j--)
	{
		den.SETcoefTab(i, _den->GETcoefTab(j));
		if (j == 0)
		{
			break; // compatibilit� unsigned int, j ne peut etre �gale � -1
		}
	}
		
	if (den.GETcoefTab(den.GETorder()) < 0)
		den = - 1.0 * den;

	Polynome ligne1(*_den);
	Polynome ligne2(*_den);

	if (_den->GETorder() > 2)
	{
		_jury->editSize(2, _den->GETorder() + 1);
		for (unsigned int i(0); i <= _den->GETorder(); i++) // premi�re ligne
			_jury->SETthiscoef(0, i, _den->GETcoefTab(i));
		for (unsigned int i(0); i <= _den->GETorder(); i++) // deuxi�me ligne
			_jury->SETthiscoef(1, i, den.GETcoefTab(i));
	}
	else
	{
		_jury->editSize(1, _den->GETorder() + 1);
		for (unsigned int i = 0; i <= _den->GETorder(); i++)
			_jury->SETthiscoef(0, i, _den->GETcoefTab(i));
	}
	
	
	while (ligne2.GETorder() > 2)
	{
		ligne2.SETorder(ligne2.GETorder() - 1);
		for (unsigned int i(0), j(ligne2.GETorder()); i <= ligne2.GETorder(), j >= 0; i++, j--)
		{
			ligne2.SETcoefTab
			(	i,
				(
					(ligne1.GETcoefTab(0) * ligne1.GETcoefTab(i))
					-
					(ligne1.GETcoefTab(ligne1.GETorder()) * ligne1.GETcoefTab(ligne1.GETorder() - i))
				)
			);
			if (j == 0) break;
		}
		if (ligne2.GETorder() > 2) 
		{
			_jury->editSize(_jury->GETlength() + 2, _den->GETorder() + 1);
			for (unsigned int i(0); i <= ligne2.GETorder(); i++)
				_jury->SETthiscoef(_jury->GETlength() - 2, i, ligne2.GETcoefTab(i));
			for (unsigned int i(0), j = ligne2.GETorder(); i <= ligne2.GETorder(), j >= 0; i++, j--)
			{
				_jury->SETthiscoef(_jury->GETlength() - 1, i, ligne2.GETcoefTab(j));
				if (j == 0) break;
			}
		}
		else
		{
			_jury->editSize(_jury->GETlength() + 1, _den->GETorder() + 1);
			for (unsigned int i(0); i <= ligne2.GETorder(); i++)
				_jury->SETthiscoef(_jury->GETlength() - 1, i, ligne2.GETcoefTab(i));
		}
		ligne1 = ligne2;
	}
	
	 
	stream << std::endl << std::endl << "table of Jury = " << *_jury;

	/* ---------------------------------------------------------------------- */
	/* 2�me Partie															  */
	/* Conditions de stabilit�												  */
	/* ---------------------------------------------------------------------- */

	Uint8 condition(0);

	/* ---------------------------------------------------------------------- */
	/* condition abs(a0) < an												  */
	/* ---------------------------------------------------------------------- */

	stream << std::endl << std::endl << "abs(a0) = " << abs(_den->GETcoefTab(0));
	if (abs(_den->GETcoefTab(0)) < _den->GETcoefTab(_den->GETorder()))
	{
		stream << " < a" << _den->GETorder() << " = " << _den->GETcoefTab(_den->GETorder()) << "	Ok";
		condition++;
	}
	else
		stream << " > a" << _den->GETorder() << " = " << _den->GETcoefTab(_den->GETorder()) << "	Not Ok";


	/* ---------------------------------------------------------------------- */
	/* condition D(1) > 0													  */
	/* ---------------------------------------------------------------------- */
	double somme(0);
	for (unsigned int i(0); i <= _den->GETorder(); i++)
		somme += _den->GETcoefTab(i);
	
	stream << std::endl << "D(1) = " << somme;
	if (somme > 0)
	{
		stream << " > 0	Ok";
		condition++;
	}
	else
		stream << " <= 0 Not Ok";


	/* ---------------------------------------------------------------------- */
	/* condition D(-1) > 0 si n pair et ondition D(-1) < 0 si n impair		  */
	/* ---------------------------------------------------------------------- */
	somme = 0;
	for (unsigned int i(0); i <= _den->GETorder(); i++)
		somme += _den->GETcoefTab(i) * pow(-1, i);
	stream << std::endl << "D(-1) = " << somme;
	if	(	
			(	
				somme > 0
				&&
				(_den->GETorder() % 2) == 0
			)
			||
			(
				somme < 0
				&&
				(_den->GETorder() % 2) == 1
			)
		)
	{
		stream << "	Ok";
		condition++;
	}
	else
		stream << "	Not Ok";
		
	if (_den->GETorder() > 2)
	{
		/* ---------------------------------------------------------------------- */
		/* condition Q0 > Q2													  */
		/* ---------------------------------------------------------------------- */
		stream << std::endl << "Q0 = " << abs(ligne2.GETcoefTab(0));
		if (abs(ligne2.GETcoefTab(0)) > abs(ligne2.GETcoefTab(2)))
		{
			stream << " > Q2 = " << abs(ligne2.GETcoefTab(2)) << "	Ok";
			condition++;
		}
		else
			stream << " < Q2 = " << abs(ligne2.GETcoefTab(2)) << "	Not Ok";
	}
	else
	{
		condition++;
	}
	

	if (condition == JURY_STABILITY_CONDITIONS)
	{
		stream << std::endl;
		tableauJury = stream.str();
		std::cout << tableauJury;
		return true;
	}
	else
	{
		stream << std::endl;
		tableauJury = stream.str();
		std::cout << tableauJury;
		return false;
	}
}

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
bool FCTDiscret::Bode
(
	double wMin,
	double wMax,
	unsigned int nbpoint,
	double** gainPhase
)
{
	std::ofstream reponse("bin/files/Bode.txt");
	std::string texte("");
	std::ostringstream stream;

	double amplitude(wMax - wMin);
	double increment(amplitude / nbpoint);
	double gain(0), phase(0);
	Complexe Z, c, cnum, cden;

	/* ---------------------------------------------------------------------- */
	/* Dans le diagramme de Bode wMin n'atteint jamais 0					  */
	/* ---------------------------------------------------------------------- */
	if (wMin == 0)
		wMin = 0.001;


	unsigned int o(0);
	if (reponse)
	{
		for (double i(wMin); i <= wMax; i += increment)
		{
			Z = Complexe::tfReIm(1, i * _deltaT);
			cnum = Complexe::tfPolynomeComplexe(*_num, Z);
			cden = Complexe::tfPolynomeComplexe(*_den, Z);
			c = cnum / cden;
			gainPhase[0][o] = i;
			gainPhase[1][o] = gain = 20 * log10(Complexe::module(c));
			gainPhase[2][o] = phase = -Complexe::arg(c);
			stream << std::endl << i << " , " << gain << " , " << phase;
			o++;
		}
		texte = stream.str();
		reponse << texte;
		std::cout << texte;
		return true;
	}
	else
		return false;
}

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
void closeLoop
(
	const FCTDiscret& openLoop,
	const FCTDiscret& returnLoop
)
{
	
	FCTDiscret num(openLoop);
	FCTDiscret den(1.0 + openLoop * returnLoop);

	Polynome numPoly(*num.GETnum() * *num.GETden());
	Polynome denPoly(*den.GETnum() * *num.GETden());
	FCTDiscret resultat(numPoly, denPoly, num.GETdeltaT());

	std::cout << std::endl << std::endl << "CloseLoop" << std::endl << resultat << std::endl;
}

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
void testFCTDiscret()
{
	std::string fctdiscret;
	std::ostringstream stream;

	stream << std::endl << "___TEST FCTDiscret___";
	Polynome a((unsigned int)3);
	a.SETcoefTab(2, 1), a.SETcoefTab(1, 2);
	Polynome b(a);
	b.SETcoefTab(2, 2), b.SETcoefTab(0, 1);
	a.grow(2), a.SETcoefTab(0, 51), a.SETcoefTab(1, -512);

	FCTDiscret fct1(b, a, 10.3);

	b.SETcoefTab(0, 7.3);
	b.SETcoefTab(1, -91);
	FCTDiscret fct2(a, b, 10.3);
	stream << std::endl << std::endl << "Fct1 constructeur par valeur:" << std::endl << fct1 << std::endl;
	stream << std::endl << "Fct2 constructeur par recopie:" << std::endl << fct2 << std::endl;
	FCTDiscret fctmultiplication = fct1 * fct2;
	stream << std::endl << "multiplication de fct1 * fct2, Fonctions de transfert :" << std::endl << fctmultiplication << std::endl;
	FCTDiscret fctaddition = fct1 + fct2;
	stream << std::endl << "addition de fct1 + fct2,  Fonctions de transfert :" << std::endl << fctaddition << std::endl;
	FCTDiscret fctsoustraction = fct1 - fct2;
	stream << std::endl << "soustraction de fct1 - fct2,  Fonctions de transfert :" << std::endl << fctsoustraction << std::endl;
	
	stream << std::endl << "taille du num de fct1 = " << fct1.GETnum()->GETorder();
	fct1.GETnum()->SETorder(5);
	stream << std::endl << "taille du num de fct1 = " << fct1.GETnum()->GETorder();
	fct1.GETnum()->SETcoefTab(4, 5.6), fct1.GETnum()->SETcoefTab(3, -5.6);
	stream << std::endl << "Fct1 :" << std::endl << fct1 << std::endl << std::endl;
	FCTDiscret integ;
	integ.GETnum()->SETorder(0), integ.GETnum()->SETcoefTab(0, 1);
	integ.GETden()->SETorder(1), integ.GETden()->SETcoefTab(1, 1);
	stream << std::endl << "integ = " << std::endl << integ << std::endl;
	stream << std::endl << "integ * fct1 = " << std::endl << (integ * fct1) << std::endl;

	FCTDiscret openLoop = fct1 * integ;
	FCTDiscret returnLoop = -1.0;

	closeLoop(openLoop, returnLoop);

	fctdiscret = stream.str();
	std::cout << fctdiscret;
}

/* *********************************************************
 *						 assesseurs						   *
 ********************************************************* */

 /* Define in FCTDiscret.h */

/*
*	End Of File : FCTDiscret.cpp
*/
