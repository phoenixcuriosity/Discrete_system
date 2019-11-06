/*

	Discrete_system
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version: 3.0
	file version 2.0

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


/*
* NAME : showStartSuccess
* ROLE : Affiche sur la console si le programme à réussi à démarrer
* INPUT  PARAMETERS : void
* OUTPUT PARAMETERS : Affichage sur la console et dans le fichier log
* RETURNED VALUE    : void
*/
void IHM::showStartSuccess()
{
	logfileconsole("_________START PROGRAM_________");
	logfileconsole("Dev version: 3.0");
	logfileconsole("Created by SAUTER Robin");
	logfileconsole("This is a free software, you can redistribute it and/or modify it\n");
}

/*
* NAME : logfileconsole
* ROLE : Affiche sur la console et dans le fichier log le std::string en entrée
* INPUT  PARAMETERS : const std::string& msg : le message en entrée
* OUTPUT PARAMETERS : Affichage sur la console et dans le fichier log
* RETURNED VALUE    : void
*/
void IHM::logfileconsole(const std::string& msg)
{
	const std::string logtxt = "bin/files/log.txt";
	std::ofstream log(logtxt, std::ios::app);
	if (log)
	{
		std::cout << std::endl << msg;
		log << std::endl << msg;
	}
	else
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le Fichier : " << logtxt;
}

/*
* NAME : eventSDL
* ROLE : Prise en compte des évenements SDL (souris/clavier)
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Action réaliser par des évenements SDL
* RETURNED VALUE    : void
*/
void IHM::eventSDL(Sysinfo& sysinfo)
{
	SDL_Event event;

	SDL_WaitEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:	// permet de quitter
		sysinfo.var.continuer = false;
		break;
	case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
		switch (event.key.keysym.sym)
		{
		case SDLK_F5:

			break;
		case SDLK_F6:

			break;
		case SDLK_ESCAPE:
			sysinfo.var.continuer = false;
			break;
		case SDLK_SPACE:

			break;
		case SDLK_KP_1:
			break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
		IHM::mouse(sysinfo, event);
		break;
	case SDL_MOUSEWHEEL:
		break;
	}
}



void rendueEcran(Sysinfo& sysinfo){
	SDL_RenderClear(sysinfo.screen.renderer);
	
	for (unsigned int i = 0; i < sysinfo.allTextes.txtEcranTitre.size(); i++)
		sysinfo.allTextes.txtEcranTitre[i]->renderTextureTestStates(sysinfo.var.stateScreen, sysinfo.var.select);

	if (sysinfo.var.stateScreen == STATEecrantitre) {
		for (unsigned int i = 0; i < sysinfo.allButtons.ecranTitre.size(); i++)
			sysinfo.allButtons.ecranTitre[i]->renderButtonTexte(sysinfo.var.stateScreen);
	}
	else if (sysinfo.var.stateScreen == STATEfunctionTransfer || sysinfo.var.stateScreen == STATETFcreateNumDen
		|| sysinfo.var.stateScreen == STATETFcreateBode || sysinfo.var.stateScreen == STATETFdisplayBode) {
		for (unsigned int i = 0; i < sysinfo.allButtons.ecranFCT.size(); i++)
			sysinfo.allButtons.ecranFCT[i]->renderButtonTexte(sysinfo.var.stateScreen);
		for (unsigned int i = 0; i < sysinfo.allTextes.CreateNumDen.size(); i++)
			sysinfo.allTextes.CreateNumDen[i]->renderTextureTestStates(sysinfo.var.stateScreen, sysinfo.var.select);
	}
	else if (sysinfo.var.stateScreen == STATEstateSystem || sysinfo.var.stateScreen == STATESScreateMatrice
		|| sysinfo.var.stateScreen == STATESSsimulate || sysinfo.var.stateScreen == STATEreponseTemporelle) {
		for (unsigned int i = 0; i < sysinfo.allButtons.ecranSYSETAT.size(); i++)
			sysinfo.allButtons.ecranSYSETAT[i]->renderButtonTexte(sysinfo.var.stateScreen);
	}
	SDL_RenderPresent(sysinfo.screen.renderer);
}

