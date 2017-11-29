#include "FCTDiscret.h"

using namespace std;

FCTDiscret::FCTDiscret()
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
	return false;
}
FCTDiscret operator+(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat = resultat.addition(a, b);
	return resultat;
}
FCTDiscret operator-(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat = resultat.soustraction(a, b);
	return resultat;
}
FCTDiscret operator*(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat = resultat.multiplication(a, b);
	return resultat;
}



FCTDiscret FCTDiscret::addition(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	return resultat;
}
FCTDiscret FCTDiscret::soustraction(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	return resultat;
}
FCTDiscret FCTDiscret::multiplication(const FCTDiscret& a, const FCTDiscret& b){
	FCTDiscret resultat;
	resultat.SETnum(a.GETnum().multiplication(a.GETnum, b.GETnum));
	resultat.SETden(a.GETden().multiplication(a.GETden, b.GETden));
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
	Polynome a(5);
	a.SETcoefTab(3, 1);
	a.SETcoefTab(1, 69.1);
	Polynome b(a);

	cout << endl << "taille de a = " + to_string(a.GETsize());
	b.SETcoefTab(2, 12.6);
	cout << endl << "valeur de l'index " << 2 << "= " + to_string(b.GETcoefTab(2));
	a.grow(2.3);

	a.SETcoefTab(0, -0.9);
	a.SETcoefTab(4, -6534.69461354);
	b.SETcoefTab(0, 96.36);
	b.SETcoefTab(1, -619);

	cout << endl;
	FCTDiscret fct(b, a, 10.3);
	fct.affichageTextuel();
	cout << endl;
}
