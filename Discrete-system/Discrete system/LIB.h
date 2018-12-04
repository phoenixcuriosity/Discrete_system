/*

	Discrete_system
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:2.11

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


#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <iomanip>
#include <vector>

#include "bin/SDL2-2.0.6/include/SDL.h"
#include "bin/SDL2-2.0.6/include/SDL_ttf.h"
#include "bin/SDL2-2.0.6/include/SDL_image.h"

typedef struct Screen Screen;
typedef struct Fichier Fichier;
typedef struct Var Var;
typedef struct AllTextures AllTextures;
typedef struct AllTextes AllTextes;
typedef struct AllButtons AllButtons;
typedef struct Sysinfo Sysinfo;

class IHM;
class Complexe;
class FCTDiscret;
class Matrice;
class Polynome;
class Signal;
class SYSETATDiscret;
class Texture;
class Texte;
class ButtonImage;
class ButtonTexte;


#endif