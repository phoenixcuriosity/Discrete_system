#include "mainLoop.h"

#include "init.h"

using namespace std;

void mainLoop(sysinfo& information){
	
	unsigned int number = 0;
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
		testPolynome();
		
		
		
		
		break;
	case selectSYSETAT:
		logfileconsole("You have select SYSETATDiscret");
		
		
		
		
		
		break;
	}
}

