/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.26

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/


#include "FCTDiscret.h"

using namespace std;

FCTDiscret::FCTDiscret() : _num(), _den(), _deltaT(1)
{
}
FCTDiscret::FCTDiscret(double userValue) : _num(allocate(userValue)), _den(allocate(1.0)), _deltaT(1)
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

const string FCTDiscret::printOn(bool on) const{
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


bool FCTDiscret::tabJury(){
	/*
		calcul du critère de Jury permettant de statuer sur la stabilité du système
		tableau de Jury -> Matrice pouvant changer de taille en fonction de l'ordre du den
	*/
	string tableauJury;
	ostringstream stream;

	Polynome den(_den.GETorder());
	for (int i = 0, j = _den.GETorder(); i <= _den.GETorder(), j >= 0; i++, j--)
		den.SETcoefTab(i, _den.GETcoefTab(j));
	if (den.GETcoefTab(den.GETorder()) < 0)
		den = - 1.0 * den;

	
	
	Polynome ligne1(_den);
	Polynome ligne2(_den);

	Matrice Jury;
	if (_den.GETorder() > 2){
		Jury.editsize(2, _den.GETorder() + 1);
		for (unsigned int i = 0; i <= _den.GETorder(); i++)
			Jury.SETthiscoef(0, i, _den.GETcoefTab(i));
		for (unsigned int i = 0; i <= _den.GETorder(); i++)
			Jury.SETthiscoef(1, i, den.GETcoefTab(i));
	}
	else{
		Jury.editsize(1, _den.GETorder() + 1);
		for (unsigned int i = 0; i <= _den.GETorder(); i++)
			Jury.SETthiscoef(0, i, _den.GETcoefTab(i));
	}
	
	while (ligne2.GETorder() > 2){
		ligne2.editsize(ligne2.GETorder() - 1);
		for (int i = 0, j = ligne2.GETorder(); i <= ligne2.GETorder(), j >= 0; i++, j--)
			ligne2.SETcoefTab(i, ((ligne1.GETcoefTab(0) * ligne1.GETcoefTab(i)) - (ligne1.GETcoefTab(ligne1.GETorder()) * ligne1.GETcoefTab(ligne1.GETorder() - i))));
		
		if (ligne2.GETorder() > 2) {
			Jury.editsize(Jury.GETlength() + 2, _den.GETorder() + 1);
			for (unsigned int i = 0; i <= ligne2.GETorder(); i++)
				Jury.SETthiscoef(Jury.GETlength() - 2, i, ligne2.GETcoefTab(i));
			for (int i = 0, j = ligne2.GETorder(); i <= ligne2.GETorder(), j >= 0; i++, j--)
				Jury.SETthiscoef(Jury.GETlength() - 1, i, ligne2.GETcoefTab(j));
		}
		else {
			Jury.editsize(Jury.GETlength() + 1, _den.GETorder() + 1);
			for (unsigned int i = 0; i <= ligne2.GETorder(); i++)
				Jury.SETthiscoef(Jury.GETlength() - 1, i, ligne2.GETcoefTab(i));
		}
		ligne1 = ligne2;
	}
	stream << endl << endl << "table of Jury = " << Jury;



	unsigned int condition = 0;

	/*
		condition abs(a0) < an
	*/
	stream << endl << endl << "abs(a0) = " << abs(_den.GETcoefTab(0));
	if (abs(_den.GETcoefTab(0)) < _den.GETcoefTab(_den.GETorder())){
		stream << " < a" << _den.GETorder() << " = " << _den.GETcoefTab(_den.GETorder()) << "	Ok";
		condition++;
	}
	else
		stream << " > a" << _den.GETorder() << " = " << _den.GETcoefTab(_den.GETorder()) << "	Not Ok";


	/*
	condition D(1) > 0
	*/
	double somme = 0;
	for (unsigned int i = 0; i <= _den.GETorder(); i++)
		somme += _den.GETcoefTab(i);
	
	stream << endl << "D(1) = " << somme;
	if (somme > 0){
		stream << "	Ok";
		condition++;
	}
	else
		stream << "Not Ok";

	/*
	condition D(-1) > 0 si n pair et ondition D(-1) < 0 si n impair
	*/
	somme = 0;
	for (unsigned int i = 0; i <= _den.GETorder(); i++)
		somme += _den.GETcoefTab(i) * pow(-1, i);
	stream << endl << "D(-1) = " << somme;
	if ((somme > 0 && (_den.GETorder() % 2) == 0) || (somme < 0 && (_den.GETorder() % 2) == 1)) {
		stream << "	Ok";
		condition++;
	}
	else
		stream << "	Not Ok";
		
	if (_den.GETorder() > 2){
		/*
		condition Q0 > Q2
		*/
		stream << endl << "Q0 = " << abs(ligne2.GETcoefTab(0));
		if (abs(ligne2.GETcoefTab(0)) > abs(ligne2.GETcoefTab(2))){
			stream << " > Q2 = " << abs(ligne2.GETcoefTab(2)) << "	Ok";
			condition++;
		}
		else
			stream << " < Q2 = " << abs(ligne2.GETcoefTab(2)) << "	Not Ok";
	}
	else{
		condition++;
	}
	

	if (condition == 4){
		stream << endl;
		tableauJury = stream.str();
		cout << tableauJury;
		return true;
	}
	else{
		stream << endl;
		tableauJury = stream.str();
		cout << tableauJury;
		return false;
	}
}

bool FCTDiscret::Bode(double wMin, double wMax, unsigned int nbpoint){
	/*
		Diagramme de Bode en gain et phase
	*/

	ofstream reponse("Bode.txt");
	string texte;
	ostringstream stream;

	double amplitude = wMax - wMin;
	double increment = amplitude / nbpoint;
	double gain = 0, phase = 0;
	Complexe Z, c, cnum, cden;

	for (double i = wMin; i <= wMax; i += increment){
		Z = tfReIm(1, i * _deltaT);
		cnum = tfPolynomeComplexe(_num, Z);
		cden = tfPolynomeComplexe(_den, Z);
		c = cnum / cden;
		gain = 20 * log10(module(c));
		phase = - arg(c);
		stream << endl << i << " , " << gain << " , " << phase;

	}
	texte = stream.str();
	reponse << texte;
	cout << texte;
	return true;
}



void closeLoop(const FCTDiscret& openLoop, const FCTDiscret& returnLoop){
	FCTDiscret num;
	FCTDiscret den;


	num = openLoop;
	den = 1.0 + openLoop * returnLoop;

	//cout << endl << "CloseLoop = " << endl << num << endl << endl << den;

	FCTDiscret resultat;
	resultat.SETnum(num.GETnum() * num.GETden());
	resultat.SETden(den.GETnum() * num.GETden());

	cout << endl << endl << "CloseLoop" << endl << resultat << endl;
	
}




Polynome FCTDiscret::allocate(double userValue) const{
	Polynome a(userValue);
	return a;
}


void testFCTDiscret(){
	string fctdiscret;
	ostringstream stream;

	stream << endl << "___TEST FCTDiscret___";
	Polynome a((unsigned int)3);
	a.SETcoefTab(2, 1), a.SETcoefTab(1, 2);
	Polynome b(a);
	b.SETcoefTab(2, 2), b.SETcoefTab(0, 1);
	a.grow(2), a.SETcoefTab(0, 51), a.SETcoefTab(1, -512);

	FCTDiscret fct1(b, a, 10.3);
	b.SETcoefTab(0, 7.3);
	b.SETcoefTab(1, -91);
	FCTDiscret fct2(a, b, 10.3);
	stream << endl << endl << "Fct1 constructeur par valeur:" << endl << fct1 << endl;
	stream << endl << "Fct2 constructeur par recopie:" << endl << fct2 << endl;
	FCTDiscret fctmultiplication = fct1 * fct2;
	stream << endl << "multiplication de fct1 * fct2, Fonctions de transfert :" << endl << fctmultiplication << endl;
	FCTDiscret fctaddition = fct1 + fct2;
	stream << endl << "addition de fct1 + fct2,  Fonctions de transfert :" << endl << fctaddition << endl;
	FCTDiscret fctsoustraction = fct1 - fct2;
	stream << endl << "soustraction de fct1 - fct2,  Fonctions de transfert :" << endl << fctsoustraction << endl;
	
	stream << endl << "taille du num de fct1 = " << fct1.GETnum().GETorder();
	fct1.SETnumOrder(5);
	stream << endl << "taille du num de fct1 = " << fct1.GETnum().GETorder();
	fct1.SETnumThisCoef(4, 5.6), fct1.SETnumThisCoef(3, -5.6);
	stream << endl << "Fct1 :" << endl << fct1 << endl << endl;
	FCTDiscret integ;
	integ.SETnumOrder(0), integ.SETnumThisCoef(0, 1);
	integ.SETdenOrder(1), integ.SETdenThisCoef(1, 1);
	stream << endl << "integ = " << endl << integ << endl;
	stream << endl << "integ * fct1 = " << endl << (integ * fct1) << endl;

	FCTDiscret openLoop = fct1 * integ;
	FCTDiscret returnLoop = -1.0;

	closeLoop(openLoop, returnLoop);

	fctdiscret = stream.str();
	cout << fctdiscret;
}
