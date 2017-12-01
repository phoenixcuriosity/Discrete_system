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
	testVecteur();
	
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

