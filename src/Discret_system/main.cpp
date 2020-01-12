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


#include "IHM.h"
#include "LoadConfig.h"
#include "End.h"
#include "KeyboardMouse.h"

int main(int argc, char *argv[])
{
	Sysinfo sysinfo;
	End::initPtrSysinfo(sysinfo);

	sysinfo.var.argc = argc;
	sysinfo.var.argv = argv;

	try
	{
		LoadConfig::initSysinfo(sysinfo);
		LoadConfig::initSDL(sysinfo.screen, sysinfo.allTextes.font);
	}
	catch (const std::string& msg)
	{
		End::exitError(msg);
	}
	
	/* 
	 * try/catch générale
	 * Utilisé si tous les autres try/catch n'ont pas d'action
	 */
	try
	{
		if (LoadConfig::initfile(sysinfo.fichier))
		{
			IHM::showStartSuccess();

			LoadConfig::loadAllTextures(sysinfo);

			sysinfo.var.stateScreen = STATEecrantitre;
			IHM::rendueEcran(sysinfo);

			IHM::logfileconsole("_ Start mainLoop _");
			while (sysinfo.var.continuer)
			{
				KeyboardMouse::eventSDL(sysinfo);
			}
			End::deleteAll(sysinfo);
			IHM::logfileconsole("_ End mainLoop _");
		}
		else
			return EXIT_FAILURE;
	}
	catch (const std::string & msg)
	{
		End::exitError(msg);
	}
	

	return EXIT_SUCCESS;
}
