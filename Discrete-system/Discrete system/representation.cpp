/*
Discret_system
author : SAUTER Robin
2017 - 2018
version:0.17

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "representation.h"

using namespace std;

void representation(sysinfo& information){
	unsigned int nbech = 0;
	string destroy = "";

	ifstream reponse(information.file.reponseTemporelle);
	if (reponse) {
		reponse >> destroy;
		if (destroy.compare("nbech:") == 0){
			reponse >> nbech;
		}
		else
			cout << endl << "ERREUR: Impossible d'utiliser le fichier : " << information.file.reponseTemporelle << ", le premier mot n'ai pas 'nbech:'";
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << information.file.reponseTemporelle;


}