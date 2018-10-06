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
#include "discrete_system_LIB.h"
#include "LIB.h"

///////////////////////////// IHM //////////////////////////////
/* IHM :: STATIC */
bool IHM::initfile(fichier& file) {
	/*
	initialisation des fichiers
	tests d'ouverture
	*/
	std::ofstream log(file.log);
	if (log) {}
	else {
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.log;
		return false;
	}
	std::ofstream reponseTemporelle(file.reponseTemporelle);
	if (reponseTemporelle) {}
	else {
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.reponseTemporelle;
		return false;
	}
	std::ofstream bode(file.bode);
	if (bode) {}
	else {
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.bode;
		return false;
	}
	std::ofstream load(file.load, std::ios::app);
	if (load) {}
	else {
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.load;
		return false;
	}
	logfileconsole("Created by SAUTER Robin");

	return true;
}
void IHM::logfileconsole(const std::string &msg) {
	const std::string logtxt = "bin/files/log.txt";
	std::ofstream log(logtxt, std::ios::app);
	if (log) {
		std::cout << std::endl << msg;
		log << std::endl << msg;
	}
	else
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}
void IHM::logSDLError(std::ostream &os, const std::string &msg) {
	const std::string logtxt = "bin/log/log.txt";
	std::ofstream log(logtxt, std::ios::app);
	if (log) {
		os << msg << " error: " << SDL_GetError() << std::endl;
		log << msg << " error: " << SDL_GetError() << std::endl;
	}
	else
		std::cout << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt << std::endl;
}
void IHM::initsdl(sysinfo& information) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << std::endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
	else {
		information.ecran.window = SDL_CreateWindow("Discret System", 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (information.ecran.window == nullptr)
			SDL_Quit();
		else
			logfileconsole("CreateWindow Success");
		information.ecran.renderer = SDL_CreateRenderer(information.ecran.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (information.ecran.renderer == nullptr) {
			SDL_DestroyWindow(information.ecran.window);
			SDL_Quit();
		}
		else
			logfileconsole("CreateRenderer Success");

		if (TTF_Init() != 0) {
			SDL_DestroyRenderer(information.ecran.renderer);
			SDL_DestroyWindow(information.ecran.window);
			SDL_Quit();
		}
		else
			logfileconsole("TTF_Init Success");


		const std::string fontFile = "arial.ttf";

		for (unsigned int i = 1; i < 80; i++)
			information.allTextures.font[i] = TTF_OpenFont(fontFile.c_str(), i);

		logfileconsole("SDL_Init Success");
	}
}



/* IHM :: METHODES */
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
void IHM::SETfct(FCTDiscret* fct){
	if (_fct != nullptr)
		delete _fct;
	_fct = fct;
}
void IHM::SETsys(SYSETATDiscret* sys){
	if (_sys != nullptr)
		delete _sys;
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
		IHM::logfileconsole("_____FCT doesn't exist");
		return false;
	}
	return true;
}
void loadAllTextures(sysinfo& information){

	// ______Writetxt_____ 
	information.variables.statescreen = STATEecrantitre;
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre,
		blended, "Dev version: 2.8", White, NoColor, 16, 0, 0);
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre,
		blended, "Developed by SAUTER Robin", White, NoColor, 16, 0, 16);
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre,
		blended, "Discret System", { 0, 255, 255, 255 }, NoColor, 28, SCREEN_WIDTH / 2, 25, center_x);

	
	information.variables.statescreen = STATEfunctionTransfer;
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre,
		blended, "Transfert Function", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, center_x);

	information.variables.statescreen = STATETFcreateNumDen;
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre,
		blended, "Create the Transfer Function", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, center_x);
	
	information.variables.statescreen = STATETFcreateBode;
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre,
		blended, "Create Bode", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, center_x);

	information.variables.statescreen = STATETFdisplayBode;
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre,
		blended, "Display Bode", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, center_x);
	
	information.variables.statescreen = STATEstateSystem;
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre,
		blended, "State System", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, center_x);

	information.variables.statescreen = STATESScreateMatrice;
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre,
		blended, "Create Matrix A, B, C and D", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, center_x);

	information.variables.statescreen = STATESSsimulate;
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre,
		blended, "Simulate", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, center_x);

	information.variables.statescreen = STATEreponseTemporelle;
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre,
		blended, "Simulation", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, center_x);

	// ______Buttons_____
	information.variables.statescreen = STATEecrantitre;
	int spacemenu = 64, initspacemenu = 200;

	Buttons::createbutton(information, information.allButtons.ecranTitre,
		shaded, "Transfer Function", WriteColorButton, BackColorButton, 26, SCREEN_WIDTH / 2, initspacemenu, center);
	Buttons::createbutton(information, information.allButtons.ecranTitre,
		shaded, "State System", WriteColorButton, BackColorButton, 26, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	Buttons::createbutton(information, information.allButtons.ecranTitre,
		shaded, "Closed Loop", WriteColorButton, BackColorButton, 26, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	Buttons::createbutton(information, information.allButtons.ecranTitre,
		shaded, "Quit", WriteColorButton, BackColorButton, 26, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);

	information.variables.statescreen = STATEfunctionTransfer;
	spacemenu = 48, initspacemenu = 100;
	Buttons::createbutton(information, information.allButtons.ecranFCT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0);
	Buttons::createbutton(information, information.allButtons.ecranFCT,
		shaded, "Create the Transfer Function", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu, center);
	Buttons::createbutton(information, information.allButtons.ecranFCT,
		shaded, "Display the Transfer Function", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	Buttons::createbutton(information, information.allButtons.ecranFCT,
		shaded, "Jury", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	Buttons::createbutton(information, information.allButtons.ecranFCT,
		shaded, "Bode", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);

	information.variables.statescreen = STATETFcreateBode;
	Buttons::createbutton(information, information.allButtons.ecranFCT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0);

	information.variables.statescreen = STATETFdisplayBode;
	Buttons::createbutton(information, information.allButtons.ecranFCT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0);



	information.variables.statescreen = STATEstateSystem;
	spacemenu = 48, initspacemenu = 100;
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0);
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Edit Matrix A, B, C and D", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu, center);
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Compute A, B, C and D", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Display the State System", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Simulate", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);

	information.variables.statescreen = STATESScreateMatrice;
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0);

	information.variables.statescreen = STATESSsimulate;
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0);
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Step", WriteColorButton, BackColorButton, 24, 100, 100);
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Ramp", WriteColorButton, BackColorButton, 24, 200, 100);
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Sinus", WriteColorButton, BackColorButton, 24, 300, 100);
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Import Signal", WriteColorButton, BackColorButton, 24, 400, 100);

	information.variables.statescreen = STATEreponseTemporelle;
	Buttons::createbutton(information, information.allButtons.ecranSYSETAT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0);

}
void rendueEcran(sysinfo& information){
	SDL_RenderClear(information.ecran.renderer);
	

	for (unsigned int i = 0; i < information.allTextures.txtEcranTitre.size(); i++)
		information.allTextures.txtEcranTitre[i]->renderTextureTestStates(information.ecran.renderer, information.variables.statescreen, information.variables.select);

	if (information.variables.statescreen == STATEecrantitre) {
		for (unsigned int i = 0; i < information.allButtons.ecranTitre.size(); i++)
			information.allButtons.ecranTitre[i]->renderButton(information.ecran.renderer, information.variables.statescreen);
	}
	else if (information.variables.statescreen == STATEfunctionTransfer || information.variables.statescreen == STATETFcreateNumDen
		|| information.variables.statescreen == STATETFcreateBode || information.variables.statescreen == STATETFdisplayBode) {
		for (unsigned int i = 0; i < information.allButtons.ecranFCT.size(); i++)
			information.allButtons.ecranFCT[i]->renderButton(information.ecran.renderer, information.variables.statescreen);
	}
	else if (information.variables.statescreen == STATEstateSystem || information.variables.statescreen == STATESScreateMatrice
		|| information.variables.statescreen == STATESSsimulate || information.variables.statescreen == STATEreponseTemporelle) {
		for (unsigned int i = 0; i < information.allButtons.ecranSYSETAT.size(); i++)
			information.allButtons.ecranSYSETAT[i]->renderButton(information.ecran.renderer, information.variables.statescreen);
	}
	SDL_RenderPresent(information.ecran.renderer);
}

