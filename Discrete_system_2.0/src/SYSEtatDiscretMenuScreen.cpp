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

/* *********************************************************
 *						Include							   *
 ********************************************************* */

#include "SYSEtatDiscretMenuScreen.h"
#include "ScreenIndices.h"

/* 
	include for struct parameters
		File
		GUI_Parameters
*/
#include "App.h"

/*
    Include for computeValueToScale
*/
#include "LIBUTI.h"

#include "FCTMenuScreen_GUI.h"



 /* *********************************************************
  *						Classe	 						    *
  ********************************************************* */

SYSEtatDiscretMenuScreen::SYSEtatDiscretMenuScreen
(
	File* file,
	SYSETATDiscret* sysEtatDiscret,
	FCTDiscret* fctDiscret,
	GUI_Parameters& parameters
)
: 
RealEngine2D::IGameScreen(),
m_nextScreenIndexMenu(INIT_SCREEN_INDEX),
m_gui(),
m_file(file),
m_sysEtatDiscret(sysEtatDiscret),
m_fctDiscret(fctDiscret),
m_sysPrintCom(EMPTY_STRING),
m_sysPrintObs(EMPTY_STRING),
m_isInitialize(false)
{
	build();
	m_gui.gLSLProgram = parameters.gLSLProgram;
	m_gui.spriteFont = *(parameters.spriteFont);
	m_gui.window = parameters.window;
}

SYSEtatDiscretMenuScreen::~SYSEtatDiscretMenuScreen()
{
	destroy();
}

int SYSEtatDiscretMenuScreen::getNextScreenIndex()const
{
	return m_nextScreenIndexMenu;
}
int SYSEtatDiscretMenuScreen::getPreviousScreenIndex()const
{
	return MAINMENU_SCREEN_INDEX;
}

void SYSEtatDiscretMenuScreen::build()
{
	m_screenIndex = SYSETATDISCRET_SCREEN_INDEX;
}

void SYSEtatDiscretMenuScreen::destroy()
{
	m_gui.gui.destroy();
}

bool SYSEtatDiscretMenuScreen::onEntry()
{
	if (!m_isInitialize)
	{

		/* --- m_gui.gui --- */

		m_gui.gui.init(m_file->GUIPath);

		m_gui.gui.loadScheme(GUI_SKIN_THEME_SCHEME);

		m_gui.gui.setFont(GUI_SKIN_FONT);

		/* --- m_gui.cameraHUD --- */

		m_gui.cameraHUD.init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());
		m_gui.cameraHUD.SETposition(glm::vec2(m_game->getWindow().GETscreenWidth() / 2, m_game->getWindow().GETscreenHeight() / 2));

		/* --- m_gui.spriteBatch --- */

		m_gui.spriteBatchHUDDynamic.init();
		m_gui.spriteBatchHUDStatic.init();

		/* --- m_gui --- */

		static const float yDisplay{ 0.1f }, ydelta{ 0.05f };
		unsigned int indexDisplay{ 0 };

		m_gui.returnMainMenu = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_BUTTON,
				{ 0, 0, 0.15, 0.05 },
				RealEngine2D::NOT_BY_PERCENT,
				"Return"));

		m_gui.returnMainMenu->setText("Return to main menu");
		m_gui.returnMainMenu->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&SYSEtatDiscretMenuScreen::onReturnMainMenuClicked, this)
		);

		m_gui.calculABCDbutton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_BUTTON,
				{ 0, 0.1, 0.25, 0.05 },
				RealEngine2D::NOT_BY_PERCENT,
				"CalculABCD"));

		m_gui.calculABCDbutton->setText("Process discret FCT -> discret Sys");
		m_gui.calculABCDbutton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&SYSEtatDiscretMenuScreen::onCalculABCDClicked, this)
		);

		m_gui.SetDisplayPrecisionButton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_BUTTON,
				{ 0, 0.15, 0.25, 0.05 },
				RealEngine2D::NOT_BY_PERCENT,
				"SetDisplayPrecision"));

		m_gui.SetDisplayPrecisionButton->setText("Set Display Precision (1 to 10)");
		m_gui.SetDisplayPrecisionButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&SYSEtatDiscretMenuScreen::onSetDisplayPrecisionClicked, this)
		);

		static const float deltaYGUI{ GUI_SPACE_FCT_Y * float(m_gui.window->GETscreenWidth()) };
		static const glm::vec2 sizeGUI{ GUI_FACTOR_SIZE * float(m_gui.window->GETscreenWidth()) };
		static const float screenWidthDiv2{ float(m_gui.window->GETscreenWidth()) / 2.f };

		float yLine{ float(m_gui.window->GETscreenHeight()) - deltaYGUI };
		m_gui.editBox = static_cast<CEGUI::Editbox*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_Editbox,
				{ 0.f, 0.2f, 0.15f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"editBoxc"));
		m_gui.editBox->hide();


		m_gui.gui.setMouseCursor(GUI_SKIN_THEME_MOUSE);
		m_gui.gui.showMouseCursor();

		/* HIDE normal mouse cursor */
		SDL_ShowCursor(GUI_HIDE_NORMAL_CURSOR);
	}
	else
	{
		
	}
	

	return true;
}

void SYSEtatDiscretMenuScreen::onExit()
{
	/* Do nothing */
}


