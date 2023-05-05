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

#ifndef LIBUTI_H
#define LIBUTI_H

#define PRECISION_DIV 1e-12

#include <string>

enum class ValidityCheckMinDouble : bool
{
	InvalidRange = false,
	ValidRange = true
};

/* ----------------------------------------------------------------------------------- */
/* NAME: checkMinDouble																   */
/* ROLE: Check if the value is not in range of precision : +-PRECISION_DIV			   */
/* RVALUE: false -> value out of range ; true : value in range						   */
/* ------------------------------------------------------------------------------------*/
ValidityCheckMinDouble checkMinDouble
(
	/* IN */
	const double value
);

double computeValueToScale
(
	double value,
	double minValue,
	double maxValue,
	double minScale,
	double maxScale,
	int divToScaleSize = 1
);

std::string inverseLineRead(const std::string& txt);

#endif // !LIBUTI_H

