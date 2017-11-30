#ifndef ConstantesAndStructures_H
#define ConstantesAndStructures_H

#include "LIB.h"

#include "FCTDiscret.h"
#include "SYSETATDiscret.h"


const unsigned int SCREEN_WIDTH = 720;
const unsigned int SCREEN_HEIGHT = 480;


enum { selectnothing, selectFCT, selectSYSETAT };




typedef struct texture texture;
struct texture {
	TTF_Font *font[80];
};




typedef struct screen screen;
struct screen {
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	texture allTextures;
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
	//FCTDiscret fct;
	//SYSETATDiscret sys;

	unsigned int userRequest = 0;
};



typedef struct sysinfo sysinfo;
struct sysinfo {
	screen ecran;
	fichier file;
	var variable;
};







#endif