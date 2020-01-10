/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version: 3.2
	file version 1.0

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

#include "KeyboardMouse.h"
#include "discrete_system_LIB.h"
#include "IHM.h"
#include "End.h"

/*
* NAME : eventSDL
* ROLE : Recherche infini des évenements d'entré de type SDL_event : souris, clavier
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : évenements d'entré utilisateur
* RETURNED VALUE    : void
*/
void KeyboardMouse::eventSDL(Sysinfo& sysinfo)
{
	SDL_Event event;
	
	SDL_WaitEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:	// permet de quitter le jeu
		sysinfo.var.continuer = 0;
		break;
	case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
		switch (event.key.keysym.sym)
		{




		case SDLK_ESCAPE:
			keySDLK_ESCAPE();
			break;
		case SDLK_BACKSPACE:
			keySDLK_BACKSPACE(sysinfo);
			break;
		case SDLK_RETURN:
			keySDLK_RETURN(sysinfo);
			break;
		case SDLK_KP_ENTER:
			keySDLK_KP_ENTER(sysinfo);
			break;


		case SDLK_KP_PERIOD:
			keySDLK_KP_PERIOD(sysinfo);
			break;
		case SDLK_KP_0:
			keySDLK_KP_0(sysinfo);
			break;
		case SDLK_KP_1:
			keySDLK_KP_1(sysinfo);
			break;
		case SDLK_KP_2:
			keySDLK_KP_2(sysinfo);
			break;
		case SDLK_KP_3:
			keySDLK_KP_3(sysinfo);
			break;
		case SDLK_KP_4:
			keySDLK_KP_4(sysinfo);
			break;
		case SDLK_KP_5:
			keySDLK_KP_5(sysinfo);
			break;
		case SDLK_KP_6:
			keySDLK_KP_6(sysinfo);
			break;
		case SDLK_KP_7:
			keySDLK_KP_7(sysinfo);
			break;
		case SDLK_KP_8:
			keySDLK_KP_8(sysinfo);
			break;
		case SDLK_KP_9:
			keySDLK_KP_9(sysinfo);
			break;
		default:
			/* N/A */
			break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
		mouse(sysinfo, event);
		break;
	default:
		/* N/A */
		break;
	}
}






void KeyboardMouse::keySDLK_ESCAPE()
{
	End::exitError("[INFO]__: keySDLK_ESCAPE");
}
void KeyboardMouse::keySDLK_BACKSPACE(Sysinfo& sysinfo)
{
	
}
void KeyboardMouse::keySDLK_RETURN(Sysinfo& sysinfo)
{
	
}
void KeyboardMouse::keySDLK_KP_ENTER(Sysinfo& sysinfo)
{
	
}

void KeyboardMouse::keySDLK_KP_PERIOD(Sysinfo& sysinfo)
{

}


void KeyboardMouse::keySDLK_KP_0(Sysinfo& sysinfo)
{

}

void KeyboardMouse::keySDLK_KP_1(Sysinfo& sysinfo)
{
	
}
void KeyboardMouse::keySDLK_KP_2(Sysinfo& sysinfo)
{
	
}
void KeyboardMouse::keySDLK_KP_3(Sysinfo& sysinfo)
{
	
}
void KeyboardMouse::keySDLK_KP_4(Sysinfo& sysinfo)
{
	
}
void KeyboardMouse::keySDLK_KP_5(Sysinfo& sysinfo)
{
	
}
void KeyboardMouse::keySDLK_KP_6(Sysinfo& sysinfo)
{
	
}
void KeyboardMouse::keySDLK_KP_7(Sysinfo& sysinfo)
{
	
}
void KeyboardMouse::keySDLK_KP_8(Sysinfo& sysinfo)
{
	
}
void KeyboardMouse::keySDLK_KP_9(Sysinfo& sysinfo)
{
	
}


