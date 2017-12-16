/*
Discret_system
author : SAUTER Robin
2017 - 2018
version:0.16-A

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#ifndef Signal_H
#define Signal_H

#include "LIB.h"

class Signal{
public:
	Signal();
	~Signal();

private:
	unsigned int _nbech;
	double* _tab;
};


class Impulsion : public Signal{
public:
	Impulsion();
	~Impulsion();

private:
	double _amplitude;
};
class Echelon : public Signal{
public:
	Echelon();
	~Echelon();

private:
	double _amplitude;
};
class Rampe : public Signal{
public:
	Rampe();
	~Rampe();

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