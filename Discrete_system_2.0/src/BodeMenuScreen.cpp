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

#include "BodeMenuScreen.h"
#include "ScreenIndices.h"

#include "App.h"

#include "FCTMenuScreen_GUI.h"
#include "FCTDiscret.h"

#include "LIBUTI.h"

#define BODE_GAIN_MIN_VALUE -999999999.0;
#define BODE_GAIN_MAX_VALUE 999999999.0;
#define BODE_PHASE_MIN_VALUE -999999999.0;
#define BODE_PHASE_MAX_VALUE 999999999.0;

const unsigned int OFFSET_BODEGRAPH_NB_DECADE = 1;


const int MAX_DECADE_CONVERSION = 2;

BodeMenuScreen::BodeMenuScreen
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
m_rawCalculatedBodeGraph(),
m_displayCalculatedBodeGraph(),
m_maxValues(),
m_axisData(),
m_isInitialize(false)
{
	build();
	m_gui.gLSLProgram = parameters.gLSLProgram;
	m_gui.spriteFont = *(parameters.spriteFont);
	m_gui.window = parameters.window;

	m_maxValues.maxGain = BODE_GAIN_MIN_VALUE;
	m_maxValues.minGain = BODE_GAIN_MAX_VALUE;
	m_maxValues.maxPhase = BODE_PHASE_MIN_VALUE;
	m_maxValues.minPhase = BODE_PHASE_MAX_VALUE;
}

BodeMenuScreen::~BodeMenuScreen()
{
	destroy();
}

int BodeMenuScreen::getNextScreenIndex()const
{
	return m_nextScreenIndexMenu;
}
int BodeMenuScreen::getPreviousScreenIndex()const
{
	return MAINMENU_SCREEN_INDEX;
}

void BodeMenuScreen::build()
{
	m_screenIndex = BODE_SCREEN_INDEX;
}

void BodeMenuScreen::destroy()
{
	m_gui.gui.destroy();
}

bool BodeMenuScreen::onEntry()
{
	if (!m_isInitialize)
	{
		m_gui.gui.init(m_file->GUIPath);

		m_gui.gui.loadScheme(GUI_SKIN_THEME_SCHEME);

		m_gui.gui.setFont(GUI_SKIN_FONT);

		m_gui.cameraHUD.init(m_game->getWindow().GETscreenWidth(), m_game->getWindow().GETscreenHeight());
		m_gui.cameraHUD.SETposition(glm::vec2(m_game->getWindow().GETscreenWidth() / 2, m_game->getWindow().GETscreenHeight() / 2));

		m_gui.spriteBatchHUDDynamic.init();
		m_gui.spriteBatchHUDStatic.init();


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
			CEGUI::Event::Subscriber(&BodeMenuScreen::onReturnMainMenuClicked, this)
		);


		m_gui.editBodeGraph = static_cast<CEGUI::PushButton*>
			(m_gui.gui.createWidget(
				"AlfiskoSkin/Button",
				{ 0.f, 0.15f, 0.2f, 0.1f },
				RealEngine2D::NOT_BY_PERCENT,
				"EditGraph"));

		m_gui.editBodeGraph->setText("Edit Bode Graph");
		m_gui.editBodeGraph->subscribeEvent
		(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&BodeMenuScreen::onEditBodeGraphClicked, this)
		);

		m_gui.editBoxBodeGraph = static_cast<CEGUI::Editbox*>
			(m_gui.gui.createWidget(
				GUI_SKIN_THEME_Editbox,
				{ 0.25f, 0.5f, 0.5f, 0.08f },
				RealEngine2D::NOT_BY_PERCENT,
				"editBoxBode"));
		m_gui.editBoxBodeGraph->hide();


		m_gui.gui.setMouseCursor("AlfiskoSkin/MouseArrow");
		m_gui.gui.showMouseCursor();

		/* HIDE normal mouse cursor */
		SDL_ShowCursor(0);


		m_gui.bodeInputGUI = BodeInputGUI::editFreqMin;

		m_isInitialize = true;
	}
	else
	{
		
	}
	

	return true;
}

