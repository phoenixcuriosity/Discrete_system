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