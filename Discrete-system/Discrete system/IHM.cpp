/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.26

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "IHM.h"

using namespace std;

IHM::IHM() : _fct(0), _sys(0), _step(0), _ramp(0)
{
	_fct = new FCTDiscret;
	_sys = new SYSETATDiscret;
	_step = new Echelon;
	_ramp = new Rampe;
}
IHM::~IHM()
{	
	if (_fct != nullptr){
		delete _fct;
		_fct = nullptr;
	}
	if (_sys != nullptr){
		delete _sys;
		_sys = nullptr;
	}
	if (_step != nullptr){
		delete _step;
		_step = nullptr;
	}
	if (_ramp != nullptr){
		delete _ramp;
		_ramp = nullptr;
	}
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
	//testSignal();
	//testIHM();

	logfileconsole("_________START PROGRAM_________");
	logfileconsole("version: 26");
	logfileconsole("This is a free software, you can redistribute it and/or modify it\n");

	while (continuer){
		logfileconsole("Main menu");
		logfileconsole("type 1 menu Fct Discret\n or type 2 menu Discrete System\n or type 3 to exit the program\n");
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
		logfileconsole("Menu Fct Discret");
		logfileconsole("type 1 to create the numerator and the denominator");
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
			if (assertFCT(*ihm.GETfct(), test)){
				if (ihm.GETfct()->tabJury())
					logfileconsole("the system is stable\n");
				else
					logfileconsole("the system is unstable\n");
			}	
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
		logfileconsole("Menu edit FCT");
		logfileconsole("type 1 to edit the numerator");
		logfileconsole("or type 2 to edit the denominator \nor type 3 to edit deltaT");
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
	/*
		Création du numérateur avec un test pour vérifier l'ordre à la fin
	*/
	unsigned int order = 0, realOrderNum = 0;
	double coef = 0;

	logfileconsole("You have selected to create Numerator");
	logfileconsole("order of numerator? : ");
	cin >> order;
	ihm.GETfct()->SETnum(order);
	logfileconsole("new order = " + to_string(order));
	for (unsigned int i = 0; i <= order; i++){
		logfileconsole("coef n:" + to_string(i) + " = ");
		cin >> coef;
		logfileconsole("new coef n:" + to_string(i) + " = " + to_string(coef));
		ihm.GETfct()->SETnumThisCoef(i, coef);
	}
	for (int i = order; i >= 0; i--){
		if (ihm.GETfct()->GETnum().GETcoefTab(i) != 0){
			realOrderNum = i;
			break;
		}
	}
	ihm.GETfct()->SETnumOrder(realOrderNum);
	logfileconsole("You have created the numerator, order : " + to_string(realOrderNum));
}
void createDen(IHM& ihm){
	/*
		Création du dénominateur avec un test pour vérifier l'ordre à la fin
	*/
	unsigned int order = 0, realOrderDen = 0;
	double coef = 0;

	logfileconsole("You have selected to create Denominator");
	logfileconsole("order of denominator? : ");
	cin >> order;
	ihm.GETfct()->SETden(order);
	logfileconsole("new order = " + to_string(order));
	for (unsigned int i = 0; i <= order; i++){
		logfileconsole("coef n:" + to_string(i) + " = ");
		cin >> coef;
		logfileconsole("new coef n:" + to_string(i) + " = " + to_string(coef));
		ihm.GETfct()->SETdenThisCoef(i, coef);
	}
	for (int i = order; i >= 0; i--){
		if (ihm.GETfct()->GETden().GETcoefTab(i) != 0){
			realOrderDen = i;
			break;
		}
	}
	ihm.GETfct()->SETdenOrder(realOrderDen);
	logfileconsole("You have created the denominator, order : " + to_string(realOrderDen));
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
		logfileconsole("Menu Discrete System");
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
	unsigned int requestInput = 0, requestInitial = 0;;
	bool continuer = true;
	double amplitude = 0, slope = 0;
	unsigned int nbech = 0;

	logfileconsole("You have selected simulation");

	

	logfileconsole("What type of Input ?");
	while (continuer){
		logfileconsole("type 1 for a step");
		logfileconsole("or type 2 for a ramp \nor type 3 for a sinus : ");
		cin >> requestInput;
		switch (requestInput){
		case stepInput:
			logfileconsole("number of samples : ");
			cin >> nbech;
			ihm.GETstep()->SETnbech(nbech);
			logfileconsole("Amplitude : ");
			cin >> amplitude;
			ihm.GETstep()->SETamplitude(amplitude);
			continuer = false;
			break;
		case rampInput:
			logfileconsole("number of samples : ");
			cin >> nbech;
			ihm.GETramp()->SETnbech(nbech);
			logfileconsole("Slope : ");
			cin >> slope;
			ihm.GETramp()->SETslope(slope);
			continuer = false;
			break;
		case sinusInput:
			
			break;
		}
	}
	continuer = true;
	double coef = 0;
	Matrice x0(ihm.GETsys()->GETA().GETlength(), 1);
	logfileconsole("\ncondition initial : x0\n");
	cout << x0 << endl;
	while (continuer){
		logfileconsole("\ntype 1 for a default initial condition");
		logfileconsole("or type 2 to edit initial condition : ");
		cin >> requestInitial;
		switch (requestInitial){
		case 1:
			continuer = false;
			break;
		case 2:
			for (unsigned int i = 0; i < ihm.GETsys()->GETA().GETlength(); i++){
				logfileconsole("\ncoef n: " + to_string(i) + ",0 = ");
				cin >> coef;
				x0.SETthiscoef(i, 0, coef);
			}
			cout << endl << "new x0 :" << endl << x0;
			continuer = false;
			break;
		}
	}
	if (requestInput == stepInput)
		ihm.GETsys()->simulation("ReponseTemporelle.txt", *ihm.GETstep(), x0);
	else if (requestInput == rampInput)
		ihm.GETsys()->simulation("ReponseTemporelle.txt", *ihm.GETramp(), x0);
	else if (requestInput == sinusInput)
		ihm.GETsys()->simulation("ReponseTemporelle.txt", *ihm.GETramp(), x0);
	else
		logfileconsole("______No Input Signal");
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
void IHM::SETramp(Rampe* ramp){
	_ramp = ramp;
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
Rampe* IHM::GETramp()const{
	return _ramp;
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
	cout << endl << *ihm.GETsys();
	if (ihm.GETfct()->tabJury())
		cout << endl << "the system is stable";
	else
		cout << endl << "the system is unstable";
	cout << endl << "BODE" << endl;
	ihm.GETfct()->Bode(0.1, 10, 100);

	Echelon E(50, 10.0);
	Matrice x0(ihm.GETsys()->GETA().GETlength(), 1);
	x0.SETthiscoef(0, 0, 0.1);

	cout << endl << endl << endl << "Reponse temporelle avec E = 10.0" << endl;
	ihm.GETsys()->simulation("ReponseTemporelle.txt", E, x0);

	cout << endl << endl;
}
void logfileconsole(const std::string &msg) {
	const string logtxt = "log.txt";
	ofstream log(logtxt, ios::app);
	if (log) {
		cout << endl << msg;
		log << endl << msg;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}