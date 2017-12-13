#ifndef Signal_H
#define Signal_H

#include "LIB.h"

class Signal{
public:
	Signal();
	~Signal();

private:
	double _duree, _amplitude, _frequence;
	double* _tab;
};


class Impulsion : public Signal{
public:
	Impulsion();
	~Impulsion();
};
class Echelon : public Signal{
public:
	Echelon();
	~Echelon();
};
class Rampe : public Signal{
public:
	Rampe();
	~Rampe();
};
class Sinus : public Signal{
public:
	Sinus();
	~Sinus();
};


#endif