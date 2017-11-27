#include "FCTDiscret.h"

using namespace std;

FCTDiscret::FCTDiscret()
{
}

FCTDiscret::FCTDiscret(Factor& num, Factor& den) : _num(num), _den(den)
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



Factor FCTDiscret::GETnum() const{
	return _num;
}
Factor FCTDiscret::GETden() const{
	return _den;
}



