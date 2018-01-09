/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.20

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "SYSETATDiscret.h"

using namespace std;

SYSETATDiscret::SYSETATDiscret()
: _A(), _B(), _C(), _D(), _Te(1)
{
}
SYSETATDiscret::SYSETATDiscret(const SYSETATDiscret& a)
: _A(a._A), _B(a._B), _C(a._C), _D(a._D), _Te(a._Te)
{
}
SYSETATDiscret::~SYSETATDiscret()
{
}

std::ostream& operator<<(std::ostream& os, const SYSETATDiscret& s){
	return os << s.printOn(false);
}


void SYSETATDiscret::SETA(const Matrice& Z){
	_A = Z;
}
void SYSETATDiscret::SETB(const Matrice& Z){
	_B = Z;
}
void SYSETATDiscret::SETC(const Matrice& Z){
	_C = Z;
}
void SYSETATDiscret::SETD(const Matrice& Z){
	_D = Z;
}
void SYSETATDiscret::SETTe(unsigned int nbech){
	_Te = nbech;
}
void SYSETATDiscret::SETeditSizeA(unsigned int length, unsigned int height){
	_A.editsize(length, height);
}
void SYSETATDiscret::SETeditSizeB(unsigned int length, unsigned int height){
	_B.editsize(length, height);
}
void SYSETATDiscret::SETeditSizeC(unsigned int length, unsigned int height){
	_C.editsize(length, height);
}
void SYSETATDiscret::SETeditSizeD(unsigned int length, unsigned int height){
	_D.editsize(length, height);
}
void SYSETATDiscret::SETthisCoefA(unsigned int i, unsigned int j, double userValue){
	_A.SETthiscoef(i, j, userValue);
}
void SYSETATDiscret::SETthisCoefB(unsigned int i, unsigned int j, double userValue){
	_B.SETthiscoef(i, j, userValue);
}
void SYSETATDiscret::SETthisCoefC(unsigned int i, unsigned int j, double userValue){
	_C.SETthiscoef(i, j, userValue);
}
void SYSETATDiscret::SETthisCoefD(unsigned int i, unsigned int j, double userValue){
	_D.SETthiscoef(i, j, userValue);
}
Matrice SYSETATDiscret::GETA()const{
	return _A;
}
Matrice SYSETATDiscret::GETB()const{
	return _B;
}
Matrice SYSETATDiscret::GETC()const{
	return _C;
}
Matrice SYSETATDiscret::GETD()const{
	return _D;
}
double SYSETATDiscret::GETTe()const{
	return _Te;
}



void SYSETATDiscret::calculABCD(const FCTDiscret& fct){
	unsigned int realOrderDen = 0;
	unsigned int realOrderNum = 0;

	for (int i = fct.GETden().GETorder(); i >= 0; i--){
		if (fct.GETden().GETcoefTab(i) != 0){
			realOrderDen = i;
			break;
		}
	}
	for (int i = fct.GETnum().GETorder(); i >= 0; i--){
		if (fct.GETnum().GETcoefTab(i) != 0){
			realOrderNum = i;
			break;
		}
	}
	if (realOrderDen > realOrderNum){
		_A.editsize(realOrderDen, realOrderDen);
		for (unsigned int i = 0; i < realOrderDen; i++) {
			_A.SETthiscoef(realOrderDen - 1, i,
				-(fct.GETden().GETcoefTab(i) / fct.GETden().GETcoefTab(realOrderDen)));
		}
		for (unsigned int i = 0; i < realOrderDen; i++) {
			for (unsigned int j = 1; j < realOrderDen; j++) {
				_A.SETthiscoef(i, j, 1);
				i++;
			}
		}
		

		_B.editsize(realOrderDen, 1);
		_B.SETthiscoef(_B.GETlength() - 1, 0, 1 / fct.GETden().GETcoefTab(realOrderDen));
		

		_C.editsize(1, realOrderDen);
		for (unsigned int i = 0; i <= realOrderNum; i++) {
			_C.SETthiscoef(0, i, fct.GETnum().GETcoefTab(i));
		}
		

		_D.editsize(1, 1);
	}
	else
		cout << endl << "______Order of Num >= Order of Den";
}


void SYSETATDiscret::simulation(const std::string& namefile, const Signal& signal, Matrice& x0) {
	ofstream reponse(namefile);
	ostringstream repy;
	string rep;
	Matrice dx(_A.GETlength(), 1), y(1, 1);



	for (unsigned int i = 0; i < signal.GETnbech(); i++){
		dx = _A * x0 + _B * signal.GETthiscoef(i);
		y = _C * x0 + _D * signal.GETthiscoef(i);
		x0 = dx;
		repy << endl << i << " , " << signal.GETthiscoef(i) << " , " << y.GETthiscoef(0, 0);
	}

	rep = repy.str();
	cout << rep;
	if (reponse) {
		reponse << rep;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << namefile;
}

string SYSETATDiscret::printOn(bool on)const{
	string equation;
	ostringstream stream;

	stream << endl << endl << "Forme Compagne de Commande";
	stream << endl << "Matrice Ac :" << _A << endl << "Matrice Bc :" << _B << endl << "Matrice Cc :" << _C << endl << "Matrice D :" << _D;
	stream << endl << endl << "Forme Compagne d'Observabilite";
	stream << endl << "Matrice Ao :" << transposistion(_A) << endl << "Matrice Bo :" << transposistion(_B)
		<< endl << "Matrice Co :" << transposistion(_C) << endl << "Matrice D :" << _D;

	equation = stream.str();
	if (on)
		cout << equation;
	return equation;
}


void testSYSETATDiscret(){
	cout << endl << "___TEST SYSETATDiscret___";


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
	cout << endl << endl << endl << "fct = " << endl << fct;

	SYSETATDiscret sys;
	sys.calculABCD(fct);
	sys.SETTe(100);
	cout << endl << sys;
	fct.tabJury();
	cout << endl << "BODE" << endl;
	fct.Bode(0.1, 10, 100);

	/*
	FCTDiscret fct2;
	fct2.SETnumOrder(1);
	fct2.SETnumThisCoef(1, 1);
	fct2.SETdenOrder(1);
	fct2.SETdenThisCoef(0, -1);
	fct2.SETdenThisCoef(1, 1);
	cout << endl << fct2;
	fct2.Bode(0.1, 10, 100);
	*/

	Echelon E(50, 10.0);
	Matrice x0(sys.GETA().GETlength(), 1);
	x0.SETthiscoef(0, 0, 0.1);

	cout << endl << endl << endl << "Reponse temporelle avec E = 10.0" << endl;
	sys.simulation("bin/SaveAndLoad/ReponseTemporelle.txt", E, x0);
}