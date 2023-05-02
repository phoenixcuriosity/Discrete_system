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

#ifndef BodeMenuScreen_H
#define BodeMenuScreen_H

#include "LIB.h"

#include <RealEngine2D/src/IGameScreen.h>

#include "BodeGraphData.h"

#include <RealEngine2D\src\Vertex.h>
#include <RealEngine2D\src\GLSLProgram.h>
#include <RealEngine2D\src\GameEngine.h>
#include <RealEngine2D\src\Window.h>
#include <RealEngine2D\src\Camera2D.h>
#include <RealEngine2D\src\SpriteBatch.h>
#include <RealEngine2D\src\InputManager.h>
#include <RealEngine2D\src\Timing.h>
#include <RealEngine2D\src\SpriteFont.h>
#include <RealEngine2D/src/AudioEngine.h>
#include <RealEngine2D/src/GUI.h>




struct File;
struct GUI_Parameters;

typedef enum 
{
	editFreqMin = 1,
	editFreqMax = 2,
	editNbPoint = 3
}BodeInputGUI;

typedef struct
{
	double maxGain;
	double minGain;

	double maxPhase;
	double minPhase;
} MaxValues;

typedef struct
{
	std::string xAxis;
	std::string yAxis;
	unsigned int nbOfDecade;
	unsigned int nbpoint;
	double freqMin;
	double freqMax;
} AxisData;

typedef struct
{
	RealEngine2D::GUI gui;

	BodeInputGUI bodeInputGUI;

	std::shared_ptr<RealEngine2D::SpriteFont> spriteFont;
	RealEngine2D::GLSLProgram* gLSLProgram;
	RealEngine2D::Camera2D cameraHUD;

	RealEngine2D::SpriteBatch spriteBatchHUDDynamic;
	RealEngine2D::SpriteBatch spriteBatchHUDStatic;

	RealEngine2D::Window* window;

	CEGUI::PushButton* returnMainMenu;
	CEGUI::PushButton* editBodeGraph;

	CEGUI::Editbox* editBoxBodeGraph;

} BodeMenuGUI;

class BodeMenuScreen : public RealEngine2D::IGameScreen
{
public:
	BodeMenuScreen
	(
		File* file,
		FCTDiscret* m_fctDiscret,
		GUI_Parameters& parameters
	);
	~BodeMenuScreen();

	virtual int getNextScreenIndex()const override;
	virtual int getPreviousScreenIndex()const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual bool onEntry() override;
	virtual void onExit() override;

private:

	virtual void initHUDText();

public:

	virtual void update() override;
	virtual void draw() override;

	void KeyMouseinput(const SDL_Event& ev);

private:


	bool onReturnMainMenuClicked(const CEGUI::EventArgs& e);
	bool onEditBodeGraphClicked(const CEGUI::EventArgs& e);

private:

	void displayBodeGraph();

	void searchMaxValues();

	void createAxis();


public:


private:
	int m_nextScreenIndexMenu = INIT_SCREEN_INDEX;

	BodeMenuGUI m_gui;

	File* m_file;

	/* Fonctionnal data */
	FCTDiscret* m_fctDiscret;

	BodeGraph m_rawCalculatedBodeGraph;
	BodeGraph m_displayCalculatedBodeGraph;

	MaxValues m_maxValues;
	AxisData m_axisData;

	bool m_isInitialize;
};

#endif // !BodeMenuScreen_H



