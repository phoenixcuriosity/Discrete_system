/*
Discret_system
author : SAUTER Robin
2017 - 2018
version:0.16

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/


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
	SYSETATDiscret sys;
	unsigned int userRequest = 0;
};



typedef struct sysinfo sysinfo;
struct sysinfo {
	fichier file;
	var variable;
};







#endif