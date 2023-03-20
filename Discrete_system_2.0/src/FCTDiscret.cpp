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

#include "FCTDiscret.h"

#include "Complexe.h"

#include "LIBUTI.h"

/* *********************************************************
 *					Class FCTDiscret					   *
 ********************************************************* */

/* *********************************************************
 *				constructeurs et destructeur			   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : FCTDiscret																   */
/* ROLE : Constructeur par défaut													   */
/* INPUT  PARAMETERS : void			 												   */
/* OUTPUT PARAMETERS : Création d'un objet FCTDiscret : num = 1 / den = 1			   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
FCTDiscret::FCTDiscret() 
:
m_isInitialize(false),
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
/* ROLE : Constructeur par cast du numérateur										   */
/* INPUT  PARAMETERS : double num : numérateur										   */
/* OUTPUT PARAMETERS : Création d'un objet FCTDiscret : num / 1						   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
FCTDiscret::FCTDiscret
(
	double num
)
:
m_isInitialize(false),
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
/* ROLE : Constructeur par num et den avec deltaT sa période						   */
/* INPUT  PARAMETERS : Polynome& num : objet Polynome numérateur					   */
/* INPUT  PARAMETERS : Polynome& den : objet Polynome dénominateur			 		   */
/* INPUT  PARAMETERS : double deltaT			 									   */
/* OUTPUT PARAMETERS : Création d'un objet FCTDiscret :	num / den					   */
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
m_isInitialize(false),
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
/* INPUT  PARAMETERS : const FCTDiscret& : Objet à recopier		 					   */
/* OUTPUT PARAMETERS : Création d'un objet FCTDiscret recopie de l'entrée			   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
FCTDiscret::FCTDiscret
(
	const FCTDiscret& F
)
: 
m_isInitialize(false),
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
/* OUTPUT PARAMETERS : Objet FCTDiscret détruit										   */
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
/* ROLE : Allocation de la mémoire pour _num, _den et _jury							   */
/* INPUT  PARAMETERS : Polynome num : Polynome numérateur de la FCTDiscret			   */
/* INPUT  PARAMETERS : Polynome den : Polynome dénominateur de la FCTDiscret		   */
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
/* ROLE : Déallocation de la mémoire pour _num, _den et _jury						   */
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
		//IHM::logfileconsole("[ERROR]___: FCTDiscret::~FCTDiscret : _jury == nullptr");
	}

	if (nullptr != _num)
	{
		delete _num;
		_num = nullptr;
	}
	else
	{
		//IHM::logfileconsole("[ERROR]___: FCTDiscret::~FCTDiscret : _num == nullptr");
	}

	if (nullptr != _den)
	{
		delete _den;
		_den = nullptr;
	}
	else
	{
		//IHM::logfileconsole("[ERROR]___: FCTDiscret::~FCTDiscret : _den == nullptr");
	}
}


/* *********************************************************
 *			opérations entre 2 objets FCTDiscret		   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : operator =																   */
/* ROLE : Redéfinition de l'opérateur =												   */
/* INPUT  PARAMETERS : const FCTDiscret& F : objet permettant l'égalisation			   */
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
/* ROLE : Redéfinition de l'opérateur =												   */
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
/* ROLE : Redéfinition de l'opérateur +												   */
/* ROLE : Addition entre les 2 Inputs												   */
/* INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret					   */
/* INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret					   */
/* OUTPUT PARAMETERS : résultat de l'addition (a + b)								   */
/* RETURNED VALUE    : FCTDiscret : retourne un objet résultat de l'addition		   */
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
/* ROLE : Redéfinition de l'opérateur -												   */
/* ROLE : Soustraction entre les 2 Inputs											   */
/* INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret					   */
/* INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret					   */
/* OUTPUT PARAMETERS : résultat de la soustraction (a - b)							   */
/* RETURNED VALUE    : FCTDiscret : retourne un objet résultat de la soustraction	   */
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
/* ROLE : Redéfinition de l'opérateur *												   */
/* ROLE : Multiplication entre les 2 Inputs											   */
/* INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret					   */
/* INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret					   */
/* OUTPUT PARAMETERS : résultat de la multiplication (a * b)						   */
/* RETURNED VALUE    : FCTDiscret : retourne un objet résultat de la Multiplication	   */
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

void getByCopyReversePolynomeOrder(const Polynome& src, Polynome& dest)
{
	for (int i((int)src.GETorder()); i >= 0; i--)
	{
		dest.SETcoefTab((src.GETorder() - i), src.GETcoefTab(i));
	}
}

