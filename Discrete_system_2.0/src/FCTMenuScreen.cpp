/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
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

#include "FCTMenuScreen.h"
#include "ScreenIndices.h"

#include "App.h"

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
		m_gui.gui.init(m_file->GUIPath);

		m_gui.gui.loadScheme("AlfiskoSkin.scheme");

		m_gui.gui.setFont("DejaVuSans-12");

		m_gui.cameraHUD.init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());
		m_gui.cameraHUD.SETposition(glm::vec2(m_game->getWindow().GETscreenWidth() / 2, m_game->getWindow().GETscreenHeight() / 2));

		m_gui.spriteBatchHUDDynamic.init();
		m_gui.spriteBatchHUDStatic.init();

		//initHUDText();

		m_gui.secondOrdreButton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				"AlfiskoSkin/Button",
				{ 0, 0.1f, 0.15f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"SecondOrdre"));

		m_gui.secondOrdreButton->setText("Pre-filled Second Order");
		m_gui.secondOrdreButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FCTMenuScreen::onsecondOrdreButtonClicked, this)
		);

		m_gui.juryProcessButton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				"AlfiskoSkin/Button",
				{ 0, 0.2f, 0.15f, 0.05f },
				RealEngine2D::NOT_BY_PERCENT,
				"Jury"));

		m_gui.juryProcessButton->setText("Process Jury table");
		m_gui.juryProcessButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FCTMenuScreen::onJuryButtonClicked, this)
		);


		m_gui.returnMainMenu = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				"AlfiskoSkin/Button",
				{ 0, 0, 0.15, 0.05 },
				RealEngine2D::NOT_BY_PERCENT,
				"Return"));

		m_gui.returnMainMenu->setText("Return to main menu");
		m_gui.returnMainMenu->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&FCTMenuScreen::onReturnMainMenuClicked, this)
		);


		m_gui.gui.setMouseCursor("AlfiskoSkin/MouseArrow");
		m_gui.gui.showMouseCursor();

		/* HIDE normal mouse cursor */
		SDL_ShowCursor(0);
	}
	else
	{
		
	}
	

	return true;
}

void FCTMenuScreen::initHUDText(const std::string& msg)
{
	m_gui.spriteBatchHUDStatic.begin();

	std::string dummy{ msg };

	std::string num{ dummy.substr(0, dummy.find_first_of("\n")) };
	dummy.erase(0, dummy.find_first_of("\n") + 1);
	std::string bar{ dummy.substr(0, dummy.find_first_of("\n")) };
	dummy.erase(0, dummy.find_first_of("\n") + 1);
	std::string den{ dummy };

	m_gui.spriteFont->draw
	(
		m_gui.spriteBatchHUDStatic,
		num.c_str(),
		glm::vec2
		(
			float(m_gui.window->GETscreenWidth() / 2),
			float(m_gui.window->GETscreenHeight() / 2) 
		), // offset pos
		glm::vec2(0.64f), // size
		0.0f,
		RealEngine2D::COLOR_GOLD,
		RealEngine2D::Justification::MIDDLE
	);
	m_gui.spriteFont->draw
	(
		m_gui.spriteBatchHUDStatic,
		bar.c_str(),
		glm::vec2
		(
			float(m_gui.window->GETscreenWidth() / 2),
			float(m_gui.window->GETscreenHeight() / 2) - 50.f
		), // offset pos
		glm::vec2(0.64f), // size
		0.0f,
		RealEngine2D::COLOR_GOLD,
		RealEngine2D::Justification::MIDDLE
	);
	m_gui.spriteFont->draw
	(
		m_gui.spriteBatchHUDStatic,
		den.c_str(),
		glm::vec2
		(
			float(m_gui.window->GETscreenWidth() / 2),
			float(m_gui.window->GETscreenHeight() / 2) - 100.f
		), // offset pos
		glm::vec2(0.64f), // size
		0.0f,
		RealEngine2D::COLOR_GOLD,
		RealEngine2D::Justification::MIDDLE
	);

	m_gui.spriteBatchHUDStatic.end();
}

void FCTMenuScreen::onExit()
{
	/* Do nothing */
}


//----------------------------------------------------------GameLoop----------------------------------------------------------------//



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

	//m_gui.spriteBatchHUDDynamic.begin();


	//m_gui.spriteBatchHUDDynamic.end();

	//m_gui.spriteBatchHUDDynamic.renderBatch();

	m_gui.spriteBatchHUDStatic.renderBatch();


	/* --- GL unbind --- */
	glBindTexture(GL_TEXTURE_2D, 0);
	m_gui.gLSLProgram->unuse();

	/* --- Draw UI --- */
	m_gui.gui.draw();
}




void FCTMenuScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_gui.gui.onSDLEvent(ev, m_game->getInputManager());
		m_game->onSDLEvent(ev);
	}
}

bool FCTMenuScreen::onsecondOrdreButtonClicked(const CEGUI::EventArgs& /* e */)
{
	m_fctDiscret->secondOrdre();
	m_isInitialize = true;
	initHUDText(m_fctDiscret->printOn());
	return true;
}

bool FCTMenuScreen::onJuryButtonClicked(const CEGUI::EventArgs& /* e */)
{
	if (m_fctDiscret->isInitialize())
	{
		m_fctDiscret->tabJury();
	}
	return true;
}

bool FCTMenuScreen::onReturnMainMenuClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = MAINMENU_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}
