#include "FCTDiscret.h"

using namespace std;

FCTDiscret::FCTDiscret()
{
}

FCTDiscret::~FCTDiscret()
{
}





void FCTDiscret::SaisieFCT(){

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