void BodeMenuScreen::initHUDText()
{
	static const float deltaYGUI{ GUI_SPACE_FCT_Y * float(m_gui.window->GETscreenWidth()) };
	static const glm::vec2 sizeGUI{ GUI_FACTOR_SIZE * float(m_gui.window->GETscreenWidth()) };
	static const float screenWidthDiv2{ float(m_gui.window->GETscreenWidth()) / 2.f };

	float yLine{ float(m_gui.window->GETscreenHeight()) - deltaYGUI };

	m_gui.spriteBatchHUDStatic.begin();

	switch (m_gui.bodeInputGUI)
	{
	case BodeInputGUI::editFreqMin:
		m_gui.spriteFont->draw
		(
			m_gui.spriteBatchHUDStatic,
			"Edit Min Freq",
			{ screenWidthDiv2, yLine },
			sizeGUI, NO_DEPTH,
			RealEngine2D::COLOR_LIGHT_GREY,
			RealEngine2D::Justification::MIDDLE
		);
		break;
	case BodeInputGUI::editFreqMax:
		m_gui.spriteFont->draw
		(
			m_gui.spriteBatchHUDStatic,
			"Edit Max Freq",
			{ screenWidthDiv2, yLine },
			sizeGUI, NO_DEPTH,
			RealEngine2D::COLOR_LIGHT_GREY,
			RealEngine2D::Justification::MIDDLE
		);
		break;
	case BodeInputGUI::editNbPoint:
		m_gui.spriteFont->draw
		(
			m_gui.spriteBatchHUDStatic,
			"Edit number of points",
			{ screenWidthDiv2, yLine },
			sizeGUI, NO_DEPTH,
			RealEngine2D::COLOR_LIGHT_GREY,
			RealEngine2D::Justification::MIDDLE
		);
		break;
	default:
		/* Do nothing */
		break;
	}
	

	m_gui.spriteBatchHUDStatic.end();
}

void BodeMenuScreen::onExit()
{
	/* Do nothing */
}


//----------------------------------------------------------GameLoop----------------------------------------------------------------//


/* ----------------------------------------------------------------------------------- */
/* NAME: draw																		   */
/* ROLE: Cyclic function every app cycle / draw			 							   */
/* IN: none																			   */
/* OUT: none																		   */
/* RVALUE: none																		   */
/* ------------------------------------------------------------------------------------*/
void BodeMenuScreen::draw()
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

