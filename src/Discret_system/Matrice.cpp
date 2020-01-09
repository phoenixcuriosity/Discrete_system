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

#include "Matrice.h"

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
	if (_tab != nullptr) 
	{
		for (unsigned int i = 0; i < _length; i++)
		{
			delete[] _tab[i];
			_tab[i] = nullptr;
		}
		delete[] _tab;
		_tab = nullptr;
	}
}





Matrice& Matrice::operator=(const Matrice& M)
{
	if (this != &M) 
	{
		if (_tab != nullptr)
			delete  _tab;
		_length = M._length;
		_height = M._height;
		_tab = allocate(M);
	}
	return *this;
}
bool operator==(const Matrice& A, const Matrice& B)
{
	if (A._length == B._length && A._height == B._height)
	{
		for (unsigned int i = 0; i < A._length; i++)
		{
			for (unsigned int j = 0; j < B._length; j++)
			{
				if (A._tab[i][j] != B._tab[i][j])
					return false;
			}
		}
		return true;
	}
	return false;
}
Matrice operator+(const Matrice& a, const Matrice& b)
{
	Matrice resultat = addition(a, b);
	return resultat;
}
Matrice operator-(const Matrice& a, const Matrice& b)
{
	Matrice resultat = soustraction(a, b);
	return resultat;
}
Matrice operator*(const Matrice& a, const Matrice& b)
{
	Matrice resultat = multiplication(a, b);
	return resultat;
}
Matrice addition(const Matrice& A, const Matrice& B)
{
	Matrice addition(A._length, A._height);
	if (Matrice::assertSize(A._length, A._height, B._length, B._height))
	{
		for (unsigned int i = 0; i < A._length; i++)
		{
			for (unsigned int j = 0; j < A._height; j++)
				addition.SETthiscoef(i, j, A.GETthiscoef(i, j) + B.GETthiscoef(i, j));
		}
	}
	return addition;
}
Matrice soustraction(const Matrice& A, const Matrice& B)
{
	Matrice soustraction(A._length, A._height);
	if (Matrice::assertSize(A._length, A._height, B._length, B._height))
	{
		for (unsigned int i = 0; i < A._length; i++)
		{
			for (unsigned int j = 0; j < A._height; j++)
				soustraction.SETthiscoef(i, j, A.GETthiscoef(i, j) - B.GETthiscoef(i, j));
		}
	}
	return soustraction;
}
Matrice multiplication(const Matrice& A, const Matrice& B)
{
	double somme = 0;
	
	if (A._height == B._length)
	{
		Matrice multiplication(A._length, B._height);
		for (unsigned int iMulti = 0, iA = 0; iMulti < multiplication._length, iA < A._length; iMulti++, iA++)
		{
			for (unsigned int jMulti = 0, jB = 0; jMulti < multiplication._height, jB < B._height; jMulti++, jB++)
			{
				somme = 0;
				for (unsigned int jA = 0, iB = 0; jA < A._height, iB < B._length; jA++, iB++)
					somme += A.GETthiscoef(iA, jA) * B.GETthiscoef(iB, jB);
				multiplication.SETthiscoef(iMulti, jMulti, somme);
			}
		}
		return multiplication;
	}
	else if (A._length == 1 && A._height == 1)
	{
		Matrice multiplication(B.GETlength(), B.GETheight());
		for (unsigned int iB = 0; iB < B.GETlength(); iB++) 
		{
			for (unsigned int jB = 0; jB < B.GETheight(); jB++)
				multiplication.SETthiscoef(iB, jB, A.GETthiscoef(0,0) * B.GETthiscoef(iB, jB));
		}
		return multiplication;
	}
	else if (B._length == 1 && B._height == 1) 
	{
		Matrice multiplication(A.GETlength(), A.GETheight());
		for (unsigned int iA = 0; iA < A.GETlength(); iA++) 
		{
			for (unsigned int jA = 0; jA < A.GETheight(); jA++)
				multiplication.SETthiscoef(iA, jA, B.GETthiscoef(0, 0) * A.GETthiscoef(iA, jA));
		}
		return multiplication;
	}
	else 
	{
		Matrice multiplication(1, 1);
		std::cout << std::endl << "___________Matrice : Error multiplication : A._lenght != B._height";
		return multiplication;
	}
	
}
void Matrice::SETthiscoef(unsigned int i, unsigned int j, double userValue)
{
	if (assertIndex(i, j))
		_tab[i][j] = userValue;
}
double Matrice::GETthiscoef(unsigned int i, unsigned int j)const
{
	if (assertIndex(i, j))
		return _tab[i][j];
	return 0;
}
unsigned int Matrice::GETlength()const
{
	return _length;
}
unsigned int Matrice::GETheight()const 
{
	return _height;
}




