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




Matrice& Matrice::operator=(const Matrice& M) {
	if (this != &M) {
		if (_tab != nullptr)
			delete  _tab;
		_lenght = M._lenght;
		_height = M._height;
		_tab = allocate(M);
	}
	return *this;
}
/**/
bool operator==(const Matrice& A, const Matrice& B) {
	if (A._lenght == B._lenght && A._height == B._height){
		for (unsigned int i = 0; i < A._lenght; i++){
			for (unsigned int j = 0; j < B._lenght; j++){
				if (A._tab[i][j] != B._tab[i][j])
					return false;
			}
		}
		return true;
	}
	return false;
}
Matrice operator+(const Matrice& a, const Matrice& b) {
	Matrice resultat = addition(a, b);
	return resultat;
}
Matrice operator-(const Matrice& a, const Matrice& b) {
	Matrice resultat = soustraction(a, b);
	return resultat;
}
Matrice operator*(const Matrice& a, const Matrice& b) {
	Matrice resultat = multiplication(a, b);
	return resultat;
}


Matrice addition(const Matrice&, const Matrice&) {
	Matrice addition;
	return addition;
}
Matrice soustraction(const Matrice&, const Matrice&) {
	Matrice soustraction;
	return soustraction;
}
Matrice multiplication(const Matrice&, const Matrice&) {
	Matrice multiplication;
	return multiplication;
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
	if (assertIndex(i, j))
		_tab[i][j] = userValue;
}
double Matrice::GETthiscoef(unsigned int i, unsigned int j)const {
	if (assertIndex(i, j))
		return _tab[i][j];
	return 0;
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

bool Matrice::assertIndex(unsigned int lenght, unsigned int height)const {
	if (lenght <= _lenght && height <= _height)
		return true;
	else {
		cout << endl << "Matrice : assertIndex false";
		return false;
	}
}



void testMatrice(){
	cout << endl << "___TEST MATRICE___";
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