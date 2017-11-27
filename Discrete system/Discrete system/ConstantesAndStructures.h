#ifndef ConstantesAndStructures_H
#define ConstantesAndStructures_H

#include "LIB.h"

#include "FCTDiscret.h"
#include "SYSETATDiscret.h"


typedef struct screen screen;
struct screen {
	
};
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
	SYSETATDiscret sys;
};



typedef struct sysinfo sysinfo;
struct sysinfo {
	screen ecran;
	fichier file;
	var variable;
};


#endif