void setFirstL
(
	const Polynome* srcOrder,
	const Polynome* srcReverse,
	Matrice* dest
)
{
	if (srcOrder->GETorder() > MIN_ORDER_DEN_TAB_JURY)
	{
		dest->editSize(MIN_ORDER_DEN_TAB_JURY, srcOrder->GETorder() + 1);
		for (unsigned int i(0); i <= srcOrder->GETorder(); i++) // première ligne
			dest->SETthiscoef(0, i, srcOrder->GETcoefTab(i));
		for (unsigned int i(0); i <= srcReverse->GETorder(); i++) // deuxième ligne
			dest->SETthiscoef(1, i, srcReverse->GETcoefTab(i));
	}
	else
	{
		dest->editSize(MIN_ORDER_DEN_TAB_JURY - 1, srcOrder->GETorder() + 1);
		for (unsigned int i = 0; i <= srcOrder->GETorder(); i++)
			dest->SETthiscoef(0, i, srcOrder->GETcoefTab(i));
	}
}

/* *********************************************************
 *						 affichage						   *
 ********************************************************* */

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : printOn																	   */
/* ROLE : Création d'une représentation visuelle de la FCTDiscret					   */
/* INPUT  PARAMETERS : bool on = true : si true -> affichage direct ...				   */
/* INPUT  PARAMETERS : ... sur std::cout // sinon false 							   */
/* OUTPUT PARAMETERS : chaine de caratères représentant la FCTDiscret				   */
/* RETURNED VALUE    : std::string : chaine de caratères							   */
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
		//for (unsigned int i(0); i < ((_num->GETstringSize() / 2) - (_den->GETstringSize() / 2)); i++)
		//	stream << " ";
		stream << _den->printOn(false);
		equation = stream.str();
	}
	else if (_num->GETstringSize() < _den->GETstringSize())
	{
		stringSize = _den->GETstringSize();
		//for (unsigned int i(0); i < ((_den->GETstringSize() / 2) - (_num->GETstringSize() / 2)); i++)
		//	stream << " ";
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
 *				Possibilités d'initialisation			   *
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
	_deltaT = 0.01;
	m_isInitialize = true;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : secondOrdre																   */
/* ROLE : Initialisation de la FCTDiscret en second ordre							   */
/* ROLE : num : ordre 0 -> num = 1													   */
/* ROLE : den : ordre 2 -> den = Z² + 0.5Z - 1										   */
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
	_deltaT = 0.01;
	m_isInitialize = true;
}

/* *********************************************************
 *					opérations sur l'objet				   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : tabJury																	   */