/* ----------------------------------------------------------------------------------- */
/* NAME: initHUDText																   */
/* ROLE: Shall display initial text													   */
/* IN: void			 																   */
/* OUT: void																		   */
/* RVALUE: void																		   */
/* ------------------------------------------------------------------------------------*/
void SYSEtatDiscretMenuScreen::initHUDText()
{
	static const float deltaYGUI{ GUI_SPACE_FCT_Y * float(m_gui.window->GETscreenWidth()) };
	static const glm::vec2 sizeGUI{ GUI_FACTOR_SIZE * float(m_gui.window->GETscreenWidth()) };
	static const float screenWidthDiv2{ float(m_gui.window->GETscreenWidth()) / 2.f };

	float yLine{ float(m_gui.window->GETscreenHeight()) - deltaYGUI };

	m_gui.spriteBatchHUDStatic.begin();

	m_gui.spriteFont->draw
	(
		m_gui.spriteBatchHUDStatic,
		m_sysPrintCom.c_str(),
		{ 0, 0 },
		sizeGUI, NO_DEPTH,
		RealEngine2D::COLOR_LIGHT_GREY,
		RealEngine2D::Justification::LEFT
	);

	m_gui.spriteFont->draw
	(
		m_gui.spriteBatchHUDStatic,
		m_sysPrintObs.c_str(),
		{ screenWidthDiv2, 0 },
		sizeGUI, NO_DEPTH,
		RealEngine2D::COLOR_LIGHT_GREY,
		RealEngine2D::Justification::LEFT
	);

	

	m_gui.spriteBatchHUDStatic.end();
}



//----------------------------------------------------------GameLoop----------------------------------------------------------------//


void SYSEtatDiscretMenuScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_gui.gui.onSDLEvent(ev, m_game->getInputManager());
		m_game->onSDLEvent(ev);
		KeyMouseinput(ev);
	}
}

void SYSEtatDiscretMenuScreen::draw()
{
	m_gui.cameraHUD.update();

	/* line for CEGUI because CEGUI doesn't do it, do not remove  */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Back */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gui.gLSLProgram->use();
	/* use GL_TEXTURE0 for 1 pipe; use GL_TEXTURE1/2/3 for multiple */
	glActiveTexture(GL_TEXTURE0);

	const GLint textureLocation = m_gui.gLSLProgram->getUnitformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	

	/* --- Draw --- */
	



	/* --- camera --- */
	/* GL - get parameter P */
	const GLint pLocation = m_gui.gLSLProgram->getUnitformLocation("P");
	glm::mat4 cameraMatrix = m_gui.cameraHUD.GETcameraMatrix();

	/* --- Render --- */
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_gui.spriteBatchHUDStatic.renderBatch();


	/* --- GL unbind --- */
	glBindTexture(GL_TEXTURE_2D, 0);
	m_gui.gLSLProgram->unuse();

	/* --- Draw UI --- */
	m_gui.gui.draw();
}

/* ----------------------------------------------------------------------------------- */
/* NAME: KeyMouseinput																   */
/* ROLE: Shall interprets user's inputs			 									   */
/* IN: ev : user input from SDL event												   */
/* OUT: void																		   */
/* RVALUE: void																		   */
/* ------------------------------------------------------------------------------------*/
void SYSEtatDiscretMenuScreen::KeyMouseinput(const SDL_Event& ev)
{
	if (m_game->getInputManager().isKeyDown(SDLK_KP_ENTER))
	{
		const unsigned int userInput{ (unsigned int)std::stoi(m_gui.editBox->getText().c_str()) };
		if (userInput > MIN_PRECISION_USER_INPUT && userInput < MAX_PRECISION_USER_INPUT)
		{
			m_sysEtatDiscret->GETA()->SETprecision(userInput);
			m_sysEtatDiscret->GETB()->SETprecision(userInput);
			m_sysEtatDiscret->GETC()->SETprecision(userInput);
			m_sysEtatDiscret->GETD()->SETprecision(userInput);
			m_gui.editBox->hide();
			m_gui.editBox->setText(EMPTY_STRING);
		}
	}
}

bool SYSEtatDiscretMenuScreen::onCalculABCDClicked(const CEGUI::EventArgs& /* e */)
{
	m_sysEtatDiscret->calculABCD(m_fctDiscret);
	std::string tmp{ m_sysEtatDiscret->printOn(false) };
	splitComObs(tmp);
	m_sysPrintCom.push_back('\n');
	m_sysPrintObs.push_back('\n');
	m_sysPrintCom = inverseLineRead(m_sysPrintCom);
	m_sysPrintObs = inverseLineRead(m_sysPrintObs);

	initHUDText();
	return true;
}

bool SYSEtatDiscretMenuScreen::onSetDisplayPrecisionClicked(const CEGUI::EventArgs& /* e */)
{
	m_gui.editBox->show();
	return true;
}

bool SYSEtatDiscretMenuScreen::onReturnMainMenuClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = MAINMENU_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}


void SYSEtatDiscretMenuScreen::splitComObs(const std::string& txt)
{
	std::string::size_type n{ txt.find("Forme Compagne d'Observabilite") };
	m_sysPrintCom = txt.substr(0, n);
	m_sysPrintObs = txt.substr(n, txt.size());
}