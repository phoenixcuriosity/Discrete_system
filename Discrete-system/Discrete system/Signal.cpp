/*
Discrete_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.29

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "Signal.h"

using namespace std;



Signal::Signal() : _tab(allocate(1)), _nbech(1), _deltaT(0)
{
}
Signal::Signal(unsigned int size, double deltaT) : _tab(allocate(size, 0)), _nbech(size), _deltaT(deltaT)
{
}
Signal::Signal(unsigned int size, double deltaT, double* tab) : _tab(tab), _nbech(size), _deltaT(deltaT)
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
void Signal::SETdeltaT(double deltaT){
	_deltaT = deltaT;
}
unsigned int Signal::GETnbech()const{
	return _nbech;
}
double Signal::GETthiscoef(unsigned int index)const{
	if (assertIndex(index))
		return _tab[index];
	return 0;
}
double Signal::GETdeltaT()const{
	return _deltaT;
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

	Echelon step(10, 0.1, 5);
	stream << endl << "Echelon de " << step.GETnbech() << " echantillons d'amplitude " << step.GETamplitude() << step << endl;

	Rampe ramp(10, 0.2 ,2);
	stream << "Rampe de " << ramp.GETnbech() << " echantillons de pente " << ramp.GETslope() << ramp << endl;

	randomSignal sig;
//	loadFromFile(sig);
	stream << "Signal de " << sig.GETnbech() << " echantillons de deltaT " << sig.GETdeltaT() << "s" << sig << endl;
	

	texte = stream.str();
	cout << texte;
}









Echelon::Echelon() : _amplitude(1)
{
}
Echelon::Echelon(unsigned int nbech, double deltaT,double amplitude) : Signal(nbech, deltaT), _amplitude(amplitude)
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

const std::string Echelon::printOn(bool on)const{
	ostringstream stream;
	string texte = "";
	for (unsigned int i = 0; i < this->GETnbech(); i++){
		stream << endl << i * this->GETdeltaT() << " , " << _amplitude;
	}
	texte = stream.str();
	if (on)
		cout << texte;
	return texte;
}







Rampe::Rampe() : Signal(), _slope(0)
{
}
Rampe::Rampe(unsigned int nbech, double deltaT, double slope): Signal(nbech, deltaT,calculAmplitude(nbech, deltaT,slope)), _slope(slope)
{
}
Rampe::~Rampe()
{
}


void Rampe::SETslope(double slope){
	_slope = slope;
	for (unsigned int i = 0; i < this->GETnbech(); i++)
		this->SETthiscoef(i, slope * this->GETdeltaT() * i);
}
double Rampe::GETslope()const{
	return _slope;
}

double* Rampe::calculAmplitude(unsigned int nbech, double deltaT,double slope){
	double somme = 0;
	double* buffer = new double[nbech];
	for (unsigned int i = 0; i < nbech; i++)
		buffer[i] = slope * deltaT * i;
	return buffer;
}

const std::string Rampe::printOn(bool on)const{
	ostringstream stream;
	string texte = "";
	for (unsigned int i = 0; i < this->GETnbech(); i++){
		stream << endl << i * this->GETdeltaT() << " , " << this->GETthiscoef(i);
	}
	texte = stream.str();
	if (on)
		cout << texte;
	return texte;
}










Sinus::Sinus() : Signal(), _amplitude(1), _w(1), _dephasage(0)
{
}
Sinus::Sinus(unsigned int nbech, double deltaT, double amplitude, double w, double dephasage) 
: Signal(nbech, deltaT, calculAmplitude(nbech, deltaT,amplitude, w, dephasage)), _amplitude(amplitude), _w(w), _dephasage(dephasage)
{
}
Sinus::~Sinus()
{
}

double* Sinus::calculAmplitude(unsigned int nbech, double deltaT, double amplitude, double w, double dephasage){
	double* buffer = new double[nbech];
	for (unsigned int i = 0; i < nbech; i++)
		buffer[i] = amplitude * sin(w * i * deltaT + dephasage);
	return buffer;
}


void Sinus::SETamplitude(double amplitude){
	_amplitude = amplitude;
	for (unsigned int i = 0; i < this->GETnbech(); i++)
		this->SETthiscoef(i, _amplitude * sin(_w * i * this->GETdeltaT() + _dephasage));
}
void Sinus::SETw(double w){
	_w = w;
	for (unsigned int i = 0; i < this->GETnbech(); i++)
		this->SETthiscoef(i, _amplitude * sin(_w * i * this->GETdeltaT() + _dephasage));
}
void Sinus::SETdephasage(double dephasage){
	_dephasage = dephasage;
	for (unsigned int i = 0; i < this->GETnbech(); i++)
		this->SETthiscoef(i, _amplitude * sin(_w * i * this->GETdeltaT() + _dephasage));
}
double Sinus::GETamplitude()const{
	return _amplitude;
}
double Sinus::GETw()const{
	return _w;
}
double Sinus::GETdephasage()const{
	return _dephasage;
}

const std::string Sinus::printOn(bool on)const{
	ostringstream stream;
	string texte = "";
	for (unsigned int i = 0; i < this->GETnbech(); i++){
		stream << endl << i * this->GETdeltaT() << " , " << this->GETthiscoef(i);
	}
	texte = stream.str();
	if (on)
		cout << texte;
	return texte;
}





randomSignal::randomSignal() : Signal()
{
}
randomSignal::~randomSignal()
{
}



const std::string randomSignal::printOn(bool on)const{
	ostringstream stream;
	string texte = "";
	for (unsigned int i = 0; i < this->GETnbech(); i++){
		stream << endl << i * this->GETdeltaT() << " , " << this->GETthiscoef(i);
	}
	texte = stream.str();
	if (on)
		cout << texte;
	return texte;
}