void KeyboardMouse::mouse(Sysinfo& sysinfo, SDL_Event event)
{
	/*
	Handle Mouse Event
	BUTTON_LEFT
	BUTTON_RIGHT

	*/


	if (event.button.button == SDL_BUTTON_LEFT)
	{


		if (sysinfo.var.stateScreen == STATEecrantitre)
		{
			for (unsigned int i = 0; i < sysinfo.allButtons.ecranTitre.size(); i++)
			{
				// recherche si une bouton est dans ces coordonnées


				// boutons du main menu
				if (
					sysinfo.allButtons.ecranTitre["Transfer Function"]
						->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y)
					)
				{
					sysinfo.var.stateScreen = STATEfunctionTransfer;
					IHM::rendueEcran(sysinfo);
					break;
				}
				else if (
							sysinfo.allButtons.ecranTitre["State System"]
								->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y)
						)
				{
					sysinfo.var.stateScreen = STATEstateSystem;
					IHM::rendueEcran(sysinfo);
					break;
				}
				else if (
							sysinfo.allButtons.ecranTitre["Closed Loop"]
								->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y)
						)
				{
					// Todo
					break;
				}
				else if (
							sysinfo.allButtons.ecranTitre["Quit"]
								->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y)
						)
				{
					sysinfo.var.continuer = false;
					break;
				}
			}
		}





		else if (
					sysinfo.var.stateScreen == STATEfunctionTransfer
				 || sysinfo.var.stateScreen == STATETFcreateNumDen
				 || sysinfo.var.stateScreen == STATETFcreateBode
				 || sysinfo.var.stateScreen == STATETFdisplayBode
				)
		{
			for (unsigned int i = 0; i < sysinfo.allButtons.ecranFCT.size(); i++)
			{
				if	(	sysinfo.allButtons.ecranFCT["Main menu"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y)
					 ||	sysinfo.allButtons.ecranFCT["Main menu (1)"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y)
					 || sysinfo.allButtons.ecranFCT["Main menu (2)"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y)
					)
				{
					sysinfo.var.stateScreen = STATEecrantitre;
					IHM::rendueEcran(sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranFCT["Create the Transfer Function"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{
					IHM::CreateNumDen(sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranFCT["Display the Transfer Function"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{
					IHM::displayTF(sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranFCT["Jury"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{
					IHM::displayJury(sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranFCT["Bode"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{
					IHM::displayBode(sysinfo);
					break;
				}
			}
		}





		else if (sysinfo.var.stateScreen == STATEstateSystem
			|| sysinfo.var.stateScreen == STATESScreateMatrice
			|| sysinfo.var.stateScreen == STATESSsimulate
			|| sysinfo.var.stateScreen == STATEreponseTemporelle
			)
		{
			for (unsigned int i = 0; i < sysinfo.allButtons.ecranSYSETAT.size(); i++)
			{
				if	(	sysinfo.allButtons.ecranSYSETAT["Main menu"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y)
					 ||	sysinfo.allButtons.ecranSYSETAT["Main menu (1)"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y)
					 ||	sysinfo.allButtons.ecranSYSETAT["Main menu (2)"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y)
					 || sysinfo.allButtons.ecranSYSETAT["Main menu (3)"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y)
					)
				{
					sysinfo.var.stateScreen = STATEecrantitre;
					IHM::rendueEcran(sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT["Edit Matrix A, B, C and D"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{
					IHM::createMatrice(sysinfo);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT["Compute A, B, C and D"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{

					if (sysinfo.fctDiscret->GETden().GETorder() > 0)
						IHM::computeABCD(sysinfo);
					else
						Texte::writeTexte
						(sysinfo.screen.renderer, sysinfo.allTextes.font,
							blended, "Order of Denominator is 0", { 255, 0, 0, 255 }, NoColor,
							16, (SCREEN_WIDTH / 2) + 130, 148,
							no_angle, center_y
						);

					SDL_RenderPresent(sysinfo.screen.renderer);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT["Display the State System"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{
					if (sysinfo.sysetatDiscret == nullptr)
						Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, blended,
							"SS doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 196, no_angle, center_y);
					else {
						IHM::displayStateSystem(sysinfo);
						Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, blended,
							"OK", { 0, 255, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 196, no_angle, center_y);
					}
					SDL_RenderPresent(sysinfo.screen.renderer);

					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT["Simulate"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{
					if (sysinfo.sysetatDiscret == nullptr)
						Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, blended,
							"SS doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 244, no_angle, center_y);
					else {
						sysinfo.var.stateScreen = STATESSsimulate;
						IHM::rendueEcran(sysinfo);

					}
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT["Step"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{
					sysinfo.allButtons.ecranSYSETAT["Step"]->changeOn();
					IHM::rendueEcran(sysinfo);
					Echelon step;
					IHM::createSignal(sysinfo, step);
					IHM::createStep(sysinfo, step);
					sysinfo.var.stateScreen = STATEreponseTemporelle;
					IHM::rendueEcran(sysinfo);
					IHM::displayReponseTemp(sysinfo, step);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT["Ramp"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{
					sysinfo.allButtons.ecranSYSETAT["Ramp"]->changeOn();
					IHM::rendueEcran(sysinfo);
					Rampe ramp;
					IHM::createSignal(sysinfo, ramp);
					IHM::createRamp(sysinfo, ramp);
					sysinfo.var.stateScreen = STATEreponseTemporelle;
					IHM::rendueEcran(sysinfo);
					IHM::displayReponseTemp(sysinfo, ramp);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT["Sinus"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{
					//Sinus sinus(500, 0.1, 1, 1, 0);
					sysinfo.allButtons.ecranSYSETAT["Sinus"]->changeOn();
					IHM::rendueEcran(sysinfo);
					Sinus sinus;
					IHM::createSignal(sysinfo, sinus);
					IHM::createSinus(sysinfo, sinus);
					sysinfo.var.stateScreen = STATEreponseTemporelle;
					IHM::rendueEcran(sysinfo);
					IHM::displayReponseTemp(sysinfo, sinus);
					break;
				}
				else if (sysinfo.allButtons.ecranSYSETAT["Import Signal"]
							->searchButtonTexte(sysinfo.var.stateScreen, event.button.x, event.button.y))
				{
					sysinfo.allButtons.ecranSYSETAT["Import Signal"]->changeOn();
					IHM::rendueEcran(sysinfo);
					break;
				}
			}
		}
	}
}
unsigned int KeyboardMouse::CinNumberUnsignedInt(Sysinfo& sysinfo, const std::string& msg, unsigned int x, unsigned int y)
{
	bool continuer = true;
	unsigned int number = 0;
	int8_t digit = 0;
	SDL_Event event;
	int SDL_EnableUNICODE(1); // on azerty

	while (continuer) {
		SDL_WaitEvent(&event);
		switch (event.type) {
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
			if (continuer) {
				if (digit != -1) {
					number = (number * 10) + digit;
					digit = -1;
					IHM::rendueEcran(sysinfo);
					Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
						blended, "Press ENTER to validate", { 255, 0, 0, 255 }, NoColor, 16, 0, 50, no_angle);
					Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
						blended, "Press Backspace to retry", { 255, 0, 0, 255 }, NoColor, 16, 0, 66, no_angle);
					Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
						blended, msg + std::to_string(number), { 0, 64, 255, 255 }, NoColor, 18, x, y, no_angle, center_x);
					SDL_RenderPresent(sysinfo.screen.renderer);
				}
			}
			break;
		}
	}
	return number;
}



double KeyboardMouse::CinNumberDouble(Sysinfo& sysinfo, const std::string& msg, unsigned int x, unsigned int y) {
	bool continuer = true, postive = true, puissancePositive = true;
	double number = 0, digit = 0;
	unsigned int p = 1;
	SDL_Event event;
	int SDL_EnableUNICODE(1); // on azerty

	while (continuer) {
		SDL_WaitEvent(&event);
		switch (event.type) {
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
			if (continuer) {
				if (digit != -1) {
					IHM::rendueEcran(sysinfo);
					Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
						blended, "Press ENTER to validate", { 255, 0, 0, 255 }, NoColor, 16, 0, 50, no_angle);
					Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
						blended, "Press Backspace to retry", { 255, 0, 0, 255 }, NoColor, 16, 0, 66, no_angle);

					if (puissancePositive) {
						number = (number * 10) + digit;
						if (!postive)
							number = -number;
						Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
							blended, msg + std::to_string(number), { 0, 64, 255, 255 }, NoColor, 18, x, y, no_angle, center_x);
					}
					else {
						number += (digit / pow(10, p));
						p++;
						if (!postive)
							number = -number;
						Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
							blended, msg + std::to_string(number), { 0, 64, 255, 255 }, NoColor, 18, x, y, no_angle, center_x);
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