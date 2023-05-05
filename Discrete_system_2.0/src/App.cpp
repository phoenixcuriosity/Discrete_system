/*

	Discrete_system
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	file version 4.2.2

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

#include "App.h"

#include <RealEngine2D/src/ScreenList.h>

#include <iostream>

#include <tinyxml2/tinyxml2.h>

static std::ofstream* ptrlogger;

App::App()
:
RealEngine2D::IMainGame(),
m_mainMenuScreen(INIT_TO_NULLPTR),
m_spriteFont(INIT_TO_NULLPTR),
m_gLSLProgram(),
m_file(),
m_logger(),
m_fctDiscret(),
m_sysetatDiscret()
{
	/* Do nothing */
}

App::~App()
{
	m_mainMenuScreen.reset();
	deleteAll();
	m_spriteFont.reset();

}

void App::onInit()
{
	/* Set location of logging file */
	m_file.log = "bin/log/log.txt";

	initFile();

	ptrlogger = &m_logger;

	initMain();

	m_window.SETscreenWidth(int(RealEngine2D::Window::getHorizontal() / SCREEN_MULTIPLY_COEF));
	m_window.SETscreenHeight(int(RealEngine2D::Window::getVertical() / SCREEN_MULTIPLY_COEF));
}


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initShaders																   */
/* ROLE : Init shaders for OpenGL													   */
/* ROLE : 2 files : colorShadingVert and colorShadingFrag							   */
/* ROLE : 3 parameters : vertexPosition	, vertexColor , vertexUV					   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void App::InitShaders()
{
	m_gLSLProgram.compileShaders(m_file.colorShadingVert, m_file.colorShadingFrag);
	m_gLSLProgram.addAttribut("vertexPosition");
	m_gLSLProgram.addAttribut("vertexColor");
	m_gLSLProgram.addAttribut("vertexUV");
	m_gLSLProgram.linkShaders();
	m_spriteFont = std::make_shared<RealEngine2D::SpriteFont>(fontGUI.c_str(), 64);
}


void App::onExit()
{
	/* Do nothing */
}

void App::addScreens()
{
	GUI_Parameters AppToScreenParameters;
	AppToScreenParameters.spriteFont = &m_spriteFont;
	AppToScreenParameters.gLSLProgram = &m_gLSLProgram;
	AppToScreenParameters.window = &m_window;

	

	/* Create shared Ptr */
	m_mainMenuScreen = std::make_shared<MainMenuScreen>
		(
			&m_file,
			&m_fctDiscret,
			&m_sysetatDiscret,
			AppToScreenParameters
		);

	m_FCTMenuScreen = std::make_shared<FCTMenuScreen>
		(
			&m_file,
			&m_fctDiscret,
			AppToScreenParameters
		);

	m_BodeMenuScreen = std::make_shared<BodeMenuScreen>
		(
			&m_file,
			&m_fctDiscret,
			AppToScreenParameters
		);

	m_SYSEtatDiscretMenuScreen = std::make_shared<SYSEtatDiscretMenuScreen>
		(
			&m_file,
			&m_sysetatDiscret,
			&m_fctDiscret,
			AppToScreenParameters
		);


	/* Add Screen to listed Screen */
	m_screenList->addScreen(m_mainMenuScreen);
	m_screenList->addScreen(m_FCTMenuScreen);
	m_screenList->addScreen(m_BodeMenuScreen);
	m_screenList->addScreen(m_SYSEtatDiscretMenuScreen);

	/* Set default Screen */
	m_screenList->setScreen(m_mainMenuScreen->GETscreenIndex());
}





/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initFile																	   */
/* ROLE : Initialisation des fichiers : log											   */
/* INPUT : struct File& : nom des fichiers											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void App::initFile()
{
	m_logger.open(m_file.log, std::ofstream::out | std::ofstream::trunc);
	if (!m_logger.is_open())
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		/* N/A */
	}
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : initMain																	   */
/* ROLE : Chargement des informations de la configuration du jeu					   */
/* INPUT : struct Sysinfo& : structure globale du programme							   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void App::initMain()
{
	logfileconsole("[INFO]___: [START] : initMain");

	tinyxml2::XMLDocument config{};
	config.LoadFile(configFilePath.c_str());

	if (config.ErrorID() == 0)
	{
		const char* root("Config");


		const char
			* s_FilePaths("FilePaths"),
				* s_Bode("Bode"),
				* s_Load("Load"),
				* s_ReponseTemporelle("ReponseTemporelle"),
				* s_ColorShadingVert("ColorShadingVert"),
				* s_ColorShadingFrag("ColorShadingFrag"),
				* s_ImagesPath("ImagesPath"),
				* s_GUIPath("GUIPath");

		m_file.bode = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Bode)->GetText();
		m_file.load = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_Load)->GetText();
		m_file.reponseTemporelle = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ReponseTemporelle)->GetText();
		m_file.colorShadingVert = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ColorShadingVert)->GetText();
		m_file.colorShadingFrag = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ColorShadingFrag)->GetText();
		m_file.imagesPath = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_ImagesPath)->GetText();
		m_file.GUIPath = config.FirstChildElement(root)->FirstChildElement(s_FilePaths)->FirstChildElement(s_GUIPath)->GetText();
	}
	else
	{
		throw("Impossible d'ouvrir le fichier " + (std::string)configFilePath);
	}

	logfileconsole("[INFO]___: [END] : initMain");
}


//----------------------------------------------------------Destroy----------------------------------------------------------------//

void App::destroy()
{
	deleteAll();
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : exitError																	   */
/* ROLE : Enregistre l'erreur survenue et termine le programme de façon sécurisée	   */
/* INPUT : const std::string msg : message de l'erreur								   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void App::exitError
(
	const std::string& msg
)
{
	logfileconsole("[ERROR]___: " + msg);
	deleteAll();
	logfileconsole("[ERROR]___: Last msg before exitError : " + msg);
	ptrlogger->close();
	exit(EXIT_FAILURE);
}

/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : deleteAll																	   */
/* ROLE : Destruction des allocations dynamique du programme						   */
/* ROLE : Destruction de la fenetre et du Renderer de la SDL						   */
/* INPUT/OUTPUT : struct Sysinfo& : structure globale du programme					   */
/* RETURNED VALUE    : void															   */
/* ------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- */
void App::deleteAll()
{
	logfileconsole("[INFO]___: [START] *********_________ DeleteAll _________*********");




	/* *********************************************************
	 *				 START delete SDL						   *
	 ********************************************************* */


	SDL_Quit();

	/* *********************************************************
	 *				 END delete SDL							   *
	 ********************************************************* */

	 /* ### Don't put code below here ### */

	logfileconsole("[INFO]___: [END] : *********_________ DeleteAll _________*********");

	logfileconsole("[INFO]___: SDL_Quit Success");
	logfileconsole("[INFO]___:________PROGRAMME FINISH________");
	ptrlogger->close();
}

//----------------------------------------------------------Logger----------------------------------------------------------------//


/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
/* NAME : logfileconsole															   */
/* ROLE : Transmission du message sur la console et dans le fichier log.txt			   */
/* INPUT : const std::string msg : message											   */
/* RETURNED VALUE    : void															   */
/* ----------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------- */
void App::logfileconsole
(
	const std::string& msg
)
{
	time_t now{ time(0) };
	struct tm  tstruct{};
	char  buf[80]{};
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%F %X", &tstruct);

#ifdef _DEBUG
	std::cout << std::endl << buf << "      " << msg;
#endif // DEBUG_MODE
	*ptrlogger << std::endl << buf << "      " << msg;
}