#include "LIB.h"
#include "ConstantesAndStructures.h"

int initfile(sysinfo& information);

using namespace std;

int main(int argc, char *argv[]){
	sysinfo information;
	
	
	if (initfile(information)){
		
	}
	else
		return 0;

	return EXIT_SUCCESS;
}




int initfile(sysinfo& information){
	ofstream log(information.file.log);
	if (log){}
	else{
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << information.file.log;
		return 0;
	}
	ofstream save(information.file.save);
	if (save){}
	else{
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << information.file.save;
		return 0;
	}
	ofstream load(information.file.load, ios::app);
	if (load){}
	else{
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << information.file.load;
		return 0;
	}

	return 1;
}