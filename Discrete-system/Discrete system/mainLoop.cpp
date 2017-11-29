#include "mainLoop.h"

#include "init.h"
#include "FCTLoop.h"

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
		FCTLoop();
		
		
		
		
		break;
	case selectSYSETAT:
		logfileconsole("You have select SYSETATDiscret");
		
		
		
		
		
		break;
	}
}

