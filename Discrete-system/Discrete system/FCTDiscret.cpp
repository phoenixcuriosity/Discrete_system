#include "FCTDiscret.h"

using namespace std;

FCTDiscret::FCTDiscret() : _num(), _den(), _deltaT(1)
{
}

FCTDiscret::FCTDiscret(Polynome& num, Polynome& den, double deltaT) : _num(num), _den(den), _deltaT(deltaT)
{
}

FCTDiscret::~FCTDiscret()
{
}




FCTDiscret& FCTDiscret::operator=(const FCTDiscret& a){
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
FCTDiscret operator+(FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat = a.addition(a, b);
	return resultat;
}
FCTDiscret operator-(FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat = a.soustraction(a, b);
	return resultat;
}
FCTDiscret operator*(FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat = a.multiplication(a, b);
	return resultat;
}



FCTDiscret FCTDiscret::addition(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat.SETnum(a.GETnum().multiplication(a.GETnum(), b.GETden()));
	resultat.SETnum(a.GETnum().addition(resultat.GETnum(), a.GETnum().multiplication(b.GETnum(), a.GETden())));
	resultat.SETden(a.GETnum().multiplication(a.GETden(), b.GETden()));
	return resultat;
}
FCTDiscret FCTDiscret::soustraction(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat.SETnum(a.GETnum().multiplication(a.GETnum(), b.GETden()));
	resultat.SETnum(a.GETnum().soustraction(resultat.GETnum(), a.GETnum().multiplication(b.GETnum(), a.GETden())));
	resultat.SETden(a.GETnum().multiplication(a.GETden(), b.GETden()));
	return resultat;
}
FCTDiscret FCTDiscret::multiplication(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat.SETnum(a.GETnum().multiplication(a.GETnum(), b.GETnum()));
	resultat.SETden(a.GETden().multiplication(a.GETden(), b.GETden()));
	return resultat;
}


void FCTDiscret::ModifFCT(){

}

void FCTDiscret::affichageTextuel() const{
	unsigned int stringSize = 0;
	string barre = "";
	string middle = "";

	if (_num.GETstringSize() > _den.GETstringSize()){
		stringSize = _num.GETstringSize();
		_num.printOn();
		for (unsigned int i = 0; i < stringSize; i++)
			barre += "-";
		cout << endl << barre;
		for (unsigned int i = 0; i < ((_num.GETstringSize() / 2) - (_den.GETstringSize() / 2)); i++)
			middle += " ";
		cout << endl << middle;
		_den.printOn();
	}
	else if (_num.GETstringSize() < _den.GETstringSize()){
		stringSize = _den.GETstringSize();
		for (unsigned int i = 0; i < ((_den.GETstringSize() / 2) - (_num.GETstringSize() / 2)); i++)
			middle += " ";
		cout << middle;
		_num.printOn();
		for (unsigned int i = 0; i < stringSize; i++)
			barre += "-";
		cout << endl << barre;
		cout << endl;
		_den.printOn();
	}
	else{
		stringSize = _num.GETstringSize();
		_num.printOn();
		for (unsigned int i = 0; i < stringSize; i++)
			barre += "-";
		cout << endl << barre;
		cout << endl;
		_den.printOn();
	}
}


void FCTDiscret::SETnum(const Polynome &a){
	_num = a;
}
void FCTDiscret::SETden(const Polynome &a){
	_den = a;
}



Polynome FCTDiscret::GETnum() const{
	return _num;
}
Polynome FCTDiscret::GETden() const{
	return _den;
}


void testFCTDiscret(){
	cout << endl << "___TEST FCTDiscret___";
	Polynome a(3);
	a.SETcoefTab(2, 1);
	a.SETcoefTab(1, 2);
	Polynome b(a);
	b.SETcoefTab(2, 2);
	a.grow(2);
	a.SETcoefTab(0, 51);
	a.SETcoefTab(1, -512);
	b.SETcoefTab(0, 1);
	

	cout << endl;
	FCTDiscret fct1(b, a, 10.3);
	b.SETcoefTab(0, 7.3);
	b.SETcoefTab(1, -91);
	FCTDiscret fct2(a, b, 10.3);
	fct1.affichageTextuel();
	cout << endl;
	cout << endl;
	cout << endl;
	fct2.affichageTextuel();
	cout << endl;
	cout << endl << "multiplication de a * b, Fonctions de transfert :";
	cout << endl;
	FCTDiscret fctmultiplication = fct1 * fct2;
	fctmultiplication.affichageTextuel();
	cout << endl;
	cout << endl << "addition de a + b,  Fonctions de transfert :";
	cout << endl;
	FCTDiscret fctaddition = fct1 + fct2;
	fctaddition.affichageTextuel();
	cout << endl;
	cout << endl << "soustraction de a - b,  Fonctions de transfert :";
	cout << endl;
	FCTDiscret fctsoustraction = fct1 - fct2;
	fctsoustraction.affichageTextuel();
	cout << endl;
}
