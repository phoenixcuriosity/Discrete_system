#include "DynamicArray.h"

const unsigned int DynamicArray::BLOCK_SIZE = 10;

DynamicArray::DynamicArray() :
data(allocate(BLOCK_SIZE)), data_size(BLOCK_SIZE)
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

DynamicArray::~DynamicArray(){
	if (data != NULL) delete[] data;
}

unsigned int DynamicArray::size() const{
	return data_size;
}

unsigned int DynamicArray::blockSize() const{
	return BLOCK_SIZE;
}

void DynamicArray::assertIndex(unsigned int i) const{
	if (i > data_size) {
		std::ostringstream os;
		os << i;
		throw std::out_of_range(os.str());
	}
}

int DynamicArray::get(unsigned int i) const{
	assertIndex(i);
	return data[i];
}

void DynamicArray::set(unsigned int i, int value){
	assertIndex(i);
	data[i] = value;
}

int & DynamicArray::operator[](unsigned int i){
	//assertIndex(i);
	return data[i];
}

DynamicArray & DynamicArray::operator=(const DynamicArray & a){
	if (this != &a) // identifie l'objet
	{
		delete[] data;
		data_size = a.data_size;
		data = allocate(a);
	}
	return *this;
}

std::ostream & DynamicArray::printOn(std::ostream & os) const{
	os << '[';
	for (unsigned int i = 0; i < data_size; i++)
		os << data[i] << ' ';
	os << ']' << std::endl;
	return os;
}

int * DynamicArray::allocate(unsigned int sz) const{
	int * buffer = new int[sz];
	for (unsigned int i = 0; i < sz; i++) {
		buffer[i] = 0;
	}
	return buffer;
}

int * DynamicArray::allocate(const DynamicArray & a) const{
	int * buffer = new int[a.data_size];
	for (unsigned int i = 0; i < a.data_size; i++) {
		buffer[i] = a.data[i];
	}
	return buffer;
}

void DynamicArray::grow(){
	const unsigned int newSize = data_size + BLOCK_SIZE;
	int* newTab = allocate(newSize);

	for (unsigned int i = 0; i < data_size; i++) {
		newTab[i] = data[i];
	}

	delete[] data;

	data_size = newSize;
	data = newTab;
}