/* ----------------------------------------------------------------------------------- */
/* NAME: update																		   */
/* ROLE: Cyclic function every app cycle			 								   */
/* IN: none																			   */
/* OUT: none																		   */
/* RVALUE: none																		   */
/* ------------------------------------------------------------------------------------*/
void BodeMenuScreen::update()
{
	SDL_Event ev{};
	while (SDL_PollEvent(&ev))
	{
		m_gui.gui.onSDLEvent(ev, m_game->getInputManager());
		m_game->onSDLEvent(ev);
		KeyMouseinput(ev);
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME: KeyMouseinput																   */
/* ROLE: Shall interprets user's inputs			 									   */
/* IN: ev : user input from SDL event												   */
/* OUT: void																		   */
/* RVALUE: void																		   */
/* ------------------------------------------------------------------------------------*/
void BodeMenuScreen::KeyMouseinput(const SDL_Event& /* ev */)
{
	if (m_game->getInputManager().isKeyDown(SDLK_KP_ENTER))
	{
		switch (m_gui.bodeInputGUI)
		{
		case BodeInputGUI::editFreqMin:
			m_axisData.freqMin = std::stod(m_gui.editBoxBodeGraph->getText().c_str());
			m_gui.bodeInputGUI = BodeInputGUI::editFreqMax;
			initHUDText();
			break;
		case BodeInputGUI::editFreqMax:
		{
			m_axisData.freqMax = std::stod(m_gui.editBoxBodeGraph->getText().c_str());
			m_gui.bodeInputGUI = BodeInputGUI::editNbPoint;

			int maxDecade{ (int)std::ceil(log10(m_axisData.freqMax)) };
			if (maxDecade > MAX_DECADE_CONVERSION)
			{
				m_fctDiscret->SETdeltaT
				(
					std::pow(TEN_POWER, -(maxDecade - MAX_DECADE_CONVERSION))
				);
			}
			else
			{
				/* Do nothing */

				/* Default Value is 0.1s */
			}

			initHUDText();
			break;
		}
		case BodeInputGUI::editNbPoint:
			m_axisData.nbpoint = (unsigned int)std::stoi(m_gui.editBoxBodeGraph->getText().c_str());
			m_gui.editBoxBodeGraph->hide();
			m_gui.editBodeGraph->hide();
			displayBodeGraph();
			break;
		default:
			/* Do nothing */
			break;
		}

		m_gui.editBoxBodeGraph->setText(EMPTY_STRING);
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME: onReturnMainMenuClicked													   */
/* ROLE: Return to main menu							 							   */
/* IN: none																			   */
/* OUT: none																		   */
/* RVALUE: bool : always true														   */
/* ------------------------------------------------------------------------------------*/
bool BodeMenuScreen::onReturnMainMenuClicked(const CEGUI::EventArgs& /* e */)
{
	m_nextScreenIndexMenu = MAINMENU_SCREEN_INDEX;
	m_currentState = RealEngine2D::ScreenState::CHANGE_PREVIOUS;
	return true;
}

/* ----------------------------------------------------------------------------------- */
/* NAME: onReturnMainMenuClicked													   */
/* ROLE: Start to edit Bode graph						 							   */
/* IN: none																			   */
/* OUT: none																		   */
/* RVALUE: bool : always true														   */
/* ------------------------------------------------------------------------------------*/
bool BodeMenuScreen::onEditBodeGraphClicked(const CEGUI::EventArgs& e)
{
	m_gui.editBoxBodeGraph->show();
	initHUDText();
	return true;
}

/* ----------------------------------------------------------------------------------- */
/* NAME: displayBodeGraph															   */
/* ROLE: Display Bode graph with min/max freq and nb points							   */
/* IN: none																			   */
/* OUT: none																		   */
/* RVALUE: none																		   */
/* ------------------------------------------------------------------------------------*/
void BodeMenuScreen::displayBodeGraph()
{
	m_fctDiscret->Bode
	(
		m_axisData.freqMin,
		m_axisData.freqMax,
		m_axisData.nbpoint,
		&(m_axisData.nbOfDecade),
		m_rawCalculatedBodeGraph
	);

	static const glm::vec2 sizeGUI{ GUI_FACTOR_SIZE * float(m_gui.window->GETscreenWidth()) / 2.0f };

	createAxis();

	searchMaxValues();

	m_displayCalculatedBodeGraph.resize(m_rawCalculatedBodeGraph.size());

	static const double screenWidth{ (double)m_gui.window->GETscreenWidth() };
	static const double screenHeight{ (double)m_gui.window->GETscreenHeight() };
	static const unsigned int scPerDecade{ (unsigned int)std::floor((screenWidth - screenWidth / 16.0) / (double)m_axisData.nbOfDecade) };
	static const unsigned int endLoop{ m_axisData.nbpoint / m_axisData.nbOfDecade };
	static const double screenHeightDIV32{ screenHeight / 32.0 };
	static const double screenHeightDIV16Bor{ screenHeight - screenHeight / 16.0 };
	static const double screenWidthDIV32{ screenWidth / 32.0 };
	unsigned int currentIndex{ 0 };

	m_gui.spriteBatchHUDStatic.begin();

	for (unsigned int j{ OFFSET_BODEGRAPH_NB_DECADE }; j < m_axisData.nbOfDecade + OFFSET_BODEGRAPH_NB_DECADE; j++)
	{

		for (unsigned int ic{ 0 }; ic < endLoop; ic++)
		{
			currentIndex = ic + ((j - OFFSET_BODEGRAPH_NB_DECADE) * endLoop);
			m_displayCalculatedBodeGraph[currentIndex].gain = computeValueToScale
			(
				m_rawCalculatedBodeGraph[currentIndex].gain,
				m_maxValues.minGain,
				m_maxValues.maxGain,
				screenHeightDIV32,
				screenHeightDIV16Bor
			);


			m_displayCalculatedBodeGraph[currentIndex].freq = computeValueToScale
			(
				m_rawCalculatedBodeGraph[currentIndex].freq,
				m_rawCalculatedBodeGraph[((j - OFFSET_BODEGRAPH_NB_DECADE) * endLoop)].freq,
				m_rawCalculatedBodeGraph[(j * endLoop) - OFFSET_BODEGRAPH_NB_DECADE].freq,
				screenWidthDIV32 + ((j - OFFSET_BODEGRAPH_NB_DECADE) * scPerDecade),
				screenWidthDIV32 + (j * scPerDecade)
			);


			m_displayCalculatedBodeGraph[currentIndex].phase = computeValueToScale
			(
				m_rawCalculatedBodeGraph[currentIndex].phase,
				m_maxValues.minPhase,
				m_maxValues.maxPhase,
				screenHeightDIV32,
				screenHeightDIV16Bor
			);


			m_gui.spriteFont->draw
			(
				m_gui.spriteBatchHUDStatic,
				"+",
				{
					m_displayCalculatedBodeGraph[currentIndex].freq,
					m_displayCalculatedBodeGraph[currentIndex].gain
				},
				sizeGUI, NO_DEPTH,
				RealEngine2D::COLOR_RED,
				RealEngine2D::Justification::MIDDLE
			);
			m_gui.spriteFont->draw
			(
				m_gui.spriteBatchHUDStatic,
				"o",
				{
					m_displayCalculatedBodeGraph[currentIndex].freq,
					m_displayCalculatedBodeGraph[currentIndex].phase
				},
				sizeGUI, NO_DEPTH,
				RealEngine2D::COLOR_GREEN,
				RealEngine2D::Justification::MIDDLE
			);

		}
	}


	m_gui.spriteFont->draw
	(
		m_gui.spriteBatchHUDStatic,
		m_axisData.xAxis.c_str(),
		{ float(m_gui.window->GETscreenWidth()) / 2.f, float(m_gui.window->GETscreenHeight()) / 2.f },
		sizeGUI, NO_DEPTH,
		RealEngine2D::COLOR_BLUE,
		RealEngine2D::Justification::MIDDLE
	);
	m_gui.spriteFont->draw
	(
		m_gui.spriteBatchHUDStatic,
		m_axisData.yAxis.c_str(),
		{ float(m_gui.window->GETscreenWidth()) / 2.f, float(m_gui.window->GETscreenHeight()) / 32.f },
		sizeGUI, NO_DEPTH,
		RealEngine2D::COLOR_BLUE,
		RealEngine2D::Justification::LEFT
	);

	m_gui.spriteBatchHUDStatic.end();
}

/* ----------------------------------------------------------------------------------- */
/* NAME: searchMaxValues															   */
/* ROLE: Search min/max Gain and Phase in m_rawCalculatedBodeGraph					   */
/* IN: none																			   */
/* OUT: none																		   */
/* RVALUE: none																		   */
/* ------------------------------------------------------------------------------------*/
void BodeMenuScreen::searchMaxValues()
{
	for (unsigned int ic = 0; ic < m_rawCalculatedBodeGraph.size(); ic++)
	{
		if (m_rawCalculatedBodeGraph[ic].gain > m_maxValues.maxGain)
		{
			m_maxValues.maxGain = m_rawCalculatedBodeGraph[ic].gain;
		}

		if (m_rawCalculatedBodeGraph[ic].gain < m_maxValues.minGain)
		{
			m_maxValues.minGain = m_rawCalculatedBodeGraph[ic].gain;
		}

		if (m_rawCalculatedBodeGraph[ic].phase > m_maxValues.maxPhase)
		{
			m_maxValues.maxPhase = m_rawCalculatedBodeGraph[ic].phase;
		}

		if (m_rawCalculatedBodeGraph[ic].phase < m_maxValues.minPhase)
		{
			m_maxValues.minPhase = m_rawCalculatedBodeGraph[ic].phase;
		}
	}
}

/* ----------------------------------------------------------------------------------- */
/* NAME: createAxis																	   */
/* ROLE: Create axis x and y														   */
/* IN: none																			   */
/* OUT: none																		   */
/* RVALUE: none																		   */
/* ------------------------------------------------------------------------------------*/
void BodeMenuScreen::createAxis()
{
	const unsigned int xAxisSize = (unsigned int)std::ceil((m_gui.window->GETscreenWidth()) / (5.f));
	const unsigned int yAxisSize = (unsigned int)std::ceil(float(m_gui.window->GETscreenHeight()) / (18.f));

	m_axisData.xAxis.clear();
	m_axisData.yAxis.clear();

	for (unsigned int i{ 0 }; i < xAxisSize; i++)
	{
		m_axisData.xAxis += '-';
	}
	for (unsigned int i{ 0 }; i < yAxisSize; i++)
	{
		m_axisData.yAxis += "|\n";
	}
}

