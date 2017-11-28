#ifndef DynamicArray_H
#define DynamicArray_H

#include "lib.h"

class DynamicArray
{
public:
	DynamicArray();
	DynamicArray(unsigned int);
	DynamicArray(const DynamicArray&);

	~DynamicArray();

	virtual int& operator [] (unsigned int); // redefinition de []
	virtual DynamicArray& operator = (const DynamicArray&); // methode de comparaison

	virtual std::ostream& printOn(std::ostream&) const; // affiche de manière textuelle le tabdyn

	virtual int *allocate(unsigned int) const; // alloue la mémoire pour un élément de taille int
	virtual int *allocate(const DynamicArray&) const; // alloue la mémoire pour une recopie d'un tableau existant
	virtual void assertIndex(unsigned int) const; // lance une erreure si l'index du tab est plus grand que le tab

	virtual void grow(); // créé 

	virtual unsigned int size() const;
	virtual unsigned int blockSize() const;

	virtual int get(unsigned int) const;
	virtual void set(unsigned int, int);

private:
	int* data;
	unsigned int data_size;
	const static unsigned int BLOCK_SIZE;
};



#endif