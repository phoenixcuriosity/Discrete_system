/*

	Discrete_system
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:2.9

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "IHM.h"

void mainLoop(IHM& ihm);

int main(int argc, char *argv[]){
	IHM ihm;
	fichier file;
	
	if (IHM::initfile(file)) {
		mainLoop(ihm);
	}
	else
		return 0;

	return 0;
}
void mainLoop(IHM& ihm) {
	/*
		Menu principal
	*/
	unsigned int request = 0;
	FCTDiscret testFCT;
	IHM::logfileconsole("_________Init Success_________");

	sysinfo information;
	IHM::initsdl(information);

	IHM::logfileconsole("_________START PROGRAM_________");
	IHM::logfileconsole("Dev version: 2.9");
	IHM::logfileconsole("This is a free software, you can redistribute it and/or modify it\n");

	loadAllTextures(information);
	information.variables.statescreen = STATEecrantitre;
	rendueEcran(information);

	SDL_Event event;
	int SDL_EnableUNICODE(1); // on azerty

	IHM::logfileconsole("_ Start mainLoop _");
	while (information.variables.continuer) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:	// permet de quitter
			information.variables.continuer = false;
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym) {
			case SDLK_F5:

				break;
			case SDLK_F6:

				break;
			case SDLK_ESCAPE:
				information.variables.continuer = false;
				break;
			case SDLK_SPACE:

				break;
			case SDLK_KP_1:
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
			mouse(ihm, information, event);
			break;
		case SDL_MOUSEWHEEL:
			break;
		}
	}
	IHM::deleteAll(information);
	IHM::logfileconsole("_ End mainLoop _");
}
