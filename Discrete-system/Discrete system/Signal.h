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



#endif