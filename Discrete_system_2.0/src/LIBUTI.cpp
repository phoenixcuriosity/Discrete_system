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

#include "LIBUTI.h"

bool checkMinMaxValidityRange
(
	double min,
	double max
)
{
	if (min < max)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool checkDIVDen(double value)
{
	if (value < PRECISION_DIV && value > -PRECISION_DIV)
	{
		return false;
	}
	return true;
}

double computeValueToScale
(
	double value,
	double minValue,
	double maxValue,
	double minScale,
	double maxScale,
	int divToScaleSize /* = 1 */
)
{
	if (checkMinMaxValidityRange(minValue, maxValue) && checkMinMaxValidityRange(minScale, maxScale))
	{
		double result(value);
		double rangeValue(maxValue - minValue);
		double rangeScale(maxScale - minScale);

		if ((checkDIVDen(rangeValue) == false) || (checkDIVDen(divToScaleSize) == false))
		{
			return 0.0;
		}

		result = result / divToScaleSize;

		result -= minValue;

		result = result / rangeValue;

		result *= rangeScale;

		result += minScale;

		return result;
	}
	else
	{
		throw("[ERROR]___: computeValueToScale : checkMinMaxValidityRange");
	}
}