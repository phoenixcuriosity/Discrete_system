/*
Discrete_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.27

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "IHM.h"

using namespace std;

IHM::IHM() : _fct(0), _sys(0)
{
	_fct = new FCTDiscret;
	_sys = new SYSETATDiscret;
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


	//Echelon step;
	//loadFromFile(step);

	
	logfileconsole("_________START PROGRAM_________");
	logfileconsole("version: 27");
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
	system("cls");
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
	system("cls");
}
void modifFCT(IHM& ihm){
	unsigned int request = 0;
	double deltaT = 0;
	unsigned int order = 0;
	double coef = 0;
	bool continuer = true;

	while (continuer){
		system("cls");
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
	system("cls");
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
	system("cls");
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
	system("cls");
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
		logfileconsole("or type 2 to compute A, B, C, D \nor type 3 to display A,B,C,D \nor type 4 to simulate");
		logfileconsole("or type 5 to return to previous menu : ");
		cin >> request;
		switch (request){
		case editMatrice:
			editmatriceLoop(ihm);
			break;
		case calculMatriceABCD:
			if (assertFCT(*ihm.GETfct(),test)){
				ihm.GETsys()->calculABCD(*ihm.GETfct());
				cout << endl << *ihm.GETsys();
			}
			break;
		case displaySys:
			cout << *ihm.GETsys();
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
void editmatriceLoop(IHM& ihm){
	system("cls");
	bool continuer = true;
	unsigned int request = 0, length = 0, height = 0;
	logfileconsole("You have selected edit A, B, C, D");
	logfileconsole("On default matrix are filled with 0");

	cout << endl << "Default A :" << endl << ihm.GETsys()->GETA();
	cout << endl << "Default B :" << endl << ihm.GETsys()->GETB();
	cout << endl << "Default C :" << endl << ihm.GETsys()->GETC();
	cout << endl << "Default D :" << endl << ihm.GETsys()->GETD();

	
	logfileconsole("length of A : ");
	cin >> length;
	logfileconsole("height of A : ");
	cin >> height;
	
	ihm.GETsys()->SETeditSizeA(length, height);
	ihm.GETsys()->SETeditSizeB(length, 1);
	ihm.GETsys()->SETeditSizeC(1, height);
	ihm.GETsys()->SETeditSizeD(1, 1);

	cout << endl << "A :" << endl << ihm.GETsys()->GETA();
	cout << endl << "B :" << endl << ihm.GETsys()->GETB();
	cout << endl << "C :" << endl << ihm.GETsys()->GETC();
	cout << endl << "D :" << endl << ihm.GETsys()->GETD();

	logfileconsole("Matrix A : ");
	double coef = 0;

	for (unsigned int i = 0; i < length; i++){
		for (unsigned int j = 0; j < height; j++){
			logfileconsole("coef " + to_string(i) + "," + to_string(j) + " = ");
			cin >> coef;
			ihm.GETsys()->SETthisCoefA(i, j, coef);
		}
	}

	logfileconsole("Matrix B : ");
	for (unsigned int i = 0; i < length; i++){
		logfileconsole("coef " + to_string(i) + ",0 = ");
		cin >> coef;
		ihm.GETsys()->SETthisCoefB(i, 0, coef);
	}

	logfileconsole("Matrix C : ");
	for (unsigned int j = 0; j < height; j++){
		logfileconsole("coef 0," + to_string(j) + " = ");
		cin >> coef;
		ihm.GETsys()->SETthisCoefC(0, j, coef);
	}

	logfileconsole("Matrix D : ");
	logfileconsole("coef 0,0 = ");
	cin >> coef;
	ihm.GETsys()->SETthisCoefD(0, 0, coef);

	logfileconsole("You have successfully created A, B, C, D");
}

void simulationLoop(IHM& ihm){
	system("cls");
	Echelon step;
	Rampe ramp;
	Sinus sinus;
	randomSignal sig;
	unsigned int requestInput = 0, requestInitial = 0;;
	bool continuer = true;
	double deltaT = 0, amplitude = 0, slope = 0, w = 0, dephasage = 0;
	unsigned int nbech = 0;

	logfileconsole("You have selected simulation");

	logfileconsole("What type of Input ?");
	while (continuer){
		logfileconsole("type 1 for a step");
		logfileconsole("or type 2 for a ramp \nor type 3 for a sinus \nor type 4 to import from load.txt : ");
		cin >> requestInput;
		switch (requestInput){
		case stepInput:
			logfileconsole("number of samples : ");
			cin >> nbech;
			step.SETnbech(nbech);
			logfileconsole("deltaT : ");
			cin >> deltaT;
			step.SETdeltaT(deltaT);
			logfileconsole("Amplitude : ");
			cin >> amplitude;
			step.SETamplitude(amplitude);
			continuer = false;
			break;
		case rampInput:
			logfileconsole("number of samples : ");
			cin >> nbech;
			ramp.SETnbech(nbech);
			logfileconsole("deltaT : ");
			cin >> deltaT;
			ramp.SETdeltaT(deltaT);
			logfileconsole("Slope : ");
			cin >> slope;
			ramp.SETslope(slope);
			continuer = false;
			break;
		case sinusInput:
			logfileconsole("number of samples : ");
			cin >> nbech;
			sinus.SETnbech(nbech);
			logfileconsole("deltaT : ");
			cin >> deltaT;
			sinus.SETdeltaT(deltaT);
			logfileconsole("Amplitude : ");
			cin >> amplitude;
			sinus.SETamplitude(amplitude);
			logfileconsole("w : ");
			cin >> w;
			sinus.SETw(w);
			logfileconsole("dephasage : ");
			cin >> dephasage;
			sinus.SETdephasage(dephasage);
			break;
		case load:
			loadFromFile(sig);
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
		ihm.GETsys()->simulation("ReponseTemporelle.txt", step, x0);
	else if (requestInput == rampInput)
		ihm.GETsys()->simulation("ReponseTemporelle.txt", ramp, x0);
	else if (requestInput == sinusInput)
		ihm.GETsys()->simulation("ReponseTemporelle.txt", sinus, x0);
	else if (requestInput == load)
		ihm.GETsys()->simulation("ReponseTemporelle.txt", sig, x0);
	else
		logfileconsole("______No Input Signal");
}
void loadFromFile(Signal& sig){
	ifstream load("load.txt");
	double ech = 0;
	string destroy = "";
	bool continuer = true;


	while (continuer){
		if (load.eof())
			continuer = false;
		else{
			load >> ech;
			cout << endl << ech;
			load >> destroy;
			cout << endl << destroy;
			load >> ech;
			cout << endl << ech;
			cout << endl << destroy;
			load >> ech;
			cout << endl << ech;
		}
	}
	
}




void IHM::SETfct(FCTDiscret* fct){
	_fct = fct;
}
void IHM::SETsys(SYSETATDiscret* sys){
	_sys = sys;
}
FCTDiscret* IHM::GETfct()const{
	return _fct;
}
SYSETATDiscret* IHM::GETsys()const{
	return _sys;
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