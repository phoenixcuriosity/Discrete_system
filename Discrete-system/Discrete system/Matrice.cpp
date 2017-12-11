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


Matrice addition(const Matrice& A, const Matrice& B) {
	Matrice addition(A._lenght, A._height);
	if (assertSize(A._lenght, A._height, B._lenght, B._height)){
		for (unsigned int i = 0; i < A._lenght; i++){
			for (unsigned int j = 0; j < A._height; j++)
				addition.SETthiscoef(i, j, A.GETthiscoef(i, j) + B.GETthiscoef(i, j));
		}
	}
	return addition;
}
Matrice soustraction(const Matrice& A, const Matrice& B) {
	Matrice soustraction(A._lenght, A._height);
	if (assertSize(A._lenght, A._height, B._lenght, B._height)){
		for (unsigned int i = 0; i < A._lenght; i++){
			for (unsigned int j = 0; j < A._height; j++)
				soustraction.SETthiscoef(i, j, A.GETthiscoef(i, j) - B.GETthiscoef(i, j));
		}
	}
	return soustraction;
}
Matrice multiplication(const Matrice& A, const Matrice& B) {
	double somme = 0;
	Matrice multiplication(A._lenght, B._height);
	for (unsigned int iMulti = 0, iA = 0; iMulti < multiplication._lenght, iA < A._lenght; iMulti++, iA++){
		for (unsigned int jMulti = 0, jB = 0; jMulti < multiplication._height, jB < B._height; jMulti++, jB++){
			somme = 0;
			for (unsigned int jA = 0, iB = 0; jA < A._height, iB < B._lenght; jA++, iB++)
				somme += A.GETthiscoef(iA, jA) * B.GETthiscoef(iB, jB);
			multiplication.SETthiscoef(iMulti, jMulti, somme);
		}
	}
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
bool assertSize(unsigned int lenghtA, unsigned int heightA, unsigned int lenghtB, unsigned int heightB){
	if (lenghtA == lenghtB && heightA == heightB)
		return true;
	else {
		cout << endl << "Matrice : assertSize false";
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
	cout << endl;

	Matrice D(3, 3);
	D.ones();
	Matrice E(D);
	Matrice F = D + E;
	cout << endl << "Matrice F : D + E = ";
	F.printOn();

	Matrice G = F - E;
	cout << endl << "Matrice G : F - E = ";
	G.printOn();

	Matrice H = F * F;
	cout << endl << "Matrice H : F(3x3) * F(3x3) = ";
	H.printOn();

	cout << endl << "nouvelle matrice F avec le coef 0,2 = 3";
	F.SETthiscoef(0, 2, 3);
	F.printOn();
	H = F * F;
	cout << endl << "Matrice H : F(3x3) * F(3x3) = ";
	H.printOn();

	F = C + D;
	cout << endl << "nouvelle matrice F = C + D";
	F.printOn();
	H = F * F;
	cout << endl << "Matrice H : F(3x3) * F(3x3) = ";
	H.printOn();
	/*
	Matrice I = A * H;
	cout << endl << "Matrice I : A(5x5) * H(3x3) = ";
	I.printOn();
	*/

	/*
	Matrice VL(1, 5);
	VL.ones();
	cout << endl << "Matrice VL : ligne = ";
	VL.printOn();

	Matrice VC(5, 1);
	VC.ones();
	cout << endl << "Matrice VC : colonne = ";
	VC.printOn();
	*/
	cout << endl << endl;
}