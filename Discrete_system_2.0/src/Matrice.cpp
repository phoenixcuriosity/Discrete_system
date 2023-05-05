/*

	Discrete_system
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	file version 4.2.2

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

/* *********************************************************
 *						Include							   *
 ********************************************************* */

#include "Matrice.h"

/* *********************************************************
 *						Class Matrice					   *
 ********************************************************* */

/* *********************************************************
 *				constructeurs et destructeur			   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* NAME : Matrice																	   */
/* ROLE : Constructeur par d�faut													   */
/* INPUT  PARAMETERS : void			 												   */
/* OUTPUT PARAMETERS : 		( 0 | 0 )												   */
/* OUTPUT PARAMETERS : 		( 0 | 0 )											       */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
Matrice::Matrice()
:
_tab(allocate(1, 1)),
_length(1),
_height(1),
m_displayPrecision(DEFAULT_DISPLAY_PRECISION)
{
}

/* ----------------------------------------------------------------------------------- */
/* NAME : Matrice																	   */
/* ROLE : Constructeur cast d'un double vers un objet Matice						   */
/* INPUT  PARAMETERS : double Value : Valeur unique des coefficients de la Matrice	   */
/* OUTPUT PARAMETERS : 		( Value | Value )										   */
/* OUTPUT PARAMETERS : 		( Value | Value )									       */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
Matrice::Matrice
(
	double Value
)
:
_tab(allocate(1, 1, Value)),
_length(1),
_height(1),
m_displayPrecision(DEFAULT_DISPLAY_PRECISION)
{
}

/* ----------------------------------------------------------------------------------- */
/* NAME : Matrice																	   */
/* ROLE : Constructeur par taille													   */
/* INPUT  PARAMETERS : unsigned int lenght : nombre de colonnes						   */
/* INPUT  PARAMETERS : unsigned int height : nombre de lignes						   */
/* OUTPUT PARAMETERS : 		( 0 | ... | 0 )											   */
/* OUTPUT PARAMETERS : 		( . | ... | . )											   */
/* OUTPUT PARAMETERS : 		( 0 | ... | 0 )											   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
Matrice::Matrice
(
	unsigned int lenght,
	unsigned int height
)
:
_tab(allocate(lenght, height)),
_length(lenght),
_height(height),
m_displayPrecision(DEFAULT_DISPLAY_PRECISION)
{
}

/* ----------------------------------------------------------------------------------- */
/* NAME : Matrice																	   */
/* ROLE : Constructeur par taille et par valeur	de tab								   */
/* INPUT  PARAMETERS : unsigned int lenght : nombre de colonnes						   */
/* INPUT  PARAMETERS : unsigned int height : nombre de lignes						   */
/* OUTPUT PARAMETERS : 		(    tab[0][0]   | ... |   tab[lenght][0]    )		   	   */
/* OUTPUT PARAMETERS : 		( .............. | ... | ................... )			   */
/* OUTPUT PARAMETERS : 		( tab[0][height] | ... | tab[lenght][height] )			   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
Matrice::Matrice
(
	double** tab,
	unsigned int lenght,
	unsigned int height
)
: _tab(tab),
_length(lenght),
_height(height),
m_displayPrecision(DEFAULT_DISPLAY_PRECISION)
{
}

/* ----------------------------------------------------------------------------------- */
/* NAME : Matrice																	   */
/* ROLE : Constructeur par d�faut													   */
/* INPUT  PARAMETERS : const Matrice& M : Matrice � copier			 				   */
/* OUTPUT PARAMETERS : Matrice r�sultat de la copie de celle d'entr�e				   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
Matrice::Matrice
(
	const Matrice& M
)
:
_tab(allocate(M)), 
_length(M._length),
_height(M._height),
m_displayPrecision(DEFAULT_DISPLAY_PRECISION)
{
}

/* ----------------------------------------------------------------------------------- */
/* NAME : ~Matrice																	   */
/* ROLE : Destructeur de la classe Matrice											   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : Objet Matrice d�truit										   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
Matrice::~Matrice()
{
	deAllocate(_length, _tab);
}


/* *********************************************************
 *					assert and allocate					   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* NAME : allocate																	   */