/*
	transpose la matrice
*/
Matrice transposition(const Matrice& A)
{
	Matrice resultat(A.GETheight(), A.GETlength());
	for (unsigned int i = 0; i < resultat.GETlength(); i++)
	{
		for (unsigned int j = 0; j < resultat.GETheight(); j++)
			resultat.SETthiscoef(i, j, A.GETthiscoef(j, i));
	}
	return resultat;
}
/*
	Ramplit la matrice de 0
*/
void Matrice::zero()
{
	for (unsigned int i = 0; i < _length; i++)
	{
		for (unsigned int j = 0; j < _height; j++)
		{
			_tab[i][j] = 0;
		}
	}
}


/*
		Ramplit la matrice de 1
*/
void Matrice::ones()
{
	for (unsigned int i = 0; i < _length; i++)
	{
		for (unsigned int j = 0; j < _height; j++)
		{
			_tab[i][j] = 1;
		}
	}
}



/*
		Permet de changer la taille d'une matrice en gardant les coefficients existant
*/
void Matrice::editsize(unsigned int length, unsigned int height)
{
	if (assertRange(length, height))
	{
		double** buffer = new double*[length];
		for (unsigned int i = 0; i < length; i++)
			buffer[i] = new double[height];

		unsigned int maxLength = std::max(_length, length);
		unsigned int maxHeight = std::max(_height, height);
		unsigned int minLength = std::min(_length, length);
		unsigned int minHeight = std::min(_height, height);

		for (unsigned int i = 0; i < minLength; i++)
		{
			for (unsigned int j = 0; j < minHeight; j++)
				buffer[i][j] = _tab[i][j];
		}

		if (length >= _length && height >= _height && (length != _length || height != _height))
		{
			for (unsigned int i = 0; i < maxLength; i++)
			{
				for (unsigned int j = 0; j < maxHeight; j++)
				{
					if (i >= minLength || j >= minHeight)
						buffer[i][j] = 0;
				}
			}
		}
		else if (length >= _length && height <= _height && (length != _length || height != _height))
		{
			for (unsigned int i = 0; i < maxLength; i++) 
			{
				for (unsigned int j = 0; j < minHeight; j++)
				{
					if (i >= minLength)
						buffer[i][j] = 0;
				}
			}
		}
		else if (length <= _length && height >= _height && (length != _length || height != _height))
		{
			for (unsigned int i = 0; i < minLength; i++)
			{
				for (unsigned int j = 0; j < maxHeight; j++)
				{
					if (j >= minHeight)
						buffer[i][j] = 0;
				}
			}
		}
		else if (length <= _length && height <= _height && (length != _length || height != _height))
		{
			/* Todo */
		}
		else if (length == _length && height == _height)
		{
			for (unsigned int i = 0; i < _length; i++)
			{
				for (unsigned int j = 0; j < _height; j++)
					buffer[i][j] = _tab[i][j];
			}
		}

		if (_tab != nullptr) 
		{
			for (unsigned int i = 0; i < _length; i++)
			{
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



/*
	fait grandir la matrice de 1 ligne et une colonne en gardant les coefficients existant
*/
void Matrice::growOneLOneC()
{
	double** buffer = new double*[_length + 1];
	for (unsigned int i = 0; i < _length + 1; i++)
		buffer[i] = new double[_height + 1];

	for (unsigned int i = 0; i < _length; i++)
	{
		for (unsigned int j = 0; j < _height; j++)
			buffer[i][j] = _tab[i][j];
	}
	for (unsigned int i = 0; i < _length + 1; i++) 
	{
		for (unsigned int j = 0; j < _height + 1; j++)
		{
			if (i == _length || j == _height)
				buffer[i][j] = 0;
		}
	}

	if (_tab != nullptr)
	{
		for (unsigned int i = 0; i < _length; i++) 
		{
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


std::ostream& operator<<(std::ostream& os, const Matrice& s)
{
	return os << s.printOn(false);
}


const std::string Matrice::printOn(bool on)const
{
	std::ostringstream stream;
	std::string matrice = "";
	for (unsigned int i = 0; i < _length; i++)
	{
		stream << std::endl << "|";
		for (unsigned int j = 0; j < _height; j++)
			stream << "\t" << _tab[i][j];
		stream << " |";
	}
	matrice = stream.str();
	if (on)
		std::cout << matrice;
	return matrice;
}



/*
	alloue un tableau de taille size de type double initialisé à 0
*/
double** Matrice::allocate(unsigned int length, unsigned int height) const
{
	double** buffer = nullptr;
	if (assertRange(length, height))
	{
		buffer = new double*[length];
		for (unsigned int i = 0; i < length; i++)
			buffer[i] = new double[height];

		for (unsigned int i = 0; i < length; i++)
		{
			for (unsigned int j = 0; j < height; j++)
				buffer[i][j] = 0;
		}
	}
	return buffer;
}




/*
	alloue un tableau de taille size de type double initialisé à 0
*/
double** Matrice::allocate(unsigned int length, unsigned int height, double userValue) const
{
	
	double** buffer = nullptr;
	if (assertRange(length, height))
	{
		buffer = new double*[length];
		for (unsigned int i = 0; i < length; i++)
			buffer[i] = new double[height];

		for (unsigned int i = 0; i < length; i++)
		{
			for (unsigned int j = 0; j < height; j++)
				buffer[i][j] = userValue;
		}
	}
	return buffer;
}




/*
		recopie de l'allocation de la matrice P
*/
double** Matrice::allocate(const Matrice& P) const
{
	
	double** buffer = new double*[P._length];
	for (unsigned int i = 0; i < P._length; i++)
		buffer[i] = new double[P._height];

	for (unsigned int i = 0; i < P._length; i++)
	{
		for (unsigned int j = 0; j < P._height; j++)
			buffer[i][j] = P._tab[i][j];
	}
	return buffer;
}




bool Matrice::assertIndex(unsigned int lenght, unsigned int height)const
{
	if (lenght < _length && height < _height)
		return true;
	else 
	{
		std::cout << std::endl << "__________Matrice : assertIndex false";
		return false;
	}
}


bool Matrice::assertRange(unsigned int length, unsigned int height)const
{
	if (length > 0 && length < 10000 && height > 0 && height < 10000)
		return true;
	else 
	{
		std::cout << std::endl << "__________Matrice : editsize : Range error";
		return false;
	}
}


bool Matrice::assertSize(unsigned int lenghtA, unsigned int heightA, unsigned int lenghtB, unsigned int heightB)
{
	if (lenghtA == lenghtB && heightA == heightB)
		return true;
	else 
	{
		std::cout << std::endl << "__________Matrice : assertSize false";
		return false;
	}
}



void testMatrice()
{
	std::ostringstream stream;
	std::string matrice = "";

	stream << std::endl << "___TEST MATRICE___";
	Matrice A(5, 5);
	stream << std::endl << std::endl << "Matrice A, constructeur par value1: " << A;
	Matrice B(A);
	B.ones();
	stream << std::endl << std::endl << "Matrice B constructeur par recopie : " << B;
	B.SETthiscoef(0, 0, 3);
	B.SETthiscoef(1, 4, 0.1);
	B.SETthiscoef(2, 1, -0.96);
	stream << std::endl << std::endl << "coef de la matrice B a l'index 2,1 = " << B.GETthiscoef(2, 1);
	stream << std::endl << std::endl << "Matrice B modifie : " << B << std::endl << std::endl;

	double** a = new double*[3];
	for (unsigned int i = 0; i < 3; i++)
		a[i] = new double[3];

	for (unsigned int i = 0; i < 3; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
			a[i][j] = 2;
	}
	Matrice C(a, 3 ,3);
	stream << std::endl << "Matrice C, constructeur par value2: : " << C << std::endl;
	Matrice D(3, 3);
	D.ones();
	Matrice E(D);
	Matrice F = D + E;
	stream << std::endl << "Matrice F : D + E = " << F;
	Matrice G = F - E;
	stream << std::endl << "Matrice G : F - E = " << G;
	Matrice H = F * F;
	stream << std::endl << "Matrice H : F(3x3) * F(3x3) = " << H;
	F.SETthiscoef(0, 2, 3);
	stream << std::endl << "nouvelle matrice F avec le coef 0,2 = 3" << F;
	H = F * F;
	stream << std::endl << "Matrice H : F(3x3) * F(3x3) = " << H;
	F = C + D;
	stream << std::endl << "nouvelle matrice F = C + D" << F;
	H = F * F;
	stream << std::endl << "Matrice H : F(3x3) * F(3x3) = " << H;
	Matrice K;
	stream << std::endl << "Matrice K constructeur par defaut:" << K;
	K.editsize(3, 3);
	stream << std::endl << "Matrice K : K.editsize(3, 3) :" << K;
	Matrice J(1, 5);
	stream << std::endl << "J(1x5)" << J;
	J.editsize(5, 1);
	stream << std::endl << "J(5x1)" << J;

	K.ones();
	K.editsize(3, 4);
	
	K.SETthiscoef(0, 0, 3.6), K.SETthiscoef(0, 1, -3.6), K.SETthiscoef(0, 2, 3.6);
	stream << std::endl << "Matrice K :" << K;
	Matrice L = transposition(K);
	stream << std::endl << "L transposee de K" << L;

	J.editsize(1, 1);
	stream << std::endl << "J(1x1)" << J;
	J.growOneLOneC();
	stream << std::endl << "J grow :" << J;
	K.growOneLOneC();
	stream << std::endl << "K grow :" << K;
	
	Matrice M = 2 * K;
	stream << std::endl << "M = 2 * K" << M;
	stream << std::endl << std::endl;

	matrice = stream.str();
	std::cout << matrice;
}