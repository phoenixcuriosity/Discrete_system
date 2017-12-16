/*
	Discret_system
	author : SAUTER Robin
	2017 - 2018
	version:0.17
	
	This library is free software; you can redistribute it and/or modify it
	You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "ConstantesAndStructures.h"

#include "init.h"
#include "mainLoop.h"

using namespace std;

int main(int argc, char *argv[]){
	
	sysinfo information;
	
	if (initfile(information.file)) {
		mainLoop(information);
	}
	else
		return 0;

	return EXIT_SUCCESS;
}
