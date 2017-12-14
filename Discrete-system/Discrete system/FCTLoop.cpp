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
			
			information.variable.fct.SETnumOrder(1);
			information.variable.fct.SETnumThisCoef(0, 3.2);
			information.variable.fct.SETnumThisCoef(1, -6.3);
			information.variable.fct.SETdenOrder(3);
			information.variable.fct.SETdenThisCoef(0, 3.2);
			information.variable.fct.SETdenThisCoef(1, -6.3);
			information.variable.fct.SETdenThisCoef(2, 3.2);
			information.variable.fct.SETdenThisCoef(3, 0.6);
			cout << endl << "fct = " << endl << information.variable.fct;

			information.variable.A.editsize(information.variable.fct.GETden().GETorder(),
				information.variable.fct.GETden().GETorder());
			for (unsigned int i = 0; i < information.variable.fct.GETden().GETorder(); i++) {
				information.variable.A.SETthiscoef(information.variable.fct.GETden().GETorder() - 1,
					i,
					-(information.variable.fct.GETden().GETcoefTab(i) / information.variable.fct.GETden().GETcoefTab(information.variable.fct.GETden().GETorder())));
			}
			for (unsigned int i = 0; i < information.variable.fct.GETden().GETorder(); i++) {
				for (unsigned int j = 1; j < information.variable.fct.GETden().GETorder(); j++) {
					information.variable.A.SETthiscoef(i, j, 1);
					i++;
				}
			}
			cout << endl << "Matrice A :" << information.variable.A;

			information.variable.B.editsize(information.variable.fct.GETden().GETorder(), 1);
			information.variable.B.SETthiscoef(information.variable.B.GETlength() - 1, 0, 1 / information.variable.fct.GETden().GETcoefTab(information.variable.fct.GETden().GETorder()));
			cout << endl << "Matrice B :" << information.variable.B;

			information.variable.C.editsize(1, information.variable.fct.GETden().GETorder());
			for (unsigned int i = 0; i <= information.variable.fct.GETnum().GETorder(); i++) {
				information.variable.C.SETthiscoef(0, i,
					information.variable.fct.GETden().GETcoefTab(i));
			}
			cout << endl << "Matrice C :" << information.variable.C;
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