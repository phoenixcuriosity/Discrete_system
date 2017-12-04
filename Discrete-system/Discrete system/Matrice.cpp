#include "Matrice.h"

using namespace std;

Matrice::Matrice() : _tab(allocate(2, 2)), _lenght(2), _height(2)
{
}
Matrice::Matrice(unsigned int lenght, unsigned int height) : _tab(allocate(lenght, height)), _lenght(lenght), _height(height)
{
}
Matrice::Matrice(double** tab, unsigned int lenght, unsigned int height)
: _tab(tab), _lenght(lenght), _height(height)
{
}
Matrice::Matrice(const Matrice& M)
:_tab(allocate(M)), _lenght(M._lenght), _height(M._height)
{
}
Matrice::~Matrice()
{
	if (_tab != nullptr) {
		for (unsigned int i = 0; i < _lenght; i++) {
			delete[] _tab[i];
			_tab[i] = nullptr;
		}
		delete _tab;
		_tab = nullptr;
	}
}


double** Matrice::allocate(unsigned int lenght, unsigned int height) const {
	/*
	alloue un tableau de taille size de type double initialisé à 0
	*/
	double** buffer = new double*[lenght];
	for (unsigned int i = 0; i < height; i++)
		buffer[i] = new double[height];

	for (unsigned int i = 0; i < lenght; i++){
		for (unsigned int j = 0; j < height; j++)
			buffer[i][j] = 0;
	}
	return buffer;
}
double** Matrice::allocate(const Matrice& P) const {
	double** buffer = new double*[P._lenght];
	for (unsigned int i = 0; i < P._height; i++)
		buffer[i] = new double[P._height];

	for (unsigned int i = 0; i < P._lenght; i++){
		for (unsigned int j = 0; j < P._height; j++)
			buffer[i][j] = P._tab[i][j];
	}
	return buffer;
}


void Matrice::SETthiscoef(unsigned int i, unsigned int j, double userValue) {
	_tab[i][j] = userValue;
}
double Matrice::GETthiscoef(unsigned int i, unsigned int j)const {
	return _tab[i][j];
}

void Matrice::ones(){
	for (unsigned int i = 0; i < _lenght; i++){
		for (unsigned int j = 0; j < _height; j++){
			_tab[i][j] = 1;
		}
	}
}

void Matrice::printOn()const{
	for (unsigned int i = 0; i < _lenght; i++){
		cout << endl << "|";
		for (unsigned int j = 0; j < _height; j++)
			cout << " " << _tab[i][j];
		cout << "|";
	}
}

void testMatrice(){
	cout << endl << "___TEST MATRICE___";
	cout << endl << "(uniquement pour matrice carre)";
	Matrice A(5, 5);
	cout << endl << endl << "Matrice A, constructeur par value1: ";
	A.printOn();
	Matrice B(A);
	B.ones();
	cout << endl << endl << "Matrice B constructeur par recopie : ";
	B.printOn();
	B.SETthiscoef(0, 0, 3);
	B.SETthiscoef(1, 4, 0.1);
	B.SETthiscoef(2, 1, -0.96);
	cout << endl << endl << "coef de la matrice B a l'index 2,1 = " << B.GETthiscoef(2, 1);
	cout << endl << endl << "Matrice B modifie : ";
	B.printOn();
	cout << endl << endl;

	
	double** a = new double*[3];
	for (unsigned int i = 0; i < 3; i++)
		a[i] = new double[3];

	for (unsigned int i = 0; i < 3; i++){
		for (unsigned int j = 0; j < 3; j++)
			a[i][j] = 2;
	}
	Matrice C(a, 3 ,3);
	cout << endl << "Matrice C, constructeur par value2: : ";
	C.printOn();
	cout << endl << endl;
}