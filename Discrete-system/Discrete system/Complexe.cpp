/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.20

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "Complexe.h"

using namespace std;
const double Pi = 3.14159265358979323846;


Complexe::Complexe() : _Re(0), _Im(0)
{
}
Complexe::Complexe(double Re, double Im) : _Re(Re), _Im(Im)
{
}
Complexe::~Complexe()
{
}


Complexe& Complexe::operator = (const Complexe& a){
	if (this != &a){
		_Re = a.GETRe();
		_Im = a.GETIm();
	}
	return *this;
}
bool operator ==(const Complexe& a, const Complexe& b){
	if (a.GETRe() == b.GETRe() && a.GETIm() == b.GETIm())
		return true;
	else
		return false;
}
ostream& operator<<(std::ostream& os, const Complexe& c){
	return os << c.printOn(false);
}
Complexe operator+(const Complexe& a, const Complexe& b){
	Complexe resultat;
	resultat.SETRe(a.GETRe() + b.GETRe());
	resultat.SETIm(a.GETIm() + b.GETIm());
	return resultat;
}
Complexe operator-(const Complexe& a, const Complexe& b){
	Complexe resultat;
	resultat.SETRe(a.GETRe() - b.GETRe());
	resultat.SETIm(a.GETIm() - b.GETIm());
	return resultat;
}
Complexe operator*(const Complexe& a, const Complexe& b){
	Complexe resultat;
	resultat.SETRe(a.GETRe() * b.GETRe() - (a.GETIm() * b.GETIm()));
	resultat.SETIm(2 * a.GETRe() * b.GETIm());
	return resultat;
}
Complexe operator/(const Complexe& a, const Complexe& b) {
	Complexe resultat;
	resultat.SETRe((a.GETRe() * b.GETRe() + a.GETIm() * b.GETIm()) / (pow(b.GETRe(), 2) + pow(b.GETIm(), 2)));
	resultat.SETIm((a.GETIm() * b.GETRe() + a.GETRe() * b.GETIm()) / (pow(b.GETRe(), 2) + pow(b.GETIm(), 2)));
	return resultat;
}

double module(const Complexe& a){
	double module = sqrt(pow(a.GETRe(), 2) + pow(a.GETIm(), 2));
	return module;
}
double arg(const Complexe& a){
	double argument = 0;
	argument = atan(a.GETIm() / a.GETRe()) * (180 / Pi);
	if (a.GETRe() < 0)
		argument += Pi;
	return argument;
}




void Complexe::SETRe(double Re){
	_Re = Re;
}
void Complexe::SETIm(double Im){
	_Im = Im;
}
double Complexe::GETRe()const{
	return _Re;
}
double Complexe::GETIm()const{
	return _Im;
}



string Complexe::printOn(bool on)const{
	string texte;
	ostringstream stream;

	if (_Re != 0)
		stream << _Re;
	if (_Im != 0){
		if (_Im < 0)
			stream << " - " << abs(_Im) << "j";
		else
			stream << " + " << _Im << "j";
	}
	texte = stream.str();
	if (on)
		cout << texte;
	return texte;
}




void testComplexe(){
	string texte = "";
	ostringstream stream;

	stream << endl << "___TEST COMPLEXE___";

	Complexe a(3, 2);
	Complexe b(-0.3, 3);


	stream << endl << "Complexe a = " << a;
	stream << endl << "Complexe b = " << b;
	stream << endl << "Complexe a + b = " << a + b;
	stream << endl << "Complexe a - b = " << a - b;
	stream << endl << "Complexe a * b = " << a * b;
	stream << endl << "Complexe a / b = " << a / b;
	stream << endl << "Module de a = " << module(a);
	stream << endl << "arg de a = " << arg(a) << endl << endl;

	texte = stream.str();
	cout << texte;
}