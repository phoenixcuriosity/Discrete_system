/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.21

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "Signal.h"

using namespace std;



Signal::Signal() : _tab(allocate(1)), _nbech(1)
{
}
Signal::Signal(unsigned int size) : _tab(allocate(size)), _nbech(size)
{
}
Signal::Signal(unsigned int size, double userValue) : _tab(allocate(size, userValue)), _nbech(size)
{
}
Signal::Signal(unsigned int size, double* tab) : _tab(tab), _nbech(size)
{
}
Signal::~Signal()
{
	if (_tab != nullptr) {
		delete   _tab;
		_tab = nullptr;
	}
}

void Signal::SETnbech(unsigned int nbech){
	_nbech = nbech;
}
void Signal::SETthiscoef(unsigned int index, double userValue){
	if (assertIndex(index))
		_tab[index] = userValue;
}
unsigned int Signal::GETnbech()const{
	return _nbech;
}
double Signal::GETthiscoef(unsigned int index)const{
	if (assertIndex(index))
		return _tab[index];
	return 0;
}

bool Signal::assertIndex(unsigned int index)const {
	if (index < _nbech)
		return true;
	else {
		cout << endl << "_______Signal : assertIndex false";
		return false;
	}
}

std::string Signal::printOn(bool on){
	string equation = "";
	ostringstream stream;

	if (on)
		cout << equation;
	return equation = stream.str();
}

double* Signal::allocate(unsigned int size) const {
	/*
	alloue un tableau de taille size de type double initialisé à 0
	*/
	double* buffer = new double[size];
	for (unsigned int i = 0; i < size; i++)
		buffer[i] = 0.0;
	return buffer;
}
double* Signal::allocate(unsigned int size, double userValue) const {
	/*
	alloue un tableau de taille size de type double initialisé à 0
	*/
	double* buffer = new double[size];
	for (unsigned int i = 0; i < size; i++)
		buffer[i] = userValue;
	return buffer;
}









Echelon::Echelon() : _amplitude(1)
{
}
Echelon::Echelon(unsigned int nbech, double amplitude) : Signal(nbech, amplitude), _amplitude(amplitude)
{
}
Echelon::~Echelon()
{
}


void Echelon::SETamplitude(double amplitude){
	_amplitude = amplitude;
}
double Echelon::GETamplitude()const{
	return _amplitude;
}







Rampe::Rampe()
{
}
Rampe::Rampe(unsigned int nbech, double slope):Signal(nbech, calculAmplitude(nbech, slope)), _slope(slope)
{
}
Rampe::~Rampe()
{
}

double* Rampe::calculAmplitude(unsigned int nbech, double slope){
	double somme = 0;
	double* buffer = new double[nbech];
	for (unsigned int i = 0; i < nbech; i++){
		buffer[i] = somme;
		somme += slope;
	}
	return buffer;
}
