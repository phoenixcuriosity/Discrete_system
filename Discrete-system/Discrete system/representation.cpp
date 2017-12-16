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