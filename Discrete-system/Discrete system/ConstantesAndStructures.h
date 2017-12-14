#ifndef ConstantesAndStructures_H
#define ConstantesAndStructures_H

#include "LIB.h"

#include "FCTDiscret.h"
#include "SYSETATDiscret.h"



enum { selectnothing, selectFCT, selectSYSETAT , exitProgram};
enum { nothing, createNumDen, editFCT, displayFCT, previousMenuFCT };


typedef struct fichier fichier;
struct fichier {
	const std::string log = "bin/log/log.txt";
	const std::string reponseTemporelle = "bin/SaveAndLoad/ReponseTemporelle.txt";
	const std::string bode = "bin/SaveAndLoad/Bode.txt";
	const std::string load = "bin/SaveAndLoad/load.txt";
};
typedef struct var var;
struct var {
	FCTDiscret fct;
	//SYSETATDiscret sys;
	Matrice A, B, C, D;
	unsigned int userRequest = 0;
};



typedef struct sysinfo sysinfo;
struct sysinfo {
	fichier file;
	var variable;
};







#endif