/*

	Discrete_system
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:2.10

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "Polynome.h"

Polynome::Polynome() : _order(1), _tab(allocate(1)), _stringSize(0)
{
}
Polynome::Polynome(unsigned int size) : _order(size), _tab(allocate(size)), _stringSize(0)
{
}
Polynome::Polynome(double userValue) : _order(0), _tab(allocate(0, userValue)), _stringSize(0)
{
}
Polynome::Polynome(unsigned int size, double tab[]) : _order(size), _tab(allocate(size,tab)), _stringSize(0)
{
}
Polynome::Polynome(const Polynome& P) : _order(P._order), _tab(allocate(P)), _stringSize(0)
{
}
Polynome::~Polynome()
{
	if (_tab != nullptr) {
		delete   _tab;
		_tab = nullptr;
	}
}
Polynome& Polynome::operator=(const Polynome& a){
	/*
		si le polynome n'est pas le meme que celui testé alors le polynome prend les valeurs des attributs de a
	*/
	if (this != &a){
		if (_tab != nullptr)
			delete  _tab;
		_order = a._order;
		_tab = a.allocate(a);
	}
	return *this;
}
bool operator==(const Polynome& a, const Polynome& b){
	/*
		test coef par coef si le polynome est identique
	*/
	if (b.GETorder() == a.GETorder()){
		for (unsigned int i = 0; i < a.GETorder(); i++){
			if (b.GETcoefTab(i) != a.GETcoefTab(i))
				return false;
		}
		return true;
	}
	else
		return false;
}
Polynome operator+(const Polynome& a, const Polynome& b){
	Polynome resultat = addition(a, b);
	return resultat;
}
Polynome operator-(const Polynome& a, const Polynome& b){
	Polynome resultat = soustraction(a, b);
	return resultat;
}
Polynome operator*(const Polynome& a, const Polynome& b){
	Polynome resultat = multiplication(a, b);
	return resultat;
}
Polynome addition(const Polynome& a, const Polynome& b) {
	/*
	addition de 2 polynomes en choisissant la nouvelle taille par le plus grand ordre
	*/
	unsigned int maxSize = max(a.GETorder(), b.GETorder());
	unsigned int minSize = min(a.GETorder(), b.GETorder());



	if (maxSize == a.GETorder()) {
		Polynome newPolynome(a);
		for (unsigned int i = 0; i <= minSize; i++)
			newPolynome.SETcoefTab(i, newPolynome.GETcoefTab(i) + b.GETcoefTab(i));
		return newPolynome;
	}
	else {
		Polynome newPolynome(b);
		for (unsigned int i = 0; i <= minSize; i++)
			newPolynome.SETcoefTab(i, newPolynome.GETcoefTab(i) + a.GETcoefTab(i));
		return newPolynome;
	}
}
Polynome soustraction(const Polynome& a, const Polynome& b) {
	/*
		soustraction de 2 polynomes en choisissant la nouvelle taille par le plus grand ordre
	*/
	unsigned int maxSize = max(a.GETorder(), b.GETorder());
	unsigned int minSize = min(a.GETorder(), b.GETorder());

	Polynome newPolynome(maxSize);
	if (a.GETorder() == maxSize) {
		for (unsigned int i = 0; i <= maxSize; i++)
			newPolynome.SETcoefTab(i, a.GETcoefTab(i));
		for (unsigned int i = 0; i <= minSize; i++)
			newPolynome.SETcoefTab(i, newPolynome.GETcoefTab(i) - b.GETcoefTab(i));
	}
	else {
		for (unsigned int i = 0; i <= maxSize; i++)
			newPolynome.SETcoefTab(i, b.GETcoefTab(i));
		for (unsigned int i = 0; i <= minSize; i++)
			newPolynome.SETcoefTab(i, newPolynome.GETcoefTab(i) - a.GETcoefTab(i));
	}
	return newPolynome;
}
Polynome multiplication(const Polynome& a, const Polynome& b) {
	/*
		multiplication de 2 polynomes
	*/
	unsigned int maxSize = a.GETorder() + b.GETorder();

	Polynome newPolynome(maxSize);
	for (unsigned int i = 0; i <= a.GETorder(); i++) {
		for (unsigned int j = 0; j <= b.GETorder(); j++)
			newPolynome.SETcoefTab(i + j, newPolynome.GETcoefTab(i + j) + a.GETcoefTab(i) * b.GETcoefTab(j));
	}
	return newPolynome;
}