/* ROLE : Création du tableau de Jury (objet Matrice)								   */
/* ROLE : Calcul du critère de Jury permettant de statuer sur la stabilité du système  */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : Matrice de Jury complétée et status de la stabilité			   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
bool FCTDiscret::tabJury(std::ostringstream& stream)
{
	std::string tableauJury("");

	/* ---------------------------------------------------------------------- */
	/* 1ere Partie															  */
	/* Remplissage du tableau de Jury										  */
	/* ---------------------------------------------------------------------- */

	Polynome den(_den->GETorder());
	getByCopyReversePolynomeOrder(*_den, den);
		
	if (den.GETcoefTab(den.GETorder()) < 0)
		den = - 1.0 * den;
	
	setFirstL(_den, &den, _jury);

	Polynome ligne1(*_den);
	Polynome ligne2(*_den);

	while (ligne2.GETorder() > MIN_ORDER_DEN_TAB_JURY)
	{
		ligne2.SETorder(ligne2.GETorder() - 1);
		for (
				int i(0), j(ligne2.GETorder());
				(i <= (int)ligne2.GETorder()) && (j >= 0);
				i++, j--
			)
		{
			ligne2.SETcoefTab
			(	(unsigned int)i,
				(
					(ligne1.GETcoefTab(0) * ligne1.GETcoefTab((unsigned int)i))
					-
					(ligne1.GETcoefTab(ligne1.GETorder()) * ligne1.GETcoefTab(ligne1.GETorder() - (unsigned int)i))
				)
			);
		}
		if (ligne2.GETorder() > MIN_ORDER_DEN_TAB_JURY)
		{
			_jury->editSize(_jury->GETlength() + 2, _den->GETorder() + 1);
			for (unsigned int i(0); i <= ligne2.GETorder(); i++)
			{
				_jury->SETthiscoef(_jury->GETlength() - 2, i, ligne2.GETcoefTab(i));
			}
			for (
					int i(0), j = (int)ligne2.GETorder();
					(i <= (int)ligne2.GETorder()) && (j >= 0);
					i++, j--
				)
			{
				_jury->SETthiscoef(_jury->GETlength() - 1, (unsigned int)i, ligne2.GETcoefTab((unsigned int)j));
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
	
	 
	stream << *_jury;

	/* ---------------------------------------------------------------------- */
	/* 2ème Partie															  */
	/* Conditions de stabilité												  */
	/* ---------------------------------------------------------------------- */

	Uint8 condition(0);

	/* ---------------------------------------------------------------------- */
	/* condition abs(a0) < an												  */
	/* ---------------------------------------------------------------------- */

	stream << std::endl << "abs(a0) = " << abs(_den->GETcoefTab(0));
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
	double somme(0.0);
	for (unsigned int i(0); i <= _den->GETorder(); i++)
		somme += _den->GETcoefTab(i);
	
	stream << std::endl << "D(1) = " << somme;
	if (somme > 0.0)
	{
		stream << " > 0	Ok";
		condition++;
	}
	else
		stream << " <= 0 Not Ok";


	/* ---------------------------------------------------------------------- */
	/* condition D(-1) > 0 si n pair et ondition D(-1) < 0 si n impair		  */
	/* ---------------------------------------------------------------------- */
	somme = 0.0;
	for (unsigned int i(0); i <= _den->GETorder(); i++)
		somme += _den->GETcoefTab(i) * pow(-1, i);
	stream << std::endl << "D(-1) = " << somme;
	if	(
			somme > 0.0
			&&
			(_den->GETorder() % 2) == 0
		)
	{
		stream << " / positive sum / n pair / Ok";
		condition++;
	}
	else
	if
		(
			somme < 0.0
			&&
			(_den->GETorder() % 2) == 1
		)
	{
		stream << " / negative sum / n impair / Ok";
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
/* ROLE : Représentation visuelle de diagramme de Bode de la FCTDiscret				   */
/* INPUT  PARAMETERS : double wMin : fréquence min									   */
/* INPUT  PARAMETERS : double wMax : fréquence max									   */
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
	unsigned int* nbOfDecade,
	BodeGraph& bodeGraph
)
{
	std::ofstream reponse("bin/files/Bode.txt");
	std::string texte("");
	std::ostringstream stream;
	
	Complexe Z, c;
	t_bode blank;

	/* In case of second call */
	bodeGraph.clear();

	/* 
		In Bode, freq = 0.0 does not exist 
		Limitation to a minimum value
	*/
	if (checkDIVDen(wMin) == false)
	{
		wMin = BODE_FREQ_MIN;
	}

	const int firstDecade{ (int)std::floor(log10(wMin)) };
	const int LastDecade{ (int)std::ceil(log10(wMax)) };
	*nbOfDecade = (unsigned int)(LastDecade - firstDecade);
	
	int currentDecade{ firstDecade };
	const unsigned int nbPointPerDecade{ nbpoint / *nbOfDecade };

	double offset{ 0.0 };
	double increment{ 0.0 };
	for (unsigned int l{ 0 }; l < *nbOfDecade; l++)
	{
		offset = std::pow(TEN_POWER, currentDecade);
		increment = ((double)BODE_FREQ_INCR_FACTOR * offset) / (double)nbPointPerDecade;

		for (unsigned int j{ 0 }; j < nbPointPerDecade; j++)
		{
			blank.freq = (double)j * increment + offset;

			Z = Complexe::tfReIm(COMPLEXE_UNIT_REAL, blank.freq * _deltaT);

			c = Complexe::tfPolynomeComplexe(*_num, Z) / Complexe::tfPolynomeComplexe(*_den, Z);

			blank.gain = (double)BODE_GAIN_FACTOR * log10(Complexe::module(c));
			blank.phase = -Complexe::arg(c);

			stream << std::endl << blank.freq << " , " << blank.gain << " , " << blank.phase;
			bodeGraph.push_back(blank);
		}
		currentDecade++;
	}
	texte = stream.str();
	reponse << texte;
	std::cout << texte;
	
	return false;
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : closeLoop																	   */
/* ROLE : Calcul de la Boucle Fermée												   */
/* INPUT  PARAMETERS : const FCTDiscret& openLoop									   */
/* INPUT  PARAMETERS : const FCTDiscret& returnLoop									   */
/* OUTPUT PARAMETERS : Boucle Fermée												   */
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
/* ROLE : Test des méthodes et fonctions de la classe FCTDiscret					   */
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
