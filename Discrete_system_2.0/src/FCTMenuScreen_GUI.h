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

#ifndef FCTMenuScreen_GUI_H
#define FCTMenuScreen_GUI_H

/* *********************************************************
 *						Constantes						   *
 ********************************************************* */

#define GUI_DISPLAY_FCT_SIZE 0.8f
#define GUI_DISPLAY_JURY_SIZE 0.64f

#define GUI_DISPLAY_SIZE_REF 1920.f

#define GUI_DISPLAY_FCT_SPACE_FACTOR 100.f

#define GUI_FACTOR_SIZE GUI_DISPLAY_FCT_SIZE / GUI_DISPLAY_SIZE_REF
#define GUI_FACTOR_JURY_SIZE GUI_DISPLAY_JURY_SIZE / GUI_DISPLAY_SIZE_REF

#define GUI_SPACE_FCT_Y GUI_FACTOR_SIZE * GUI_DISPLAY_FCT_SPACE_FACTOR
#define GUI_SPACE_JURY_Y GUI_FACTOR_JURY_SIZE * GUI_DISPLAY_FCT_SPACE_FACTOR

#define GUI_SPACE_BETWEEN_FCT_JURY 2.f

#define GUI_SKIN_THEME std::string("AlfiskoSkin")
#define GUI_SKIN_THEME_SCHEME GUI_SKIN_THEME + std::string(".scheme")
#define GUI_SKIN_THEME_BUTTON GUI_SKIN_THEME + std::string("/Button")
#define GUI_SKIN_THEME_Editbox GUI_SKIN_THEME + std::string("/Editbox")
#define GUI_SKIN_THEME_MOUSE GUI_SKIN_THEME + std::string("/MouseArrow")
#define GUI_SKIN_FONT std::string("DejaVuSans-12")

#define GUI_HIDE_NORMAL_CURSOR int(0)


#endif // !FCTMenuScreen_GUI_H

