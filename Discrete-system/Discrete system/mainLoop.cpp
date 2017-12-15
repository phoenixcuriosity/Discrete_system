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

	information.variable.fct.SETnumOrder(1);
	information.variable.fct.SETnumThisCoef(0, 57);
	information.variable.fct.SETnumThisCoef(1, -4.2);
	information.variable.fct.SETdenOrder(3);
	information.variable.fct.SETdenThisCoef(0, 3.2);
	information.variable.fct.SETdenThisCoef(1, -6.3);
	information.variable.fct.SETdenThisCoef(2, 3.2);
	information.variable.fct.SETdenThisCoef(3, 0.6);
	//information.variable.fct.SETdenOrder(4);
	cout << endl << "fct = " << endl << information.variable.fct;

	information.variable.sys.calculABCD(information.variable.fct);
	cout << endl << information.variable.sys;
	tabJury(information.variable.fct);
	
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

