#include "Vecteur.h"

using namespace std;

Vecteur::Vecteur() : Polynome(), _ligne(true)
{
}
Vecteur::Vecteur(unsigned int size, bool ligne): Polynome(size), _ligne(ligne)
{
}
Vecteur::Vecteur(unsigned int size, double tab[], bool ligne): Polynome(size, tab), _ligne(ligne)
{
}
Vecteur::Vecteur(const Vecteur& V): Polynome(V), _ligne(V._ligne)
{
}
Vecteur::~Vecteur()
{
}

void Vecteur::printOn()const {
	if (_ligne) {
		cout << "[";
		for (unsigned int i = 0; i < this->GETsize(); i++)
			cout << " " << this->GETcoefTab(i);
		cout << "]";
	}
	else
		for (unsigned int i = 0; i < this->GETsize(); i++)
			cout << "|" << this->GETcoefTab(i) << "|" << endl;
}

void testVecteur() {
	cout << endl << "___TEST VECTEUR___";
	Vecteur A(3);
	A.SETcoefTab(1, 3.2);
	A.SETcoefTab(0, -96);
	cout << endl;
	cout << "Vecteur A constructeur par valeur1 en ligne:" << endl;
	A.printOn();
	cout << endl;
	Vecteur B(5, VColonne);
	B.SETcoefTab(0, -956.3);
	B.SETcoefTab(4, 6);
	B.SETcoefTab(1, 4);
	cout << "Vecteur B constructeur par recopie en colonne:" << endl;
	B.printOn();
	cout << endl;
	Vecteur C;
	C.SETcoefTab(0, 2);
	cout << "Vecteur C constructeur par defaut:" << endl;
	C.printOn();
	cout << endl;
	
	double poly[3] = { 1, 2, 3 };
	Vecteur D(3, poly);
	cout << "Vecteur D constructeur par valeur2:" << endl;
	D.printOn();
	cout << endl;

}
