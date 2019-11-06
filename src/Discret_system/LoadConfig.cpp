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

#include "LoadConfig.h"
#include "IHM.h"


/*
* NAME : initSysinfo
* ROLE : Initialisation des structures et variables de la strucutre Sysinfo
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : structure initialisée
* RETURNED VALUE    : void
*/
void LoadConfig::initSysinfo(Sysinfo& sysinfo)
{

}


/*
 * NAME : initfile
 * ROLE : Initialisation des fichiers du projet
 * INPUT  PARAMETERS : struct Fichier& : structure globale des fichiers
 * OUTPUT PARAMETERS : Affichage de la map sur la fenetre "mainMap"
 * RETURNED VALUE    : bool : false -> si erreur / true -> si aucune erreur
 */
bool LoadConfig::initfile(Fichier& file)
{
	/*
	initialisation des Fichiers
	tests d'ouverture
	*/
	std::ofstream log(file.log);
	if (log)
	{
		/* N/A */
	}
	else
	{
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le Fichier : " << file.log;
		return false;
	}

	std::ofstream reponseTemporelle(file.reponseTemporelle);
	if (reponseTemporelle)
	{
		/* N/A */
	}
	else
	{
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le Fichier : " << file.reponseTemporelle;
		return false;
	}

	std::ofstream bode(file.bode);
	if (bode)
	{
		/* N/A */
	}
	else
	{
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le Fichier : " << file.bode;
		return false;
	}

	std::ofstream load(file.load, std::ios::app);
	if (load)
	{
		/* N/A */
	}
	else 
	{
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le Fichier : " << file.load;
		return false;
	}
	return true;
}

/*
* NAME : initsdl
* ROLE : Initialisation des variables de la librairie SDL
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : variables SDL initialisées
* RETURNED VALUE    : void
*/
void LoadConfig::initsdl(Sysinfo& sysinfo)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << std::endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
	}	
	else
	{
		sysinfo.screen.window = SDL_CreateWindow("Discret System", 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (sysinfo.screen.window == nullptr)
		{
			SDL_Quit();
		}	
		else
			IHM::logfileconsole("CreateWindow Success");

		sysinfo.screen.renderer = SDL_CreateRenderer(sysinfo.screen.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (sysinfo.screen.renderer == nullptr)
		{
			SDL_DestroyWindow(sysinfo.screen.window);
			SDL_Quit();
		}
		else
			IHM::logfileconsole("CreateRenderer Success");

		if (TTF_Init() != 0)
		{
			SDL_DestroyRenderer(sysinfo.screen.renderer);
			SDL_DestroyWindow(sysinfo.screen.window);
			SDL_Quit();
		}
		else
			IHM::logfileconsole("TTF_Init Success");


		const std::string fontFile = "arial.ttf";

		for (unsigned int i = 1; i < MAX_FONT; i++)
			sysinfo.allTextes.font[i] = TTF_OpenFont(fontFile.c_str(), i);

		IHM::logfileconsole("SDL_Init Success");
	}
}

/*
* NAME : loadAllTextures
* ROLE : Chargement des Textures/Boutons/Textes du programme
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : Chargement des Textures/Boutons/Textes
* RETURNED VALUE    : void
*/
void loadAllTextures(Sysinfo& sysinfo)
{

	// ______Writetxt_____ 
	sysinfo.var.stateScreen = STATEecrantitre;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select,
		sysinfo.allTextes.txtEcranTitre, blended, "Dev version: 2.11", White, NoColor, 16, 0, 0, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select,
		sysinfo.allTextes.txtEcranTitre, blended, "Developed by SAUTER Robin", White, NoColor, 16, 0, 16, nonTransparent);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select,
		sysinfo.allTextes.txtEcranTitre, blended, "Discret System", { 0, 255, 255, 255 }, NoColor, 28, SCREEN_WIDTH / 2, 25, nonTransparent, center_x);


	sysinfo.var.stateScreen = STATEfunctionTransfer;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Transfert Function", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, nonTransparent, center_x);

	sysinfo.var.stateScreen = STATETFcreateNumDen;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Create the Transfer Function", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, nonTransparent, center_x);

	sysinfo.var.stateScreen = STATETFcreateBode;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Create Bode", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, nonTransparent, center_x);

	sysinfo.var.stateScreen = STATETFdisplayBode;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Display Bode", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, nonTransparent, center_x);

	sysinfo.var.stateScreen = STATEstateSystem;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "State System", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, nonTransparent, center_x);

	sysinfo.var.stateScreen = STATESScreateMatrice;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Create Matrix A, B, C and D", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, nonTransparent, center_x);

	sysinfo.var.stateScreen = STATESSsimulate;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Simulate", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, nonTransparent, center_x);

	sysinfo.var.stateScreen = STATEreponseTemporelle;
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Simulation", { 0, 255, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 0, nonTransparent, center_x);

	// ______Buttons_____
	sysinfo.var.stateScreen = STATEecrantitre;
	int spacemenu = 64, initspacemenu = 200;

	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranTitre,
		shaded, "Transfer Function", WriteColorButton, BackColorButton, 26, SCREEN_WIDTH / 2, initspacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranTitre,
		shaded, "State System", WriteColorButton, BackColorButton, 26, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranTitre,
		shaded, "Closed Loop", WriteColorButton, BackColorButton, 26, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranTitre,
		shaded, "Quit", WriteColorButton, BackColorButton, 26, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);

	sysinfo.var.stateScreen = STATEfunctionTransfer;
	spacemenu = 48, initspacemenu = 100;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranFCT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0, nonTransparent);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranFCT,
		shaded, "Create the Transfer Function", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranFCT,
		shaded, "Display the Transfer Function", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranFCT,
		shaded, "Jury", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranFCT,
		shaded, "Bode", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);

	sysinfo.var.stateScreen = STATETFcreateBode;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranFCT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0, nonTransparent);

	sysinfo.var.stateScreen = STATETFdisplayBode;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranFCT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0, nonTransparent);



	sysinfo.var.stateScreen = STATEstateSystem;
	spacemenu = 48, initspacemenu = 100;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0, nonTransparent);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Edit Matrix A, B, C and D", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Compute A, B, C and D", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Display the State System", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Simulate", WriteColorButton, BackColorButton, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, nonTransparent, center);

	sysinfo.var.stateScreen = STATESScreateMatrice;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0, nonTransparent);

	sysinfo.var.stateScreen = STATESSsimulate;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0, nonTransparent);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Step", WriteColorButton, BackColorButton, 24, 100, 100, nonTransparent);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Ramp", WriteColorButton, BackColorButton, 24, 200, 100, nonTransparent);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Sinus", WriteColorButton, BackColorButton, 24, 300, 100, nonTransparent);
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Import Signal", WriteColorButton, BackColorButton, 24, 400, 100, nonTransparent);

	sysinfo.var.stateScreen = STATEreponseTemporelle;
	ButtonTexte::createButtonTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allButtons.ecranSYSETAT,
		shaded, "Main menu", WriteColorButton, BackColorButton, 24, 0, 0, nonTransparent);

}


/*
*	End Of File : LoadConfig.cpp
*/
