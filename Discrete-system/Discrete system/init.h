/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.26

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/


#ifndef init_H
#define init_H

#include "IHM.h"

typedef struct fichier fichier;
struct fichier {
	const std::string log = "log.txt";
	const std::string reponseTemporelle = "ReponseTemporelle.txt";
	const std::string bode = "Bode.txt";
	const std::string load = "load.txt";
};

bool initfile(fichier& file);

#endif
