/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version: 3.1
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

#ifndef KeyboardMouse_H
#define KeyboardMouse_H

#include "LIB.h"

class KeyboardMouse
{
public:


	/*
	* NAME : eventSDL
	* ROLE : Recherche infini des évenements d'entré de type SDL_event : souris, clavier
	* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	* OUTPUT PARAMETERS : évenements d'entré utilisateur
	* RETURNED VALUE    : void
	*/
	static void eventSDL(Sysinfo& sysinfo);


public:
	/* *********************************************************
	 *			KeyboardMouse::STATIC::UNE TOUCHE			   *
	 ********************************************************* */

	static void keySDLK_ESCAPE();
	static void keySDLK_BACKSPACE(Sysinfo& sysinfo);
	static void keySDLK_RETURN(Sysinfo& sysinfo);
	static void keySDLK_KP_ENTER(Sysinfo& sysinfo);


	static void keySDLK_KP_PERIOD(Sysinfo&);
	static void keySDLK_KP_0(Sysinfo&);
	static void keySDLK_KP_1(Sysinfo&);
	static void keySDLK_KP_2(Sysinfo&);
	static void keySDLK_KP_3(Sysinfo&);
	static void keySDLK_KP_4(Sysinfo&);
	static void keySDLK_KP_5(Sysinfo&);
	static void keySDLK_KP_6(Sysinfo&);
	static void keySDLK_KP_7(Sysinfo&);
	static void keySDLK_KP_8(Sysinfo&);
	static void keySDLK_KP_9(Sysinfo&);


public:
	/* *********************************************************
	 *			KeyboardMouse::STATIC::SOURIS				   *
	 ********************************************************* */

	 /*
	 * NAME : mouse
	 * ROLE : Dispatch entre clique droit ou clique gauche
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * INPUT  PARAMETERS : SDL_Event : l'évenement du clique
	 * OUTPUT PARAMETERS : choix du clique
	 * RETURNED VALUE    : void
	 */
	static void mouse(Sysinfo&, SDL_Event);

	static unsigned int CinNumberUnsignedInt(Sysinfo&, const std::string& msg, unsigned int, unsigned int);
	static double CinNumberDouble(Sysinfo&, const std::string& msg, unsigned int, unsigned int);

};

#endif /* KeyboardMouse_H */


/*
*	End Of File : KeyboardMouse.h
*/