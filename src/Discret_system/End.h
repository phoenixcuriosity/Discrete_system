/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version: 3.1
	file version 2.1

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

#ifndef End_H
#define End_H

#include "discrete_system_LIB.h"
#include "IHM.h"

class End
{
public:

	/*
	 * NAME : initPtrSysinfo
	 * ROLE : Initialisation du Ptr pour exitError
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : ptrSysinfo* = &sysinfo
	 * RETURNED VALUE    : void
	 */
	static void initPtrSysinfo
	(
		Sysinfo& sysinfo
	);

	/*
	 * NAME : deleteFCTDiscret
	 * ROLE : Déallocation du Ptr
	 * INPUT  PARAMETERS : FCTDiscret* : Ptr sur un objet FCTDiscret
	 * OUTPUT PARAMETERS : FCTDiscret* = nullptr
	 * RETURNED VALUE    : void
	 */
	static void deleteFCTDiscret
	(
		FCTDiscret* fCTDiscret
	);

	/*
	 * NAME : deleteSYSETATDiscret
	 * ROLE : Déallocation du Ptr
	 * INPUT  PARAMETERS : FCTDiscret* : Ptr sur un objet SYSETATDiscret
	 * OUTPUT PARAMETERS : SYSETATDiscret* = nullptr
	 * RETURNED VALUE    : void
	 */
	static void deleteSYSETATDiscret
	(
		SYSETATDiscret* sysetatDiscret
	);

	/*
	 * NAME : exitError
	 * ROLE : Cette fonction est appelée si une erreur survient
	 * ROLE : Appel de la fonction deleteAll et termine le programme ...
	 * ROLE : ... avec le code erreur EXIT_FAILURE
	 * INPUT  PARAMETERS : const std::string& : msg d'erreur
	 * OUTPUT PARAMETERS : EXIT_FAILURE
	 * RETURNED VALUE    : void
	 */
	static void exitError
	(
		const std::string& msg
	);

	/*
	 * NAME : deleteAll
	 * ROLE : Déallocation des Ptr et des structures/objets 
	 * INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
	 * OUTPUT PARAMETERS : delete Ptr
	 * RETURNED VALUE    : void
	 */
	static void deleteAll
	(
		Sysinfo&
	);

	static void deleteTexture
	(
		std::unordered_map<std::string, Texture*>& unmap,
		const std::string& name
	);

	static void deleteTexte
	(
		std::unordered_map<std::string, Texte*>& unmap,
		const std::string& name
	);

	static void deleteButtonTexte
	(
		std::unordered_map<std::string, ButtonTexte*>& unmap,
		const std::string& name
	);
};

#endif // !End_H

/*
*	End Of File : End.h
*/