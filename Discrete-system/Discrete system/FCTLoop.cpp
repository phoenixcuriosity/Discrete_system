#include "FCTLoop.h"

using namespace std;

#include "init.h"


void FCTLoop(sysinfo& information){
	unsigned int request = 0;
	double deltaT = 0;
	bool continuer = true;
	
	while (continuer){
		logfileconsole("You have selected Fct Discret");
		logfileconsole("type 1 to create the num and the den");
		logfileconsole("or type 2 to edit the FCT or type 3 to display the FCT");
		logfileconsole("or type 4 to return to previous menu : ");
		cin >> request;
		switch (request){
		case createNumDen:
			
			/*
			cout << "Init deltaT = " << information.variable.fct.GETdeltaT() << "s";
			logfileconsole("deltaT of FCT? : ");
			cin >> deltaT;
			information.variable.fct.SETdeltaT(deltaT);
			cout << "New deltaT = " << information.variable.fct.GETdeltaT() << "s";
			createNum(information);
			createDen(information);
			logfileconsole("You have created with SUCCESS the FCT, Yeah!!! You did it!!!");
			logfileconsole("Now try to diplay it");
			cout << endl << endl;
			*/
			break;
		case editFCT:
			break;
		case displayFCT:
			information.variable.fct.printOn();
			break;
		case previousMenuFCT:
			continuer = false;
			break;
		}
	}	
}

void createNum(sysinfo& information){
	unsigned int order = 0;
	double coef = 0;

	logfileconsole("You have selected to create Num");
	logfileconsole("order of FCT? : ");
	cin >> order;
	information.variable.fct.SETnum(order);
	for (unsigned int i = 0; i <= order; i++){
		logfileconsole("coef n:" + to_string(i) + " = ");
		cin >> coef;
		information.variable.fct.SETnumThisCoef(i, coef);
	}
	logfileconsole("You create the Num");
}
void createDen(sysinfo& information){
	unsigned int order = 0;
	double coef = 0;

	logfileconsole("You have selected to create Den");
	logfileconsole("order of FCT? : ");
	cin >> order;
	information.variable.fct.SETden(order);
	for (unsigned int i = 0; i <= order; i++){
		logfileconsole("coef n:" + to_string(i) + " = ");
		cin >> coef;
		information.variable.fct.SETdenThisCoef(i, coef);
	}
	logfileconsole("You create the Den");
}