/* ROLE : Alloue un tableau de taille length et height de type double initialis� � 0   */
/* INPUT  PARAMETERS : unsigned int lenght : Nombre de colonnes						   */
/* INPUT  PARAMETERS : unsigned int height : Nombre de lignes						   */
/* OUTPUT PARAMETERS : Matrice de taille length et height contenant les 0			   */
/* RETURNED VALUE    : double** : matrice de taille length et height contenant les 0   */
/* ------------------------------------------------------------------------------------*/
double** Matrice::allocate
(
	unsigned int length,
	unsigned int height
) const
{
	double** buffer(nullptr);
	if (assertRange(length, height))
	{
		buffer = new double* [length];
		for (unsigned int i(0); i < length; i++)
			buffer[i] = new double[height];

		for (unsigned int i(0); i < length; i++)
		{
			for (unsigned int j(0); j < height; j++)
				buffer[i][j] = 0;
		}
	}
	return buffer;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : allocate																	   */
/* ROLE : Alloue un tableau de tableau de taille length et height ...				   */
/* ROLE : ... de type double initialis� � Value										   */
/* INPUT  PARAMETERS : unsigned int lenght : Nombre de colonnes						   */
/* INPUT  PARAMETERS : unsigned int height : Nombre de lignes						   */
/* INPUT  PARAMETERS : double Value : Valeur d'initialisation						   */
/* OUTPUT PARAMETERS : Matrice de taille length et height contenant les Value		   */
/* RETURNED VALUE    : double** : matrice de taille length et height				   */
/* ------------------------------------------------------------------------------------*/
double** Matrice::allocate
(
	unsigned int length,
	unsigned int height,
	double userValue
) const
{

	double** buffer(nullptr);
	if (assertRange(length, height))
	{
		buffer = new double* [length];
		for (unsigned int i(0); i < length; i++)
			buffer[i] = new double[height];

		fillTabLoop(length, height, buffer, userValue);
	}
	return buffer;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : allocate																	   */
/* ROLE : Recopie de l'attribut _tab de la Matrice en entr�e						   */
/* INPUT  PARAMETERS : const Matrice& : Matrice de recopie							   */
/* OUTPUT PARAMETERS : Matrice de taille length et height contenant la recopie 		   */
/* RETURNED VALUE    : double** : matrice de taille length et height				   */
/* ------------------------------------------------------------------------------------*/
double** Matrice::allocate
(
	const Matrice& P
) const
{

	double** buffer(new double* [P._length]);
	for (unsigned int i(0); i < P._length; i++)
		buffer[i] = new double[P._height];

	for (unsigned int i(0); i < P._length; i++)
	{
		for (unsigned int j(0); j < P._height; j++)
			buffer[i][j] = P._tab[i][j];
	}
	return buffer;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : deAllocate																   */
/* ROLE : D�truit l'allocation dynamique de tab										   */
/* INPUT  PARAMETERS : unsigned int lenght : Nombre de colonnes						   */
/* INPUT  PARAMETERS : double** tab : tableau de valeur								   */
/* OUTPUT PARAMETERS : delete tab													   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
void Matrice::deAllocate
(
	unsigned int length,
	double** tab
)
{
	if (nullptr != tab)
	{
		for (unsigned int i(0); i < length; i++)
		{
			if (nullptr != tab[i])
			{
				delete[] tab[i];
				tab[i] = nullptr;
			}	
		}
		delete[] tab;
		tab = nullptr;
	}
	else
	{
		std::cout << std::endl << "tab == nullptr";
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME : assertIndex																   */
/* ROLE : Test in range pour length et height compar� � ceux dans la Matrice		   */
/* INPUT  PARAMETERS : unsigned int lenght : Nombre de colonnes						   */
/* INPUT  PARAMETERS : unsigned int height : Nombre de lignes						   */
/* OUTPUT PARAMETERS : Validation Out Of Range ou In Range							   */
/* RETURNED VALUE    : bool : false -> length and/or height Out Of Range of Matrice	   */
/* RETURNED VALUE    : bool : true -> length and height In Range of Matrice			   */
/* ------------------------------------------------------------------------------------*/
bool Matrice::assertIndex
(
	unsigned int lenght,
	unsigned int height
)const
{
	if	(
			lenght < _length
			&&
			height < _height
		)
		return true;
	else
	{
		std::cout << std::endl << "__________Matrice : assertIndex false";
		return false;
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME : assertRange																   */
/* ROLE : Test in range > 0 et MAX_MATRICE_SIZE										   */
/* INPUT  PARAMETERS : unsigned int lenght : Nombre de colonnes						   */
/* INPUT  PARAMETERS : unsigned int height : Nombre de lignes						   */
/* OUTPUT PARAMETERS : Validation Out Of Range ou In Range							   */
/* RETURNED VALUE    : bool : false -> length and/or height Out Of Range of Matrice	   */
/* RETURNED VALUE    : bool : true -> length and height In Range of Matrice			   */
/* ------------------------------------------------------------------------------------*/
bool Matrice::assertRange
(
	/* IN */
	const unsigned int length,
	const unsigned int height
)const
{
	if	(
			length > 0
			&&
			length < MAX_MATRICE_SIZE
			&&
			height > 0
			&&
			height < MAX_MATRICE_SIZE
		)
	{
		return true;
	}	
	else
	{
		std::cout << std::endl << "__________Matrice : editSize : Range error";
		return false;
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME : assertSize																   */
/* ROLE : Test le premier couple == deuxi�me couple									   */
/* INPUT  PARAMETERS : unsigned int lenghtA : Nombre de colonnes Matrice A			   */
/* INPUT  PARAMETERS : unsigned int heightA : Nombre de lignes Matrice A			   */
/* INPUT  PARAMETERS : unsigned int lenghtB : Nombre de colonnes Matrice B			   */
/* INPUT  PARAMETERS : unsigned int heightB : Nombre de lignes Matrice B			   */
/* OUTPUT PARAMETERS : Validation si meme taille									   */
/* RETURNED VALUE    : bool : false -> length and/or height Out Of Range of Matrice	   */
/* RETURNED VALUE    : bool : true -> length and height In Range of Matrice			   */
/* ------------------------------------------------------------------------------------*/
bool Matrice::assertSize
(
	/* IN */
	const unsigned int lenghtA,
	const unsigned int heightA,
	const unsigned int lenghtB,
	const unsigned int heightB
)
{
	if	(
			lenghtA == lenghtB
			&&
			heightA == heightB
		)
	{
		return true;
	}
	else
	{
		std::cout << std::endl << "__________Matrice : assertSize false";
		return false;
	}
}


/* *********************************************************
 *			op�rations entre 2 objets Matrice			   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* NAME : operator =																   */
/* ROLE : Red�finition de l'op�rateur =												   */
/* INPUT  PARAMETERS : const Matrice& P : objet permettant l'�galisation			   */
/* OUTPUT PARAMETERS : this = P														   */
/* RETURNED VALUE    : Matrice& : return this										   */
/* ------------------------------------------------------------------------------------*/
Matrice& Matrice::operator=
(
	const Matrice& M
)
{
	if (this != &M) 
	{
		if (_tab != nullptr)
			deAllocate(_length, _tab);
		_length = M._length;
		_height = M._height;
		_tab = allocate(M);
	}
	return *this;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : operator ==																   */
/* ROLE : Red�finition de l'op�rateur ==											   */
/* ROLE : Comparaison entre les 2 Polynome en Input									   */
/* INPUT  PARAMETERS : const Matrice& a : un objet Matrice 							   */
/* INPUT  PARAMETERS : const Matrice& b : un objet Matrice							   */
/* OUTPUT PARAMETERS : Comparaison													   */
/* RETURNED VALUE    : bool : == -> true // != -> false								   */
/* ------------------------------------------------------------------------------------*/
bool operator==
(
	const Matrice& A,
	const Matrice& B
)
{
	if	(
			A._length == B._length
			&&
			A._height == B._height
		)
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

/* ----------------------------------------------------------------------------------- */
/* NAME : operator+																	   */
/* ROLE : Red�finition de l'op�rateur +												   */
/* ROLE : Addition entre les 2 Inputs												   */
/* INPUT  PARAMETERS : const Matrice& a : un objet Matrice 							   */
/* INPUT  PARAMETERS : const Matrice& b : un objet Matrice							   */
/* OUTPUT PARAMETERS : r�sultat de l'addition (a + b)								   */
/* RETURNED VALUE    : Matrice : retourne un objet r�sultat de l'addition			   */
/* ------------------------------------------------------------------------------------*/
Matrice operator+
(
	const Matrice& A,
	const Matrice& B
)
{
	Matrice addition(A._length, A._height);
	if (Matrice::assertSize(A._length, A._height, B._length, B._height))
	{
		for (unsigned int i(0); i < A._length; i++)
		{
			for (unsigned int j(0); j < A._height; j++)
				addition.SETthiscoef(i, j, A.GETthiscoef(i, j) + B.GETthiscoef(i, j));
		}
	}
	return addition;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : operator-																	   */
/* ROLE : Red�finition de l'op�rateur -												   */
/* ROLE : Soustraction entre les 2 Inputs											   */
/* INPUT  PARAMETERS : const Matrice& a : un objet Matrice 							   */
/* INPUT  PARAMETERS : const Matrice& b : un objet Matrice							   */
/* OUTPUT PARAMETERS : r�sultat de soustraction (a - b)								   */
/* RETURNED VALUE    : Matrice : retourne un objet r�sultat de la soustraction		   */
/* ------------------------------------------------------------------------------------*/
Matrice operator-
(
	const Matrice& A, 
	const Matrice& B
)
{
	Matrice soustraction(A._length, A._height);
	if (Matrice::assertSize(A._length, A._height, B._length, B._height))
	{
		for (unsigned int i(0); i < A._length; i++)
		{
			for (unsigned int j(0); j < A._height; j++)
				soustraction.SETthiscoef(i, j, A.GETthiscoef(i, j) - B.GETthiscoef(i, j));
		}
	}
	return soustraction;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : operator*																	   */
/* ROLE : Red�finition de l'op�rateur *												   */
/* ROLE : Multiplication entre les 2 Inputs											   */
/* INPUT  PARAMETERS : const Matrice& a : un objet Matrice	 						   */
/* INPUT  PARAMETERS : const Matrice& b : un objet Matrice							   */
/* OUTPUT PARAMETERS : r�sultat de la multiplication (a * b)						   */
/* RETURNED VALUE    : Matrice : retourne un objet r�sultat de la multiplication	   */
/* ------------------------------------------------------------------------------------*/
Matrice operator*
(
	const Matrice& A,
	const Matrice& B
)
{
	/* ---------------------------------------------------------------------- */
	/* Cas 1																  */
	/* Si le nombre de lignes de A est �gale au nombre de colonnes de B		  */
	/* ---------------------------------------------------------------------- */
	if (A._height == B._length)
	{
		double somme(0);
		Matrice multiplication(A._length, B._height);
		for (unsigned int iMulti(0), iA(0); iMulti < multiplication._length, iA < A._length; iMulti++, iA++)
		{
			for (unsigned int jMulti(0), jB(0); jMulti < multiplication._height, jB < B._height; jMulti++, jB++)
			{
				somme = 0;
				for (unsigned int jA(0), iB(0); jA < A._height, iB < B._length; jA++, iB++)
					somme += A.GETthiscoef(iA, jA) * B.GETthiscoef(iB, jB);
				multiplication.SETthiscoef(iMulti, jMulti, somme);
			}
		}
		return multiplication;
	}
	/* ---------------------------------------------------------------------- */
	/* Cas 2																  */
	/* Si le nombre de colonnes de A est �gale � 1							  */
	/* et																	  */
	/* Si le nombre de lignes de A est �gale � 1							  */
	/* ---------------------------------------------------------------------- */
	else if (
				A._length == 1
				&&
				A._height == 1
			)
	{
		Matrice multiplication(B.GETlength(), B.GETheight());
		for (unsigned int iB(0); iB < B.GETlength(); iB++)
		{
			for (unsigned int jB(0); jB < B.GETheight(); jB++)
				multiplication.SETthiscoef(iB, jB, A.GETthiscoef(0, 0) * B.GETthiscoef(iB, jB));
		}
		return multiplication;
	}
	/* ---------------------------------------------------------------------- */
	/* Cas 3																  */
	/* Si le nombre de colonnes de B est �gale � 1							  */
	/* et																	  */
	/* Si le nombre de lignes de B est �gale � 1							  */
	/* ---------------------------------------------------------------------- */
	else if (
				B._length == 1
				&&
				B._height == 1
			)
	{
		Matrice multiplication(A.GETlength(), A.GETheight());
		for (unsigned int iA(0); iA < A.GETlength(); iA++)
		{
			for (unsigned int jA(0); jA < A.GETheight(); jA++)
				multiplication.SETthiscoef(iA, jA, B.GETthiscoef(0, 0) * A.GETthiscoef(iA, jA));
		}
		return multiplication;
	}
	/* ---------------------------------------------------------------------- */
	/* Cas 4																  */
	/* Reste des cas diff�rents de 1, 2 et 3								  */
	/* ---------------------------------------------------------------------- */
	else
	{
		Matrice multiplication(1, 1);
		std::cout << std::endl << "___________Matrice : Error multiplication : A._lenght != B._height";
		return multiplication;
	}
}

/* *********************************************************
 *					op�rations sur l'objet				   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* NAME : fillTabLoop																   */
/* ROLE : Rempli la Matrice de taille length * height de valeur value				   */
/* INPUT  PARAMETERS : unsigned int length : Nombre de colonnes						   */
/* INPUT  PARAMETERS : unsigned int height : Nombre de lignes						   */
/* INPUT  PARAMETERS : double*** tab : Ptr Matrice � remplir						   */
/* INPUT  PARAMETERS : double value : Valeur � appliquer							   */
/* OUTPUT PARAMETERS : Matrice remplie de value										   */
/* RETURNED VALUE    : Matrice														   */
/* ------------------------------------------------------------------------------------*/
void Matrice::fillTabLoop
(
	unsigned int length,
	unsigned int height,
	double** tab,
	double value

)
{
	for (unsigned int i(0); i < length; i++)
	{
		for (unsigned int j(0); j < height; j++)
		{
			tab[i][j] = value;
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME : transposition																   */
/* ROLE : Transpose la Matrice en entr�e											   */
/* INPUT  PARAMETERS : const Matrice& : Matrice � transposer						   */
/* OUTPUT PARAMETERS : Transpos� de la Matrice en entr�e							   */
/* RETURNED VALUE    : Matrice														   */
/* ------------------------------------------------------------------------------------*/
Matrice transposition
(
	const Matrice& A
)
{
	Matrice resultat(A.GETheight(), A.GETlength());
	for (unsigned int i(0); i < resultat.GETlength(); i++)
	{
		for (unsigned int j(0); j < resultat.GETheight(); j++)
			resultat.SETthiscoef(i, j, A.GETthiscoef(j, i));
	}
	return resultat;
}

/* ----------------------------------------------------------------------------------- */
/* NAME : zero																		   */
/* ROLE : Rempli la Matrice de taille length * height de 0							   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : Matrice remplie de 0											   */
/* RETURNED VALUE    : Matrice														   */
/* ------------------------------------------------------------------------------------*/
void Matrice::zero()
{
	fillTabLoop(_length, _height, _tab, 0);
}

/* ----------------------------------------------------------------------------------- */
/* NAME : ones																		   */
/* ROLE : Rempli la Matrice de taille length * height de 1							   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : Matrice remplie de 1											   */
/* RETURNED VALUE    : Matrice														   */
/* ------------------------------------------------------------------------------------*/
void Matrice::ones()
{
	fillTabLoop(_length, _height, _tab, 1);
}

/* ----------------------------------------------------------------------------------- */
/* NAME : editSize																	   */
/* ROLE : Changement de taille de la Matrice 										   */
/* ROLE : Si plus grand remplissage 0, si plus petit suppression des derniers		   */
/* INPUT  PARAMETERS : unsigned int length : Nombre de colonnes						   */
/* INPUT  PARAMETERS : unsigned int height : Nombre de lignes						   */
/* OUTPUT PARAMETERS : Matrice agrandie ou rapetissie								   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
void Matrice::editSize
(
	unsigned int length,
	unsigned int height
)
{
	if (assertRange(length, height))
	{
		/* ---------------------------------------------------------------------- */
		/* Partie 1																  */
		/* Remplissage d'un buffer au min de length et height					  */
		/* ---------------------------------------------------------------------- */

		double** buffer(new double*[length]);
		for (unsigned int i(0); i < length; i++)
			buffer[i] = new double[height];

		unsigned int maxLength(std::max(_length, length));
		unsigned int maxHeight(std::max(_height, height));
		unsigned int minLength(std::min(_length, length));
		unsigned int minHeight(std::min(_height, height));

		for (unsigned int i(0); i < minLength; i++)
		{
			for (unsigned int j(0); j < minHeight; j++)
				buffer[i][j] = _tab[i][j];
		}

		/* ---------------------------------------------------------------------- */
		/* Partie 2																  */
		/* Gestion des diff�rents cas											  */
		/* ---------------------------------------------------------------------- */


		/* ---------------------------------------------------------------------- */
		/* Cas 1																  */
		/* Si le nombre de colonnes est sup�rieur ou �gale � celui de la Matrice  */
		/* et																	  */
		/* Si le nombre de ligne est sup�rieur ou �gale � celui de la Matrice	  */
		/* et																	  */
		/* Si un des deux est diff�rent 										  */
		/* ---------------------------------------------------------------------- */
		if (
				length >= _length
				&&
				height >= _height
				&&
				(	
					length != _length
					||
					height != _height
				)
			)
		{
			for (unsigned int i(0); i < maxLength; i++)
			{
				for (unsigned int j(0); j < maxHeight; j++)
				{
					if (i >= minLength || j >= minHeight)
						buffer[i][j] = 0;
				}
			}
		}
		/* ---------------------------------------------------------------------- */
		/* Cas 2																  */
		/* Si le nombre de colonnes est sup�rieur ou �gale � celui de la Matrice  */
		/* et																	  */
		/* Si le nombre de ligne est inf�rieur ou �gale � celui de la Matrice	  */
		/* et																	  */
		/* Si un des deux est diff�rent 										  */
		/* ---------------------------------------------------------------------- */
		else if (
					length >= _length
					&&
					height <= _height
					&&
					(
						length != _length
						||
						height != _height
					)
				)
		{
			for (unsigned int i(0); i < maxLength; i++) 
			{
				for (unsigned int j(0); j < minHeight; j++)
				{
					if (i >= minLength)
						buffer[i][j] = 0;
				}
			}
		}
		/* ---------------------------------------------------------------------- */
		/* Cas 3																  */
		/* Si le nombre de colonnes est inf�rieur ou �gale � celui de la Matrice  */
		/* et																	  */
		/* Si le nombre de ligne est sup�rieur ou �gale � celui de la Matrice	  */
		/* et																	  */
		/* Si un des deux est diff�rent 										  */
		/* ---------------------------------------------------------------------- */
		else if (
					length <= _length
					&&
					height >= _height
					&&
					(	
						length != _length
						||
						height != _height
					)
				)
		{
			for (unsigned int i(0); i < minLength; i++)
			{
				for (unsigned int j(0); j < maxHeight; j++)
				{
					if (j >= minHeight)
						buffer[i][j] = 0;
				}
			}
		}
		/* ---------------------------------------------------------------------- */
		/* Cas 4																  */
		/* Si le nombre de colonnes est inf�rieur ou �gale � celui de la Matrice  */
		/* et																	  */
		/* Si le nombre de ligne est inf�rieur ou �gale � celui de la Matrice	  */
		/* et																	  */
		/* Si un des deux est diff�rent 										  */
		/* ---------------------------------------------------------------------- */
		else if (
					length <= _length
					&&
					height <= _height
					&&
					(
						length != _length
						||
						height != _height
					)
				)
		{
			/* N/A */
			/* Action d�j� r�alis�e dans Partie 1 */
		}
		/* ---------------------------------------------------------------------- */
		/* Cas 5																  */
		/* Si le nombre de colonnes est �gale � celui de la Matrice				  */
		/* et																	  */
		/* Si le nombre de ligne est �gale � celui de la Matrice				  */
		/* ---------------------------------------------------------------------- */
		else if (
					length == _length
					&&
					height == _height
				)
		{
			/* N/A */
			/* Action d�j� r�alis�e dans Partie 1 */
		}
		/* ---------------------------------------------------------------------- */
		/* Cas 6																  */
		/* D�fault																  */
		/* ---------------------------------------------------------------------- */
		else
		{
			std::cout << std::endl << "[ERROR]___: Matrice::editSize : cas impossible";
		}

		/* ---------------------------------------------------------------------- */
		/* Partie 3																  */
		/* Actualisation des infomations										  */
		/* ---------------------------------------------------------------------- */

		deAllocate(_length, _tab);
		_tab = buffer;
		_length = length;
		_height = height;
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME : growOneLOneC																   */
/* ROLE : Agrandie de 1 le nombre colonnes et de lignes de la Matrice  				   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : Matrice agrandie de 1 remplie de 0							   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
void Matrice::growOneLOneC()
{
	double** buffer(new double*[_length + GROW1L1C]);
	for (unsigned int i(0); i < _length + GROW1L1C; i++)
		buffer[i] = new double[_height + GROW1L1C];

	for (unsigned int i(0); i < _length + GROW1L1C; i++)
	{
		for (unsigned int j(0); j < _height + GROW1L1C; j++)
		{
			if (i == _length || j == _height)
			{
				buffer[i][j] = 0;
			}
			else
			{
				buffer[i][j] = _tab[i][j];
			}
		}		
	}

	/* ---------------------------------------------------------------------- */
	/* Actualisation des infomations										  */
	/* ---------------------------------------------------------------------- */

	deAllocate(_length, _tab);
	_tab = buffer;
	_length++;
	_height++;
}

/* *********************************************************
 *						 affichage						   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* NAME : operator<<																   */
/* ROLE : Red�finition de l'op�rateur <<											   */
/* ROLE : Envoi sur le ostream (std::cout, ...) une forme textuelle ...				   */
/* ROLE : ... de l'objet cr��e par la fonction printOn								   */
/* INPUT  PARAMETERS : std::ostream& os : stream de sortie : std::cout, ...			   */
/* INPUT  PARAMETERS : const Matrice& s : La Matrice � afficher						   */
/* OUTPUT PARAMETERS : affichage textuelle de la Matrice sur la console				   */
/* RETURNED VALUE    : std::ostream& : std::cout, ...								   */
/* ------------------------------------------------------------------------------------*/
std::ostream& operator<<
(
	std::ostream& os,
	const Matrice& s
)
{
	return os << s.printOn(false);
}


/* ----------------------------------------------------------------------------------- */
/* NAME : printOn																	   */
/* ROLE : Cr�ation d'une repr�sentation visuelle de la Matrice						   */
/* INPUT  PARAMETERS : bool on = true : si true -> affichage direct ... 			   */
/* INPUT  PARAMETERS : ... sur std::cout // sinon false								   */
/* OUTPUT PARAMETERS : chaine de carat�res repr�sentant de la Matrice				   */
/* RETURNED VALUE    : std::string : chaine de carat�res							   */
/* ------------------------------------------------------------------------------------*/
const std::string Matrice::printOn(bool on)const
{
	std::ostringstream stream;
	std::string matrice("");
	for (unsigned int i(0); i < _length; i++)
	{
		stream << std::endl << "|";
		for (unsigned int j = 0; j < _height; j++)
		{
			if (_tab[i][j] >= 0.0)
			{
				/* space for "+" */
				stream << "\t" << " " << std::fixed << std::setprecision(m_displayPrecision) << _tab[i][j];
			}
			else
			{
				stream << "\t" << std::fixed << std::setprecision(m_displayPrecision) << _tab[i][j];
			}

		}

		stream << " |";
	}
	matrice = stream.str();
	if (on)
		std::cout << matrice;
	return matrice;
}



/* *********************************************************
 *							Test						   *
 ********************************************************* */


/* ----------------------------------------------------------------------------------- */
/* NAME : testMatrice																   */
/* ROLE : For DEV only																   */
/* ROLE : Test des m�thodes et fonctions de la classe Matrice						   */
/* INPUT  PARAMETERS : void															   */
/* OUTPUT PARAMETERS : Test de la classe											   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
void testMatrice()
{
	std::ostringstream stream;
	std::string matrice("");

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

	double** a(new double*[3]);
	for (unsigned int i(0); i < 3; i++)
		a[i] = new double[3];

	for (unsigned int i(0); i < 3; i++)
	{
		for (unsigned int j(0); j < 3; j++)
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
	K.editSize(3, 3);
	stream << std::endl << "Matrice K : K.editSize(3, 3) :" << K;
	Matrice J(1, 5);
	stream << std::endl << "J(1x5)" << J;
	J.editSize(5, 1);
	stream << std::endl << "J(5x1)" << J;

	K.ones();
	K.editSize(3, 4);
	
	K.SETthiscoef(0, 0, 3.6), K.SETthiscoef(0, 1, -3.6), K.SETthiscoef(0, 2, 3.6);
	stream << std::endl << "Matrice K :" << K;
	Matrice L = transposition(K);
	stream << std::endl << "L transposee de K" << L;

	J.editSize(1, 1);
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

/* *********************************************************
 *						 assesseurs						   *
 ********************************************************* */

void Matrice::SETthiscoef
(
	unsigned int i,
	unsigned int j,
	double userValue
)
{
	if (assertIndex(i, j))
		_tab[i][j] = userValue;
}

void Matrice::SETprecision
(
	Uint8 precision
)
{
	m_displayPrecision = precision;
}

double Matrice::GETthiscoef
(
	unsigned int i,
	unsigned int j
)const
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

Uint8 Matrice::GETprecision()const
{
	return m_displayPrecision;
}

/*
*	End Of File : Matrice.cpp
*/