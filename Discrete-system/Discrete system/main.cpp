/*
	Discrete_system
	author : SAUTER Robin
	2017 - 2018
	last modification on this file on version:0.22
	
	This library is free software; you can redistribute it and/or modify it
	You can check for update on github.com -> https://github.com/phoenixcuriosity/Discrete_system

*/



#include "init.h"
#include "IHM.h"

using namespace std;

int main(int argc, char *argv[]){
	IHM ihm;
	fichier file;
	
	if (initfile(file)) {
		mainLoop(ihm);
	}
	else
		return 0;

	return EXIT_SUCCESS;
}