void mouse(IHM& ihm, sysinfo& information, SDL_Event event){
	/*
	Handle Mouse Event
	BUTTON_LEFT
	BUTTON_RIGHT

	*/
	std::string test, fct;

	if (event.button.button == SDL_BUTTON_LEFT){

		if (information.variables.statescreen == STATEecrantitre) {
			for (unsigned int i = 0; i < information.allButtons.ecranTitre.size(); i++) { // recherche si une bouton est dans ces coordonnées

			// boutons du main menu

				if (information.allButtons.ecranTitre[i]->searchButton(fct = "Transfer Function", information.variables.statescreen, event.button.x, event.button.y)) {
					information.variables.statescreen = STATEfunctionTransfer;
					rendueEcran(information);
					break;
				}
				else if (information.allButtons.ecranTitre[i]->searchButton(fct = "State System", information.variables.statescreen, event.button.x, event.button.y)) {
					information.variables.statescreen = STATEstateSystem;
					rendueEcran(information);
					break;
				}
				else if (information.allButtons.ecranTitre[i]->searchButton(fct = "Closed Loop", information.variables.statescreen, event.button.x, event.button.y)) {

					break;
				}
				else if (information.allButtons.ecranTitre[i]->searchButton(fct = "Quit", information.variables.statescreen, event.button.x, event.button.y)) {
					information.variables.continuer = false;
					break;
				}
			}
		}
		else if (information.variables.statescreen == STATEfunctionTransfer || information.variables.statescreen == STATETFcreateNumDen
			|| information.variables.statescreen == STATETFcreateBode || information.variables.statescreen == STATETFdisplayBode) {
			for (unsigned int i = 0; i < information.allButtons.ecranFCT.size(); i++) {
				if (information.allButtons.ecranFCT[i]->searchButton(fct = "Main menu", information.variables.statescreen, event.button.x, event.button.y)) {
					information.variables.statescreen = STATEecrantitre;
					rendueEcran(information);
					break;
				}
				else if (information.allButtons.ecranFCT[i]->searchButton(fct = "Create the Transfer Function", information.variables.statescreen, event.button.x, event.button.y)) {
					CreateNumDen(ihm, information);
					break;
				}
				else if (information.allButtons.ecranFCT[i]->searchButton(fct = "Display the Transfer Function", information.variables.statescreen, event.button.x, event.button.y)) {
					displayTF(ihm, information);
					break;
				}
				else if (information.allButtons.ecranFCT[i]->searchButton(fct = "Jury", information.variables.statescreen, event.button.x, event.button.y)) {
					displayJury(ihm, information);
					break;
				}
				else if (information.allButtons.ecranFCT[i]->searchButton(fct = "Bode", information.variables.statescreen, event.button.x, event.button.y)) {
					displayBode(ihm, information);
					break;
				}
			}
		}
		else if (information.variables.statescreen == STATEstateSystem || information.variables.statescreen == STATESScreateMatrice
			|| information.variables.statescreen == STATESSsimulate || information.variables.statescreen == STATEreponseTemporelle) {
			for (unsigned int i = 0; i < information.allButtons.ecranSYSETAT.size(); i++) {
				if (information.allButtons.ecranSYSETAT[i]->searchButton(fct = "Main menu", information.variables.statescreen, event.button.x, event.button.y)) {
					information.variables.statescreen = STATEecrantitre;
					rendueEcran(information);
					break;
				}
				else if (information.allButtons.ecranSYSETAT[i]->searchButton(fct = "Edit Matrix A, B, C and D", information.variables.statescreen, event.button.x, event.button.y)) {
					createMatrice(ihm, information);
					break;
				}
				else if (information.allButtons.ecranSYSETAT[i]->searchButton(fct = "Compute A, B, C and D", information.variables.statescreen, event.button.x, event.button.y)) {
					if (ihm.GETfct()->GETden().GETorder() > 0)
						computeABCD(ihm, information);
					else
						Texture::writetxt(information, blended,
							"Order of Denominator is 0", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 130, 148, center_y);
					SDL_RenderPresent(information.ecran.renderer);
					break;
				}
				else if (information.allButtons.ecranSYSETAT[i]->searchButton(fct = "Display the State System", information.variables.statescreen, event.button.x, event.button.y)) {
					SYSETATDiscret SYS;
					if (SYS == *ihm.GETsys())
						Texture::writetxt(information, blended, 
							"SS doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 196, center_y);
					else {
						displayStateSystem(ihm, information);
						Texture::writetxt(information, blended,
							"OK", { 0, 255, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 196, center_y);
					}
					SDL_RenderPresent(information.ecran.renderer);

					break;
				}
				else if (information.allButtons.ecranSYSETAT[i]->searchButton(fct = "Simulate", information.variables.statescreen, event.button.x, event.button.y)) {
					SYSETATDiscret SYS;
					if (SYS == *ihm.GETsys())
						Texture::writetxt(information, blended,
							"SS doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 244, center_y);
					else {
						information.variables.statescreen = STATESSsimulate;
						rendueEcran(information);

					}
					break;
				}
				else if (information.allButtons.ecranSYSETAT[i]->searchButton(fct = "Step", information.variables.statescreen, event.button.x, event.button.y)) {
					information.allButtons.ecranSYSETAT[i]->changeOn();
					rendueEcran(information);
					Echelon step;
					createSignal(ihm, information, step);
					createStep(ihm, information, step);
					information.variables.statescreen = STATEreponseTemporelle;
					rendueEcran(information);
					displayReponseTemp(ihm, information, step);
					break;
				}
				else if (information.allButtons.ecranSYSETAT[i]->searchButton(fct = "Ramp", information.variables.statescreen, event.button.x, event.button.y)) {
					information.allButtons.ecranSYSETAT[i]->changeOn();
					rendueEcran(information);
					Rampe ramp;
					createSignal(ihm, information, ramp);
					createRamp(ihm, information, ramp);
					information.variables.statescreen = STATEreponseTemporelle;
					rendueEcran(information);
					displayReponseTemp(ihm, information, ramp);
					break;
				}
				else if (information.allButtons.ecranSYSETAT[i]->searchButton(fct = "Sinus", information.variables.statescreen, event.button.x, event.button.y)) {
					//Sinus sinus(500, 0.1, 1, 1, 0);
					information.allButtons.ecranSYSETAT[i]->changeOn();
					rendueEcran(information);
					Sinus sinus;
					createSignal(ihm, information, sinus);
					createSinus(ihm, information, sinus);
					information.variables.statescreen = STATEreponseTemporelle;
					rendueEcran(information);
					displayReponseTemp(ihm, information, sinus);
					break;
				}
				else if (information.allButtons.ecranSYSETAT[i]->searchButton(fct = "Import Signal", information.variables.statescreen, event.button.x, event.button.y)) {
					information.allButtons.ecranSYSETAT[i]->changeOn();
					rendueEcran(information);
					break;
				}
			}
		}
	}
}
unsigned int CinNumberUnsignedInt(sysinfo& information, const std::string& msg, unsigned int x, unsigned int y){
	bool continuer = true;
	unsigned int number = 0, digit = 0;
	SDL_Event event;
	int SDL_EnableUNICODE(1); // on azerty
	
	while (continuer){
		SDL_WaitEvent(&event);
		switch (event.type){
		case SDL_QUIT:	// permet de quitter
			information.variables.continuer = false;
			continuer = false;
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				information.variables.continuer = false;
				continuer = false;
				break;
			case SDLK_BACKSPACE:
				number = 0;
				digit = 0;
				break;
			case SDLK_RETURN:
				continuer = false;
				break;
			case SDLK_KP_ENTER:
				continuer = false;
				break;
			case SDLK_1:
				digit = 1;
				break;
			case SDLK_2:
				digit = 2;
				break;
			case SDLK_3:
				digit = 3;
				break;
			case SDLK_4:
				digit = 4;
				break;
			case SDLK_5:
				digit = 5;
				break;
			case SDLK_6:
				digit = 6;
				break;
			case SDLK_7:
				digit = 7;
				break;
			case SDLK_8:
				digit = 8;
				break;
			case SDLK_9:
				digit = 9;
				break;
			case SDLK_KP_0:
				digit = 0;
				break;
			case SDLK_KP_1:
				digit = 1;
				break;
			case SDLK_KP_2:
				digit = 2;
				break;
			case SDLK_KP_3:
				digit = 3;
				break;
			case SDLK_KP_4:
				digit = 4;
				break;
			case SDLK_KP_5:
				digit = 5;
				break;
			case SDLK_KP_6:
				digit = 6;
				break;
			case SDLK_KP_7:
				digit = 7;
				break;
			case SDLK_KP_8:
				digit = 8;
				break;
			case SDLK_KP_9:
				digit = 9;
				break;
			}
			if (continuer){
				if (digit != -1){
					number = (number * 10) + digit;
					digit = -1;
					rendueEcran(information);
					Texture::writetxt(information, blended,"Press ENTER to validate", { 255, 0, 0, 255 }, NoColor, 16, 0, 50);
					Texture::writetxt(information, blended, "Press Backspace to retry", { 255, 0, 0, 255 }, NoColor, 16, 0, 66);
					Texture::writetxt(information, blended, msg + std::to_string(number), { 0, 64, 255, 255 }, NoColor, 18, x, y, center_x);
					SDL_RenderPresent(information.ecran.renderer);
				}
			}
			break;
		}
	}
	return number;
}
double CinNumberDouble(sysinfo& information, const std::string& msg, unsigned int x, unsigned int y){
	bool continuer = true, postive = true, puissancePositive = true;
	double number = 0, digit = 0;
	unsigned int p = 1;
	SDL_Event event;
	int SDL_EnableUNICODE(1); // on azerty

	while (continuer){
		SDL_WaitEvent(&event);
		switch (event.type){
		case SDL_QUIT:	// permet de quitter
			information.variables.continuer = false;
			continuer = false;
			digit = -1;
			number = 0;
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				information.variables.continuer = false;
				continuer = false;
				digit = -1;
				number = 0;
				break;
			case SDLK_BACKSPACE:
				postive = true;
				puissancePositive = true;
				number = 0;
				digit = 0;
				break;
			case SDLK_RETURN:
				continuer = false;
				break;
			case SDLK_KP_ENTER:
				continuer = false;
				break;
			case SDLK_KP_MINUS:
				postive = false;
				break;
			case SDLK_KP_PLUS:
				postive = true;
				break;
			case SDLK_KP_PERIOD:
				puissancePositive = false;
				break;
			case SDLK_1:
				digit = 1;
				break;
			case SDLK_2:
				digit = 2;
				break;
			case SDLK_3:
				digit = 3;
				break;
			case SDLK_4:
				digit = 4;
				break;
			case SDLK_5:
				digit = 5;
				break;
			case SDLK_6:
				digit = 6;
				break;
			case SDLK_7:
				digit = 7;
				break;
			case SDLK_8:
				digit = 8;
				break;
			case SDLK_9:
				digit = 9;
				break;
			case SDLK_KP_0:
				digit = 0;
				break;
			case SDLK_KP_1:
				digit = 1;
				break;
			case SDLK_KP_2:
				digit = 2;
				break;
			case SDLK_KP_3:
				digit = 3;
				break;
			case SDLK_KP_4:
				digit = 4;
				break;
			case SDLK_KP_5:
				digit = 5;
				break;
			case SDLK_KP_6:
				digit = 6;
				break;
			case SDLK_KP_7:
				digit = 7;
				break;
			case SDLK_KP_8:
				digit = 8;
				break;
			case SDLK_KP_9:
				digit = 9;
				break;
			}
			if (continuer){
				if (digit != -1){
					rendueEcran(information);
					Texture::writetxt(information, blended, "Press ENTER to validate", { 255, 0, 0, 255 }, NoColor, 16, 0, 50);
					Texture::writetxt(information, blended, "Press Backspace to retry", { 255, 0, 0, 255 }, NoColor, 16, 0, 66);
					
					if (puissancePositive){
						number = (number * 10) + digit;
						if (!postive)
							number = -number;
						Texture::writetxt(information, blended, msg + std::to_string(number), { 0, 64, 255, 255 }, NoColor, 18, x, y, center_x);
					}
					else{
						number += (digit / pow(10, p));
						p++;
						if (!postive)
							number = -number;
						Texture::writetxt(information, blended, msg + std::to_string(number), { 0, 64, 255, 255 }, NoColor, 18, x, y, center_x);
					}
					SDL_RenderPresent(information.ecran.renderer);
					digit = -1;
				}
			}
			break;
		}
	}
	return number;
}
void CreateNumDen(IHM& ihm, sysinfo& information){
	IHM::logfileconsole("_ Start CreateNumDen _");
	information.variables.statescreen = STATETFcreateNumDen;
	rendueEcran(information);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 50);

	Texture::writetxt(information, blended, "Order of the Numerator : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, center_x);
	SDL_RenderPresent(information.ecran.renderer);
	ihm.GETfct()->SETnumOrder(CinNumberUnsignedInt(information, "Order of the Numerator : ", SCREEN_WIDTH / 2, 50));
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "Order of the Numerator : " + std::to_string(ihm.GETfct()->GETnum().GETorder()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, center_x);
	rendueEcran(information);
	for (unsigned int z = 0; z <= ihm.GETfct()->GETnum().GETorder(); z++){
		Texture::writetxt(information, blended, "coef n:" + std::to_string(z) + " = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 75, center_x);
		SDL_RenderPresent(information.ecran.renderer);
		ihm.GETfct()->SETnumThisCoef(z, CinNumberDouble(information, "coef n:" + std::to_string(z) + " = ", SCREEN_WIDTH / 2, 75));
		rendueEcran(information);
	}


	Texture::writetxt(information, blended, "Order of the Denominator : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, center_x);
	SDL_RenderPresent(information.ecran.renderer);
	ihm.GETfct()->SETdenOrder(CinNumberUnsignedInt(information, "Order of the Denominator : ", SCREEN_WIDTH / 2, 100));
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "Order of the Denominator : " + std::to_string(ihm.GETfct()->GETden().GETorder()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, center_x);
	rendueEcran(information);
	for (unsigned int z = 0; z <= ihm.GETfct()->GETden().GETorder(); z++){
		Texture::writetxt(information, blended, "coef n:" + std::to_string(z) + " = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 125, center_x);
		SDL_RenderPresent(information.ecran.renderer);
		ihm.GETfct()->SETdenThisCoef(z, CinNumberDouble(information, "coef n:" + std::to_string(z) + " = ", SCREEN_WIDTH / 2, 125));
		rendueEcran(information);
	}

	Texture::writetxt(information, blended, "Sampling time : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, center_x);
	SDL_RenderPresent(information.ecran.renderer);
	ihm.GETfct()->SETdeltaT(CinNumberDouble(information, "Sampling time : ", SCREEN_WIDTH / 2, 150));
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "Sampling time : " + std::to_string(ihm.GETfct()->GETdeltaT()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, center_x);
	rendueEcran(information);

	//for (unsigned int i = 0; i < information.allTextures.tabTexture.size(); i++)
		//information.allTextures.tabTexture[i]->TextureTestString();

	information.variables.statescreen = STATEfunctionTransfer;
	rendueEcran(information);
	IHM::logfileconsole("_ End CreateNumDen _");
}
void displayTF(IHM& ihm, sysinfo& information){
	IHM::logfileconsole("_ Start displayTF _");
	std::ostringstream stream; std::string texte;
	std::string barre;
	FCTDiscret FCT;
	if (FCT == *ihm.GETfct()){
		Texture::writetxt(information, blended, "TF doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 175, 148, center_y);
		SDL_RenderPresent(information.ecran.renderer);
	}
	else{
		unsigned int stringSize = 0;
		stringSize = max(ihm.GETfct()->GETnum().GETstringSize(), ihm.GETfct()->GETden().GETstringSize());
		for (unsigned int i = 0; i < ihm.GETfct()->GETden().GETstringSize(); i++)
			barre += "-";

		stream << ihm.GETfct()->GETnum().printOn(false); texte = stream.str(); stream.str(""); stream.clear();
		Texture::writetxt(information, blended, texte, { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 400, center_x);
		Texture::writetxt(information, blended, barre, { 0, 64, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 414, center_x);
		stream << ihm.GETfct()->GETden().printOn(false); texte = stream.str(); stream.str(""); stream.clear();
		Texture::writetxt(information, blended, texte, { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 436, center_x);
		SDL_RenderPresent(information.ecran.renderer);
	}
	IHM::logfileconsole("_ End displayTF _");
}
void displayJury(IHM& ihm, sysinfo& information){
	IHM::logfileconsole("_ Start displayJury _");
	unsigned int initspace = 180;
	std::string texte; std::ostringstream stream;
	FCTDiscret FCT;

	if (FCT == *ihm.GETfct()){
		Texture::writetxt(information, blended, "TF doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 175, 196, center_y);
		SDL_RenderPresent(information.ecran.renderer);
	}
	else{
		if (ihm.GETfct()->tabJury())
			Texture::writetxt(information, blended, "The system is stable", { 0, 255, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 100, 196, center_y);
		else
			Texture::writetxt(information, blended, "The system is unstable", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 100, 196, center_y);

		for (unsigned int i = 0; i < ihm.GETfct()->GETjury().GETlength(); i++){
			stream << "|";
			for (unsigned int j = 0; j < ihm.GETfct()->GETjury().GETheight(); j++)
				stream << " " << ihm.GETfct()->GETjury().GETthiscoef(i, j) << " ";
			stream << "|";
			texte = stream.str();
			stream.str("");
			stream.clear();
			Texture::writetxt(information, blended, texte, { 255, 255, 255, 255 }, NoColor, 16, 0, initspace += 16);
		}
	}
	SDL_RenderPresent(information.ecran.renderer);
	IHM::logfileconsole("_ End displayJury _");
}
void displayBode(IHM& ihm, sysinfo& information){
	IHM::logfileconsole("_ Start displayBode _");
	information.variables.statescreen = STATETFcreateBode;
	rendueEcran(information);
	double wmin = 0, wmax = 0;
	unsigned int nbpoint = 0;

	Texture::writetxt(information, blended, "W min : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, center_x);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 50);
	SDL_RenderPresent(information.ecran.renderer);
	wmin = CinNumberDouble(information, "W min : ", SCREEN_WIDTH / 2, 50);
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "W min : " + std::to_string(wmin), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, center_x);
	rendueEcran(information);

	Texture::writetxt(information, blended, "W max : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, center_x);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 100);
	SDL_RenderPresent(information.ecran.renderer);
	wmax = CinNumberDouble(information, "W max : ", SCREEN_WIDTH / 2, 100);
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "W max : " + std::to_string(wmax), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, center_x);
	rendueEcran(information);

	Texture::writetxt(information, blended, "Number of points : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, center_x);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 150);
	SDL_RenderPresent(information.ecran.renderer);
	nbpoint= CinNumberUnsignedInt(information, "Number of points : ", SCREEN_WIDTH / 2, 150);
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "Number of points : " + std::to_string(nbpoint), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, center_x);
	rendueEcran(information);

	information.variables.statescreen = STATETFdisplayBode;
	rendueEcran(information);

	double** gainPhase = new double*[3];
	for (unsigned int i = 0; i < 3; i++)
		gainPhase[i] = new double[nbpoint];

	for (unsigned int i = 0; i < 3; i++){
		for (unsigned int j = 0; j < nbpoint; j++)
			gainPhase[i][j] = 0;
	}
	ihm.GETfct()->Bode(wmin, wmax, nbpoint, gainPhase);

	double gainMax = gainPhase[1][0], gainMin = gainPhase[1][0];
	double phaseMax = gainPhase[2][0], phaseMin = gainPhase[2][0];
	for (unsigned int i = 0; i < nbpoint; i++){
		if (gainPhase[1][i] > gainMax)
			gainMax = gainPhase[1][i];
		if (gainPhase[1][i] < gainMin)
			gainMin = gainPhase[1][i];

		if (gainPhase[2][i] > phaseMax)
			phaseMax = gainPhase[2][i];
		if (gainPhase[2][i] < phaseMin)
			phaseMin = gainPhase[2][i];
	}

	double amplitudeGain = max(abs(gainMax), abs(gainMin));
	double amplitudePhase = max(abs(phaseMax), abs(phaseMin));
	
	std::string barre;
	barre = "";
	for (unsigned int z = 0; z < 100; z++)
		barre += "-";
	barre += ">w(2xPixf)";
	Texture::writetxt(information, blended, barre, { 255, 255, 255, 255 }, NoColor, 16, 40, 460, center_y);
	barre = "";
	unsigned int initspace = 14;
	for (unsigned int z = 0; z < 30; z++)
		Texture::writetxt(information, blended, "|", { 255, 255, 255, 255 }, NoColor, 16, 50, initspace += 16, center_x);

	Texture::writetxt(information, blended, std::to_string(wmin), { 255, 255, 255, 255 }, NoColor, 10, 30, 472, center_y);
	Texture::writetxt(information, blended, std::to_string(wmax), { 255, 255, 255, 255 }, NoColor, 10, 530, 472, center_y);

	unsigned int x0 = 50, xmax = 550; 
	unsigned int ymingain = 30, ymaxgain = 230;
	unsigned int yminphase = 250, ymaxphase = 450;
	//double pasGraph = (xmax - x0) / nbpoint;
	double ecartRelatif = wmax / wmin;
	unsigned int longeurAxe = xmax - x0;
	double* pasGraph = new double[nbpoint];
	pasGraph[0] = 0;
	unsigned int k = 0;
	double increment = (wmax - wmin) / nbpoint;
	double nbpointParDecade = 50;
	for (unsigned int i = 0; i < 10; i++){
		pasGraph[i] = ((longeurAxe * log(gainPhase[0][i])) / log(ecartRelatif)) + 250;
		std::cout << std::endl << i << " , " << pasGraph[i] << " , " << gainPhase[0][i];
	}

	
	for (unsigned int z = x0, n = 0; z < xmax, n < 10; z += pasGraph[n], n++){
		Texture::writetxt(information, blended,"+", { 255, 0, 0, 255 }, NoColor, 8, x0 + z, ymaxgain - ((gainPhase[1][n] / amplitudeGain) * (ymaxgain - ymingain)), center);
		//writetxt(information, "+", { 0, 255, 0, 255 }, 8, x0 + z, yminphase - ((gainPhase[2][n] / amplitudePhase) * (ymaxphase - yminphase)), center);
	}
	SDL_RenderPresent(information.ecran.renderer);
	
	
	delete[] pasGraph;

	for (unsigned int i = 0; i < 3; i++)
		delete[] gainPhase[i];
	delete[] gainPhase;

	IHM::logfileconsole("_ End displayBode _");
}
void createMatrice(IHM& ihm, sysinfo& information){
	IHM::logfileconsole("_ Start createMatrice _");
	information.variables.statescreen = STATESScreateMatrice;
	rendueEcran(information);

	unsigned int length = 0;


	Texture::writetxt(information, blended, "Length or height of A : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, center_x);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 50);
	SDL_RenderPresent(information.ecran.renderer);
	length = CinNumberUnsignedInt(information, "Length or height of A : ", SCREEN_WIDTH / 2, 50);
	ihm.GETsys()->SETeditSizeA(length, length);
	ihm.GETsys()->SETeditSizeB(length, 1);
	ihm.GETsys()->SETeditSizeC(1, length);
	ihm.GETsys()->SETeditSizeD(1, 1);
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended,
		"Length of A : " + std::to_string(ihm.GETsys()->GETA().GETlength()) + " and Height of A : " + std::to_string(ihm.GETsys()->GETA().GETheight()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, center_x);
	rendueEcran(information);

	displayStateSystem(ihm, information);

	for (unsigned int i = 0; i < ihm.GETsys()->GETA().GETlength(); i++){
		for (unsigned int j = 0; j < ihm.GETsys()->GETA().GETheight(); j++){
			Texture::writetxt(information, blended, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 75, center_x);
			SDL_RenderPresent(information.ecran.renderer);
			ihm.GETsys()->SETthisCoefA(i, j, CinNumberDouble(information, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", SCREEN_WIDTH / 2, 75));
			rendueEcran(information);
			displayStateSystem(ihm, information);
		}
	}

	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended,
		"Length of B : " + std::to_string(ihm.GETsys()->GETB().GETlength()) + " and Height of B : " + std::to_string(ihm.GETsys()->GETB().GETlength()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, center_x);
	rendueEcran(information);
	displayStateSystem(ihm, information);

	for (unsigned int i = 0; i < ihm.GETsys()->GETB().GETlength(); i++){
		for (unsigned int j = 0; j < ihm.GETsys()->GETB().GETheight(); j++){
			Texture::writetxt(information, blended, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 125, center_x);
			SDL_RenderPresent(information.ecran.renderer);
			ihm.GETsys()->SETthisCoefB(i, j, CinNumberDouble(information, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", SCREEN_WIDTH / 2, 125));
			rendueEcran(information);
			displayStateSystem(ihm, information);
		}
	}

	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended,
		"Length of C : " + std::to_string(ihm.GETsys()->GETC().GETlength()) + " and Height of C : " + std::to_string(ihm.GETsys()->GETC().GETheight()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, center_x);
	rendueEcran(information);
	displayStateSystem(ihm, information);

	for (unsigned int i = 0; i < ihm.GETsys()->GETC().GETlength(); i++){
		for (unsigned int j = 0; j < ihm.GETsys()->GETC().GETheight(); j++){
			Texture::writetxt(information, blended, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 175, center_x);
			SDL_RenderPresent(information.ecran.renderer);
			ihm.GETsys()->SETthisCoefC(i, j, CinNumberDouble(information, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", SCREEN_WIDTH / 2, 175));
			rendueEcran(information);
			displayStateSystem(ihm, information);
		}
	}

	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended,
		"Length of D : " + std::to_string(ihm.GETsys()->GETD().GETlength()) + " and Height of D : " + std::to_string(ihm.GETsys()->GETD().GETheight()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 200, center_x);
	rendueEcran(information);
	displayStateSystem(ihm, information);

	Texture::writetxt(information, blended, "coef [0][0] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 225, center_x);
	SDL_RenderPresent(information.ecran.renderer);
	ihm.GETsys()->SETthisCoefD(0, 0, CinNumberDouble(information, "coef [0][0] = ", SCREEN_WIDTH / 2, 225));
	rendueEcran(information);
	displayStateSystem(ihm, information);


	IHM::logfileconsole("_ End createMatrice _");
}
void computeABCD(IHM& ihm, sysinfo& information){
	IHM::logfileconsole("_ Start computeABCD _");
	FCTDiscret FCT;
	if (FCT == *ihm.GETfct())
		Texture::writetxt(information, blended, "TF doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 148, center_y);
	else{
		if (ihm.GETfct()->GETden().GETorder() > ihm.GETfct()->GETnum().GETorder()){
			ihm.GETsys()->calculABCD(*ihm.GETfct());
			Texture::writetxt(information, blended, "OK", { 0, 255, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 148, center_y);
		}
		else
			Texture::writetxt(information, blended, "Order of Num >= Den", { 255, 0, 0, 255 }, NoColor, 14, (SCREEN_WIDTH / 2) + 150, 148, center_y);
	}
	SDL_RenderPresent(information.ecran.renderer);
	IHM::logfileconsole("_ End computeABCD _");
}
void displayStateSystem(IHM& ihm, sysinfo& information){
	IHM::logfileconsole("_ Start displayStateSystem _");
	unsigned int initspace = 100;
	std::string texte; std::ostringstream stream;
	Texture::writetxt(information, blended, "Matrix A", { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	for (unsigned int i = 0; i < ihm.GETsys()->GETA().GETlength(); i++){
		stream << "|";
		for (unsigned int j = 0; j < ihm.GETsys()->GETA().GETheight(); j++)
			stream << " " << ihm.GETsys()->GETA().GETthiscoef(i, j) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		Texture::writetxt(information, blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	}

	initspace += 32;
	Texture::writetxt(information, blended, "Matrix B", { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	for (unsigned int i = 0; i < ihm.GETsys()->GETB().GETlength(); i++){
		stream << "|";
		for (unsigned int j = 0; j < ihm.GETsys()->GETB().GETheight(); j++)
			stream << " " << ihm.GETsys()->GETB().GETthiscoef(i, j) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		Texture::writetxt(information, blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	}

	initspace += 32;
	Texture::writetxt(information, blended, "Matrix C", { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	for (unsigned int i = 0; i < ihm.GETsys()->GETC().GETlength(); i++){
		stream << "|";
		for (unsigned int j = 0; j < ihm.GETsys()->GETC().GETheight(); j++)
			stream << " " << ihm.GETsys()->GETC().GETthiscoef(i, j) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		Texture::writetxt(information, blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	}

	initspace += 32;
	Texture::writetxt(information, blended, "Matrix D", { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	stream << "| " << ihm.GETsys()->GETD().GETthiscoef(0, 0) << " |";
	texte = stream.str();
	stream.str("");
	stream.clear();
	Texture::writetxt(information, blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);

	SDL_RenderPresent(information.ecran.renderer);
	IHM::logfileconsole("_ End displayStateSystem _");
}
void createSignal(IHM& ihm, sysinfo& information, Signal& sig){
	IHM::logfileconsole("_ Start createSignal _");
	Texture::writetxt(information, blended, "Number of samples : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, center_x);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 150);
	SDL_RenderPresent(information.ecran.renderer);
	sig.SETnbech(CinNumberUnsignedInt(information, "Number of samples : ", SCREEN_WIDTH / 2, 150));
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "Number of samples : " + std::to_string(sig.GETnbech()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, center_x);
	rendueEcran(information);

	Texture::writetxt(information, blended, "DeltaT : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 200, center_x);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 200);
	SDL_RenderPresent(information.ecran.renderer);
	sig.SETdeltaT(CinNumberDouble(information, "DeltaT : ", SCREEN_WIDTH / 2, 200));
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "DeltaT : " + std::to_string(sig.GETdeltaT()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 200, center_x);
	rendueEcran(information);

	IHM::logfileconsole("_ End createSignal _");
}
void createStep(IHM& ihm, sysinfo& information, Echelon& step){
	IHM::logfileconsole("_ Start createStep _");

	Texture::writetxt(information, blended, "Amplitude : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, center_x);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 70, 250);
	SDL_RenderPresent(information.ecran.renderer);
	step.SETamplitude(CinNumberDouble(information, "Amplitude : ", SCREEN_WIDTH / 2, 250));
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "Amplitude : " + std::to_string(step.GETamplitude()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, center_x);
	rendueEcran(information);

	IHM::logfileconsole("_ End createStep _");
}
void createRamp(IHM& ihm, sysinfo& information, Rampe& ramp){
	IHM::logfileconsole("_ Start createRamp _");

	Texture::writetxt(information, blended, "Slope : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, center_x);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 250);
	SDL_RenderPresent(information.ecran.renderer);
	ramp.SETslope(CinNumberDouble(information, "Slope : ", SCREEN_WIDTH / 2, 250));
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "Slope : " + std::to_string(ramp.GETslope()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, center_x);
	rendueEcran(information);

	IHM::logfileconsole("_ End createRamp _");
}
void createSinus(IHM& ihm, sysinfo& information, Sinus& sinus){
	IHM::logfileconsole("_ Start createSinus _");

	Texture::writetxt(information, blended, "Amplitude : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, center_x);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 70, 250);
	SDL_RenderPresent(information.ecran.renderer);
	sinus.SETamplitude(CinNumberDouble(information, "Amplitude : ", SCREEN_WIDTH / 2, 250));
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "Amplitude : " + std::to_string(sinus.GETamplitude()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, center_x);
	rendueEcran(information);

	Texture::writetxt(information, blended, "Angular velocity (w): ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 300, center_x);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 300);
	SDL_RenderPresent(information.ecran.renderer);
	sinus.SETw(CinNumberDouble(information, "Angular velocity (w): ", SCREEN_WIDTH / 2, 300));
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "Angular velocity (w): " + std::to_string(sinus.GETw()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 300, center_x);
	rendueEcran(information);

	Texture::writetxt(information, blended, "Phase (phi): ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 350, center_x);
	Texture::writetxt(information, blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 70, 350);
	SDL_RenderPresent(information.ecran.renderer);
	sinus.SETdephasage(CinNumberDouble(information, "Phase (phi): ", SCREEN_WIDTH / 2, 350));
	Texture::loadwritetxt(information, information.allTextures.txtEcranTitre, blended, "Phase (phi): " + std::to_string(sinus.GETdephasage()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 350, center_x);
	rendueEcran(information);

	IHM::logfileconsole("_ End createSinus _");
}
void displayReponseTemp(IHM& ihm, sysinfo& information, Signal& sig){
	IHM::logfileconsole("_ Start displayReponseTemp _");
	std::string barre;
	barre = "0";
	for (unsigned int z = 0; z < 100; z++)
		barre += "-";
	barre += ">t(s)";
	Texture::writetxt(information, blended, barre, { 255, 255, 255, 255 }, NoColor, 16, 40, 250, center_y);
	barre = "";
	unsigned int initspace = 34;
	for (unsigned int z = 0; z < 30; z++)
		Texture::writetxt(information, blended, "|", { 255, 255, 255, 255 }, NoColor, 16, 50, initspace += 16, center_x);


	Matrice X0(ihm.GETsys()->GETA().GETlength(), 1);

	double* yOut = new double[sig.GETnbech()];
	ihm.GETsys()->simulation("bin/files/ReponseTemporelle.txt", sig, X0, yOut);


	unsigned int x0 = 50, xmin = 50, xmax = 550;
	unsigned int y0 = 250, ymin = 450, ymax = 50;
	

	double max = 0, min = 0;
	for (unsigned int z = 0; z < sig.GETnbech(); z++){
		if (sig.GETthiscoef(z) > max)
			max = sig.GETthiscoef(z);
		if (yOut[z] > max)
			max = yOut[z];
		if (sig.GETthiscoef(z) < min)
			min = sig.GETthiscoef(z);
		if (yOut[z] < min)
			min = yOut[z];
	}

	unsigned int pasGraph = (xmax - xmin) / sig.GETnbech();
	Texture::writetxt(information, blended, std::to_string(max), { 255, 0, 0, 255 }, NoColor, 8, 20, 50, center);
	for (unsigned int z = xmin, n = 0; z < xmax, n < sig.GETnbech(); z += pasGraph, n++){
		Texture::writetxt(information, blended, "|", { 255, 255, 255, 255 }, NoColor, 8, z, y0, center);

		if (sig.GETthiscoef(n) > 0)
			Texture::writetxt(information, blended, "+", { 255, 0, 0, 255 }, NoColor, 8, z, y0 - ((sig.GETthiscoef(n) / max) * (y0 - ymax)), center);
		else if (sig.GETthiscoef(n) < 0)
			Texture::writetxt(information, blended, "+", { 255, 0, 0, 255 }, NoColor, 8, z, y0 + ((sig.GETthiscoef(n) / min) * (ymin - y0)), center);

		if (yOut[n] > 0)
			Texture::writetxt(information, blended, "+", { 0, 255, 0, 255 }, NoColor, 8, z, y0 - ((yOut[n] / max) * (y0 - ymax)), center);
		else if (yOut[n] < 0)
			Texture::writetxt(information, blended, "+", { 0, 255, 0, 255 }, NoColor, 8, z, y0 + ((yOut[n] / min) * (ymin - y0)), center);

		if (n == 10)
			Texture::writetxt(information, blended, std::to_string(sig.GETdeltaT() * 10), { 255, 255, 255, 255 }, NoColor, 8, z, y0 + 10, center);
	}
	delete[] yOut;
	SDL_RenderPresent(information.ecran.renderer);
	IHM::logfileconsole("_ Start displayReponseTemp _");
}

void IHM::deleteAll(sysinfo& information){
	logfileconsole("*********_________ Start DeleteAll _________*********");
	for (unsigned int i = 1; i < 80; i++)
		TTF_CloseFont(information.allTextures.font[i]);

	deleteDyTabPlayerAndTextures(information.allTextures.txtEcranTitre, "txtEcranTitre");
	deleteDyTabPlayerAndTextures(information.allButtons.ecranTitre, "ecranTitre");
	deleteDyTabPlayerAndTextures(information.allButtons.ecranFCT, "ecranFCT");
	deleteDyTabPlayerAndTextures(information.allButtons.ecranSYSETAT, "ecranSYSETAT");
	SDL_DestroyRenderer(information.ecran.renderer);
	SDL_DestroyWindow(information.ecran.window);
	information.ecran.renderer = nullptr;
	information.ecran.window = nullptr;
	logfileconsole("*********_________ End DeleteAll _________*********");
}
