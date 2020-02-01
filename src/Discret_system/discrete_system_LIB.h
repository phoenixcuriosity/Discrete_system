/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version: 3.5
	file version 2.2

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


#ifndef init_H
#define init_H

#include "LIB.h"
#include "Texture.h"

/* *********************************************************
						 Constantes
  ********************************************************* */

//--- Constantes concernant l'ecran et la dimension de la fenetre  -----------------------------------------------------------------------------------

// longueur de la fenetre SDL en pixel
const Uint16 SCREEN_WIDTH = 640;

// hauteur de la fenetre SDL en pixel
const Uint16 SCREEN_HEIGHT = 640;

const double Pi = 3.14159265358979323846;

/* *********************************************************
						 Enum
  ********************************************************* */

// différents état de l'écran
enum STATE_TYPE: Uint8
{
	STATEnothing,
	STATEecrantitre,
	STATEfunctionTransfer,
	STATETFcreateNumDen,
	STATETFcreateBode,
	STATETFdisplayBode,
	STATEstateSystem,
	STATESScreateMatrice,
	STATESSsimulate,
	STATEreponseTemporelle,
	STATEclosedLoop,
	STATEtests
};

// spécifications de la séléction
enum SELECT_TYPE: Uint8
{	
	selectnothing,
	NotToSelect,
	selectcreate,
	selectinspect,
	selectmove
};



/* *********************************************************
						Structures
  ********************************************************* */
//---------------------- Structure niveau 1 ---------------------------------------------------------------------------------------------------------
struct Screen
{
	// ptr sur la fenetre crée par la SDL
	SDL_Window *window = nullptr;

	// ptr sur le renderer crée par la SDL
	SDL_Renderer *renderer = nullptr;
};
struct Fichier
{
	const std::string log = "bin/files/log.txt";
	const std::string reponseTemporelle = "bin/files/ReponseTemporelle.txt";
	const std::string bode = "bin/files/Bode.txt";
	const std::string load = "bin/files/load.txt";
};
struct Var
{
	bool waitEvent = true;

	// variable permettant de quitter la boucle principale donc le jeu
	bool continuer = true;

	int argc = 0;

	char** argv = nullptr;

	/*
		état de la sélection du joueur
		enum : Uint8 { selectnothing, NotToSelect, selectcreate, selectinspect, selectmove };
	*/
	SELECT_TYPE select = selectnothing;

	/*
		état de l'écran du joueur
		enum : Uint8 {	STATEnothing, STATEecrantitre,
						STATEfunctionTransfer, STATETFcreateNumDen, STATETFcreateBode, STATETFdisplayBode,
						STATEstateSystem, STATESScreateMatrice, STATESSsimulate, STATEreponseTemporelle,
						STATEclosedLoop, STATEtests
					}
	*/
	STATE_TYPE stateScreen = STATEnothing;

	Uint16 mouse_x = 0;
	Uint16 mouse_y = 0;
	Uint16 ywheel = 0;
	Uint16 xwheel = 0;
};
struct AllTextures
{
	
};
struct AllTextes
{
	TTF_Font *font[MAX_FONT];

	std::unordered_map<std::string, Texte*> txtEcranTitre;
	std::unordered_map<std::string, Texte*> CreateNumDen;
};
struct AllButtons
{
	std::unordered_map<std::string, ButtonTexte*> ecranTitre;
	std::unordered_map<std::string, ButtonTexte*> ecranFCT;
	std::unordered_map<std::string, ButtonTexte*> ecranSYSETAT;
};
//---------------------- Structure niveau 0 ---------------------------------------------------------------------------------------------------------
struct Sysinfo 
{
	// contient les données en rapport à la SDL 
	Screen screen;

	// contient des variables non organisées
	Var var;

	// Fichiers du projet
	Fichier fichier;

	// contient toutes les images
	AllTextures allTextures;

	// contient tous les textes
	AllTextes allTextes;

	// contient tous les boutons
	AllButtons allButtons;

	FCTDiscret* fctDiscret = nullptr;

	SYSETATDiscret* sysetatDiscret = nullptr;
};


#endif
