/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.18-A

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "representation.h"

using namespace std;

void representation(sysinfo& information){
	string ligne;

	ifstream reponse(information.file.reponseTemporelle);
	if (reponse) {
		

		while (getline(reponse, ligne)){
			cout << ligne << endl;
		}
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << information.file.reponseTemporelle;


}