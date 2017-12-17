/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.18

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "init.h"



using namespace std;

bool initfile(fichier& file) {
	/*
	initialisation des fichiers
	tests d'ouverture
	*/
	ofstream log(file.log);
	if (log) {}
	else {
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.log;
		return false;
	}
	ofstream reponseTemporelle(file.reponseTemporelle);
	if (reponseTemporelle) {}
	else {
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.reponseTemporelle;
		return false;
	}
	ofstream bode(file.bode);
	if (bode) {}
	else {
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.bode;
		return false;
	}
	ofstream load(file.load, ios::app);
	if (load) {}
	else {
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.load;
		return false;
	}
	logfileconsole("Created by SAUTER Robin");

	return true;
}

void logfileconsole(const std::string &msg) {
	const string logtxt = "bin/log/log.txt";
	ofstream log(logtxt, ios::app);
	if (log) {
		cout << endl << msg;
		log << endl << msg;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}