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
