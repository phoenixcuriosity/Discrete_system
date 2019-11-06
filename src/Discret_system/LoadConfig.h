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

#ifndef LoadConfig_H
#define LoadConfig_H

#include "discrete_system_LIB.h"

class LoadConfig
{

public:

	/*
	 * NAME : initSysinfo
	 * ROLE : Initialisation des structures et variables de la strucutre Sysinfo
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : structure initialisée
	 * RETURNED VALUE    : void
	 */
	static void initSysinfo(Sysinfo& sysinfo);

	/*
	 * NAME : initfile
	 * ROLE : Initialisation des fichiers du projet
	 * INPUT  PARAMETERS : struct Fichier& : structure globale des fichiers
	 * OUTPUT PARAMETERS : fichiers initialisés
	 * RETURNED VALUE    : bool : false -> si erreur / true -> si aucune erreur
	 */
	static bool initfile(Fichier& file);
	
	/*
	 * NAME : initsdl
	 * ROLE : Initialisation des variables de la librairie SDL
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : variables SDL initialisées
	 * RETURNED VALUE    : void
	 */
	static void initsdl(Sysinfo& sysinfo);

	/*
	 * NAME : loadAllTextures
	 * ROLE : Chargement des Textures/Boutons/Textes du programme
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : Chargement des Textures/Boutons/Textes
	 * RETURNED VALUE    : void
	 */
	static void loadAllTextures(Sysinfo& sysinfo);

};

#endif // !LoadConfig_H

/*
*	End Of File : LoadConfig.h
*/

