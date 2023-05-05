/*

	Discrete_system
	Copyright SAUTER Robin 2017-2022 (robin.sauter@orange.fr)
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

#include "MainMenuScreen.h"
#include "ScreenIndices.h"

#include "App.h"

MainMenuScreen::MainMenuScreen
(
	File* file,
	FCTDiscret* fctDiscret,
	SYSETATDiscret* sysetatDiscret,
	GUI_Parameters& parameters
)
: 
RealEngine2D::IGameScreen(),
m_nextScreenIndexMenu(INIT_SCREEN_INDEX),
m_gui(),
m_file(file),
m_fctDiscret(fctDiscret),
m_sysetatDiscret(sysetatDiscret),
m_isInitialize(false)
{
	build();
	m_gui.gLSLProgram = parameters.gLSLProgram;
	m_gui.spriteFont = *(parameters.spriteFont);
	m_gui.window = parameters.window;
}

MainMenuScreen::~MainMenuScreen()
{
	destroy();
}

int MainMenuScreen::getNextScreenIndex()const
{
	return m_nextScreenIndexMenu;
}
int MainMenuScreen::getPreviousScreenIndex()const
{
	return INIT_SCREEN_INDEX;
}

void MainMenuScreen::build()
{
	m_screenIndex = MAINMENU_SCREEN_INDEX;
}

void MainMenuScreen::destroy()
{
	m_gui.gui.destroy();
}

bool MainMenuScreen::onEntry()
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

		initHUDText();



		const float xC(0.4f), xL(0.2f), yL(0.1f), yDelta(0.15f);
		float yC(0.2f);

		m_gui.fctButton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				"AlfiskoSkin/Button",
				{ xC, yC, xL, yL },
				RealEngine2D::NOT_BY_PERCENT,
				"FCT"));

		m_gui.fctButton->setText("Create/Modify FCT");
		m_gui.fctButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&MainMenuScreen::onCreateFCT, this)
		);

		m_gui.bodeButton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				"AlfiskoSkin/Button",
				{ xC, yC += yDelta, xL, yL },
				RealEngine2D::NOT_BY_PERCENT,
				"Bode"));

		m_gui.bodeButton->setText("Display Bode graph");
		m_gui.bodeButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&MainMenuScreen::onBodeDisplay, this)
		);
		m_gui.bodeButton->disable();

		m_gui.stateButton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				"AlfiskoSkin/Button",
				{ xC, yC += yDelta, xL, yL },
				RealEngine2D::NOT_BY_PERCENT,
				"state"));

		m_gui.stateButton->setText("Create/Modify State System");
		m_gui.stateButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&MainMenuScreen::onSYSETAT, this)
		);

		m_gui.SimulationButton = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				"AlfiskoSkin/Button",
				{ xC, yC += yDelta, xL, yL },
				RealEngine2D::NOT_BY_PERCENT,
				"simulation"));

		m_gui.SimulationButton->setText("Display temporal response");
		m_gui.SimulationButton->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&MainMenuScreen::onSimulation, this)
		);
		m_gui.SimulationButton->disable();

		m_gui.quitGame = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				"AlfiskoSkin/Button",
				{ xC, yC += yDelta, xL, yL },
				RealEngine2D::NOT_BY_PERCENT,
				"QuitGame"));

		m_gui.quitGame->setText("Quit Game");
		m_gui.quitGame->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&MainMenuScreen::onExitClicked, this)
		);


		m_gui.gui.setMouseCursor("AlfiskoSkin/MouseArrow");
		m_gui.gui.showMouseCursor();

		/* HIDE normal mouse cursor */
		SDL_ShowCursor(0);

		m_isInitialize = true;
	}
	else
	{
		if (m_fctDiscret->isInitialize())
		{
			m_gui.bodeButton->enable();
		}

		if (m_sysetatDiscret != INIT_TO_NULLPTR)
		{
			m_gui.SimulationButton->enable();
		}
	}
	

	return true;
}

void MainMenuScreen::initHUDText()
{
	m_gui.spriteBatchHUDStatic.begin();

	m_gui.spriteFont->draw
	(
		m_gui.spriteBatchHUDStatic,
		"Discret System 2.0",
		glm::vec2
		(
			float(m_gui.window->GETscreenWidth() / 2),
			float(m_gui.window->GETscreenHeight() - 50)
		), // offset pos
		glm::vec2(0.64f), // size
		0.0f,
		RealEngine2D::COLOR_GOLD,
		RealEngine2D::Justification::MIDDLE
	);

	m_gui.spriteFont->draw
	(
		m_gui.spriteBatchHUDStatic,
		"Robin SAUTER 2018-2022\nDev branch 4.0.1",
		glm::vec2(0.f,0.f), // offset pos
		glm::vec2(0.24f), // size
		0.0f,
		RealEngine2D::COLOR_RED,
		RealEngine2D::Justification::LEFT
	);

	m_gui.spriteFont->draw
	(
		m_gui.spriteBatchHUDStatic,
		" - to display a temporal response to the state system\n - to create a state system (matrix)\n - to display Bode graph of a Transfer function\n - to create a Transfer function (num/den)\nThis application serves as a tool",
		glm::vec2(0.f, float(m_gui.window->GETscreenHeight() - 200)), // offset pos
		glm::vec2(0.28f), // size
		0.0f,
		RealEngine2D::COLOR_GREY,
		RealEngine2D::Justification::LEFT
	);

	m_gui.spriteBatchHUDStatic.end();
}

void MainMenuScreen::onExit()
{
	/* Do nothing */
}


//----------------------------------------------------------GameLoop----------------------------------------------------------------//



void MainMenuScreen::draw()
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




void MainMenuScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_gui.gui.onSDLEvent(ev, m_game->getInputManager());
		m_game->onSDLEvent(ev);
	}
}


bool MainMenuScreen::onCreateFCT(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = FCT_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onBodeDisplay(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = BODE_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onSYSETAT(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = SYSETATDISCRET_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_NEXT;
	return true;
}

bool MainMenuScreen::onSimulation(const CEGUI::EventArgs& /* e */)
{
	return true;
}

bool MainMenuScreen::onExitClicked(const CEGUI::EventArgs& /* e */)
{
	m_currentState = RealEngine2D::ScreenState::EXIT_APPLICATION;
	return true;
}
