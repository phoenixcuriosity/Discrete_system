#include "ConstantesAndStructures.h"

#include "mainLoop.h"

int initfile(fichier& file);

using namespace std;

int main(int argc, char *argv[]){
	sysinfo information;
	
	
	if (initfile(information.file))
		mainLoop(information);
	else
		return 0;

	return EXIT_SUCCESS;
}




int initfile(fichier& file){
	ofstream log(file.log);
	if (log){}
	else{
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.log;
		return 0;
	}
	ofstream reponseTemporelle(file.reponseTemporelle);
	if (reponseTemporelle){}
	else{
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.reponseTemporelle;
		return 0;
	}
	ofstream bode(file.bode);
	if (bode){}
	else{
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.bode;
		return 0;
	}
	ofstream load(file.load, ios::app);
	if (load){}
	else{
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.load;
		return 0;
	}

	return 1;
}

