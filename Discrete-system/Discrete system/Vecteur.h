#ifndef Vecteur_H
#define Vecteur_H

#include "LIB.h"
#include "Polynome.h"

const bool VLigne = true;
const bool VColonne = false;

class Vecteur : public Polynome{
public:
	Vecteur();
	Vecteur(unsigned int size, bool ligne = true);
	Vecteur(unsigned int size, double tab[], bool ligne = true);
	Vecteur(const Vecteur&);
	~Vecteur();

	void printOn()const;

	friend void testVecteur();

private:
	bool _ligne;
};


#endif
