/*

	Discrete_system
	Copyright SAUTER Robin 2017-2023 (robin.sauter@orange.fr)
	file version 4.1.0

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

#ifndef FCTMenuScreen_H
#define FCTMenuScreen_H

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

#define ERROR_ORDER_FCT_CREATION_TOOL -1
#define MIN_ORDER_FCT_CREATION_TOOL 0

typedef enum
{
	FCT_msgType_nothing			= 0,
	display_FCT					= 1,
	display_FCT_JuryTab			= 2,
	FCT_CreationTool_order_Num	= 3,
	FCT_CreationTool_order_Den	= 4,
	FCT_CreationTool_coef		= 5
} FCT_msgType;

typedef enum
{
	InputToNumDen_nothing = 0,
	num					  = 1,
	den					  = 2
} InputToNumDen;

typedef struct
{
	InputToNumDen inputToNumDen;
	double currentCoef;
	int order;
} FCTCreationTool;

typedef struct
{
	RealEngine2D::GUI gui;

	std::shared_ptr<RealEngine2D::SpriteFont> spriteFont;
	RealEngine2D::GLSLProgram* gLSLProgram;
	RealEngine2D::Camera2D cameraHUD;

	RealEngine2D::SpriteBatch spriteBatchHUDDynamic;
	RealEngine2D::SpriteBatch spriteBatchHUDStatic;

	RealEngine2D::Window* window;

	CEGUI::PushButton* secondOrdreButton;
	CEGUI::PushButton* integButton;

	CEGUI::PushButton* createFCT;
	CEGUI::PushButton* SetNum;
	CEGUI::PushButton* SetDen;

	CEGUI::PushButton* juryProcessButton;
	CEGUI::PushButton* BodeGraphButton;

	CEGUI::PushButton* returnMainMenu;

	CEGUI::Editbox* editBox;

	std::string s_numFCT;
	std::string s_barFCT;
	std::string s_denFCT;
	std::string s_jury;

} FCTMenuGUI;

class FCTMenuScreen : public RealEngine2D::IGameScreen
{
public:
	FCTMenuScreen
	(
		File* file,
		FCTDiscret* m_fctDiscret,
		GUI_Parameters& parameters
	);
	~FCTMenuScreen();

	virtual int getNextScreenIndex()const override;
	virtual int getPreviousScreenIndex()const override;

	virtual void build() override;
	virtual void destroy() override;

	virtual bool onEntry() override;
	virtual void onExit() override;

private:

	virtual void initHUDText(FCT_msgType msgType);
	virtual void CreateModifyFCT();
	virtual void KeyMouseinput(const SDL_Event& ev);

public:

	virtual void update() override;
	virtual void draw() override;


private:


	bool onsecondOrdreButtonClicked(const CEGUI::EventArgs& e);
	bool onIntegButtonClicked(const CEGUI::EventArgs& e);
	bool onCreateModifyFCTButtonClicked(const CEGUI::EventArgs& e);
	bool onSetNumButtonClicked(const CEGUI::EventArgs& e);
	bool onSetDenButtonClicked(const CEGUI::EventArgs& e);
	bool onJuryButtonClicked(const CEGUI::EventArgs& e);
	bool onBodeGraphButtonClicked(const CEGUI::EventArgs& e);
	bool onReturnMainMenuClicked(const CEGUI::EventArgs& e);

	void fctHUDfilled();
	void FCTCreationToolFonction();

public:


private:
	int m_nextScreenIndexMenu = INIT_SCREEN_INDEX;

	FCTMenuGUI m_gui;

	File* m_file;

	/* Fonctionnal data */
	FCTDiscret* m_fctDiscret;
	bool m_isStable;

	FCTCreationTool m_FCTCreationTool;

	bool m_isInitialize;
};

#endif // !FCTMenuScreen_H



