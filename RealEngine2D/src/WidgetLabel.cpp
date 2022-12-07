/*

	Civ_rob_2
	Copyright SAUTER Robin 2017-2021 (robin.sauter@orange.fr)
	last modification on this file on version:0.23.9.0
	file version : 1.1

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Civ_rob_2.0

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

#include "WidgetLabel.h"

#include "Window.h"
#include "SpriteFont.h"
#include "SpriteBatch.h"

namespace RealEngine2D
{



void WidgetLabel::draw(RealEngine2D::SpriteBatch& sb, RealEngine2D::SpriteFont& sf, RealEngine2D::Window& w)
{
	if (!widget->isVisible()) return;
	glm::vec2 pos;
	pos.x = widget->getInnerRectClipper().getPosition().d_x + widget->getInnerRectClipper().getWidth() / 2.0f;
	pos.y = w.GETscreenHeight() - widget->getInnerRectClipper().getPosition().d_y;

	sf.draw(sb, text.c_str(), pos, glm::vec2(0.24f), 0.0f, color, Justification::MIDDLE);
}

}
