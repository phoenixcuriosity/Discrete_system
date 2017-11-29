#include "Matrice.h"

using namespace std;


Matrice::Matrice(unsigned int lenght, unsigned int height) : _tab(allocate(lenght, height)), _lenght(lenght), _height(height)
{
}
Matrice::Matrice(double** tab)
{
}
Matrice::Matrice(double** tab, unsigned int lenght, unsigned int height)
{
}
Matrice::~Matrice()
{

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


void Matrice::ones(){
	if (_lenght == _height){
		for (unsigned int i = 0; i < _lenght; i++){
			for (unsigned int j = 0; j < _height; j++){
				_tab[i][j] = 1;
			}
		}
	}
}

void Matrice::printOn(){
	for (unsigned int i = 0; i < _height; i++){
		cout << endl << "|";
		for (unsigned int j = 0; j < _lenght; j++)
			cout << _tab[i][j];
		cout << "|";
	}
}

void testMatrice(){
	Matrice A(5, 5);
	cout << endl << "Matrice A : ";
	A.printOn();
	Matrice B(A);
	B.ones();
	cout << endl << "Matrice B : ";
	B.printOn();
	Matrice C(2, 5);
	cout << endl << "Matrice C : ";
	C.printOn();
}