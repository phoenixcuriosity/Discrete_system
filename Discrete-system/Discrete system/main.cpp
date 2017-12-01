#include "ConstantesAndStructures.h"

#include "init.h"
#include "mainLoop.h"

using namespace std;

int main(int argc, char *argv[]){
	
	sysinfo information;
	
	if (initfile(information.file)) {
		mainLoop(information);
	}
	else
		return 0;

	return EXIT_SUCCESS;

	return 0;
}
