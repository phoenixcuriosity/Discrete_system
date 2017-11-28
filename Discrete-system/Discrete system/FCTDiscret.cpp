#include "FCTDiscret.h"

using namespace std;

FCTDiscret::FCTDiscret()
{
}

FCTDiscret::FCTDiscret(Polynome& num, Polynome& den) : _num(num), _den(den)
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
bool FCTDiscret::operator==(const FCTDiscret& a){
	if (this != &a)
		return false;
	return true;
}



void FCTDiscret::ModifFCT(){

}

void FCTDiscret::affichageTextuel() const{
	unsigned int stringSize = 0;
	string barre = "";

	if (_num.GETstringSize() > _den.GETstringSize())
		stringSize = _num.GETstringSize();
	else
		stringSize = _den.GETstringSize();

	_num.printOn();
	for (unsigned int i = 0; i < stringSize; i++)
		barre += "_";
	cout << endl << barre;
	_den.printOn();
}


void FCTDiscret::SETnum(){

}
void FCTDiscret::SETden(){

}



Polynome FCTDiscret::GETnum() const{
	return _num;
}
Polynome FCTDiscret::GETden() const{
	return _den;
}



