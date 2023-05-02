/*

	Discrete_system
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	file version 4.2.0

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

#include "FCTMenuScreen.h"
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

FCTMenuScreen::FCTMenuScreen
(
	File* file,
	FCTDiscret* m_fctDiscret,
	GUI_Parameters& parameters
)
: 
RealEngine2D::IGameScreen(),
m_nextScreenIndexMenu(INIT_SCREEN_INDEX),
m_gui(),
m_file(file),
m_fctDiscret(m_fctDiscret),
m_isStable(false),
m_FCTCreationTool(),
m_isInitialize(false)
{
	build();
	m_gui.gLSLProgram = parameters.gLSLProgram;
	m_gui.spriteFont = *(parameters.spriteFont);
	m_gui.window = parameters.window;
}

FCTMenuScreen::~FCTMenuScreen()
{
	destroy();
}

int FCTMenuScreen::getNextScreenIndex()const
{
	return m_nextScreenIndexMenu;
}
int FCTMenuScreen::getPreviousScreenIndex()const
{
	return MAINMENU_SCREEN_INDEX;
}

void FCTMenuScreen::build()
{
	m_screenIndex = FCT_SCREEN_INDEX;
}

void FCTMenuScreen::destroy()
{
	m_gui.gui.destroy();
}

bool FCTMenuScreen::onEntry()
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
			CEGUI::Event::Subscriber(&FCTMenuScreen::onReturnMainMenuClicked, this)
		);

		m_gui.secondOrdreButton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_BUTTON,
				{ 0, yDisplay + ydelta * indexDisplay, 0.15f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"SecondOrdre"));

		m_gui.secondOrdreButton->setText("Pre-filled Second Order");
		m_gui.secondOrdreButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FCTMenuScreen::onsecondOrdreButtonClicked, this)
		);
		indexDisplay++;

		m_gui.integButton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_BUTTON,
				{ 0, yDisplay + ydelta * indexDisplay, 0.15f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"integ"));

		m_gui.integButton->setText("Pre-filled Integrator");
		m_gui.integButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FCTMenuScreen::onIntegButtonClicked, this)
		);
		indexDisplay++;
		m_gui.createFCT = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_BUTTON,
				{ 0, yDisplay + ydelta * indexDisplay, 0.15f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"createFCT"));

		m_gui.createFCT->setText("Create/Modify FCT");
		m_gui.createFCT->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FCTMenuScreen::onCreateModifyFCTButtonClicked, this)
		);
		indexDisplay++;
		indexDisplay++;

		m_gui.juryProcessButton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_BUTTON,
				{ 0, yDisplay + ydelta * indexDisplay, 0.15f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"Jury"));

		m_gui.juryProcessButton->setText("Process Jury table");
		m_gui.juryProcessButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FCTMenuScreen::onJuryButtonClicked, this)
		);
		m_gui.juryProcessButton->hide();
		indexDisplay++;
		

		indexDisplay++;
		indexDisplay++;
		m_gui.SetNum = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_BUTTON,
				{ 0, yDisplay + ydelta * indexDisplay, 0.15f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"SetNum"));

		m_gui.SetNum->setText("Set Num");
		m_gui.SetNum->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FCTMenuScreen::onSetNumButtonClicked, this)
		);
		m_gui.SetNum->hide();

		indexDisplay++;
		m_gui.SetDen = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_BUTTON,
				{ 0, yDisplay + ydelta * indexDisplay, 0.15f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"SetDen"));

		m_gui.SetDen->setText("Set Den");
		m_gui.SetDen->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FCTMenuScreen::onSetDenButtonClicked, this)
		);
		m_gui.SetDen->hide();

		indexDisplay++;
		indexDisplay++;
		indexDisplay++;
		m_gui.editBox = static_cast<CEGUI::Editbox*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_Editbox,
				{ 0, yDisplay + ydelta * indexDisplay, 0.15f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"editBox"));
		
		indexDisplay++;
		indexDisplay++;
		m_gui.BodeGraphButton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_BUTTON,
				{ 0, yDisplay + ydelta * indexDisplay, 0.15f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"BodeGraph"));

		m_gui.BodeGraphButton->setText("Display Bode Graph");
		m_gui.BodeGraphButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FCTMenuScreen::onBodeGraphButtonClicked, this)
		);


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

void FCTMenuScreen::onExit()
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
void FCTMenuScreen::initHUDText(FCT_msgType msgType)
{
	m_gui.spriteBatchHUDStatic.begin();

	if (msgType >= display_FCT)
	{
		const float deltaYGUI{ GUI_SPACE_FCT_Y * float(m_gui.window->GETscreenWidth())};
		const glm::vec2 sizeGUI{ GUI_FACTOR_SIZE * float(m_gui.window->GETscreenWidth())};
		const float screenWidthDiv2{ float(m_gui.window->GETscreenWidth()) / 2.f };

		float yLine{ float(m_gui.window->GETscreenHeight()) - deltaYGUI };

		m_gui.spriteFont->draw
		(
			m_gui.spriteBatchHUDStatic,
			m_gui.s_numFCT.c_str(),
			{ screenWidthDiv2, yLine },
			sizeGUI, NO_DEPTH,
			RealEngine2D::COLOR_GOLD,
			RealEngine2D::Justification::MIDDLE
		);
		yLine -= deltaYGUI;
		m_gui.spriteFont->draw
		(
			m_gui.spriteBatchHUDStatic,
			m_gui.s_barFCT.c_str(),
			{ screenWidthDiv2, yLine },
			sizeGUI, NO_DEPTH,
			RealEngine2D::COLOR_GOLD,
			RealEngine2D::Justification::MIDDLE
		);
		yLine -= deltaYGUI;
		m_gui.spriteFont->draw
		(
			m_gui.spriteBatchHUDStatic,
			m_gui.s_denFCT.c_str(),
			{ screenWidthDiv2, yLine },
			sizeGUI, NO_DEPTH,
			RealEngine2D::COLOR_GOLD,
			RealEngine2D::Justification::MIDDLE
		);
		
		if (msgType == display_FCT_JuryTab)
		{
			const float deltaYGUIJURY{ GUI_SPACE_JURY_Y * float(m_gui.window->GETscreenWidth()) };
			const glm::vec2 sizeGUIJURY{ GUI_FACTOR_JURY_SIZE * float(m_gui.window->GETscreenWidth()) };
			std::string dummy{ m_gui.s_jury };
			std::string dummyDisplay{};


			size_t pos{ 0 };
			while ((pos = dummy.find("\t")) != std::string::npos)
			{
				dummy.replace(pos, 1, "   ");
			}

			yLine -= GUI_SPACE_BETWEEN_FCT_JURY * deltaYGUIJURY;
			m_gui.spriteFont->draw
			(
				m_gui.spriteBatchHUDStatic,
				"Jury table :",
				{ screenWidthDiv2, yLine },
				sizeGUI, NO_DEPTH,
				RealEngine2D::COLOR_LIGHT_GREY,
				RealEngine2D::Justification::RIGHT
			);
			yLine -= deltaYGUIJURY;
			while (dummy.find("|") != std::string::npos)
			{
				dummyDisplay = dummy.substr(0, dummy.find_first_of("\n"));
				dummy.erase(0, dummy.find_first_of("\n") + 1);

				m_gui.spriteFont->draw
				(
					m_gui.spriteBatchHUDStatic,
					dummyDisplay.c_str(),
					{ screenWidthDiv2, yLine },
					sizeGUI, NO_DEPTH,
					RealEngine2D::COLOR_DARK_GREY,
					RealEngine2D::Justification::MIDDLE
				);
				yLine -= deltaYGUIJURY;
			}

			/* Stability */
			m_gui.spriteFont->draw
			(
				m_gui.spriteBatchHUDStatic,
				"Jury's stability conditions :",
				{ screenWidthDiv2, yLine },
				sizeGUI, NO_DEPTH,
				RealEngine2D::COLOR_LIGHT_GREY,
				RealEngine2D::Justification::RIGHT
			);
			yLine -= deltaYGUIJURY;
			RealEngine2D::ColorRGBA8 colorS;
			for (unsigned int loopIndex{ 0 }; loopIndex < JURY_STABILITY_CONDITIONS; loopIndex++)
			{
				dummyDisplay = dummy.substr(0, dummy.find_first_of("\n"));
				dummy.erase(0, dummy.find_first_of("\n") + 1);

				
				if (dummyDisplay.find("Not") != std::string::npos)
				{
					colorS = RealEngine2D::COLOR_RED;
				}
				else
				{
					colorS = RealEngine2D::COLOR_GREEN;
				}

				m_gui.spriteFont->draw
				(
					m_gui.spriteBatchHUDStatic,
					dummyDisplay.c_str(),
					{ screenWidthDiv2, yLine },
					sizeGUI, NO_DEPTH,
					colorS,
					RealEngine2D::Justification::MIDDLE
				);
				yLine -= deltaYGUIJURY;
			}

			std::string msgStable{"The FCT is not stable"};
			colorS = RealEngine2D::COLOR_RED;
			if (m_isStable)
			{
				msgStable = "The FCT is stable";
				colorS = RealEngine2D::COLOR_GREEN;
			}
			m_gui.spriteFont->draw
			(
				m_gui.spriteBatchHUDStatic,
				msgStable.c_str(),
				{ screenWidthDiv2, yLine },
				sizeGUI, NO_DEPTH,
				colorS,
				RealEngine2D::Justification::MIDDLE
			);
			
		}
		else
		if (msgType == FCT_CreationTool_order_Num)
		{
			yLine -= deltaYGUI;
			m_gui.spriteFont->draw
			(
				m_gui.spriteBatchHUDStatic,
				"Enter a order for the Numerator",
				{ screenWidthDiv2, yLine },
				sizeGUI, NO_DEPTH,
				RealEngine2D::COLOR_BLUE,
				RealEngine2D::Justification::MIDDLE
			);
		}
		else
		if (msgType == FCT_CreationTool_order_Den)
		{
			yLine -= deltaYGUI;
			m_gui.spriteFont->draw
			(
				m_gui.spriteBatchHUDStatic,
				"Enter a order for the Denomitor",
				{ screenWidthDiv2, yLine },
				sizeGUI, NO_DEPTH,
				RealEngine2D::COLOR_BLUE,
				RealEngine2D::Justification::MIDDLE
			);
		}
		else
		if (msgType == FCT_CreationTool_coef)
		{
			yLine -= deltaYGUI;
			m_gui.spriteFont->draw
			(
				m_gui.spriteBatchHUDStatic,
				std::string("Enter a Coefficient for the order " + std::to_string(m_FCTCreationTool.order)).c_str(),
				{ screenWidthDiv2, yLine },
				sizeGUI, NO_DEPTH,
				RealEngine2D::COLOR_BLUE,
				RealEngine2D::Justification::MIDDLE
			);
		}
		else
		{
			/* Do nothing */
		}
	}

	

	m_gui.spriteBatchHUDStatic.end();
}



