#include "Matrice.h"

using namespace std;

Matrice::Matrice() : _tab(allocate(2, 2)), _length(2), _height(2)
{
}
Matrice::Matrice(unsigned int lenght, unsigned int height) : _tab(allocate(lenght, height)), _length(lenght), _height(height)
{
}
Matrice::Matrice(double** tab, unsigned int lenght, unsigned int height)
: _tab(tab), _length(lenght), _height(height)
{
}
Matrice::Matrice(const Matrice& M)
:_tab(allocate(M)), _length(M._length), _height(M._height)
{
}
Matrice::~Matrice()
{
	if (_tab != nullptr) {
		for (unsigned int i = 0; i < _length; i++) {
			delete[] _tab[i];
			_tab[i] = nullptr;
		}
		delete[] _tab;
		_tab = nullptr;
	}
}




Matrice& Matrice::operator=(const Matrice& M) {
	if (this != &M) {
		if (_tab != nullptr)
			delete  _tab;
		_length = M._length;
		_height = M._height;
		_tab = allocate(M);
	}
	return *this;
}
bool operator==(const Matrice& A, const Matrice& B) {
	if (A._length == B._length && A._height == B._height){
		for (unsigned int i = 0; i < A._length; i++){
			for (unsigned int j = 0; j < B._length; j++){
				if (A._tab[i][j] != B._tab[i][j])
					return false;
			}
		}
		return true;
	}
	return false;
}
std::ostream& operator<<(std::ostream& os, const Matrice& s){
	return os << s.printOn(false);
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
	Matrice addition(A._length, A._height);
	if (assertSize(A._length, A._height, B._length, B._height)){
		for (unsigned int i = 0; i < A._length; i++){
			for (unsigned int j = 0; j < A._height; j++)
				addition.SETthiscoef(i, j, A.GETthiscoef(i, j) + B.GETthiscoef(i, j));
		}
	}
	return addition;
}
Matrice soustraction(const Matrice& A, const Matrice& B) {
	Matrice soustraction(A._length, A._height);
	if (assertSize(A._length, A._height, B._length, B._height)){
		for (unsigned int i = 0; i < A._length; i++){
			for (unsigned int j = 0; j < A._height; j++)
				soustraction.SETthiscoef(i, j, A.GETthiscoef(i, j) - B.GETthiscoef(i, j));
		}
	}
	return soustraction;
}
Matrice multiplication(const Matrice& A, const Matrice& B) {
	double somme = 0;
	Matrice multiplication(A._length, B._height);
	if (A._length == B._height) {
		for (unsigned int iMulti = 0, iA = 0; iMulti < multiplication._length, iA < A._length; iMulti++, iA++) {
			for (unsigned int jMulti = 0, jB = 0; jMulti < multiplication._height, jB < B._height; jMulti++, jB++) {
				somme = 0;
				for (unsigned int jA = 0, iB = 0; jA < A._height, iB < B._length; jA++, iB++)
					somme += A.GETthiscoef(iA, jA) * B.GETthiscoef(iB, jB);
				multiplication.SETthiscoef(iMulti, jMulti, somme);
			}
		}
	}
	else
		cout << endl << "___________Matrice : Error multiplication : A._lenght != B._height";
	return multiplication;
}



double** Matrice::allocate(unsigned int length, unsigned int height) const {
	/*
	alloue un tableau de taille size de type double initialisé à 0
	*/

	double** buffer = new double*[length];
	for (unsigned int i = 0; i < length; i++)
		buffer[i] = new double[height];

	for (unsigned int i = 0; i < length; i++){
		for (unsigned int j = 0; j < height; j++)
			buffer[i][j] = 0;
	}
	return buffer;
}
double** Matrice::allocate(const Matrice& P) const {

	double** buffer = new double*[P._length];
	for (unsigned int i = 0; i < P._length; i++)
		buffer[i] = new double[P._height];

	for (unsigned int i = 0; i < P._length; i++){
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
unsigned int Matrice::GETlength()const {
	return _length;
}
unsigned int Matrice::GETheight()const {
	return _height;
}

void Matrice::ones(){
	for (unsigned int i = 0; i < _length; i++){
		for (unsigned int j = 0; j < _height; j++){
			_tab[i][j] = 1;
		}
	}
}
void Matrice::editsize(unsigned int lenght, unsigned int height) {
	if (_tab != nullptr) {
		for (unsigned int i = 0; i < _length; i++) {
			delete[] _tab[i];
			_tab[i] = nullptr;
		}
		delete[] _tab;
		_tab = nullptr;
	}

	double** buffer = new double*[lenght];
	for (unsigned int i = 0; i < lenght; i++)
		buffer[i] = new double[height];

	for (unsigned int i = 0; i < lenght; i++) {
		for (unsigned int j = 0; j < height; j++)
			buffer[i][j] = 0;
	}
	_tab = buffer;
	_length = lenght;
	_height = height;
}

string Matrice::printOn(bool on)const{
	ostringstream stream;
	string matrice = "";
	for (unsigned int i = 0; i < _length; i++){
		stream << endl << "|";
		for (unsigned int j = 0; j < _height; j++)
			stream << " " << _tab[i][j];
		stream << " |";
	}
	matrice = stream.str();
	if (on)
		cout << matrice;
	return matrice;
}

bool Matrice::assertIndex(unsigned int lenght, unsigned int height)const {
	if (lenght <= _length && height <= _height)
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
	cout << endl << "nouvelle matrice F = C + D" << F;
	
	H = F * F;
	cout << endl << "Matrice H : F(3x3) * F(3x3) = " << H;
	
	Matrice K;
	cout << endl << "Matrice K constructeur par defaut:" << K;
	K.editsize(3, 3);
	cout << endl << "Matrice K : K.editsize(3, 3) :" << K;
	Matrice J(1, 5);
	cout << endl << "J(1x5)" << J;

	J.editsize(5, 1);
	cout << endl << "J(5x1)" << J;

	J.editsize(1, 1);
	cout << endl << "J(1x1)" << J;
	
	cout << endl << endl;
}