/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.25

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#ifndef Signal_H
#define Signal_H

#include "LIB.h"

class Signal{ // classe abstraite -> impossible d'instancier un d'objet Signal
public:
	Signal();
	Signal(unsigned int);
	Signal(unsigned int, double);
	Signal(unsigned int, double*);
	~Signal();

	friend std::ostream& operator<<(std::ostream&, const Signal&);

	virtual void SETnbech(unsigned int);
	virtual void SETthiscoef(unsigned int, double);
	virtual double GETthiscoef(unsigned int)const;
	virtual unsigned int GETnbech()const;

	virtual std::string printOn(bool on = true)const = 0;

	friend void testSignal();


protected:
	virtual double* allocate(unsigned int) const;
	virtual double* allocate(unsigned int, double) const;

	bool assertIndex(unsigned int) const;

private:
	unsigned int _nbech;
	double* _tab;
};


class Echelon : public Signal{
public:
	Echelon();
	Echelon(unsigned int, double);
	~Echelon();

	virtual void SETamplitude(double);
	virtual double GETamplitude()const;

	virtual std::string printOn(bool on = true)const;

private:
	double _amplitude;
};
class Rampe : public Signal{
public:
	Rampe();
	Rampe(unsigned int nbech, double slope);
	~Rampe();

	virtual void SETslope(double);
	virtual double GETslope()const;

	double* calculAmplitude(unsigned int nbech, double slope);

	virtual std::string printOn(bool on = true)const;

private:
	double _slope;
};
class Sinus : public Signal{
public:
	Sinus();
	~Sinus();

private:
	double _amplitude;
	double _w;
	double _dephasage;
};


#endif