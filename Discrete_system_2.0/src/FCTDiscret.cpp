/*

	Discrete_system
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	file version 4.2.1

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
/* NAME : FCTDiscret																   */
/* ROLE : Constructeur par d�faut													   */
/* INPUT  PARAMETERS : void			 												   */
/* OUTPUT PARAMETERS : Cr�ation d'un objet FCTDiscret : num = 1 / den = 1			   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
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
/* NAME : FCTDiscret																   */
/* ROLE : Constructeur par cast du num�rateur										   */
/* INPUT  PARAMETERS : double num : num�rateur										   */
/* OUTPUT PARAMETERS : Cr�ation d'un objet FCTDiscret : num / 1						   */
/* RETURNED VALUE    : void															   */
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
/* NAME : FCTDiscret																   */
/* ROLE : Constructeur par num et den avec deltaT sa p�riode						   */
/* INPUT  PARAMETERS : Polynome& num : objet Polynome num�rateur					   */
/* INPUT  PARAMETERS : Polynome& den : objet Polynome d�nominateur			 		   */
/* INPUT  PARAMETERS : double deltaT			 									   */
/* OUTPUT PARAMETERS : Cr�ation d'un objet FCTDiscret :	num / den					   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
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
/* NAME : FCTDiscret																   */
/* ROLE : Constructeur par Recopie													   */
/* INPUT  PARAMETERS : const FCTDiscret& : Objet � recopier		 					   */
/* OUTPUT PARAMETERS : Cr�ation d'un objet FCTDiscret recopie de l'entr�e			   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
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
/* NAME: ~FCTDiscret																   */
/* ROLE: Destructeur de la classe FCTDiscret										   */
/* RVALUE: None																		   */
/* ------------------------------------------------------------------------------------*/
FCTDiscret::~FCTDiscret()
{
	deallocate();
}

/* ----------------------------------------------------------------------------------- */
/* NAME : allocate																	   */
/* ROLE : Allocation de la m�moire pour _num, _den et _jury							   */
/* INPUT  PARAMETERS : Polynome num : Polynome num�rateur de la FCTDiscret			   */
/* INPUT  PARAMETERS : Polynome den : Polynome d�nominateur de la FCTDiscret		   */
/* OUTPUT PARAMETERS : new : _num, _den , _jury										   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
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
/* NAME : deallocate																   */
/* ROLE : D�allocation de la m�moire pour _num, _den et _jury						   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : delete : _num, _den , _jury									   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
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
 *			op�rations entre 2 objets FCTDiscret		   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* NAME : operator =																   */
/* ROLE : Red�finition de l'op�rateur =												   */
/* INPUT  PARAMETERS : const FCTDiscret& F : objet permettant l'�galisation			   */
/* OUTPUT PARAMETERS : this = F														   */
/* RETURNED VALUE    : FCTDiscret& : return this									   */
/* ------------------------------------------------------------------------------------*/
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
/* NAME : operator ==																   */
/* ROLE : Red�finition de l'op�rateur =												   */
/* ROLE : Comparaison entre les 2 FCTDiscret en Input								   */
/* INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret					   */
/* INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret					   */
/* OUTPUT PARAMETERS : Comparaison													   */
/* RETURNED VALUE    : bool : == -> true // != -> false								   */
/* ------------------------------------------------------------------------------------*/
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
/* NAME : operator+																	   */
/* ROLE : Red�finition de l'op�rateur +												   */
/* ROLE : Addition entre les 2 Inputs												   */
/* INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret					   */
/* INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret					   */
/* OUTPUT PARAMETERS : r�sultat de l'addition (a + b)								   */
/* RETURNED VALUE    : FCTDiscret : retourne un objet r�sultat de l'addition		   */
/* ------------------------------------------------------------------------------------*/
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
/* NAME : operator-																	   */
/* ROLE : Red�finition de l'op�rateur -												   */
/* ROLE : Soustraction entre les 2 Inputs											   */
/* INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret					   */
/* INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret					   */
/* OUTPUT PARAMETERS : r�sultat de la soustraction (a - b)							   */
/* RETURNED VALUE    : FCTDiscret : retourne un objet r�sultat de la soustraction	   */
/* ------------------------------------------------------------------------------------*/
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
/* NAME : operator*																	   */
/* ROLE : Red�finition de l'op�rateur *												   */
/* ROLE : Multiplication entre les 2 Inputs											   */
/* INPUT  PARAMETERS : const FCTDiscret& a : un objet FCTDiscret					   */
/* INPUT  PARAMETERS : const FCTDiscret& b : un objet FCTDiscret					   */
/* OUTPUT PARAMETERS : r�sultat de la multiplication (a * b)						   */
/* RETURNED VALUE    : FCTDiscret : retourne un objet r�sultat de la Multiplication	   */
/* ------------------------------------------------------------------------------------*/
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

