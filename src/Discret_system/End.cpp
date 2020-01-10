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

#include "End.h"
#include "IHM.h"
#include "FCTDiscret.h"
#include "SYSETATDiscret.h"


/* **********************************************************
 *					 Variables Globale						*
 ********************************************************** */

Sysinfo* ptrSysinfo = nullptr;

/* **********************************************************
 *						 Fonctions							*
 ********************************************************** */

void End::initPtrSysinfo(Sysinfo& sysinfo)
{
	ptrSysinfo = &sysinfo;
}

/*
* NAME : deleteFCTDiscret
* ROLE : Déallocation du Ptr
* INPUT  PARAMETERS : FCTDiscret* : Ptr sur un objet FCTDiscret
* OUTPUT PARAMETERS : FCTDiscret* = nullptr
* RETURNED VALUE    : void
*/
void End::deleteFCTDiscret(FCTDiscret* fctDiscret)
{
	/* Erase last FCT */
	if (fctDiscret != nullptr)
	{
		delete fctDiscret;
	}
	else
	{
		/* N/A */
	}
}

/*
* NAME : deleteSYSETATDiscret
* ROLE : Déallocation du Ptr
* INPUT  PARAMETERS : FCTDiscret* : Ptr sur un objet SYSETATDiscret
* OUTPUT PARAMETERS : SYSETATDiscret* = nullptr
* RETURNED VALUE    : void
*/
void End::deleteSYSETATDiscret(SYSETATDiscret* sysetatDiscret)
{
	/* Erase previous sysinfo.sysetatDiscret */
	if (sysetatDiscret != nullptr)
	{
		delete sysetatDiscret;
	}
	else
	{
		/* N/A */
	}
}

/*
* NAME : exitError
* ROLE : Cette fonction est appelée si une erreur survient
* ROLE : Appel de la fonction deleteAll et termine le programme ...
* ROLE : ... avec le code erreur EXIT_FAILURE
* INPUT  PARAMETERS : const std::string& : msg d'erreur
* OUTPUT PARAMETERS : EXIT_FAILURE
* RETURNED VALUE    : void
*/
void End::exitError(const std::string& msg)
{
	IHM::logfileconsole(msg);
	deleteAll(*ptrSysinfo);
	IHM::logfileconsole("last msg before exit : " + msg);
	exit(EXIT_FAILURE);
}

/*
* NAME : deleteAll
* ROLE : Déallocation des Ptr et des structures/objets
* INPUT  PARAMETERS : struct Sysinfo& : structure globale du programme
* OUTPUT PARAMETERS : delete Ptr
* RETURNED VALUE    : void
*/
void End::deleteAll(Sysinfo& sysinfo)
{
	IHM::logfileconsole("*********_________ Start DeleteAll _________*********");
	for (unsigned int i = 1; i < MAX_FONT; i++)
		TTF_CloseFont(sysinfo.allTextes.font[i]);

	deleteTexte(sysinfo.allTextes.txtEcranTitre, "txtEcranTitre");
	deleteTexte(sysinfo.allTextes.CreateNumDen, "CreateNumDen");

	deleteButtonTexte(sysinfo.allButtons.ecranTitre, "ecranTitre");
	deleteButtonTexte(sysinfo.allButtons.ecranFCT, "ecranFCT");
	deleteButtonTexte(sysinfo.allButtons.ecranSYSETAT, "ecranSYSETAT");

	deleteFCTDiscret(sysinfo.fctDiscret);
	deleteSYSETATDiscret(sysinfo.sysetatDiscret);

	SDL_DestroyRenderer(sysinfo.screen.renderer);
	SDL_DestroyWindow(sysinfo.screen.window);
	sysinfo.screen.renderer = nullptr;
	sysinfo.screen.window = nullptr;
	IHM::logfileconsole("*********_________ End DeleteAll _________*********");
}

void End::deleteTexture(std::unordered_map<std::string, Texture*>& unmap, const std::string& name)
{
	for (const auto& n : unmap)
	{
		if (n.second != nullptr)
		{
			IHM::logfileconsole("[INFO]___: Delete " + name + " name = " + n.second->GETname() + " Success");
			delete n.second;
		}
		else
		{
			/* N/A */
		}
	}
}

void End::deleteTexte(std::unordered_map<std::string, Texte*>& unmap, const std::string& name)
{
	for (const auto& n : unmap)
	{
		if (n.second != nullptr)
		{
			IHM::logfileconsole("[INFO]___: Delete " + name + " name = " + n.second->GETname() + " Success");
			delete n.second;
		}
		else
		{
			/* N/A */
		}
	}
}

void End::deleteButtonTexte(std::unordered_map<std::string, ButtonTexte*>& unmap, const std::string& name)
{
	for (const auto& n : unmap)
	{
		if (n.second != nullptr)
		{
			IHM::logfileconsole("[INFO]___: Delete " + name + " name = " + n.second->GETname() + " Success");
			delete n.second;
		}
		else
		{
			/* N/A */
		}
	}
}


/*
*	End Of File : End.cpp
*/