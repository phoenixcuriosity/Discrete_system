#include "Polynome.h"

using namespace std;


Polynome::Polynome(unsigned int size) : _size(size), _tab(allocate(size)), _stringSize(0)
{
}

Polynome::Polynome(unsigned int size, double tab[]) : _size(size), _tab(tab), _stringSize(0)
{
}
Polynome::Polynome(const Polynome& P) : _size(P._size), _tab(allocate(P)), _stringSize(0)
{
}

Polynome::~Polynome()
{	
	if(_tab != nullptr)
		delete  _tab;
}



Polynome& Polynome::operator=(const Polynome& a){
	/*
		si le polynome n'est pas le meme que celui testé alors le polynome prend les valeurs des attributs de a
	*/
	if (this != &a){
		if (_tab != nullptr)
			delete  _tab;
		_size = a._size;
		_tab = a.allocate(a);
	}
	return *this;
}


bool operator==(const Polynome& a, const Polynome& b){
	/*
		test coef par coef si le polynome est identique
	*/
	if (b.GETsize() == a.GETsize()){
		for (unsigned int i = 0; i < a.GETsize(); i++){
			if (b.GETcoefTab(i) != a.GETcoefTab(i))
				return false;
		}
		return true;
	}
	else
		return false;
}
Polynome operator+(Polynome& a, const Polynome& b){
	Polynome resultat = a.addition(a, b);
	return resultat;
}
Polynome operator-(Polynome& a, const Polynome& b){
	Polynome resultat = a.soustraction(a, b);
	return resultat;
}
Polynome operator*(Polynome& a, const Polynome& b){
	Polynome resultat = a.multiplication(a, b);
	return resultat;
}


void Polynome::SETcoefTab(unsigned int index, double userValue){
	/*
		affecte la valeur userValue à l'adresse index de _tab
	*/
	if (index < _size)
		_tab[index] = userValue;
}

unsigned int Polynome::GETsize() const {
	return _size;
}
double Polynome::GETcoefTab(unsigned int index) const {
	if (index < _size)
		return _tab[index];
}
unsigned int Polynome::GETstringSize() const{
	/*
		calcul la place en byte (= nombre de caractère) pour afficher le polynome sur la console
	*/
	string equation;
	stringstream stream;
	for (int i = _size - 1; i >= 0; i--){
		if (_tab[i] < 0){
			stream << " - " << fixed << setprecision(2) << abs(_tab[i]);
			if (i > 1)
				stream << "Z^" << i;
			else if (i == 1)
				stream << "Z";
		}
		else if (_tab[i] > 0){
			stream << " + " << fixed << setprecision(2) << _tab[i];
			if (i > 1)
				stream << "Z^" << i;
			else if (i == 1)
				stream << "Z";
		}
	}
	equation = stream.str();
	_stringSize = equation.length();
	return _stringSize;
}

Polynome Polynome::addition(const Polynome& a, const Polynome& b){
	/*
	addition de 2 polynomes en choisissant la nouvelle taille par le plus grand ordre
	*/
	unsigned int maxSize = max(a.GETsize(), b.GETsize());
	unsigned int minSize = min(a.GETsize(), b.GETsize());

	if (maxSize == a.GETsize()){
		Polynome newPolynome(a);
		for (unsigned int i = 0; i < minSize; i++)
			newPolynome.SETcoefTab(i, newPolynome.GETcoefTab(i) + b.GETcoefTab(i));
		return newPolynome;
	}

	else if (maxSize == b.GETsize()){
		Polynome newPolynome(b);
		for (unsigned int i = 0; i < minSize; i++)
			newPolynome.SETcoefTab(i, newPolynome.GETcoefTab(i) + a.GETcoefTab(i));
		return newPolynome;
	}
}

