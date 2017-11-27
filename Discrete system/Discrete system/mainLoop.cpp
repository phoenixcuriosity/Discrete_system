#include "mainLoop.h"

using namespace std;

void mainLoop(sysinfo& information){
	
	logfileconsole("_________Init Success_________");
	logfileconsole("type 1 (Fct Discret) or 2 SYSETATDiscret\n");
	cin >> information.variable.userRequest;
	switch (information.variable.userRequest){
	case selectnothing:
		logfileconsole("type 1 (Fct Discret) or 2 SYSETATDiscret\n");
		cin >> information.variable.userRequest;
		break;
	case selectFCT:
		logfileconsole("You have select Fct Discret");
		/*
		
		
		
		*/
		break;
	case selectSYSETAT:
		logfileconsole("You have select SYSETATDiscret");
		/*
		
		
		
		*/
		break;
	}
}

void logfileconsole(const std::string &msg){
	const std::string logtxt = "bin/log/log.txt";
	ofstream log(logtxt, ios::app);

	//std::time_t result = std::time(nullptr);
	//<< std::asctime(std::localtime(&result))

	if (log){
		cout << endl << msg;
		log << endl << msg;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}