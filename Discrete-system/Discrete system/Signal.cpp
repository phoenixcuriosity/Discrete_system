/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.25

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

std::ostream& operator<<(std::ostream& os, const Signal& s){
	return os << s.printOn(false);
}

void Signal::SETnbech(unsigned int nbech){
	_nbech = nbech;
	double* buffer = new double[nbech];
	for (unsigned int i = 0; i < nbech; i++)
		buffer[i] = 0.0;

	delete _tab;
	_tab = buffer;
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

void testSignal(){
	ostringstream stream;
	string texte = "";

	stream << endl << endl << "___TEST Signal___" << endl << endl;

	Echelon step(10, 5);
	stream << endl << "Echelon de " << step.GETnbech() << " echantillons d'amplitude " << step.GETamplitude() << step << endl;

	Rampe ramp(10, 2);
	stream << "Rampe de " << ramp.GETnbech() << " echantillons de pente " << ramp.GETslope() << ramp << endl;


	texte = stream.str();
	cout << texte;
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
	for (unsigned int i = 0; i < this->GETnbech(); i++)
		this->SETthiscoef(i, amplitude);
}
double Echelon::GETamplitude()const{
	return _amplitude;
}

std::string Echelon::printOn(bool on)const{
	ostringstream stream;
	string texte = "";
	for (unsigned int i = 0; i < this->GETnbech(); i++){
		stream << endl << i << " , " << _amplitude;
	}
	texte = stream.str();
	if (on)
		cout << texte;
	return texte;
}







Rampe::Rampe() : Signal(), _slope(0)
{
}
Rampe::Rampe(unsigned int nbech, double slope): Signal(nbech, calculAmplitude(nbech, slope)), _slope(slope)
{
}
Rampe::~Rampe()
{
}


void Rampe::SETslope(double slope){
	_slope = slope;
	double somme = 0;
	for (unsigned int i = 0; i < this->GETnbech(); i++){
		this->SETthiscoef(i, somme);
		somme += slope;
	}	
}
double Rampe::GETslope()const{
	return _slope;
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

std::string Rampe::printOn(bool on)const{
	ostringstream stream;
	string texte = "";
	for (unsigned int i = 0; i < this->GETnbech(); i++){
		stream << endl << i << " , " << this->GETthiscoef(i);
	}
	texte = stream.str();
	if (on)
		cout << texte;
	return texte;
}
