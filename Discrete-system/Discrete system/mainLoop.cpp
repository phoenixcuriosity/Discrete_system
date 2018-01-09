/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.20

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/


#include "mainLoop.h"

#include "init.h"
#include "FCTLoop.h"
#include "representation.h"
#include "Signal.h"
#include "Complexe.h"
#include "IHM.h"

using namespace std;

void mainLoop(sysinfo& information){
	bool continuer = true;
	logfileconsole("_________Init Success_________");
	
	//testPolynome();
	//testFCTDiscret();
	//testMatrice();
	//testComplexe();
	//testSYSETATDiscret();
	testIHM();

	logfileconsole("_________START PROGRAM_________");
	logfileconsole("version: 21");
	logfileconsole("This is a free software, you can redistribute it and/or modify it\n");

	

	
	//representation(information);
	
	/*
	while (continuer){
		logfileconsole("type 1 (Fct Discret)\n or type 2 SYSETATDiscret\n or type 3 to exit the program\n");
		cin >> information.variable.userRequest;
		switch (information.variable.userRequest){
		case selectFCT:
			FCTLoop(information);
			break;
		case selectSYSETAT:
			logfileconsole("You have select SYSETATDiscret");
			break;
		case exitProgram :
			continuer = false;
			break;
		}
	}
	*/
}

