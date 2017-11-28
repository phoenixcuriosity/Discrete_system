#ifndef TemplateDynamicArray_H
#define TemplateDynamicArray_H

#include "lib.h"

template<class T>
class TemplateDynamicArray
{
public:
	TemplateDynamicArray();
	TemplateDynamicArray(unsigned int);
	TemplateDynamicArray(const TemplateDynamicArray&);

	~TemplateDynamicArray();

	virtual int& operator [] (unsigned int); // redefinition de []
	virtual TemplateDynamicArray& operator = (const TemplateDynamicArray&); // methode de comparaison

	virtual std::ostream& printOn(std::ostream&) const; // affiche de manière textuelle le tabdyn

	virtual int *allocate(unsigned int) const; // alloue la mémoire pour un élément de taille int
	virtual int *allocate(const TemplateDynamicArray&) const; // alloue la mémoire pour une recopie d'un tableau existant
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


template <class T>
const unsigned int TemplateDynamicArray<T>::BLOCK_SIZE = 10 * T;

template <class T>
TemplateDynamicArray<T>::TemplateDynamicArray() :
	data(TemplateDynamicArray<T>::allocate(TemplateDynamicArray<T>::BLOCK_SIZE)), data_size(TemplateDynamicArray<T>::BLOCK_SIZE)
{
}
template <class T>
TemplateDynamicArray<T>::TemplateDynamicArray(size_a sz) :
	size(sz), TemplateDynamicArray(new T[sz])
{
}


DynamicArray::DynamicArray(unsigned int sz) :
	data(allocate(sz)), data_size(sz)
{
}

DynamicArray::DynamicArray(const DynamicArray & a) :
	data(allocate(a.data_size)), data_size(a.data_size)
{
}


#endif
