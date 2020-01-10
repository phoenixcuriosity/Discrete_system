/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version:3.1
	file version 2.0

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

#include "SYSETATDiscret.h"

SYSETATDiscret::SYSETATDiscret()
: _Te(1)
{
	_A = new Matrice;
	_B = new Matrice;
	_C = new Matrice;
	_D = new Matrice;
}
SYSETATDiscret::SYSETATDiscret(const SYSETATDiscret& a)
: _Te(a._Te)
{
	_A = new Matrice(*a._A);
	_B = new Matrice(*a._B);
	_C = new Matrice(*a._B);
	_D = new Matrice(*a._B);
}
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

std::ostream& operator<<(std::ostream& os, const SYSETATDiscret& s)
{
	return os << s.printOn(false);
}
bool operator ==(const SYSETATDiscret& a, const SYSETATDiscret& b)
{
	if (	a.GETA() == b.GETA()
		 && a.GETB() == b.GETB()
		 && a.GETC() == b.GETC()
		 && a.GETD() == b.GETD()
		 && a.GETTe() == b.GETTe()
		)
		return true;
	return false;
}

void SYSETATDiscret::SETA(const Matrice* Z)
{
	*_A = *Z;
}
void SYSETATDiscret::SETB(const Matrice* Z)
{
	*_B = *Z;
}
void SYSETATDiscret::SETC(const Matrice* Z)
{
	*_C = *Z;
}
void SYSETATDiscret::SETD(const Matrice* Z)
{
	*_D = *Z;
}
void SYSETATDiscret::SETTe(unsigned int nbech)
{
	_Te = nbech;
}



void SYSETATDiscret::SETeditSizeA(unsigned int length, unsigned int height)
{
	_A->editsize(length, height);
}
void SYSETATDiscret::SETeditSizeB(unsigned int length, unsigned int height)
{
	_B->editsize(length, height);
}
void SYSETATDiscret::SETeditSizeC(unsigned int length, unsigned int height)
{
	_C->editsize(length, height);
}
void SYSETATDiscret::SETeditSizeD(unsigned int length, unsigned int height)
{
	_D->editsize(length, height);
}
void SYSETATDiscret::SETthisCoefA(unsigned int i, unsigned int j, double userValue)
{
	_A->SETthiscoef(i, j, userValue);
}
void SYSETATDiscret::SETthisCoefB(unsigned int i, unsigned int j, double userValue)
{
	_B->SETthiscoef(i, j, userValue);
}
void SYSETATDiscret::SETthisCoefC(unsigned int i, unsigned int j, double userValue)
{
	_C->SETthiscoef(i, j, userValue);
}
void SYSETATDiscret::SETthisCoefD(unsigned int i, unsigned int j, double userValue)
{
	_D->SETthiscoef(i, j, userValue);
}


Matrice* SYSETATDiscret::GETA()const
{
	return _A;
}
Matrice* SYSETATDiscret::GETB()const
{
	return _B;
}
Matrice* SYSETATDiscret::GETC()const
{
	return _C;
}
Matrice* SYSETATDiscret::GETD()const
{
	return _D;
}
double SYSETATDiscret::GETTe()const
{
	return _Te;
}



void SYSETATDiscret::calculABCD(const FCTDiscret& fct){
	/*
		Calcul des matrices A, B, C et D
	*/

	if (fct.GETden().GETorder() >= fct.GETnum().GETorder()){
		_A->editsize(fct.GETden().GETorder(), fct.GETden().GETorder());
		for (unsigned int i = 0; i < fct.GETden().GETorder(); i++) {
			_A->SETthiscoef(fct.GETden().GETorder() - 1, i,
				-(fct.GETden().GETcoefTab(i) / fct.GETden().GETcoefTab(fct.GETden().GETorder())));
		}
		for (unsigned int i = 0; i < fct.GETden().GETorder(); i++) {
			for (unsigned int j = 1; j < fct.GETden().GETorder(); j++) {
				_A->SETthiscoef(i, j, 1);
				i++;
			}
		}
		

		_B->editsize(fct.GETden().GETorder(), 1);
		_B->SETthiscoef(_B->GETlength() - 1, 0, 1 / fct.GETden().GETcoefTab(fct.GETden().GETorder()));
		

		_C->editsize(1, fct.GETden().GETorder());
		for (unsigned int i = 0; i <= fct.GETnum().GETorder(); i++) 
			_C->SETthiscoef(0, i, fct.GETnum().GETcoefTab(i));
		
		

		_D->editsize(1, 1);
	}
	else
		std::cout << std::endl << "______Order of Num = " << fct.GETden().GETorder() << "  > Order of Den = " << fct.GETnum().GETorder();
}


void SYSETATDiscret::simulation(const std::string& namefile, Signal& signal, Matrice& x0, double* yOut) {
	/*
		simulation du système d'état avec un signal en entré et une matrice x0
		calcul echantillon par echantillon le signal de sorti
	*/
	std::ofstream reponse(namefile);
	std::ostringstream repy;
	std::string rep;
	Matrice dx(_A->GETlength(), 1), y(1, 1);

	for (unsigned int i = 0; i < signal.GETnbech(); i++){
		dx = *_A * x0 + *_B * signal.GETthiscoef(i);
		y = *_C * x0 + *_D * signal.GETthiscoef(i);
		yOut[i] = y.GETthiscoef(0, 0);
		x0 = dx;
		repy << std::endl << signal.GETdeltaT() * i << " , " << signal.GETthiscoef(i) << " , " << y.GETthiscoef(0, 0);
	}

	rep = repy.str();
	std::cout << rep;
	if (reponse) {
		reponse << rep;
	}
	else
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le Fichier : " << namefile;

}

std::string SYSETATDiscret::printOn(bool on)const{
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


void testSYSETATDiscret(){
	std::cout << std::endl << "___TEST SYSETATDiscret___";


	FCTDiscret fct;
	fct.SETnumOrder(1);
	fct.SETnumThisCoef(0, 1);
	fct.SETnumThisCoef(1, -0.63);
	fct.SETdenOrder(4);
	fct.SETdenThisCoef(0, 0);
	fct.SETdenThisCoef(1, -0.6);
	fct.SETdenThisCoef(2, 1);
	fct.SETdenThisCoef(3, 0.01);
	fct.SETdenThisCoef(4, 2);
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

	Echelon E(50, 0.1, 10.0);
	Matrice x0(sys.GETA()->GETlength(), 1);
	x0.SETthiscoef(0, 0, 0.1);

	std::cout << std::endl << std::endl << std::endl << "Reponse temporelle avec E = 10.0" << std::endl;
	//sys.simulation("bin/files/ReponseTemporelle.txt", E, x0);
}