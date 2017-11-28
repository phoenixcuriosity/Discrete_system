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




void FCTDiscret::ModifFCT(){

}

std::ostream & FCTDiscret::affichageTextuel(std::ostream & os) const{
	//os << endl << "(" << _num << ")" << "/" << "(" << _den << ")";
	return os;
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