void Polynome::SETcoefTab(unsigned int index, double userValue){
	/*
		affecte la valeur userValue à l'adresse index de _tab
	*/
	if (assertIndex(index)) {
		_tab[index] = userValue;
	}
}
unsigned int Polynome::GETorder() const {
	return _order;
}
double Polynome::GETcoefTab(unsigned int index) const {
	if (assertIndex(index))
		return _tab[index];
	return 0;
}
unsigned int Polynome::GETstringSize() const{
	/*
		calcul la place en byte (= nombre de caractère) pour afficher le polynome sur la console
	*/
	std::string equation;
	equation = this->printOn(false);
	_stringSize = equation.length();
	return _stringSize;
}
void Polynome::SETorder(unsigned int order){
	
	double* newTab = allocate(order);
	unsigned int minSize = min(order, _order);

	for (unsigned int i = 0; i <= minSize; i++)
		newTab[i] = _tab[i];

	if (order > _order) {
		for (unsigned int i = _order; i <= order; i++)
			newTab[i] = 0;
	}

	delete[] _tab;
	_tab = nullptr;

	_order = order;
	_tab = newTab;
}
double Polynome::operator[](unsigned int index) {
	if (assertIndex(index))
		return _tab[index];
	return 0;
}
void Polynome::grow(double userValue){
	/*
		créer un nouveau tableau ayant une case de plus avec la nouvelle valeur de l'utilisateur
	*/
	double* newTab = allocate(++_order);

	for (unsigned int i = 0; i <= _order; i++)
		newTab[i] = _tab[i];

	newTab[_order] = userValue;
	delete[] _tab;

	_tab = newTab;
}
std::ostream& operator << (std::ostream& os, const Polynome& s) {
	return os << s.printOn(false);
}
std::string Polynome::printOn(bool on) const{
	/*
		affiche le polynome en z d'ordre décroissant
	*/
	std::string equation;
	std::ostringstream stream;
	for (int i = _order; i >= 0; i--){
		if (_tab[i] < 0){
			stream << " - ";
			if (abs(_tab[i]) != 1 || i < 1)
				stream << std::fixed << std::setprecision(2) << abs(_tab[i]);
			if (i > 1)
				stream << "Z^" << i;
			else if (i == 1)
				stream << "Z";
		}
		else if (_tab[i] > 0){
			if (i != _order)
				stream << " + ";
			if (_tab[i] != 1 || i < 1)
				stream << std::fixed << std::setprecision(2) <<_tab[i];
			if (i > 1)
				stream << "Z^" << i;
			else if (i == 1)
				stream << "Z";
		}
	}
	equation = stream.str();
	_stringSize = equation.length();
	if (on)
		std::cout << equation;
	return equation;
}

double* Polynome::allocate(unsigned int size) const {
	/*
	alloue un tableau de taille size de type double initialisé à 0
	*/
	double* buffer = new double[size + 1];
	for (unsigned int i = 0; i <= size; i++)
		buffer[i] = 0.0;
	return buffer;
}
double* Polynome::allocate(unsigned int size, double userValue) const {
	/*
	alloue un tableau de taille size de type double initialisé à 0
	*/
	double* buffer = new double[size + 1];
	for (unsigned int i = 0; i <= size; i++)
		buffer[i] = userValue;
	return buffer;
}
double* Polynome::allocate(unsigned int size, double* tab) const {
	/*
	alloue un tableau de taille size de type double initialisé à 0
	*/
	double* buffer = new double[size + 1];
	for (unsigned int i = 0; i <= size; i++)
		buffer[i] = tab[i];
	return buffer;
}
double* Polynome::allocate(const Polynome& P) const {
	double* buffer = new double[P._order + 1];
	for (unsigned int i = 0; i <= P._order; i++)
		buffer[i] = P._tab[i];
	return buffer;
}
bool Polynome::assertIndex(unsigned int index)const {
	if (index <= _order)
		return true;
	else {
		std::cout << std::endl << "_______Polynome : assertIndex false : index = " << index;
		return false;
	}
}

void testPolynome() {
	std::string polynome;
	std::ostringstream stream;


	stream << std::endl << "___TEST POLYNOME___";
	Polynome a((unsigned int)5);
	a.SETcoefTab(3, 1);
	a.SETcoefTab(1, 69.1);
	Polynome b(a);

	stream << std::endl << "taille de a = " + std::to_string(a.GETorder());
	b.SETcoefTab(2, 12.6);
	stream << std::endl << "valeur de l'index " << 2 << "= " + std::to_string(b.GETcoefTab(2));

	a.SETcoefTab(0, -0.9), a.SETcoefTab(4, -6534.69461354), a.grow(2.3);
	b.SETcoefTab(0, 96.36), b.SETcoefTab(1, -619);

	stream << std::endl << "taille de a = " + std::to_string(a.GETorder());
	stream << std::endl << "valeur de l'index " << 5 << "= " + std::to_string(a.GETcoefTab(5));
	stream << std::endl << "Polynome a = " << a;
	stream << std::endl << "Polynome b = " << b;
	if (a == b)
		stream << std::endl << "polynomes identique : a et b";
	else
		stream << std::endl << "polynomes different : a et b";
	
	
	Polynome addition = a + b;
	stream << std::endl << "addition de a + b = " << addition;
	Polynome soustraction1 = a - b;
	stream << std::endl << "soustraction de a - b = " << soustraction1;
	Polynome soustraction2 = addition - soustraction1;
	stream << std::endl << "addition de addition - soustraction1 = " << soustraction2;
	Polynome multiplication = a * b;
	stream << std::endl << "multiplication de a * b = " << multiplication;
	a = b;
	if (a == b)
		stream << std::endl << "polynomes identique : a et b";
	else
		stream << std::endl << "polynomes different : a et b";
	Polynome Z;
	stream << std::endl << std::endl << "taille de Z = " + std::to_string(Z.GETorder());
	Z.SETorder(6);
	stream << std::endl << "taille de Z = " + std::to_string(Z.GETorder());
	Z.SETorder(5);
	stream << std::endl << "taille de Z = " + std::to_string(Z.GETorder());
	Z.SETcoefTab(4, -3.2);
	stream << std::endl << "redefinition de l'operateur << ,  Z = " << Z;
	stream << std::endl << "Z * 2 = " << Z * 2.0;
	stream << std::endl << "Z + 2 = " << Z + 2.0;
	stream << std::endl << "Z - 2 = " << Z - 2.0 << std::endl << std::endl;

	polynome = stream.str();
	std::cout << polynome;
}