/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.24

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "IHM.h"

using namespace std;

IHM::IHM() : _fct(0), _sys(0), _step(0)
{
	_fct = new FCTDiscret;
	_sys = new SYSETATDiscret;
	_step = new Echelon;
}
IHM::~IHM()
{
	delete _fct;
	delete _sys;
	delete _step;
}


void mainLoop(IHM& ihm){
	bool continuer = true;
	unsigned int request = 0;
	logfileconsole("_________Init Success_________");

	/*
		Test des différentes classes du projet

	*/
	
	//testPolynome();
	//testFCTDiscret();
	//testMatrice();
	//testComplexe();
	//testSYSETATDiscret();
	//testIHM();


	logfileconsole("_________START PROGRAM_________");
	logfileconsole("version: 24");
	logfileconsole("This is a free software, you can redistribute it and/or modify it\n");

	while (continuer){
		logfileconsole("type 1 Fct Discret\n or type 2 SYSETATDiscret\n or type 3 to exit the program\n");
		cin >> request;
		switch (request){
		case selectFCT:
			FCTLoop(ihm);
			break;
		case selectSYSETAT:
			SYSLoop(ihm);
			break;
		case exitProgram:
			continuer = false;
			break;
		}
	}
}
void FCTLoop(IHM& ihm){
	unsigned int request = 0;
	double deltaT = 0;
	bool continuer = true;
	FCTDiscret test;

	while (continuer){
		logfileconsole("You have selected Fct Discret");
		logfileconsole("type 1 to create the num and the den");
		logfileconsole("or type 2 to edit the FCT \nor type 3 to display the FCT");
		logfileconsole("or type 4 for Jury \nor type 5 for Bode");
		logfileconsole("or type 6 to return to previous menu : ");
		cin >> request;
		switch (request){
		case createNumDen:
			cout << "Init deltaT = " << ihm.GETfct()->GETdeltaT() << "s";
			logfileconsole("deltaT of FCT? : ");
			cin >> deltaT;
			ihm.GETfct()->SETdeltaT(deltaT);
			cout << "New deltaT = " << ihm.GETfct()->GETdeltaT() << "s";
			createNum(ihm);
			createDen(ihm);
			logfileconsole("You have created with SUCCESS the FCT, Yeah!!! You did it!!!");
			logfileconsole("Now try to diplay it");
			cout << endl << endl;
			break;
		case editFCT:
			modifFCT(ihm);
			break;
		case displayFCT:
			if (assertFCT(*ihm.GETfct(), test)){
				logfileconsole("FCT\n");
				cout << endl << *ihm.GETfct();
			}
			break;
		case jury:
			if (assertFCT(*ihm.GETfct(), test))
				ihm.GETfct()->tabJury();
			break;
		case bode:
			if (assertFCT(*ihm.GETfct(), test))
				diagBode(ihm);	
			break;
		case previousMenuFCT:
			continuer = false;
			break;
		}
	}
}
void modifFCT(IHM& ihm){
	unsigned int request = 0;
	double deltaT = 0;
	unsigned int order = 0;
	double coef = 0;
	bool continuer = true;

	while (continuer){
		logfileconsole("You have selected edit FCT");
		logfileconsole("type 1 to edit the num and the den");
		logfileconsole("or type 2 to edit the den \nor type 3 to edit deltaT");
		logfileconsole("or type 4 to return to previous menu : ");
		cin >> request;
		switch (request){
		case editnum:
			createNum(ihm);
			break;
		case editden:
			createDen(ihm);
			break;
		case editdeltaT:
			cout << "Init deltaT = " << ihm.GETfct()->GETdeltaT() << "s";
			logfileconsole("deltaT of FCT? : ");
			cin >> deltaT;
			ihm.GETfct()->SETdeltaT(deltaT);
			cout << "New deltaT = " << ihm.GETfct()->GETdeltaT() << "s";
			break;
		case previousMenuEditFCT:
			continuer = false;
			break;
		}
	}
}
void createNum(IHM& ihm){
	unsigned int order = 0;
	double coef = 0;

	logfileconsole("You have selected to create Num");
	logfileconsole("order of FCT? : ");
	cin >> order;
	ihm.GETfct()->SETnum(order);
	logfileconsole("new order = " + to_string(order));
	for (unsigned int i = 0; i <= order; i++){
		logfileconsole("coef n:" + to_string(i) + " = ");
		cin >> coef;
		logfileconsole("new coef n:" + to_string(i) + " = " + to_string(coef));
		ihm.GETfct()->SETnumThisCoef(i, coef);
	}
	logfileconsole("You create the Num");
}
void createDen(IHM& ihm){
	unsigned int order = 0;
	double coef = 0;

	logfileconsole("You have selected to create Den");
	logfileconsole("order of FCT? : ");
	cin >> order;
	ihm.GETfct()->SETden(order);
	logfileconsole("new order = " + to_string(order));
	for (unsigned int i = 0; i <= order; i++){
		logfileconsole("coef n:" + to_string(i) + " = ");
		cin >> coef;
		logfileconsole("new coef n:" + to_string(i) + " = " + to_string(coef));
		ihm.GETfct()->SETdenThisCoef(i, coef);
	}
	logfileconsole("You create the Den");
}
void diagBode(IHM& ihm){
	double wMin = 0, wMax = 0;
	unsigned int nbpoint = 0;
	logfileconsole("Bode");
	logfileconsole("wMin ? : ");
	cin >> wMin;
	logfileconsole("new wMin = " + to_string(wMin));
	logfileconsole("wMax ? : ");
	cin >> wMax;
	logfileconsole("new wMax = " + to_string(wMax));
	logfileconsole("nbpoint ? : ");
	cin >> nbpoint;
	logfileconsole("new nbpoint = " + to_string(nbpoint));

	ihm.GETfct()->Bode(wMin, wMax, nbpoint);
}


