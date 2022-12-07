/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version: 3.0
	file version 2.0

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

#ifndef Signal_H
#define Signal_H


/* *********************************************************
 *						Include							   *
 ********************************************************* */

#include "LIB.h"

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

/* N/A */

/* *********************************************************
 *						Class Matrice					   *
 ********************************************************* */

// classe abstraite -> impossible d'instancier un d'objet Signal
class Signal
{ 
public:

	/* *********************************************************
	 *				constructeurs et destructeur			   *
	 ********************************************************* */


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Signal																	   */
	/* ROLE : Constructeur par d�faut													   */
	/* INPUT  : void																	   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Signal();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Signal																	   */
	/* ROLE : Constructeur																   */
	/* INPUT  : unsigned int nbech : Nombre d'�chantillions du Signal					   */
	/* INPUT  : double deltaT : p�riode d'�chantillonnage								   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Signal
	(
		unsigned int nbech,
		double deltaT
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : Signal																	   */
	/* ROLE : Constructeur																   */
	/* INPUT  : unsigned int nbech : Nombre d'�chantillions du Signal					   */
	/* INPUT  : double deltaT : P�riode d'�chantillonnage								   */
	/* INPUT  : double* tab : tableau d'�chantillions									   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	Signal
	(
		unsigned int nbech,
		double deltaT,
		double* tab
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : ~Signal																	   */
	/* ROLE : Destructeur de la classe Signal											   */
	/* INPUT : void																		   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	~Signal();

protected:

	/* *********************************************************
	 *				 allocate et test d'index				   *
	 ********************************************************* */


	virtual double* allocate(unsigned int) const;
	virtual double* allocate(unsigned int, double) const;
	bool assertIndex(unsigned int) const;

public:

	/* *********************************************************
	 *						 affichage						   *
	 ********************************************************* */


	friend std::ostream& operator<<(std::ostream&, const Signal&);
	virtual const std::string printOn(bool on = true)const = 0;

public:

	/* *********************************************************
	 *							Test						   *
	 ********************************************************* */


	friend void testSignal();

public:

	/* *********************************************************
	 *						 assesseurs						   *
	 ********************************************************* */


	virtual void SETnbech(unsigned int);
	virtual void SETthiscoef(unsigned int, double);
	virtual void SETdeltaT(double);
	virtual double GETthiscoef(unsigned int)const;
	virtual unsigned int GETnbech()const;
	virtual double GETdeltaT()const;
	//friend void loadFromFile(Signal& sig);

private:

	/* *********************************************************
	 *						Attributs						   *
	 ********************************************************* */


	unsigned int _nbech;
	double _deltaT;
	double* _tab;
};


class Echelon : public Signal{
public: // constructeurs et destructeur
	Echelon();
	Echelon(unsigned int, double deltaT, double amplitude);
	~Echelon();

public: // assesseurs
	virtual void SETamplitude(double);
	virtual double GETamplitude()const;

public: // affichage
	virtual const std::string printOn(bool on = true)const;

private:
	double _amplitude;
};

class Rampe : public Signal{
public: // constructeurs et destructeur
	Rampe();
	Rampe(unsigned int nbech, double deltaT, double slope);
	~Rampe();

public: // assesseurs
	virtual void SETslope(double);
	virtual double GETslope()const;

	double* calculAmplitude(unsigned int nbech, double deltaT, double slope);

public: // affichage
	virtual const std::string printOn(bool on = true)const;

private:
	double _slope;
};

class Sinus : public Signal{
public: // constructeurs et destructeur
	Sinus();
	Sinus(unsigned int nbech, double deltaT,double amplitude, double w, double dephasage);
	~Sinus();

	double* calculAmplitude(unsigned int nbech, double deltaT, double amplitude, double w, double dephasage);

public: // assesseurs
	void SETamplitude(double amplitude);
	void SETw(double w);
	void SETdephasage(double dephasage);
	double GETamplitude()const;
	double GETw()const;
	double GETdephasage()const;

public: // affichage
	virtual const std::string printOn(bool on = true)const;

private:
	double _amplitude;
	double _w;
	double _dephasage;
};

class randomSignal : public Signal{
public: // constructeurs et destructeur
	randomSignal();
	~randomSignal();

public: // affichage
	virtual const std::string printOn(bool on = true)const;
};


#endif