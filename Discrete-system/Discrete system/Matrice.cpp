/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.26

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "Matrice.h"

using namespace std;

Matrice::Matrice() : _tab(allocate(1, 1)), _length(1), _height(1), _stringSize(0)
{
}
Matrice::Matrice(double userValue) : _tab(allocate(1, 1, userValue)), _length(1), _height(1), _stringSize(0)
{
}
Matrice::Matrice(unsigned int lenght, unsigned int height)
: _tab(allocate(lenght, height)), _length(lenght), _height(height), _stringSize(0)
{
}
Matrice::Matrice(double** tab, unsigned int lenght, unsigned int height)
: _tab(tab), _length(lenght), _height(height), _stringSize(0)
{
}
Matrice::Matrice(const Matrice& M)
: _tab(allocate(M)), _length(M._length), _height(M._height), _stringSize(0)
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
	
	if (A._height == B._length) {
		Matrice multiplication(A._length, B._height);
		for (unsigned int iMulti = 0, iA = 0; iMulti < multiplication._length, iA < A._length; iMulti++, iA++) {
			for (unsigned int jMulti = 0, jB = 0; jMulti < multiplication._height, jB < B._height; jMulti++, jB++) {
				somme = 0;
				for (unsigned int jA = 0, iB = 0; jA < A._height, iB < B._length; jA++, iB++)
					somme += A.GETthiscoef(iA, jA) * B.GETthiscoef(iB, jB);
				multiplication.SETthiscoef(iMulti, jMulti, somme);
			}
		}
		return multiplication;
	}
	else if (A._length == 1 && A._height == 1) {
		Matrice multiplication(B.GETlength(), B.GETheight());
		for (unsigned int iB = 0; iB < B.GETlength(); iB++) {
			for (unsigned int jB = 0; jB < B.GETheight(); jB++)
				multiplication.SETthiscoef(iB, jB, A.GETthiscoef(0,0) * B.GETthiscoef(iB, jB));
		}
		return multiplication;
	}
	else if (B._length == 1 && B._height == 1) {
		Matrice multiplication(A.GETlength(), A.GETheight());
		for (unsigned int iA = 0; iA < A.GETlength(); iA++) {
			for (unsigned int jA = 0; jA < A.GETheight(); jA++)
				multiplication.SETthiscoef(iA, jA, B.GETthiscoef(0, 0) * A.GETthiscoef(iA, jA));
		}
		return multiplication;
	}
	else {
		Matrice multiplication(1, 1);
		cout << endl << "___________Matrice : Error multiplication : A._lenght != B._height";
		return multiplication;
	}
	
}




double** Matrice::allocate(unsigned int length, unsigned int height) const {
	/*
	alloue un tableau de taille size de type double initialisé à 0
	*/
	double** buffer = nullptr;
	if (assertRange(length, height)){
		buffer = new double*[length];
		for (unsigned int i = 0; i < length; i++)
			buffer[i] = new double[height];

		for (unsigned int i = 0; i < length; i++){
			for (unsigned int j = 0; j < height; j++)
				buffer[i][j] = 0;
		}
	}
	return buffer;
}
double** Matrice::allocate(unsigned int length, unsigned int height, double userValue) const {
	/*
	alloue un tableau de taille size de type double initialisé à 0
	*/
	double** buffer = nullptr;
	if (assertRange(length, height)) {
		buffer = new double*[length];
		for (unsigned int i = 0; i < length; i++)
			buffer[i] = new double[height];

		for (unsigned int i = 0; i < length; i++) {
			for (unsigned int j = 0; j < height; j++)
				buffer[i][j] = userValue;
		}
	}
	return buffer;
}
double** Matrice::allocate(const Matrice& P) const {
	/*
		recopie de l'allocation de la matrice P
	*/
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


Matrice transposistion(const Matrice& A){
	/*
		transpose la matrice
	*/
	Matrice resultat(A.GETheight(), A.GETlength());
	for (unsigned int i = 0; i < resultat.GETlength(); i++){
		for (unsigned int j = 0; j < resultat.GETheight(); j++)
			resultat.SETthiscoef(i, j, A.GETthiscoef(j, i));
	}
	return resultat;
}
void Matrice::zero(){
	/*
		Ramplit la matrice de 0
	*/
	for (unsigned int i = 0; i < _length; i++){
		for (unsigned int j = 0; j < _height; j++){
			_tab[i][j] = 0;
		}
	}
}
void Matrice::ones(){
	/*
		Ramplit la matrice de 1
	*/
	for (unsigned int i = 0; i < _length; i++){
		for (unsigned int j = 0; j < _height; j++){
			_tab[i][j] = 1;
		}
	}
}
void Matrice::editsize(unsigned int length, unsigned int height) {
	/*
		Permet de changer la taille d'une matrice en gardant les coefficients existant
	*/

	if (assertRange(length, height)){
		double** buffer = new double*[length];
		for (unsigned int i = 0; i < length; i++)
			buffer[i] = new double[height];

		unsigned int maxLength = maxM(_length, length);
		unsigned int maxHeight = maxM(_height, height);
		unsigned int minLength = minM(_length, length);
		unsigned int minHeight = minM(_height, height);

		for (unsigned int i = 0; i < minLength; i++) {
			for (unsigned int j = 0; j < minHeight; j++)
				buffer[i][j] = _tab[i][j];
		}

		if (length >= _length && height >= _height){
			for (unsigned int i = 0; i < maxLength; i++) {
				for (unsigned int j = 0; j < maxHeight; j++){
					if (i >= minLength || j >= minHeight)
						buffer[i][j] = 0;
				}
			}
		}
		else if (length >= _length && height <= _height){
			for (unsigned int i = 0; i < maxLength; i++) {
				for (unsigned int j = 0; j < minHeight; j++){
					if (i >= minLength)
						buffer[i][j] = 0;
				}
			}
		}
		else if (length <= _length && height >= _height){
			for (unsigned int i = 0; i < minLength; i++) {
				for (unsigned int j = 0; j < maxHeight; j++){
					if (j >= minHeight)
						buffer[i][j] = 0;
				}
			}
		}

		if (_tab != nullptr) {
			for (unsigned int i = 0; i < _length; i++) {
				delete[] _tab[i];
				_tab[i] = nullptr;
			}
			delete[] _tab;
			_tab = nullptr;
		}

		_tab = buffer;
		_length = length;
		_height = height;
	}
}
void Matrice::growOneLOneC(){
	/*
		fait grandir la matrice de 1 ligne et une colonne en gardant les coefficients existant
	*/
	double** buffer = new double*[_length + 1];
	for (unsigned int i = 0; i < _length + 1; i++)
		buffer[i] = new double[_height + 1];

	for (unsigned int i = 0; i < _length; i++) {
		for (unsigned int j = 0; j < _height; j++)
			buffer[i][j] = _tab[i][j];
	}
	for (unsigned int i = 0; i < _length + 1; i++) {
		for (unsigned int j = 0; j < _height + 1; j++){
			if (i == _length || j == _height)
				buffer[i][j] = 0;
		}
	}

	if (_tab != nullptr) {
		for (unsigned int i = 0; i < _length; i++) {
			delete[] _tab[i];
			_tab[i] = nullptr;
		}
		delete[] _tab;
		_tab = nullptr;
	}

	_tab = buffer;
	_length++;
	_height++;
}

const string Matrice::printOn(bool on)const{
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
		cout << endl << "__________Matrice : assertIndex false";
		return false;
	}
}
bool Matrice::assertRange(unsigned int length, unsigned int height)const {
	if (length > 0 && length < 10000 && height > 0 && height < 10000)
		return true;
	else {
		cout << endl << "__________Matrice : editsize : Range error";
		return false;
	}
}
bool assertSize(unsigned int lenghtA, unsigned int heightA, unsigned int lenghtB, unsigned int heightB){
	if (lenghtA == lenghtB && heightA == heightB)
		return true;
	else {
		cout << endl << "__________Matrice : assertSize false";
		return false;
	}
}


