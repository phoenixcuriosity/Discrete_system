/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:3.5
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

/* *********************************************************
 *						Include							   *
 ********************************************************* */

#include "SYSETATDiscret.h"


/* *********************************************************
 *					SYSETATDiscret						   *
 ********************************************************* */

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
SYSETATDiscret::SYSETATDiscret()
: 
_Te(1),
_A(new Matrice),
_B(new Matrice),
_C(new Matrice),
_D(new Matrice)
{
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : SYSETATDiscret															   */
/* ROLE : Constructeur par Recopie													   */
/* INPUT  PARAMETERS : const SYSETATDiscret& : objet à copier						   */
/* OUTPUT PARAMETERS : Création d'un système d'état copie de l'entrée				   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
SYSETATDiscret::SYSETATDiscret(const SYSETATDiscret& a)
: 
_Te(a._Te)
{
	_A = new Matrice(*a._A);
	_B = new Matrice(*a._B);
	_C = new Matrice(*a._C);
	_D = new Matrice(*a._D);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : ~SYSETATDiscret															   */
/* ROLE : Destructeur de la classe SYSETATDiscret									   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : Objet SYSETATDiscret détruit									   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
SYSETATDiscret::~SYSETATDiscret()
{
	if (_A != nullptr)
	{
		delete _A;
		_A = nullptr;
	}
	if (_B != nullptr)
	{
		delete _B;
		_B = nullptr;
	}
	if (_C != nullptr)
	{
		delete _C;
		_C = nullptr;
	}
	if (_D != nullptr)
	{
		delete _D;
		_D = nullptr;
	}
}

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
bool operator ==
(
	const SYSETATDiscret& a,
	const SYSETATDiscret& b
)
{
	if (a.GETA() == b.GETA()
		&& a.GETB() == b.GETB()
		&& a.GETC() == b.GETC()
		&& a.GETD() == b.GETD()
		&& a.GETTe() == b.GETTe()
		)
		return true;
	return false;
}

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
void SYSETATDiscret::calculABCD
(
	const FCTDiscret& fct
)
{
	if (fct.GETden()->GETorder() >= fct.GETnum()->GETorder())
	{
		_A->editSize(fct.GETden()->GETorder(), fct.GETden()->GETorder());
		for (unsigned int i(0); i < fct.GETden()->GETorder(); i++)
		{
			_A->SETthiscoef(fct.GETden()->GETorder() - 1, i,
				-(fct.GETden()->GETcoefTab(i) / fct.GETden()->GETcoefTab(fct.GETden()->GETorder())));
		}
		for (unsigned int i(0); i < fct.GETden()->GETorder(); i++)
		{
			for (unsigned int j(1); j < fct.GETden()->GETorder(); j++)
			{
				_A->SETthiscoef(i, j, 1);
				i++;
			}
		}
		

		_B->editSize(fct.GETden()->GETorder(), 1);
		_B->SETthiscoef(_B->GETlength() - 1, 0, 1 / fct.GETden()->GETcoefTab(fct.GETden()->GETorder()));
		

		_C->editSize(1, fct.GETden()->GETorder());
		for (unsigned int i(0); i <= fct.GETnum()->GETorder(); i++)
			_C->SETthiscoef(0, i, fct.GETnum()->GETcoefTab(i));
		
		

		_D->editSize(1, 1);
	}
	else
		std::cout << std::endl << "______Order of Num = " << fct.GETden()->GETorder() << "  > Order of Den = " << fct.GETnum()->GETorder();
}

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
void SYSETATDiscret::simulation
(
	const std::string& namefile,
	Signal& signal,
	Matrice& x0,
	double* yOut
)
{
	std::ofstream reponse(namefile);
	std::ostringstream repy;
	std::string rep;
	Matrice dx(_A->GETlength(), 1), y(1, 1);
	/*
	for (unsigned int i(0); i < signal.GETnbech(); i++)
	{
		dx = *_A * x0 + *_B * signal.GETthiscoef(i);
		y = *_C * x0 + *_D * signal.GETthiscoef(i);
		yOut[i] = y.GETthiscoef(0, 0);
		x0 = dx;
		repy << std::endl << signal.GETdeltaT() * i << " , " << signal.GETthiscoef(i) << " , " << y.GETthiscoef(0, 0);
	}
	*/
	rep = repy.str();
	std::cout << rep;
	if (reponse)
	{
		reponse << rep;
	}
	else
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le Fichier : " << namefile;

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
/* INPUT  PARAMETERS : const SYSETATDiscret& s : Le SYSETATDiscret à afficher		   */
/* OUTPUT PARAMETERS : affichage textuelle de SYSETATDiscret sur la console			   */
/* RETURNED VALUE    : std::ostream& : std::cout, ...								   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
std::ostream& operator<<(std::ostream& os, const SYSETATDiscret& s)
{
	return os << s.printOn(false);
}

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
std::string SYSETATDiscret::printOn(bool on)const
{
	std::string equation;
	std::ostringstream stream;

	stream << std::endl << std::endl << "Forme Compagne de Commande";
	stream << std::endl << "Matrice Ac :" << *_A << std::endl
						<< "Matrice Bc :" << *_B << std::endl
						<< "Matrice Cc :" << *_C << std::endl
						<< "Matrice D :" << *_D;

	stream << std::endl << std::endl << "Forme Compagne d'Observabilite";
	stream << std::endl << "Matrice Ao :" << transposition(*_A) << std::endl
						<< "Matrice Bo :" << transposition(*_B) << std::endl
						<< "Matrice Co :" << transposition(*_C) << std::endl
						<< "Matrice D :" << *_D;

	equation = stream.str();
	if (on)
		std::cout << equation;
	return equation;
}


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
void testSYSETATDiscret()
{
	std::cout << std::endl << "___TEST SYSETATDiscret___";


	FCTDiscret fct;
	fct.GETnum()->SETorder(1);
	fct.GETnum()->SETcoefTab(0, 1);
	fct.GETnum()->SETcoefTab(1, -0.63);
	fct.GETden()->SETorder(4);
	fct.GETden()->SETcoefTab(0, 0);
	fct.GETden()->SETcoefTab(1, -0.6);
	fct.GETden()->SETcoefTab(2, 1);
	fct.GETden()->SETcoefTab(3, 0.01);
	fct.GETden()->SETcoefTab(4, 2);
	//fct.SETdenThisCoef(5, -0.359);
	//fct.SETdenThisCoef(6, 5);
	std::cout << std::endl << std::endl << std::endl << "fct = " << std::endl << fct;

	SYSETATDiscret sys;
	sys.calculABCD(fct);
	sys.SETTe(100);
	std::cout << std::endl << sys;
	
	std::cout << std::endl << "BODE" << std::endl;
	//fct.Bode(0.1, 10, 100);

	/*
	FCTDiscret fct2;
	fct2.SETnumOrder(1);
	fct2.SETnumThisCoef(1, 1);
	fct2.SETdenOrder(1);
	fct2.SETdenThisCoef(0, -1);
	fct2.SETdenThisCoef(1, 1);
	cout << std::endl << fct2;
	fct2.Bode(0.1, 10, 100);
	*/

	//Echelon E(50, 0.1, 10.0);
	Matrice x0(sys.GETA()->GETlength(), 1);
	x0.SETthiscoef(0, 0, 0.1);

	std::cout << std::endl << std::endl << std::endl << "Reponse temporelle avec E = 10.0" << std::endl;
	//sys.simulation("bin/files/ReponseTemporelle.txt", E, x0);
}

/* *********************************************************
 *						 assesseurs						   *
 ********************************************************* */

/* Define SYSETATDiscret.h */

/*
*	End Of File : SYSETATDiscret.cpp
*/