/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.18

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/


#include "mainLoop.h"

#include "init.h"
#include "FCTLoop.h"

using namespace std;

void mainLoop(sysinfo& information){
	bool continuer = true;
	logfileconsole("_________Init Success_________");
	
	testPolynome();
	testFCTDiscret();
	testMatrice();

	logfileconsole("_________START PROGRAM_________");
	logfileconsole("version: 18");
	logfileconsole("This is a free software, you can redistribute it and/or modify it");

	information.variable.fct.SETnumOrder(1);
	information.variable.fct.SETnumThisCoef(0, 1);
	information.variable.fct.SETnumThisCoef(1, -0.63);
	information.variable.fct.SETdenOrder(2);
	information.variable.fct.SETdenThisCoef(0, 0);
	information.variable.fct.SETdenThisCoef(1, -0.6);
	information.variable.fct.SETdenThisCoef(2, 1);
	//information.variable.fct.SETdenThisCoef(3, 1);
	//information.variable.fct.SETdenThisCoef(4, 0.01);
	//information.variable.fct.SETdenThisCoef(5, -0.359);
	//information.variable.fct.SETdenThisCoef(6, 5);

	
	
	cout << endl << endl << endl << "fct = " << endl << information.variable.fct;

	information.variable.sys.calculABCD(information.variable.fct);
	information.variable.sys.SETnbech(100);
	cout << endl << information.variable.sys;
	tabJury(information.variable.fct);

	information.variable.sys.simulation(information.file.reponseTemporelle);

	FCTDiscret interg;
	interg.SETnumOrder(0), interg.SETnumThisCoef(0, 1);
	interg.SETdenOrder(1), interg.SETdenThisCoef(1, 1);
	FCTDiscret openLoop = information.variable.fct * interg;
	FCTDiscret returnLoop = -1.0;

	closeLoop(openLoop, returnLoop);
	
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

