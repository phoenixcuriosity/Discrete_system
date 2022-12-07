/*

	Discrete_system
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
	file version 4.0

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

#ifndef App_H
#define App_H

#include "LIB.h"

#include <fstream> // logger
#include <memory>

#include <RealEngine2D/src/IMainGame.h>

#include "MainMenuScreen.h"
#include "FCTMenuScreen.h"
#include "BodeMenuScreen.h"

#include "FCTDiscret.h"
#include "SYSETATDiscret.h"

#define INIT_TO_NULLPTR nullptr

const std::string configFilePath = "bin/filePath.xml";

/* Define default font for GUI texts */
const std::string fontGUI = "times.ttf";

const Uint16 SCREEN_MULTIPLY_COEF = 2;

struct File
{
	std::string log = "bin/log/log.txt";

	std::string bode = EMPTY_STRING;
	std::string load = EMPTY_STRING;
	std::string reponseTemporelle = EMPTY_STRING;

	std::string colorShadingVert = EMPTY_STRING;
	std::string colorShadingFrag = EMPTY_STRING;

	std::string imagesPath = EMPTY_STRING;
	std::string GUIPath = EMPTY_STRING;
};

typedef struct GUI_Parameters
{
	std::shared_ptr<RealEngine2D::SpriteFont>* spriteFont;
	RealEngine2D::GLSLProgram* gLSLProgram;
	RealEngine2D::Window* window;
} GUI_Parameters;

class App : public RealEngine2D::IMainGame
{
public:
	App();
	~App();

	virtual void onInit() override;
	virtual void InitShaders() override;
	virtual void onExit() override;
	virtual void addScreens() override;


	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initFile																	   */
	/* ROLE : Initialisation des fichiers : log											   */
	/* INPUT : struct File& : nom des fichiers											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initFile();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : initMain																	   */
	/* ROLE : Chargement des informations de la configuration du jeu					   */
	/* INPUT : struct Sysinfo& : structure globale du programme							   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	void initMain();

	void destroy();

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : exitError																	   */
	/* ROLE : Enregistre l'erreur survenue et termine le programme de façon sécurisée	   */
	/* INPUT : const std::string msg : message de l'erreur								   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void exitError
	(
		const std::string& msg
	);

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : deleteAll																	   */
	/* ROLE : Destruction des allocations dynamique du programme						   */
	/* ROLE : Destruction de la fenetre et du Renderer de la SDL						   */
	/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
	/* RETURNED VALUE    : void															   */
	/* ------------------------------------------------------------------------------------*/
	/* ----------------------------------------------------------------------------------- */
	static void deleteAll
	(
		
	);


public:

	/* *********************************************************
	 *						Logger							   *
	 ********************************************************* */

	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	/* NAME : logfileconsole															   */
	/* ROLE : Transmission du message sur la console et dans le fichier log.txt			   */
	/* INPUT : const std::string msg : message											   */
	/* RETURNED VALUE    : void															   */
	/* ----------------------------------------------------------------------------------- */
	/* ----------------------------------------------------------------------------------- */
	static void logfileconsole
	(
		const std::string& msg
	);

private:

	/* Screens */
	std::shared_ptr<MainMenuScreen> m_mainMenuScreen;
	std::shared_ptr<FCTMenuScreen> m_FCTMenuScreen;
	std::shared_ptr<BodeMenuScreen> m_BodeMenuScreen;

	/* GUI */
	std::shared_ptr<RealEngine2D::SpriteFont> m_spriteFont;
	RealEngine2D::GLSLProgram m_gLSLProgram;

	/* Files/Log */
	File m_file;
	std::ofstream m_logger;

	/* Fonctionnal data */
	FCTDiscret m_fctDiscret;
	SYSETATDiscret* m_sysetatDiscret;
};




#endif // !App_H