Polynome Polynome::soustraction(const Polynome& a, const Polynome& b){
	/*
		soustraction de 2 polynomes en choisissant la nouvelle taille par le plus grand ordre
	*/
	unsigned int maxSize = max(a.GETsize(), b.GETsize());
	unsigned int minSize = min(a.GETsize(), b.GETsize());

	Polynome newPolynome(maxSize);
	if (a.GETsize() == maxSize){
		for (unsigned int i = 0; i < maxSize; i++)
			newPolynome.SETcoefTab(i, a.GETcoefTab(i));
		for (unsigned int i = 0; i < minSize; i++)
			newPolynome.SETcoefTab(i, newPolynome.GETcoefTab(i) - b.GETcoefTab(i));
	}
	return newPolynome;
}
Polynome Polynome::multiplication(const Polynome& a, const Polynome& b){
	/*
		multiplication de 2 polynomes
	*/
	unsigned int maxSize = a.GETsize() + b.GETsize() - 1;
	
	Polynome newPolynome(maxSize);
	for (int i = 0; i < a.GETsize(); i++){
		for (int j = 0; j < b.GETsize(); j++)
			newPolynome.SETcoefTab(i + j, newPolynome.GETcoefTab(i + j) + a.GETcoefTab(i) * b.GETcoefTab(j));
	}
	return newPolynome;
}




void Polynome::grow(double userValue){
	/*
		créer un nouveau tableau ayant une case de plus avec la nouvelle valeur de l'utilisateur
	*/
	const unsigned int newSize = _size + 1;
	double* newTab = allocate(newSize);

	for (unsigned int i = 0; i < _size; i++)
		newTab[i] = _tab[i];

	newTab[_size] = userValue;
	delete _tab;

	_size = newSize;
	_tab = newTab;
}

void Polynome::shrink(){
	const unsigned int newSize = _size - 1;
	double* newTab = allocate(newSize - 1);

	for (unsigned int i = 0; i < newSize; i++)
		newTab[i] = _tab[i];

	delete _tab;

	_size = newSize;
	_tab = newTab;
}


void Polynome::ModifPolynome(unsigned int index, double userValue) {
	if (index < _size)
		_tab[index] = userValue;
}



void Polynome::printOn() const{
	/*
		affiche le polynome en z d'ordre décroissant
	*/
	string equation;
	stringstream stream;
	for (int i = _size - 1; i >= 0; i--){
		if (_tab[i] < 0){
			stream << " - " << fixed << setprecision(2) << abs(_tab[i]);
			if (i > 1)
				stream << "Z^" << i;
			else if (i == 1)
				stream << "Z";
		}
		else if (_tab[i] > 0){
			stream << " + " << fixed << setprecision(2) <<_tab[i];
			if (i > 1)
				stream << "Z^" << i;
			else if (i == 1)
				stream << "Z";
		}
	}
	equation = stream.str();
	_stringSize = equation.length();
	cout << equation;
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



void testPolynome() {
	Polynome a(5);
	a.SETcoefTab(3, 1);
	a.SETcoefTab(1, 69.1);
	Polynome b(a);

	cout << endl << "taille de a = " + to_string(a.GETsize());
	b.SETcoefTab(2, 12.6);
	cout << endl << "valeur de l'index " << 2 <<  "= " + to_string(b.GETcoefTab(2));
	a.grow(2.3);

	a.SETcoefTab(0, -0.9);
	a.SETcoefTab(4, -6534.69461354);
	b.SETcoefTab(0, 96.36);
	b.SETcoefTab(1, -619);

	cout << endl << "taille de a = " + to_string(a.GETsize());
	cout << endl << "valeur de l'index " << 5 << "= " + to_string(a.GETcoefTab(5));
	cout << endl << "Polynome a = ";
	a.printOn();
	cout << endl << "Polynome b = ";
	b.printOn();
	if (a==b)
		cout << endl << "same";
	else
		cout << endl << "not the same";
	
	cout << endl << "addition de a + b = ";
	Polynome addition = a + b;
	addition.printOn();

	cout << endl << "soustraction de a - b = ";
	Polynome soustraction1 = a - b;
	soustraction1.printOn();
	cout << endl << "addition de addition - soustraction1 = ";
	Polynome soustraction2 = addition - soustraction1;
	soustraction2.printOn();
	cout << endl << "multiplication de a * b = ";
	Polynome multiplication = a * b;
	multiplication.printOn();
	a = b;
	if (a == b)
		cout << endl << "same";
	else
		cout << endl << "not the same";
	cout << endl;
}