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


#ifndef init_H
#define init_H

#include "LIB.h"
#include "Texture.h"

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;

const SDL_Color Black = { 0, 0, 0, 255 };
const SDL_Color White = { 255, 255, 255, 255 };
const SDL_Color Red = { 255, 0, 0, 255 };
const SDL_Color Green = { 0, 255, 0, 255 };
const SDL_Color Blue = { 0, 0, 255, 255 };
const SDL_Color WriteColorButton = { 255, 64, 0, 255 }; // orange
const SDL_Color BackColorButton = { 64, 64, 64, 255 }; // gris
const SDL_Color NoColor = { 0, 0, 0, 0 };

enum { normal, blended, shaded };
enum {
	STATEnothing, STATEecrantitre,
	STATEfunctionTransfer, STATETFcreateNumDen, STATETFcreateBode, STATETFdisplayBode,
	STATEstateSystem, STATESScreateMatrice, STATESSsimulate, STATEreponseTemporelle,
	STATEclosedLoop, STATEtests
};
enum { selectnothing, NotToSelect, selectcreate, selectinspect, selectmove };
enum { nocenter, center_x, center_y, center };

struct screen {
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
};
struct fichier {
	const std::string log = "bin/files/log.txt";
	const std::string reponseTemporelle = "bin/files/ReponseTemporelle.txt";
	const std::string bode = "bin/files/Bode.txt";
	const std::string load = "bin/files/load.txt";
};
struct var {
	unsigned int select = selectnothing;
	unsigned int statescreen = 0; // selectnothing par défaut

	unsigned int mouse_x = 0;
	unsigned int mouse_y = 0;
	unsigned int ywheel = 0;
	unsigned int xwheel = 0;

	bool continuer = true;
};
struct texture {
	TTF_Font *font[80];
	std::vector<Texture*> txtEcranTitre;
};
struct button {
	std::vector<Buttons*> ecranTitre;
	std::vector<Buttons*> ecranFCT;
	std::vector<Buttons*> ecranSYSETAT;
};
struct sysinfo {
	var variables;
	screen ecran;
	texture allTextures;
	button allButtons;
};


#endif