//----------------------------------------------------------GameLoop----------------------------------------------------------------//


void FCTMenuScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_gui.gui.onSDLEvent(ev, m_game->getInputManager());
		m_game->onSDLEvent(ev);
		KeyMouseinput(ev);
	}
}

void FCTMenuScreen::draw()
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
void FCTMenuScreen::KeyMouseinput(const SDL_Event& ev)
{
	if (m_FCTCreationTool.inputToNumDen > InputToNumDen::InputToNumDen_nothing)
	{
		if (m_game->getInputManager().isKeyDown(SDLK_KP_ENTER))
		{
			FCTCreationToolFonction();
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME: CreateModifyFCT															   */
/* ROLE: Shall initialize the FCT from users input									   */
/* IN: void			 																   */
/* OUT: void																		   */
/* RVALUE: void																		   */
/* ------------------------------------------------------------------------------------*/
void FCTMenuScreen::CreateModifyFCT()
{
	m_gui.SetNum->show();
	m_gui.SetDen->show();
	m_fctDiscret->setToInitialized();
}

bool FCTMenuScreen::onsecondOrdreButtonClicked(const CEGUI::EventArgs& /* e */)
{
	m_fctDiscret->secondOrdre();
	fctHUDfilled();
	initHUDText(display_FCT);
	return true;
}

bool FCTMenuScreen::onIntegButtonClicked(const CEGUI::EventArgs& /* e */)
{
	m_fctDiscret->interg();
	fctHUDfilled();
	initHUDText(display_FCT);
	return true;
}

bool FCTMenuScreen::onCreateModifyFCTButtonClicked(const CEGUI::EventArgs& /* e */)
{
	CreateModifyFCT();
	return true;
}

bool FCTMenuScreen::onSetNumButtonClicked(const CEGUI::EventArgs& /* e */)
{
	m_FCTCreationTool.inputToNumDen = InputToNumDen::num;
	m_FCTCreationTool.currentCoef = 0.0;
	m_FCTCreationTool.order = ERROR_ORDER_FCT_CREATION_TOOL;
	fctHUDfilled();
	initHUDText(FCT_CreationTool_order_Num);
	return true;
}

bool FCTMenuScreen::onSetDenButtonClicked(const CEGUI::EventArgs& /* e */)
{
	m_FCTCreationTool.inputToNumDen = InputToNumDen::den;
	m_FCTCreationTool.currentCoef = 0.0;
	m_FCTCreationTool.order = ERROR_ORDER_FCT_CREATION_TOOL;
	fctHUDfilled();
	initHUDText(FCT_CreationTool_order_Den);
	return true;
}

bool FCTMenuScreen::onJuryButtonClicked(const CEGUI::EventArgs& /* e */)
{
	if (m_fctDiscret->isInitialize())
	{
		m_gui.SetNum->hide();
		m_gui.SetDen->hide();

		std::ostringstream stream;
		m_isStable = m_fctDiscret->tabJury(stream);
		m_gui.s_jury = stream.str();
		/* erase 1st \n */
		m_gui.s_jury.erase(0, 1);

		initHUDText(display_FCT_JuryTab);
	}
	return true;
}

bool FCTMenuScreen::onBodeGraphButtonClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = BODE_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool FCTMenuScreen::onReturnMainMenuClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = MAINMENU_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}

void FCTMenuScreen::fctHUDfilled()
{
	m_isInitialize = true;

	std::string dummy{ m_fctDiscret->printOn() };

	m_gui.s_numFCT = dummy.substr(0, dummy.find_first_of("\n"));
	dummy.erase(0, dummy.find_first_of("\n") + 1);
	m_gui.s_barFCT = dummy.substr(0, dummy.find_first_of("\n"));
	dummy.erase(0, dummy.find_first_of("\n") + 1);
	m_gui.s_denFCT = dummy;

	m_gui.juryProcessButton->show();
}





void FCTMenuScreen::FCTCreationToolFonction()
{
	if (m_FCTCreationTool.order > ERROR_ORDER_FCT_CREATION_TOOL)
	{
		/* Fill coef tab by order */

		m_FCTCreationTool.currentCoef = std::stod(m_gui.editBox->getText().c_str());
		m_gui.editBox->setText(EMPTY_STRING);

		if (m_FCTCreationTool.inputToNumDen == InputToNumDen::num)
		{
			m_fctDiscret->GETnum()->SETcoefTab(m_FCTCreationTool.order, m_FCTCreationTool.currentCoef);
		}
		else
		if (m_FCTCreationTool.inputToNumDen == InputToNumDen::den)
		{
			m_fctDiscret->GETden()->SETcoefTab(m_FCTCreationTool.order, m_FCTCreationTool.currentCoef);
		}
		else
		{
			/* Do nothing */
		}

		fctHUDfilled();

		if (m_FCTCreationTool.order > MIN_ORDER_FCT_CREATION_TOOL)
		{
			m_FCTCreationTool.order--;
			initHUDText(FCT_CreationTool_coef);
		}
		else
		{
			/* Stop iteration */
			m_FCTCreationTool.inputToNumDen = InputToNumDen::InputToNumDen_nothing;
			m_FCTCreationTool.order = ERROR_ORDER_FCT_CREATION_TOOL;
			m_fctDiscret->SETdeltaT(0.01);
			initHUDText(display_FCT);
		}
		
	}
	else
	{
		/* Set order to Num or Den */

		/* Use of std::stoul to avoid negative order */
		m_FCTCreationTool.order = int8_t(std::stoul(m_gui.editBox->getText().c_str()));
		m_gui.editBox->setText(EMPTY_STRING);

		if (m_FCTCreationTool.inputToNumDen == InputToNumDen::num)
		{
			m_fctDiscret->GETnum()->SETorder(m_FCTCreationTool.order);
		}
		else
		if (m_FCTCreationTool.inputToNumDen == InputToNumDen::den)
		{
			m_fctDiscret->GETden()->SETorder(m_FCTCreationTool.order);
		}
		else
		{
			/* Do nothing */
		}

		fctHUDfilled();
		initHUDText(FCT_CreationTool_coef);
	}
	
}