/* ----------------------------------------------------------------------------------- */
/* NAME: setFirstL																	   */
/* ROLE: Fill the first two matrix rows	with srcOrder and srcReverse				   */
/* RVALUE: void																		   */
/* ----------------------------------------------------------------------------------- */
void setFirstL
(
	/* IN */
	const Polynome* srcOrder,
	const Polynome* srcReverse,
	/* OUT */
	Matrice* dest
)
{
	if (srcOrder->GETorder() > MIN_ORDER_DEN_TAB_JURY)
	{
		dest->editSize(MIN_ORDER_DEN_TAB_JURY, srcOrder->GETorder() + 1);
		for (unsigned int i(0); i <= srcOrder->GETorder(); i++) // premi�re ligne
			dest->SETthiscoef(0, i, srcOrder->GETcoefTab(i));
		for (unsigned int i(0); i <= srcReverse->GETorder(); i++) // deuxi�me ligne
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
/* NAME : printOn																	   */
/* ROLE : Cr�ation d'une repr�sentation visuelle de la FCTDiscret					   */
/* INPUT  PARAMETERS : bool on = true : si true -> affichage direct ...				   */
/* INPUT  PARAMETERS : ... sur std::cout // sinon false 							   */
/* OUTPUT PARAMETERS : chaine de carat�res repr�sentant la FCTDiscret				   */
/* RETURNED VALUE    : std::string : chaine de carat�res							   */
/* ------------------------------------------------------------------------------------*/
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
 *				Possibilit�s d'initialisation			   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* NAME : interg																	   */
/* ROLE : Initialisation de la FCTDiscret en integrateur							   */
/* ROLE : num : ordre 1 -> num = Z + 1												   */
/* ROLE : den : ordre 1 -> den = Z - 1												   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : La FCTDiscret est de type integrateur						   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
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
/* NAME : secondOrdre																   */
/* ROLE : Initialisation de la FCTDiscret en second ordre							   */
/* ROLE : num : ordre 0 -> num = 1													   */
/* ROLE : den : ordre 2 -> den = Z� + 0.5Z - 1										   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : La FCTDiscret est de type second ordre						   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
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
 *					op�rations sur l'objet				   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* NAME: tabJury																	   */
/* ROLE: Cr�ation du tableau de Jury (objet Matrice)								   */
/* ROLE: Calcul du crit�re de Jury permettant de statuer sur la stabilit� du syst�me   */
/* RVALUE: false is not stable ; true is stable										   */
/* ------------------------------------------------------------------------------------*/
bool FCTDiscret::tabJury
(
	/* OUT */
	std::ostringstream& stream
)
{
	std::string tableauJury{EMPTY_STRING};

	/* ---------------------------------------------------------------------- */
	/* 1ere Partie															  */
	/* Remplissage du tableau de Jury										  */
	/* ---------------------------------------------------------------------- */

	Polynome den{ _den->GETorder() };
	getByCopyReversePolynomeOrder(*_den, den);

	if (den.isNegative())
	{
		den.inverseSign();
	}

	setFirstL(_den, &den, _jury);

	Polynome finalLine{ *_den };

	fillProcessTabJury(finalLine);
	
	stream << *_jury;

	/* ---------------------------------------------------------------------- */
	/* 2�me Partie															  */
	/* Conditions de stabilit�												  */
	/* ---------------------------------------------------------------------- */

	Uint8 condition{0};

	/* condition abs(a0) < an */

	condition += (Uint8)firstCondition(stream);

	/* condition D(1) > 0 */
	
	condition += (Uint8)secondCondition(stream);

	/* condition D(-1) > 0 si n pair et ondition D(-1) < 0 si n impair */
	
	condition += (Uint8)thirdCondition(stream);

	/* condition Q0 > Q2 */
		
	condition += (Uint8)fourthCondition(stream, finalLine);
	
	/* Check condition */

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
/* NAME: fillProcessTabJury															   */
/* ROLE: Cr�ation du tableau de Jury (objet Matrice)								   */
/* ROLE: Calcul du crit�re de Jury permettant de statuer sur la stabilit� du syst�me   */
/* RVALUE: false is not stable ; true is stable										   */
/* ------------------------------------------------------------------------------------*/
int FCTDiscret::fillProcessTabJury
(
	/* OUT */
	Polynome& finalLine
)
{
	Polynome ligne1{ *_den };
	unsigned int loopTimeOut{ 0 };

	while (finalLine.GETorder() > MIN_ORDER_DEN_TAB_JURY)
	{
		/* Loop Timeout */

		loopTimeOut++;
		if (loopTimeOut > MAX_LOOP_ITERATION_JURY_TAB)
		{
			throw("[ERROR]: [fillProcessTabJury]: [MAX_LOOP_ITERATION_JURY_TAB]");
		}

		/* Functionnal */

		finalLine.SETorder(finalLine.GETorder() - 1);
		for (
				int i(0), j(finalLine.GETorder());
				(i <= (int)finalLine.GETorder()) && (j >= 0);
				i++, j--
			)
		{
			finalLine[(unsigned int)i] = 
			(
				(ligne1[0] * ligne1[(unsigned int)i])
				-
				(ligne1[ligne1.GETorder()] * ligne1[ligne1.GETorder() - (unsigned int)i])
			);
		}

		if (finalLine.GETorder() > MIN_ORDER_DEN_TAB_JURY)
		{
			_jury->editSize(_jury->GETlength() + 2, _den->GETorder() + 1);

			for (unsigned int i(0); i <= finalLine.GETorder(); i++)
			{
				_jury->SETthiscoef(_jury->GETlength() - 2, i, finalLine[i]);
			}

			for (
					int i(0), j = (int)finalLine.GETorder();
					(i <= (int)finalLine.GETorder()) && (j >= 0);
					i++, j--
				)
			{
				_jury->SETthiscoef(_jury->GETlength() - 1, (unsigned int)i, finalLine[(unsigned int)j]);
			}
		}
		else
		{
			_jury->editSize(_jury->GETlength() + 1, _den->GETorder() + 1);
			for (unsigned int i(0); i <= finalLine.GETorder(); i++)
			{
				_jury->SETthiscoef(_jury->GETlength() - 1, i, finalLine[i]);
			}
		}
		ligne1 = finalLine;
	}
	return EXIT_SUCCESS;
}

/* ----------------------------------------------------------------------------------- */
/* NAME: firstCondition																   */
/* ROLE: condition abs(a0) < an														   */
/* RVALUE: false invalid ; true valid												   */
/* ------------------------------------------------------------------------------------*/
bool FCTDiscret::firstCondition
(
	/* OUT */
	std::ostringstream& stream
)
{
	stream << std::endl << "abs(a0) = " << abs((*_den)[0]);
	if (abs((*_den)[0]) < (*_den)[_den->GETorder()])
	{
		stream << " < a" << _den->GETorder() << " = " << (*_den)[_den->GETorder()] << "	Ok";
		return true;
	}
	else
	{
		stream << " > a" << _den->GETorder() << " = " << (*_den)[_den->GETorder()] << "	Not Ok";
		return false;
	}		
}

/* ----------------------------------------------------------------------------------- */
/* NAME: secondCondition															   */
/* ROLE: condition D(1) > 0															   */
/* RVALUE: false invalid ; true valid												   */
/* ------------------------------------------------------------------------------------*/
bool FCTDiscret::secondCondition
(
	/* OUT */
	std::ostringstream& stream
)
{
	double somme{ 0.0 };
	for (unsigned int i(0); i <= _den->GETorder(); i++)
	{
		somme += (*_den)[i];
	}

	stream << std::endl << "D(1) = " << somme;
	if (somme > 0.0)
	{
		stream << " > 0	Ok";
		return true;
	}
	else
	{
		stream << " <= 0 Not Ok";
		return false;
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME: thirdCondition																   */
/* ROLE: condition D(-1) > 0 si n pair et ondition D(-1) < 0 si n impair			   */
/* RVALUE: false invalid ; true valid												   */
/* ------------------------------------------------------------------------------------*/
bool FCTDiscret::thirdCondition
(
	/* OUT */
	std::ostringstream& stream
)
{
	double somme{ 0.0 };
	for (unsigned int i(0); i <= _den->GETorder(); i++)
	{
		somme += (*_den)[i] * pow(-1, i);
	}

	stream << std::endl << "D(-1) = " << somme;
	if	(
			somme > 0.0
			&&
			(_den->GETorder() % 2) == 0
		)
	{
		stream << " / positive sum / n pair / Ok";
		return true;
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
		return true;
	}
	else
	{
		stream << "	Not Ok";
		return false;
	}

}

/* ----------------------------------------------------------------------------------- */
/* NAME: thirdCondition																   */
/* ROLE: condition Q0 > Q2															   */
/* RVALUE: false invalid ; true valid												   */
/* ------------------------------------------------------------------------------------*/
bool FCTDiscret::fourthCondition
(
	/* OUT */
	std::ostringstream& stream,
	/* IN */
	Polynome& finalLine
)
{
	if (_den->GETorder() > MIN_ORDER_DEN_TAB_JURY)
	{

		stream << std::endl << "Q0 = " << abs(finalLine[ORDER_ZERO_P]);
		if (abs(finalLine[ORDER_ZERO_P]) > abs(finalLine[MIN_ORDER_DEN_TAB_JURY]))
		{
			stream << " > Q2 = " << abs(finalLine[MIN_ORDER_DEN_TAB_JURY]) << "	Ok";
			return true;
		}
		else
		{
			stream << " < Q2 = " << abs(finalLine[MIN_ORDER_DEN_TAB_JURY]) << "	Not Ok";
			return false;
		}		
	}
	else
	{
		return true;
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME: Bode																		   */
/* ROLE: Repr�sentation visuelle de diagramme de Bode de la FCTDiscret				   */
/* RVALUE: always true																   */
/* ------------------------------------------------------------------------------------*/
bool FCTDiscret::Bode
(
	/* IN */
	const double wMin,
	const double wMax,
	const unsigned int nbpoint,
	/* OUT */
	unsigned int* nbOfDecade,
	BodeGraph& bodeGraph
)
{
	std::ofstream reponse{ "bin/files/Bode.txt" };
	std::string texte{""};
	std::ostringstream stream{};
	
	Complexe Z{}, c{};
	t_bode blank{};

	/* In case of second call */
	bodeGraph.clear();

	/* 
		In Bode, freq = 0.0 does not exist 
		Limitation to a minimum value
	*/
	double l_wMin{ wMin };
	if (checkMinDouble(wMin) == ValidityCheckMinDouble::InvalidRange)
	{
		l_wMin = BODE_FREQ_MIN;
	}

	const int firstDecade{ (int)std::floor(log10(l_wMin)) };
	const int LastDecade{ (int)std::ceil(log10(wMax)) };
	*nbOfDecade = (unsigned int)(LastDecade - firstDecade);
	
	int currentDecade{ firstDecade };
	const unsigned int nbPointPerDecade
	{ (unsigned int)std::floor((double)nbpoint / (double)*nbOfDecade) };

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
/* NAME : closeLoop																	   */
/* ROLE : Calcul de la Boucle Ferm�e												   */
/* INPUT  PARAMETERS : const FCTDiscret& openLoop									   */
/* INPUT  PARAMETERS : const FCTDiscret& returnLoop									   */
/* OUTPUT PARAMETERS : Boucle Ferm�e												   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
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
/* NAME : testFCTDiscret															   */
/* ROLE : For DEV only																   */
/* ROLE : Test des m�thodes et fonctions de la classe FCTDiscret					   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : Test de la classe											   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
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
