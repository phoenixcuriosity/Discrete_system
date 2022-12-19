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

#ifndef BodeMenuScreen_H
#define BodeMenuScreen_H

#include "LIB.h"

#include <RealEngine2D/src/IGameScreen.h>

#include <vector>

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

typedef struct
{
	RealEngine2D::GUI gui;

	std::shared_ptr<RealEngine2D::SpriteFont> spriteFont;
	RealEngine2D::GLSLProgram* gLSLProgram;
	RealEngine2D::Camera2D cameraHUD;

	RealEngine2D::SpriteBatch spriteBatchHUDDynamic;
	RealEngine2D::SpriteBatch spriteBatchHUDStatic;

	RealEngine2D::Window* window;

	CEGUI::PushButton* returnMainMenu;

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


private:


	bool onReturnMainMenuClicked(const CEGUI::EventArgs& e);


public:


private:
	int m_nextScreenIndexMenu = INIT_SCREEN_INDEX;

	BodeMenuGUI m_gui;

	File* m_file;

	/* Fonctionnal data */
	FCTDiscret* m_fctDiscret;

	bool m_isInitialize;
};

#endif // !BodeMenuScreen_H