void SYSLoop(IHM& ihm){
	
	unsigned int request = 0;
	bool continuer = true;
	FCTDiscret test;
	SYSETATDiscret Test;

	while (continuer){
		logfileconsole("You have selected SYSETATDiscret");
		logfileconsole("type 1 to edit A, B, C, D");
		logfileconsole("or type 2 to compute A, B, C, D \nor type 3 to simulate");
		logfileconsole("or type 4 to return to previous menu : ");
		cin >> request;
		switch (request){
		case editMatrice:

			break;
		case calculMatriceABCD:
			if (assertFCT(*ihm.GETfct(),test)){
				ihm.GETsys()->calculABCD(*ihm.GETfct());
				cout << endl << *ihm.GETsys();
			}
			break;
		case simulationTemporelle:
			if (*ihm.GETsys() == Test)
				logfileconsole("A,B,C,D doesn't exist");
			else{
				simulationLoop(ihm);
			}
			break;
		case previousMenuSYS:
			continuer = false;
			break;
		}
	}
}
void simulationLoop(IHM& ihm){
	unsigned int request = 0;
	bool continuer = true;
	double amplitude = 0;
	unsigned int nbech = 0;

	logfileconsole("You have selected simulation");
	logfileconsole("What type of Input ?");
	while (continuer){
		logfileconsole("type 1 for a step");
		logfileconsole("or type 2 for a ramp \nor type 3 for a sinus : ");
		cin >> request;
		switch (request){
		case stepInput:
			logfileconsole("number of samples : ");
			cin >> nbech;
			ihm.GETstep()->SETnbech(nbech);
			cout << "new number of samples = " << ihm.GETstep()->GETnbech();
			logfileconsole("Amplitude : ");
			cin >> amplitude;
			ihm.GETstep()->SETamplitude(amplitude);
			cout << "new amplitude = " << ihm.GETstep()->GETamplitude();
			continuer = false;
			break;
		case rampInput:

			break;
		case sinusInput:
			
			break;
		}
	}
	request = 0;
	continuer = true;
	double coef = 0;
	Matrice x0(ihm.GETsys()->GETA().GETlength(), 1);
	cout << endl << "condition initial : x0 " << endl << x0;
	while (continuer){
		logfileconsole("type 1 for a default initial condition");
		logfileconsole("or type 2 to edit initial condition");
		cin >> request;
		switch (request){
		case 1:
			continuer = false;
			break;
		case 2:
			for (unsigned int i = 0; i < ihm.GETsys()->GETA().GETlength(); i++){
				cout << endl << "coef n: " << i << ",0 = ";
				cin >> coef;
				x0.SETthiscoef(i, 0, coef);
			}
			cout << endl << "new x0 :" << endl << x0;
			continuer = false;
			break;
		}
	}
	ihm.GETsys()->simulation("bin/SaveAndLoad/ReponseTemporelle.txt", *ihm.GETstep(), x0);
}




void IHM::SETfct(FCTDiscret* fct){
	_fct = fct;
}
void IHM::SETsys(SYSETATDiscret* sys){
	_sys = sys;
}
void IHM::SETstep(Echelon* step){
	_step = step;
}
FCTDiscret* IHM::GETfct()const{
	return _fct;
}
SYSETATDiscret* IHM::GETsys()const{
	return _sys;
}
Echelon* IHM::GETstep()const{
	return _step;
}


bool assertFCT(const FCTDiscret fct, const FCTDiscret test){
	if (fct == test){
		logfileconsole("_____FCT doesn't exist");
		return false;
	}
	return true;
}

void testIHM(){
	cout << endl << endl << "___TEST IHM___" << endl << endl;

	IHM ihm;
	ihm.GETfct()->SETnumOrder(1);
	ihm.GETfct()->SETnumThisCoef(0, 0);
	ihm.GETfct()->SETnumThisCoef(1, 1);
	ihm.GETfct()->SETdenOrder(2);
	ihm.GETfct()->SETdenThisCoef(0, 0);
	ihm.GETfct()->SETdenThisCoef(1, 0.1);
	ihm.GETfct()->SETdenThisCoef(2, 1.1);
	ihm.GETfct()->printOn();

	ihm.GETsys()->calculABCD(*ihm.GETfct());
	ihm.GETsys()->SETTe(100);
	ihm.GETsys()->printOn();
	ihm.GETfct()->tabJury();
	cout << endl << "BODE" << endl;
	ihm.GETfct()->Bode(0.1, 10, 100);

	Echelon E(50, 10.0);
	Matrice x0(ihm.GETsys()->GETA().GETlength(), 1);
	x0.SETthiscoef(0, 0, 0.1);

	cout << endl << endl << endl << "Reponse temporelle avec E = 10.0" << endl;
	ihm.GETsys()->simulation("bin/SaveAndLoad/ReponseTemporelle.txt", E, x0);

	cout << endl << endl;
}
void logfileconsole(const std::string &msg) {
	const string logtxt = "bin/log/log.txt";
	ofstream log(logtxt, ios::app);
	if (log) {
		cout << endl << msg;
		log << endl << msg;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}