void mouse(Sysinfo& sysinfo, SDL_Event event)
{
	/*
	Handle Mouse Event
	BUTTON_LEFT
	BUTTON_RIGHT

	*/
	std::string test, fct;

	if (event.button.button == SDL_BUTTON_LEFT){

		if (sysinfo.var.stateScreen == STATEecrantitre) {
			for (unsigned int i = 0; i < sysinfo.allButtons.ecranTitre.size(); i++) { // recherche si une bouton est dans ces coordonnées

			// boutons du main menu

				if (sysinfo.allButtons.ecranTitre[i]->searchButtonTexte(fct = "Transfer Function", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					sysinfo.var.stateScreen = STATEfunctionTransfer;
					rendueEcran(sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranTitre[i]->searchButtonTexte(fct = "State System", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					sysinfo.var.stateScreen = STATEstateSystem;
					rendueEcran(sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranTitre[i]->searchButtonTexte(fct = "Closed Loop", sysinfo.var.stateScreen, event.button.x, event.button.y)) {

					break;
				}
				else if (sysinfo.allButtons.ecranTitre[i]->searchButtonTexte(fct = "Quit", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					sysinfo.var.continuer = false;
					break;
				}
			}
		}
		else if (sysinfo.var.stateScreen == STATEfunctionTransfer || sysinfo.var.stateScreen == STATETFcreateNumDen
			|| sysinfo.var.stateScreen == STATETFcreateBode || sysinfo.var.stateScreen == STATETFdisplayBode) {
			for (unsigned int i = 0; i < sysinfo.allButtons.ecranFCT.size(); i++) {
				if (sysinfo.allButtons.ecranFCT[i]->searchButtonTexte(fct = "Main menu", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					sysinfo.var.stateScreen = STATEecrantitre;
					rendueEcran(sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranFCT[i]->searchButtonTexte(fct = "Create the Transfer Function", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					CreateNumDen(ihm, sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranFCT[i]->searchButtonTexte(fct = "Display the Transfer Function", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					displayTF(ihm, sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranFCT[i]->searchButtonTexte(fct = "Jury", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					displayJury(ihm, sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranFCT[i]->searchButtonTexte(fct = "Bode", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					displayBode(ihm, sysinfo);
					break;
				}
			}
		}
		else if (sysinfo.var.stateScreen == STATEstateSystem || sysinfo.var.stateScreen == STATESScreateMatrice
			|| sysinfo.var.stateScreen == STATESSsimulate || sysinfo.var.stateScreen == STATEreponseTemporelle) {
			for (unsigned int i = 0; i < sysinfo.allButtons.ecranSYSETAT.size(); i++) {
				if (sysinfo.allButtons.ecranSYSETAT[i]->searchButtonTexte(fct = "Main menu", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					sysinfo.var.stateScreen = STATEecrantitre;
					rendueEcran(sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT[i]->searchButtonTexte(fct = "Edit Matrix A, B, C and D", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					createMatrice(ihm, sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT[i]->searchButtonTexte(fct = "Compute A, B, C and D", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					if (ihm.GETfct()->GETden().GETorder() > 0)
						computeABCD(ihm, sysinfo);
					else
						Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, blended,
							"Order of Denominator is 0", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 130, 148, center_y);
					SDL_RenderPresent(sysinfo.screen.renderer);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT[i]->searchButtonTexte(fct = "Display the State System", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					SYSETATDiscret SYS;
					if (SYS == *ihm.GETsys())
						Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, blended,
							"SS doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 196, center_y);
					else {
						displayStateSystem(ihm, sysinfo);
						Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, blended,
							"OK", { 0, 255, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 196, center_y);
					}
					SDL_RenderPresent(sysinfo.screen.renderer);

					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT[i]->searchButtonTexte(fct = "Simulate", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					SYSETATDiscret SYS;
					if (SYS == *ihm.GETsys())
						Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, blended,
							"SS doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 244, center_y);
					else {
						sysinfo.var.stateScreen = STATESSsimulate;
						rendueEcran(sysinfo);

					}
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT[i]->searchButtonTexte(fct = "Step", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					sysinfo.allButtons.ecranSYSETAT[i]->changeOn();
					rendueEcran(sysinfo);
					Echelon step;
					createSignal(sysinfo, step);
					createStep(sysinfo, step);
					sysinfo.var.stateScreen = STATEreponseTemporelle;
					rendueEcran(sysinfo);
					displayReponseTemp(ihm, sysinfo, step);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT[i]->searchButtonTexte(fct = "Ramp", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					sysinfo.allButtons.ecranSYSETAT[i]->changeOn();
					rendueEcran(sysinfo);
					Rampe ramp;
					createSignal(sysinfo, ramp);
					createRamp(sysinfo, ramp);
					sysinfo.var.stateScreen = STATEreponseTemporelle;
					rendueEcran(sysinfo);
					displayReponseTemp(ihm, sysinfo, ramp);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT[i]->searchButtonTexte(fct = "Sinus", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					//Sinus sinus(500, 0.1, 1, 1, 0);
					sysinfo.allButtons.ecranSYSETAT[i]->changeOn();
					rendueEcran(sysinfo);
					Sinus sinus;
					createSignal(sysinfo, sinus);
					createSinus(sysinfo, sinus);
					sysinfo.var.stateScreen = STATEreponseTemporelle;
					rendueEcran(sysinfo);
					displayReponseTemp(ihm, sysinfo, sinus);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT[i]->searchButtonTexte(fct = "Import Signal", sysinfo.var.stateScreen, event.button.x, event.button.y)) {
					sysinfo.allButtons.ecranSYSETAT[i]->changeOn();
					rendueEcran(sysinfo);
					break;
				}
			}
		}
	}
}
unsigned int CinNumberUnsignedInt(Sysinfo& sysinfo, const std::string& msg, unsigned int x, unsigned int y){
	bool continuer = true;
	unsigned int number = 0;
	int8_t digit = 0;
	SDL_Event event;
	int SDL_EnableUNICODE(1); // on azerty
	
	while (continuer){
		SDL_WaitEvent(&event);
		switch (event.type){
		case SDL_QUIT:	// permet de quitter
			sysinfo.var.continuer = false;
			continuer = false;
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				sysinfo.var.continuer = false;
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
					rendueEcran(sysinfo);
					Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
						blended,"Press ENTER to validate", { 255, 0, 0, 255 }, NoColor, 16, 0, 50);
					Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
						blended, "Press Backspace to retry", { 255, 0, 0, 255 }, NoColor, 16, 0, 66);
					Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
						blended, msg + std::to_string(number), { 0, 64, 255, 255 }, NoColor, 18, x, y, center_x);
					SDL_RenderPresent(sysinfo.screen.renderer);
				}
			}
			break;
		}
	}
	return number;
}
double CinNumberDouble(Sysinfo& sysinfo, const std::string& msg, unsigned int x, unsigned int y){
	bool continuer = true, postive = true, puissancePositive = true;
	double number = 0, digit = 0;
	unsigned int p = 1;
	SDL_Event event;
	int SDL_EnableUNICODE(1); // on azerty

	while (continuer){
		SDL_WaitEvent(&event);
		switch (event.type){
		case SDL_QUIT:	// permet de quitter
			sysinfo.var.continuer = false;
			continuer = false;
			digit = -1;
			number = 0;
			break;
		case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				sysinfo.var.continuer = false;
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
					rendueEcran(sysinfo);
					Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
						blended, "Press ENTER to validate", { 255, 0, 0, 255 }, NoColor, 16, 0, 50);
					Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
						blended, "Press Backspace to retry", { 255, 0, 0, 255 }, NoColor, 16, 0, 66);
					
					if (puissancePositive){
						number = (number * 10) + digit;
						if (!postive)
							number = -number;
						Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
							blended, msg + std::to_string(number), { 0, 64, 255, 255 }, NoColor, 18, x, y, center_x);
					}
					else{
						number += (digit / pow(10, p));
						p++;
						if (!postive)
							number = -number;
						Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
							blended, msg + std::to_string(number), { 0, 64, 255, 255 }, NoColor, 18, x, y, center_x);
					}
					SDL_RenderPresent(sysinfo.screen.renderer);
					digit = -1;
				}
			}
			break;
		}
	}
	return number;
}
void CreateNumDen(IHM& ihm, Sysinfo& sysinfo){
	IHM::logfileconsole("_ Start CreateNumDen _");
	sysinfo.var.stateScreen = STATETFcreateNumDen;
	
	/* Erase last FCT */
	FCTDiscret blank;
	*ihm.GETfct() = blank;
	sysinfo.allTextes.CreateNumDen.clear();
	rendueEcran(sysinfo);

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 50);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Order of the Numerator : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, center_x);
	SDL_RenderPresent(sysinfo.screen.renderer);
	ihm.GETfct()->SETnumOrder(CinNumberUnsignedInt(sysinfo, "Order of the Numerator : ", SCREEN_WIDTH / 2, 50));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.CreateNumDen,
		blended, "Order of the Numerator : " + std::to_string(ihm.GETfct()->GETnum().GETorder()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, nonTransparent, center_x);
	rendueEcran(sysinfo);
	for (unsigned int z = 0; z <= ihm.GETfct()->GETnum().GETorder(); z++){
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "coef order:" + std::to_string(z) + " = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 75, center_x);
		SDL_RenderPresent(sysinfo.screen.renderer);
		ihm.GETfct()->SETnumThisCoef(z, CinNumberDouble(sysinfo, "coef order:" + std::to_string(z) + " = ", SCREEN_WIDTH / 2, 75));
		rendueEcran(sysinfo);
	}


	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Order of the Denominator : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, center_x);
	SDL_RenderPresent(sysinfo.screen.renderer);
	ihm.GETfct()->SETdenOrder(CinNumberUnsignedInt(sysinfo, "Order of the Denominator : ", SCREEN_WIDTH / 2, 100));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.CreateNumDen,
		blended, "Order of the Denominator : " + std::to_string(ihm.GETfct()->GETden().GETorder()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, nonTransparent, center_x);
	rendueEcran(sysinfo);
	for (unsigned int z = 0; z <= ihm.GETfct()->GETden().GETorder(); z++){
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "coef order:" + std::to_string(z) + " = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 125, center_x);
		SDL_RenderPresent(sysinfo.screen.renderer);
		ihm.GETfct()->SETdenThisCoef(z, CinNumberDouble(sysinfo, "coef order:" + std::to_string(z) + " = ", SCREEN_WIDTH / 2, 125));
		rendueEcran(sysinfo);
	}

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Sampling time : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, center_x);
	SDL_RenderPresent(sysinfo.screen.renderer);
	ihm.GETfct()->SETdeltaT(CinNumberDouble(sysinfo, "Sampling time : ", SCREEN_WIDTH / 2, 150));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.CreateNumDen,
		blended, "Sampling time : " + std::to_string(ihm.GETfct()->GETdeltaT()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, nonTransparent, center_x);
	rendueEcran(sysinfo);

	sysinfo.var.stateScreen = STATEfunctionTransfer;
	rendueEcran(sysinfo);
	IHM::logfileconsole("_ End CreateNumDen _");
}
void displayTF(IHM& ihm, Sysinfo& sysinfo){
	IHM::logfileconsole("_ Start displayTF _");
	std::ostringstream stream; std::string texte;
	std::string barre;
	FCTDiscret FCT;
	if (FCT == *ihm.GETfct()){
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "TF doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 175, 148, center_y);
		SDL_RenderPresent(sysinfo.screen.renderer);
	}
	else{
		unsigned int stringSize = 0;
		stringSize = max(ihm.GETfct()->GETnum().GETstringSize(), ihm.GETfct()->GETden().GETstringSize());
		for (unsigned int i = 0; i < ihm.GETfct()->GETden().GETstringSize(); i++)
			barre += "-";

		stream << ihm.GETfct()->GETnum().printOn(false); texte = stream.str(); stream.str(""); stream.clear();
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, texte, { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 550, center_x);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, barre, { 0, 64, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 564, center_x);
		stream << ihm.GETfct()->GETden().printOn(false); texte = stream.str(); stream.str(""); stream.clear();
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, texte, { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 580, center_x);
		SDL_RenderPresent(sysinfo.screen.renderer);
	}
	IHM::logfileconsole("_ End displayTF _");
}
void displayJury(IHM& ihm, Sysinfo& sysinfo){
	IHM::logfileconsole("_ Start displayJury _");
	unsigned int initspace = 300;
	std::string texte; std::ostringstream stream;
	FCTDiscret FCT;

	stream << std::fixed << std::setprecision(4);
	if (FCT == *ihm.GETfct()){
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "TF doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 175, 196, center_y);
		SDL_RenderPresent(sysinfo.screen.renderer);
	}
	else{
		if (ihm.GETfct()->tabJury())
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "The system is stable", { 0, 255, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 100, 196, center_y);
		else
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "The system is unstable", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 100, 196, center_y);

		for (unsigned int i = 0; i < ihm.GETfct()->GETjury().GETlength(); i++){
			stream << "|";
			for (unsigned int j = 0; j < ihm.GETfct()->GETjury().GETheight(); j++)
				if(ihm.GETfct()->GETjury().GETthiscoef(i, j) >= 0)
					stream << "    " << ihm.GETfct()->GETjury().GETthiscoef(i, j) << " ";
				else
					stream << "   -" << abs(ihm.GETfct()->GETjury().GETthiscoef(i, j)) << " ";
			stream << "|";
			texte = stream.str();
			stream.str("");
			stream.clear();
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, texte, { 255, 255, 255, 255 }, NoColor, 16, 100, initspace += 16);
		}
	}
	SDL_RenderPresent(sysinfo.screen.renderer);
	IHM::logfileconsole("_ End displayJury _");
}
void displayBode(IHM& ihm, Sysinfo& sysinfo){
	IHM::logfileconsole("_ Start displayBode _");
	double wmin = 0, wmax = 0;
	unsigned int nbpoint = 0;

	FCTDiscret FCT;
	if (FCT == *ihm.GETfct()) {
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "TF doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 175, 244, center_y);
		SDL_RenderPresent(sysinfo.screen.renderer);
	}
	else {
		sysinfo.var.stateScreen = STATETFcreateBode;
		rendueEcran(sysinfo);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "W min : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, center_x);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 50);
		SDL_RenderPresent(sysinfo.screen.renderer);
		wmin = CinNumberDouble(sysinfo, "W min : ", SCREEN_WIDTH / 2, 50);
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
			blended, "W min : " + std::to_string(wmin), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, nonTransparent, center_x);
		rendueEcran(sysinfo);

		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "W max : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, center_x);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 100);
		SDL_RenderPresent(sysinfo.screen.renderer);
		wmax = CinNumberDouble(sysinfo, "W max : ", SCREEN_WIDTH / 2, 100);
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
			blended, "W max : " + std::to_string(wmax), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, nonTransparent, center_x);
		rendueEcran(sysinfo);

		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "Number of points : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, center_x);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 150);
		SDL_RenderPresent(sysinfo.screen.renderer);
		nbpoint = CinNumberUnsignedInt(sysinfo, "Number of points : ", SCREEN_WIDTH / 2, 150);
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
			blended, "Number of points : " + std::to_string(nbpoint), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, nonTransparent, center_x);
		rendueEcran(sysinfo);

		sysinfo.var.stateScreen = STATETFdisplayBode;
		rendueEcran(sysinfo);

		double** gainPhase = new double*[3];
		for (unsigned int i = 0; i < 3; i++)
			gainPhase[i] = new double[nbpoint];

		for (unsigned int i = 0; i < 3; i++) {
			for (unsigned int j = 0; j < nbpoint; j++)
				gainPhase[i][j] = 0;
		}
		ihm.GETfct()->Bode(wmin, wmax, nbpoint, gainPhase);

		double gainMax = gainPhase[1][0], gainMin = gainPhase[1][0];
		double phaseMax = gainPhase[2][0], phaseMin = gainPhase[2][0];
		for (unsigned int i = 0; i < nbpoint; i++) {
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
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, barre, { 255, 255, 255, 255 }, NoColor, 16, 40, 460, center_y);
		barre = "";
		unsigned int initspace = 14;
		for (unsigned int z = 0; z < 30; z++)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "|", { 255, 255, 255, 255 }, NoColor, 16, 50, initspace += 16, center_x);

		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, std::to_string(wmin), { 255, 255, 255, 255 }, NoColor, 10, 30, 472, center_y);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, std::to_string(wmax), { 255, 255, 255, 255 }, NoColor, 10, 530, 472, center_y);

		unsigned int x0 = 50, xmax = 550;
		unsigned int ymingain = 30, ymaxgain = 230;
		unsigned int yminphase = 250, ymaxphase = 450;
		//double pasGraph = (xmax - x0) / nbpoint;
		double ecartRelatif = wmax / wmin;
		unsigned int longeurAxe = xmax - x0;
		double* pasGraph = new double[nbpoint];
		pasGraph[0] = 0;
		double increment = (wmax - wmin) / nbpoint;
		double nbpointParDecade = 50;
		for (unsigned int i = 0; i < 10; i++) {
			pasGraph[i] = ((longeurAxe * log(gainPhase[0][i])) / log(ecartRelatif)) + 250;
			std::cout << std::endl << i << " , " << pasGraph[i] << " , " << gainPhase[0][i];
		}


		for (unsigned int z = x0, n = 0; z < xmax, n < 10; z += (unsigned int)pasGraph[n], n++) {
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "+", { 255, 0, 0, 255 }, NoColor, 8, x0 + z, ymaxgain - (unsigned int)((gainPhase[1][n] / amplitudeGain) * (ymaxgain - ymingain)), center);
			//writetxt(sysinfo, "+", { 0, 255, 0, 255 }, 8, x0 + z, yminphase - ((gainPhase[2][n] / amplitudePhase) * (ymaxphase - yminphase)), center);
		}
		SDL_RenderPresent(sysinfo.screen.renderer);


		delete[] pasGraph;

		for (unsigned int i = 0; i < 3; i++)
			delete[] gainPhase[i];
		delete[] gainPhase;
	}

	IHM::logfileconsole("_ End displayBode _");
}
void createMatrice(IHM& ihm, Sysinfo& sysinfo){
	IHM::logfileconsole("_ Start createMatrice _");
	sysinfo.var.stateScreen = STATESScreateMatrice;
	rendueEcran(sysinfo);

	unsigned int length = 0;


	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Length or height of A : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 50);
	SDL_RenderPresent(sysinfo.screen.renderer);
	length = CinNumberUnsignedInt(sysinfo, "Length or height of A : ", SCREEN_WIDTH / 2, 50);
	ihm.GETsys()->SETeditSizeA(length, length);
	ihm.GETsys()->SETeditSizeB(length, 1);
	ihm.GETsys()->SETeditSizeC(1, length);
	ihm.GETsys()->SETeditSizeD(1, 1);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select,
		sysinfo.allTextes.txtEcranTitre, blended,
		"Length of A : " + std::to_string(ihm.GETsys()->GETA().GETlength()) + " and Height of A : " + std::to_string(ihm.GETsys()->GETA().GETheight()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, nonTransparent, center_x);
	rendueEcran(sysinfo);

	displayStateSystem(ihm, sysinfo);

	for (unsigned int i = 0; i < ihm.GETsys()->GETA().GETlength(); i++){
		for (unsigned int j = 0; j < ihm.GETsys()->GETA().GETheight(); j++){
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 75, center_x);
			SDL_RenderPresent(sysinfo.screen.renderer);
			ihm.GETsys()->SETthisCoefA(i, j, CinNumberDouble(sysinfo, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", SCREEN_WIDTH / 2, 75));
			rendueEcran(sysinfo);
			displayStateSystem(ihm, sysinfo);
		}
	}

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select,
		sysinfo.allTextes.txtEcranTitre, blended,
		"Length of B : " + std::to_string(ihm.GETsys()->GETB().GETlength()) + " and Height of B : " + std::to_string(ihm.GETsys()->GETB().GETlength()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, nonTransparent, center_x);
	rendueEcran(sysinfo);
	displayStateSystem(ihm, sysinfo);

	for (unsigned int i = 0; i < ihm.GETsys()->GETB().GETlength(); i++){
		for (unsigned int j = 0; j < ihm.GETsys()->GETB().GETheight(); j++){
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 125, center_x);
			SDL_RenderPresent(sysinfo.screen.renderer);
			ihm.GETsys()->SETthisCoefB(i, j, CinNumberDouble(sysinfo, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", SCREEN_WIDTH / 2, 125));
			rendueEcran(sysinfo);
			displayStateSystem(ihm, sysinfo);
		}
	}

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select,
		sysinfo.allTextes.txtEcranTitre, blended,
		"Length of C : " + std::to_string(ihm.GETsys()->GETC().GETlength()) + " and Height of C : " + std::to_string(ihm.GETsys()->GETC().GETheight()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, nonTransparent, center_x);
	rendueEcran(sysinfo);
	displayStateSystem(ihm, sysinfo);

	for (unsigned int i = 0; i < ihm.GETsys()->GETC().GETlength(); i++){
		for (unsigned int j = 0; j < ihm.GETsys()->GETC().GETheight(); j++){
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 175, center_x);
			SDL_RenderPresent(sysinfo.screen.renderer);
			ihm.GETsys()->SETthisCoefC(i, j, CinNumberDouble(sysinfo, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", SCREEN_WIDTH / 2, 175));
			rendueEcran(sysinfo);
			displayStateSystem(ihm, sysinfo);
		}
	}

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select,
		sysinfo.allTextes.txtEcranTitre, blended,
		"Length of D : " + std::to_string(ihm.GETsys()->GETD().GETlength()) + " and Height of D : " + std::to_string(ihm.GETsys()->GETD().GETheight()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 200, nonTransparent, center_x);
	rendueEcran(sysinfo);
	displayStateSystem(ihm, sysinfo);

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "coef [0][0] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 225, center_x);
	SDL_RenderPresent(sysinfo.screen.renderer);
	ihm.GETsys()->SETthisCoefD(0, 0, CinNumberDouble(sysinfo, "coef [0][0] = ", SCREEN_WIDTH / 2, 225));
	rendueEcran(sysinfo);
	displayStateSystem(ihm, sysinfo);


	IHM::logfileconsole("_ End createMatrice _");
}
void computeABCD(IHM& ihm, Sysinfo& sysinfo){
	IHM::logfileconsole("_ Start computeABCD _");
	FCTDiscret FCT;
	if (FCT == *ihm.GETfct())
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "TF doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 148, center_y);
	else{
		if (ihm.GETfct()->GETden().GETorder() > ihm.GETfct()->GETnum().GETorder()){
			ihm.GETsys()->calculABCD(*ihm.GETfct());
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "OK", { 0, 255, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 148, center_y);
		}
		else
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "Order of Num >= Den", { 255, 0, 0, 255 }, NoColor, 14, (SCREEN_WIDTH / 2) + 150, 148, center_y);
	}
	SDL_RenderPresent(sysinfo.screen.renderer);
	IHM::logfileconsole("_ End computeABCD _");
}
void displayStateSystem(IHM& ihm, Sysinfo& sysinfo){
	IHM::logfileconsole("_ Start displayStateSystem _");
	unsigned int initspace = 300;
	std::string texte; std::ostringstream stream;
	stream << std::fixed << std::setprecision(4);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Matrix A", { 0, 64, 255, 255 }, NoColor, 16, 100, initspace += 16);
	for (unsigned int i = 0; i < ihm.GETsys()->GETA().GETlength(); i++){
		stream << "|";
		for (unsigned int j = 0; j < ihm.GETsys()->GETA().GETheight(); j++)
			if(ihm.GETsys()->GETA().GETthiscoef(i, j) >= 0)
				stream << "   " << ihm.GETsys()->GETA().GETthiscoef(i, j) << " ";
			else 
				stream << "  -" << abs(ihm.GETsys()->GETA().GETthiscoef(i, j)) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 100, initspace += 16);
	}

	initspace = 100;
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Matrix B", { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	for (unsigned int i = 0; i < ihm.GETsys()->GETB().GETlength(); i++){
		stream << "|";
		for (unsigned int j = 0; j < ihm.GETsys()->GETB().GETheight(); j++)
			stream << " " << ihm.GETsys()->GETB().GETthiscoef(i, j) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	}

	initspace += 32;
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Matrix C", { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	for (unsigned int i = 0; i < ihm.GETsys()->GETC().GETlength(); i++){
		stream << "|";
		for (unsigned int j = 0; j < ihm.GETsys()->GETC().GETheight(); j++)
			stream << " " << ihm.GETsys()->GETC().GETthiscoef(i, j) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	}

	initspace += 32;
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Matrix D", { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);
	stream << "| " << ihm.GETsys()->GETD().GETthiscoef(0, 0) << " |";
	texte = stream.str();
	stream.str("");
	stream.clear();
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16);

	SDL_RenderPresent(sysinfo.screen.renderer);
	IHM::logfileconsole("_ End displayStateSystem _");
}
void createSignal(Sysinfo& sysinfo, Signal& sig){
	IHM::logfileconsole("_ Start createSignal _");
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Number of samples : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 150);
	SDL_RenderPresent(sysinfo.screen.renderer);
	sig.SETnbech(CinNumberUnsignedInt(sysinfo, "Number of samples : ", SCREEN_WIDTH / 2, 150));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Number of samples : " + std::to_string(sig.GETnbech()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, nonTransparent, center_x);
	rendueEcran(sysinfo);

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "DeltaT : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 200, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 200);
	SDL_RenderPresent(sysinfo.screen.renderer);
	sig.SETdeltaT(CinNumberDouble(sysinfo, "DeltaT : ", SCREEN_WIDTH / 2, 200));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "DeltaT : " + std::to_string(sig.GETdeltaT()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 200, nonTransparent, center_x);
	rendueEcran(sysinfo);

	IHM::logfileconsole("_ End createSignal _");
}
void createStep(Sysinfo& sysinfo, Echelon& step){
	IHM::logfileconsole("_ Start createStep _");

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Amplitude : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 70, 250);
	SDL_RenderPresent(sysinfo.screen.renderer);
	step.SETamplitude(CinNumberDouble(sysinfo, "Amplitude : ", SCREEN_WIDTH / 2, 250));
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Amplitude : " + std::to_string(step.GETamplitude()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, center_x);
	rendueEcran(sysinfo);

	IHM::logfileconsole("_ End createStep _");
}
void createRamp(Sysinfo& sysinfo, Rampe& ramp){
	IHM::logfileconsole("_ Start createRamp _");

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Slope : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 250);
	SDL_RenderPresent(sysinfo.screen.renderer);
	ramp.SETslope(CinNumberDouble(sysinfo, "Slope : ", SCREEN_WIDTH / 2, 250));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Slope : " + std::to_string(ramp.GETslope()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, nonTransparent, center_x);
	rendueEcran(sysinfo);

	IHM::logfileconsole("_ End createRamp _");
}
void createSinus(Sysinfo& sysinfo, Sinus& sinus){
	IHM::logfileconsole("_ Start createSinus _");

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Amplitude : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 70, 250);
	SDL_RenderPresent(sysinfo.screen.renderer);
	sinus.SETamplitude(CinNumberDouble(sysinfo, "Amplitude : ", SCREEN_WIDTH / 2, 250));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Amplitude : " + std::to_string(sinus.GETamplitude()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, nonTransparent, center_x);
	rendueEcran(sysinfo);

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Angular velocity (w): ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 300, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 300);
	SDL_RenderPresent(sysinfo.screen.renderer);
	sinus.SETw(CinNumberDouble(sysinfo, "Angular velocity (w): ", SCREEN_WIDTH / 2, 300));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Angular velocity (w): " + std::to_string(sinus.GETw()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 300, nonTransparent, center_x);
	rendueEcran(sysinfo);

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Phase (phi): ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 350, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 70, 350);
	SDL_RenderPresent(sysinfo.screen.renderer);
	sinus.SETdephasage(CinNumberDouble(sysinfo, "Phase (phi): ", SCREEN_WIDTH / 2, 350));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Phase (phi): " + std::to_string(sinus.GETdephasage()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 350, nonTransparent, center_x);
	rendueEcran(sysinfo);

	IHM::logfileconsole("_ End createSinus _");
}
void displayReponseTemp(IHM& ihm, Sysinfo& sysinfo, Signal& sig){
	IHM::logfileconsole("_ Start displayReponseTemp _");
	std::string barre;
	barre = "0";
	for (unsigned int z = 0; z < 100; z++)
		barre += "-";
	barre += ">t(s)";
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, barre, { 255, 255, 255, 255 }, NoColor, 16, 40, 250, center_y);
	barre = "";
	unsigned int initspace = 34;
	for (unsigned int z = 0; z < 30; z++)
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "|", { 255, 255, 255, 255 }, NoColor, 16, 50, initspace += 16, center_x);


	Matrice X0(ihm.GETsys()->GETA().GETlength(), 1);

	double* yOut = new double[sig.GETnbech()];
	ihm.GETsys()->simulation("bin/files/ReponseTemporelle.txt", sig, X0, yOut);


	unsigned int xmin = 50, xmax = 550;
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
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, std::to_string(max), { 255, 0, 0, 255 }, NoColor, 8, 20, 50, center);
	for (unsigned int z = xmin, n = 0; z < xmax, n < sig.GETnbech(); z += pasGraph, n++){
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "|", { 255, 255, 255, 255 }, NoColor, 8, z, y0, center);

		if (sig.GETthiscoef(n) > 0)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, 
				blended, "+", { 255, 0, 0, 255 }, NoColor, 8, z, y0 - (unsigned int)((sig.GETthiscoef(n) / max) * (y0 - ymax)), center);
		else if (sig.GETthiscoef(n) < 0)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "+", { 255, 0, 0, 255 }, NoColor, 8, z, y0 + (unsigned int)((sig.GETthiscoef(n) / min) * (ymin - y0)), center);

		if (yOut[n] > 0)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "+", { 0, 255, 0, 255 }, NoColor, 8, z, y0 - (unsigned int)((yOut[n] / max) * (y0 - ymax)), center);
		else if (yOut[n] < 0)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "+", { 0, 255, 0, 255 }, NoColor, 8, z, y0 + (unsigned int)((yOut[n] / min) * (ymin - y0)), center);

		if (n == 10)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, std::to_string(sig.GETdeltaT() * 10), { 255, 255, 255, 255 }, NoColor, 8, z, y0 + 10, center);
	}
	delete[] yOut;
	SDL_RenderPresent(sysinfo.screen.renderer);
	IHM::logfileconsole("_ Start displayReponseTemp _");
}

void IHM::deleteAll(Sysinfo& sysinfo){
	logfileconsole("*********_________ Start DeleteAll _________*********");
	for (unsigned int i = 1; i < MAX_FONT; i++)
		TTF_CloseFont(sysinfo.allTextes.font[i]);

	deleteDyTabPlayerAndTextures(sysinfo.allTextes.txtEcranTitre, "txtEcranTitre");
	deleteDyTabPlayerAndTextures(sysinfo.allTextes.CreateNumDen, "CreateNumDen");

	deleteDyTabPlayerAndTextures(sysinfo.allButtons.ecranTitre, "ecranTitre");
	deleteDyTabPlayerAndTextures(sysinfo.allButtons.ecranFCT, "ecranFCT");
	deleteDyTabPlayerAndTextures(sysinfo.allButtons.ecranSYSETAT, "ecranSYSETAT");
	SDL_DestroyRenderer(sysinfo.screen.renderer);
	SDL_DestroyWindow(sysinfo.screen.window);
	sysinfo.screen.renderer = nullptr;
	sysinfo.screen.window = nullptr;
	logfileconsole("*********_________ End DeleteAll _________*********");
}

/*
*	End Of File : IHM.cpp
*/
