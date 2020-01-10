/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version: 3.2
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

#ifndef IHM_H
#define IHM_H

#include "LIB.h"
#include "FCTDiscret.h"
#include "SYSETATDiscret.h"
#include "Signal.h"
#include "Complexe.h"
#include "discrete_system_LIB.h"
#include "Texture.h"


class IHM
{
public:

	/*
	 * NAME : showStartSuccess
	 * ROLE : Affiche sur la console si le programme à réussi à démarrer
	 * INPUT  PARAMETERS : void
	 * OUTPUT PARAMETERS : Affichage sur la console et dans le fichier log
	 * RETURNED VALUE    : void
	 */
	static void showStartSuccess();

	/*
	 * NAME : logfileconsole
	 * ROLE : Affiche sur la console et dans le fichier log le std::string en entrée
	 * INPUT  PARAMETERS : const std::string& msg : le message en entrée 
	 * OUTPUT PARAMETERS : Affichage sur la console et dans le fichier log
	 * RETURNED VALUE    : void
	 */
	static void logfileconsole(const std::string& msg);

public:

	
	static void rendueEcran(Sysinfo&);
	static void rendueEcranFCT(Sysinfo& sysinfo);
	static void rendueEcranSYSETAT(Sysinfo& sysinfo);

	
	static void CreateNumDen(Sysinfo& sysinfo);
	static void displayTF(Sysinfo& sysinfo);
	static void displayJury(Sysinfo& sysinfo);
	static void displayBode(Sysinfo& sysinfo);
	static void createMatrice(Sysinfo& sysinfo);
	static void computeABCD(Sysinfo& sysinfo);
	static void displayStateSystem(Sysinfo& sysinfo);
	static void createSignal(Sysinfo& sysinfo, Signal& sig);
	static void createStep(Sysinfo& sysinfo, Echelon& step);
	static void createRamp(Sysinfo& sysinfo, Rampe& ramp);
	static void createSinus(Sysinfo& sysinfo, Sinus& sinus);
	static void displayReponseTemp(Sysinfo& sysinfo, Signal& sig);
};


#endif

/*
*	End Of File : IHM.h
*/
