/*
Discret_system
author : SAUTER Robin
2017 - 2018
version:0.16

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/


#include "FCTDiscret.h"

using namespace std;

FCTDiscret::FCTDiscret() : _num(), _den(), _deltaT(1)
{
}

FCTDiscret::FCTDiscret(Polynome& num, Polynome& den, double deltaT) : _num(num), _den(den), _deltaT(deltaT)
{
}

FCTDiscret::FCTDiscret(const FCTDiscret& F) : _num(F.GETnum()), _den(F.GETden()), _deltaT(F.GETdeltaT())
{
}

FCTDiscret::~FCTDiscret()
{
}




FCTDiscret& FCTDiscret::operator=(const FCTDiscret& a){
	/*
		si la fct n'est pas de la meme forme alors on prend les attributs de a
	*/
	if (this != &a){
		_num = a._num;
		_den = a._den;
		_deltaT = a._deltaT;
	}
	return *this;
}
bool operator==(const FCTDiscret& a, const FCTDiscret& b){
	if (a.GETnum() == b.GETnum() && a.GETden() == b.GETden())
		return true;
	return false;
}
std::ostream& operator<<(std::ostream& os, const FCTDiscret& s){
	return os << s.printOn(false);
}

FCTDiscret operator+(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat = addition(a, b);
	return resultat;
}
FCTDiscret operator-(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat = soustraction(a, b);
	return resultat;
}
FCTDiscret operator*(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat = multiplication(a, b);
	return resultat;
}



FCTDiscret addition(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat.SETnum(a.GETnum() * b.GETden());
	resultat.SETnum(resultat.GETnum() + b.GETnum() * a.GETden());
	resultat.SETden(a.GETden() * b.GETden());
	return resultat;
}
FCTDiscret soustraction(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat.SETnum(a.GETnum() * b.GETden());
	resultat.SETnum(resultat.GETnum() - b.GETnum() * a.GETden());
	resultat.SETden(a.GETden() * b.GETden());
	return resultat;
}
FCTDiscret multiplication(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat.SETnum(a.GETnum() * b.GETnum());
	resultat.SETden(a.GETden() * b.GETden());
	return resultat;
}


void FCTDiscret::ModifFCT(){

}

string FCTDiscret::printOn(bool on) const{
	/*
		affiche sur la console : en haut le num, puis la barre de fraction et enfin le den
		affichage selon la taille de la chaine de caratere la plus longue
	*/
	unsigned int stringSize = 0;
	string equation;
	stringstream stream;

	if (_num.GETstringSize() > _den.GETstringSize()){
		stringSize = _num.GETstringSize();
		stream << _num.printOn(false) << endl;
		for (unsigned int i = 0; i < stringSize; i++)
			stream << "-";
		stream << endl;
		for (unsigned int i = 0; i < ((_num.GETstringSize() / 2) - (_den.GETstringSize() / 2)); i++)
			stream << " ";
		stream << _den.printOn(false);
		equation = stream.str();
	}
	else if (_num.GETstringSize() < _den.GETstringSize()){
		stringSize = _den.GETstringSize();
		for (unsigned int i = 0; i < ((_den.GETstringSize() / 2) - (_num.GETstringSize() / 2)); i++)
			stream << " ";
		stream << _num.printOn(false) << endl;
		for (unsigned int i = 0; i < stringSize; i++)
			stream << "-";
		stream << endl << _den.printOn(false);
		equation = stream.str();
	}
	else{
		stringSize = _num.GETstringSize();
		stream << _num.printOn(false) << endl;
		for (unsigned int i = 0; i < stringSize; i++)
			stream << "-";
		stream << endl << _den.printOn(false);
		equation = stream.str();
	}
	if (on)
		cout << equation;
	return equation;
}


void FCTDiscret::SETnum(const Polynome &a){
	_num = a;
}
void FCTDiscret::SETden(const Polynome &a){
	_den = a;
}
void FCTDiscret::SETdeltaT(double deltaT){
	_deltaT = deltaT;
}
void FCTDiscret::SETnumOrder(unsigned int order) {
	_num.editsize(order);
}
void FCTDiscret::SETdenOrder(unsigned int order) {
	_den.editsize(order);
}
void FCTDiscret::SETnumThisCoef(unsigned int index, double userValue) {
	_num.SETcoefTab(index, userValue);
}
void FCTDiscret::SETdenThisCoef(unsigned int index, double userValue) {
	_den.SETcoefTab(index, userValue);
}


Polynome FCTDiscret::GETnum() const{
	return _num;
}
Polynome FCTDiscret::GETden() const{
	return _den;
}
double FCTDiscret::GETdeltaT()const{
	return _deltaT;
}


