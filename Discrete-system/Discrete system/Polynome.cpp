#include "Polynome.h"

using namespace std;

Polynome::Polynome(unsigned int size) : _size(size), _tab(allocate(size))
{
}

Polynome::Polynome(unsigned int size, double tab[]) : _size(size), _tab(tab)
{
}
Polynome::Polynome(const Polynome& P) : _size(P._size), _tab(allocate(P._size))
{
}

Polynome::~Polynome()
{	
	if(_tab != nullptr)
		delete  _tab;
}


void Polynome::SETsize(unsigned int size) {

}
void Polynome::SETtab(double tab[]) {

}
void Polynome::SETcoefTab(unsigned int index, double userValue) const {
	_tab[index] = userValue;
}

unsigned int Polynome::GETsize() const {
	return _size;
}
double Polynome::GETcoefTab(unsigned int index) const {
	return _tab[index];
}




double* Polynome::allocate(unsigned int size) const {
	/*
	alloue un tableau de taille size de type double initialisé à 0
	*/
	double* buffer = new double[size];
	for (unsigned int i = 0; i < size; i++)
		buffer[i] = 0;
	return buffer;
}
double* Polynome::allocate(const Polynome& P) const {
	double* buffer = new double[P._size];
	for (unsigned int i = 0; i < P._size; i++)
		buffer[i] = P._tab[i];
	return buffer;
}



void Polynome::ModifPolynome(unsigned int coef, double userValue) {

}



void testPolynome() {
	Polynome a(5);
	Polynome b(a);
	cout << endl << "taille de a = " + to_string(a.GETsize());
	b.SETcoefTab(2, 12.6);
	cout << endl << "valeur de l'index " << 5 <<  "= " + to_string(b.GETcoefTab(2));
}