void testMatrice(){
	ostringstream stream;
	string matrice = "";

	stream << endl << "___TEST MATRICE___";
	Matrice A(5, 5);
	stream << endl << endl << "Matrice A, constructeur par value1: " << A;
	Matrice B(A);
	B.ones();
	stream << endl << endl << "Matrice B constructeur par recopie : " << B;
	B.SETthiscoef(0, 0, 3);
	B.SETthiscoef(1, 4, 0.1);
	B.SETthiscoef(2, 1, -0.96);
	stream << endl << endl << "coef de la matrice B a l'index 2,1 = " << B.GETthiscoef(2, 1);
	stream << endl << endl << "Matrice B modifie : " << B << endl << endl;

	double** a = new double*[3];
	for (unsigned int i = 0; i < 3; i++)
		a[i] = new double[3];

	for (unsigned int i = 0; i < 3; i++){
		for (unsigned int j = 0; j < 3; j++)
			a[i][j] = 2;
	}
	Matrice C(a, 3 ,3);
	stream << endl << "Matrice C, constructeur par value2: : " << C << endl;
	Matrice D(3, 3);
	D.ones();
	Matrice E(D);
	Matrice F = D + E;
	stream << endl << "Matrice F : D + E = " << F;
	Matrice G = F - E;
	stream << endl << "Matrice G : F - E = " << G;
	Matrice H = F * F;
	stream << endl << "Matrice H : F(3x3) * F(3x3) = " << H;
	F.SETthiscoef(0, 2, 3);
	stream << endl << "nouvelle matrice F avec le coef 0,2 = 3" << F;
	H = F * F;
	stream << endl << "Matrice H : F(3x3) * F(3x3) = " << H;
	F = C + D;
	stream << endl << "nouvelle matrice F = C + D" << F;
	H = F * F;
	stream << endl << "Matrice H : F(3x3) * F(3x3) = " << H;
	Matrice K;
	stream << endl << "Matrice K constructeur par defaut:" << K;
	K.editsize(3, 3);
	stream << endl << "Matrice K : K.editsize(3, 3) :" << K;
	Matrice J(1, 5);
	stream << endl << "J(1x5)" << J;
	J.editsize(5, 1);
	stream << endl << "J(5x1)" << J;

	K.ones();
	K.editsize(3, 4);
	
	K.SETthiscoef(0, 0, 3.6), K.SETthiscoef(0, 1, -3.6), K.SETthiscoef(0, 2, 3.6);
	stream << endl << "Matrice K :" << K;
	Matrice L = transposistion(K);
	stream << endl << "L transposee de K" << L;

	J.editsize(1, 1);
	stream << endl << "J(1x1)" << J;
	J.growOneLOneC();
	stream << endl << "J grow :" << J;
	K.growOneLOneC();
	stream << endl << "K grow :" << K;
	
	Matrice M = 2 * K;
	stream << endl << "M = 2 * K" << M;
	stream << endl << endl;

	matrice = stream.str();
	cout << matrice;
}