void tabJury(const FCTDiscret& a){
	Polynome den(a.GETden().GETorder());
	for (int i = 0, j = a.GETden().GETorder(); i <= a.GETden().GETorder(), j >= 0; i++, j--)
		den.SETcoefTab(i, a.GETden().GETcoefTab(j));
	if (den.GETcoefTab(den.GETorder()) < 0)
		den = - 1 * den;

	
	
	Polynome ligne1(a.GETden());
	Polynome ligne2(a.GETden());

	Matrice Jury(2, a.GETden().GETorder() + 1);
	for (unsigned int i = 0; i <= a.GETden().GETorder(); i++)
		Jury.SETthiscoef(0, i, a.GETden().GETcoefTab(i));
	for (unsigned int i = 0; i <= a.GETden().GETorder(); i++)
		Jury.SETthiscoef(1, i, den.GETcoefTab(i));
	
	while (ligne2.GETorder() > 2){
		ligne2.editsize(ligne2.GETorder() - 1);
		for (int i = 0, j = ligne2.GETorder(); i <= ligne2.GETorder(), j >= 0; i++, j--)
			ligne2.SETcoefTab(i, ((ligne1.GETcoefTab(0) * ligne1.GETcoefTab(i)) - (ligne1.GETcoefTab(ligne1.GETorder()) * ligne1.GETcoefTab(ligne1.GETorder() - i))));
		
		if (ligne2.GETorder() > 2) {
			Jury.editsize(Jury.GETlength() + 2, a.GETden().GETorder() + 1);
			for (unsigned int i = 0; i <= ligne2.GETorder(); i++)
				Jury.SETthiscoef(Jury.GETlength() - 2, i, ligne2.GETcoefTab(i));
			for (int i = 0, j = ligne2.GETorder(); i <= ligne2.GETorder(), j >= 0; i++, j--)
				Jury.SETthiscoef(Jury.GETlength() - 1, i, ligne2.GETcoefTab(j));
		}
		else {
			Jury.editsize(Jury.GETlength() + 1, a.GETden().GETorder() + 1);
			for (unsigned int i = 0; i <= ligne2.GETorder(); i++)
				Jury.SETthiscoef(Jury.GETlength() - 1, i, ligne2.GETcoefTab(i));
		}
		ligne1 = ligne2;
	}
	cout << endl << endl << "tableau de Jury = " << Jury;



	unsigned int condition = 0;

	/*
		condition abs(a0) < an
	*/
	cout << endl << endl << "abs(a0) = " << abs(a.GETden().GETcoefTab(0));
	if(abs(a.GETden().GETcoefTab(0)) < a.GETden().GETcoefTab(a.GETden().GETorder())){
		cout << " < a" << a.GETden().GETorder() << " = " << a.GETden().GETcoefTab(a.GETden().GETorder()) << "	Ok";
		condition++;
	}
	else
		cout << " > a" << a.GETden().GETorder() << " = " << a.GETden().GETcoefTab(a.GETden().GETorder()) << "	non Ok";


	/*
	condition D(1) > 0
	*/
	double somme = 0;
	for (unsigned int i = 0; i <= a.GETden().GETorder(); i++)
		somme += a.GETden().GETcoefTab(i);
	
	cout << endl << "D(1) = " << somme;
	if (somme > 0){
		cout << "	Ok";
		condition++;
	}
	else
		cout << "non Ok";

	/*
	condition D(-1) > 0 si n pair et ondition D(-1) < 0 si n impair
	*/
	somme = 0;
	for (unsigned int i = 0; i <= a.GETden().GETorder(); i++)
		somme += a.GETden().GETcoefTab(i) * pow(-1, i);
	cout << endl << "D(-1) = " << somme;
	if ((somme > 0 && (a.GETden().GETorder()%2) == 0) || (somme < 0 && (a.GETden().GETorder() % 2) == 1)) {
		cout << "	Ok";
		condition++;
	}
	else
		cout << "	non Ok";
		

	/*
		condition Q0 > Q2
	*/
	cout << endl << "Q0 = " << abs(ligne2.GETcoefTab(0));
	if (abs(ligne2.GETcoefTab(0)) > abs(ligne2.GETcoefTab(2))){
		cout << " > Q2 = " << abs(ligne2.GETcoefTab(2)) << "	Ok";
		condition++;
	}
	else
		cout << " < Q2 = " << abs(ligne2.GETcoefTab(2)) << "	non Ok";

	if (condition == 4)
		cout << endl << "Le systeme est stable";
	else
		cout << endl << "Le systeme est instable";

	cout << endl;
}





void testFCTDiscret(){
	cout << endl << "___TEST FCTDiscret___";
	Polynome a(3);
	a.SETcoefTab(2, 1);
	a.SETcoefTab(1, 2);
	Polynome b(a);
	b.SETcoefTab(2, 2);
	b.SETcoefTab(0, 1);

	a.grow(2);
	a.SETcoefTab(0, 51);
	a.SETcoefTab(1, -512);
	

	cout << endl;
	FCTDiscret fct1(b, a, 10.3);
	b.SETcoefTab(0, 7.3);
	b.SETcoefTab(1, -91);
	FCTDiscret fct2(a, b, 10.3);
	cout << endl << "Fct1 constructeur par valeur:" << endl;
	fct1.printOn();
	cout << endl;
	cout << endl << "Fct2 constructeur par recopie:" << endl;
	fct2.printOn();
	cout << endl;
	cout << endl << "multiplication de a * b, Fonctions de transfert :";
	cout << endl;
	FCTDiscret fctmultiplication = fct1 * fct2;
	fctmultiplication.printOn();
	cout << endl;
	cout << endl << "addition de a + b,  Fonctions de transfert :";
	cout << endl;
	FCTDiscret fctaddition = fct1 + fct2;
	fctaddition.printOn();
	cout << endl;
	cout << endl << "soustraction de a - b,  Fonctions de transfert :";
	cout << endl;
	FCTDiscret fctsoustraction = fct1 - fct2;
	fctsoustraction.printOn();
	cout << endl;

	cout << endl << "taille du num de fct1 = " << fct1.GETnum().GETorder();
	fct1.SETnumOrder(5);
	cout << endl << "taille du num de fct1 = " << fct1.GETnum().GETorder();
	fct1.SETnumThisCoef(4, 5.6);
	fct1.SETnumThisCoef(3, -5.6);
	cout << endl << "Fct1 :" << endl;
	fct1.printOn();
	cout << endl << "Fct1 avec l'operateur << Fct1 = " << endl << fct1 << endl << endl;
}
