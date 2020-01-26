/*

	Discrete_system
	Copyright SAUTER Robin 2017-2020 (robin.sauter@orange.fr)
	last modification on this file on version: 3.2
	file version 2.1

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

#include "IHM.h"
#include "discrete_system_LIB.h"
#include "LIB.h"
#include "KeyboardMouse.h"
#include "End.h"


/*
* NAME : showStartSuccess
* ROLE : Affiche sur la console si le programme à réussi à démarrer
* INPUT  PARAMETERS : void
* OUTPUT PARAMETERS : Affichage sur la console et dans le fichier log
* RETURNED VALUE    : void
*/
void IHM::showStartSuccess()
{
	logfileconsole("_________START PROGRAM_________");
	logfileconsole("Dev version: 3.1");
	logfileconsole("Created by SAUTER Robin");
	logfileconsole("This is a free software, you can redistribute it and/or modify it\n");
}

/*
* NAME : logfileconsole
* ROLE : Affiche sur la console et dans le fichier log le std::string en entrée
* INPUT  PARAMETERS : const std::string& msg : le message en entrée
* OUTPUT PARAMETERS : Affichage sur la console et dans le fichier log
* RETURNED VALUE    : void
*/
void IHM::logfileconsole(const std::string& msg)
{
	const std::string logtxt = "bin/files/log.txt";
	std::ofstream log(logtxt, std::ios::app);
	if (log)
	{
		std::cout << std::endl << msg;
		log << std::endl << msg;
	}
	else
		std::cout << std::endl << "ERREUR: Impossible d'ouvrir le Fichier : " << logtxt;
}

void IHM::rendueEcran(Sysinfo& sysinfo)
{
	SDL_RenderClear(sysinfo.screen.renderer);
	
	switch (sysinfo.var.stateScreen)
	{

	/* *********************************************************
	 *					  STATEecrantitre					   *
	 ********************************************************* */

	case STATEecrantitre:
		
		for (const auto& n : sysinfo.allTextes.txtEcranTitre)
		{
			n.second->renderTextureTestStates(sysinfo.var.stateScreen, sysinfo.var.select);
		}

		for (const auto& n : sysinfo.allButtons.ecranTitre)
		{
			n.second->renderButtonTexte(sysinfo.var.stateScreen);
		}

		break;

	/* *********************************************************
	 *					 STATEfunctionTransfer				   *
	 ********************************************************* */

	case STATEfunctionTransfer:

		rendueEcranFCT(sysinfo);

		break;

	/* *********************************************************
	 *					 STATETFcreateNumDen				   *
	 ********************************************************* */

	case STATETFcreateNumDen:

		rendueEcranFCT(sysinfo);

		break;

	/* *********************************************************
	 *					 STATEfunctionTransfer				   *
	 ********************************************************* */

	case STATETFcreateBode:

		rendueEcranFCT(sysinfo);

		break;

	/* *********************************************************
	 *					 STATETFdisplayBode					   *
	 ********************************************************* */

	case STATETFdisplayBode:

		rendueEcranFCT(sysinfo);

		break;

	/* *********************************************************
	 *					 STATEstateSystem					   *
	 ********************************************************* */

	case STATEstateSystem:

		rendueEcranSYSETAT(sysinfo);

		break;

	/* *********************************************************
	 *					 STATESScreateMatrice				   *
	 ********************************************************* */

	case STATESScreateMatrice:

		rendueEcranSYSETAT(sysinfo);

		break;

	/* *********************************************************
	 *					 STATESSsimulate					   *
	 ********************************************************* */

	case STATESSsimulate:

		rendueEcranSYSETAT(sysinfo);

		break;

	/* *********************************************************
	 *					 STATEreponseTemporelle				   *
	 ********************************************************* */

	case STATEreponseTemporelle:

		rendueEcranSYSETAT(sysinfo);

		break;

	}

	SDL_RenderPresent(sysinfo.screen.renderer);
}

void IHM::rendueEcranFCT(Sysinfo& sysinfo)
{
	for (const auto& n : sysinfo.allTextes.CreateNumDen)
	{
		n.second->renderTextureTestStates(sysinfo.var.stateScreen, sysinfo.var.select);
	}

	for (const auto& n : sysinfo.allButtons.ecranFCT)
	{
		n.second->renderButtonTexte(sysinfo.var.stateScreen);
	}	
}

void IHM::rendueEcranSYSETAT(Sysinfo& sysinfo)
{
	for (const auto& n : sysinfo.allButtons.ecranSYSETAT)
	{
		n.second->renderButtonTexte(sysinfo.var.stateScreen);
	}
}



void IHM::CreateNumDen(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_ Start CreateNumDen _");


	/* *********************************************************
	 *							Num							   *
	 ********************************************************* */

	sysinfo.var.stateScreen = STATETFcreateNumDen;
	
	End::deleteFCTDiscret(sysinfo.fctDiscret);
	sysinfo.fctDiscret = new FCTDiscret;

	sysinfo.allTextes.CreateNumDen.clear();
	rendueEcran(sysinfo);

	Texte::writeTexte
	(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 50,
		no_angle
	);

	Texte::writeTexte
	(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Order of the Numerator : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50,
		no_angle, center_x
	);
	SDL_RenderPresent(sysinfo.screen.renderer);



	sysinfo.fctDiscret->GETnum()->SETorder
		(KeyboardMouse::CinNumberUnsignedInt(sysinfo, "Order of the Numerator : ", SCREEN_WIDTH / 2, 50));


	Texte::loadTexte
	(sysinfo.screen.renderer, sysinfo.allTextes.font,
		sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.CreateNumDen,
		blended, "Order of the Numerator : " + std::to_string(sysinfo.fctDiscret->GETnum()->GETorder()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, nonTransparent,
		no_angle, center_x
	);

	rendueEcran(sysinfo);


	for (unsigned int z = 0; z <= sysinfo.fctDiscret->GETnum()->GETorder(); z++)
	{
		Texte::writeTexte
		(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "coef order:" + std::to_string(z) + " = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 75,
			no_angle, center_x
		);

		SDL_RenderPresent(sysinfo.screen.renderer);

		sysinfo.fctDiscret->GETnum()->SETcoefTab
			(z, KeyboardMouse::CinNumberDouble(sysinfo, "coef order:" + std::to_string(z) + " = ", SCREEN_WIDTH / 2, 75));
		
		rendueEcran(sysinfo);
	}


	/* *********************************************************
	 *							Den							   *
	 ********************************************************* */


	Texte::writeTexte
	(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Order of the Denominator : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100,
		no_angle, center_x
	);

	SDL_RenderPresent(sysinfo.screen.renderer);

	sysinfo.fctDiscret->GETden()->SETorder
		(KeyboardMouse::CinNumberUnsignedInt(sysinfo, "Order of the Denominator : ", SCREEN_WIDTH / 2, 100));
	
	
	Texte::loadTexte
	(sysinfo.screen.renderer, sysinfo.allTextes.font,
		sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.CreateNumDen,
		blended, "Order of the Denominator : " + std::to_string(sysinfo.fctDiscret->GETden()->GETorder()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, nonTransparent,
		no_angle, center_x
	);

	rendueEcran(sysinfo);

	for (unsigned int z = 0; z <= sysinfo.fctDiscret->GETden()->GETorder(); z++)
	{
		Texte::writeTexte
		(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "coef order:" + std::to_string(z) + " = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 125,
			no_angle, center_x
		);

		SDL_RenderPresent(sysinfo.screen.renderer);

		sysinfo.fctDiscret->GETden()->SETcoefTab
			(z, KeyboardMouse::CinNumberDouble(sysinfo, "coef order:" + std::to_string(z) + " = ", SCREEN_WIDTH / 2, 125));
		
		rendueEcran(sysinfo);
	}


	/* *********************************************************
	 *						Sampling time					   *
	 ********************************************************* */

	Texte::writeTexte
	(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Sampling time : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150,
		no_angle, center_x
	);

	SDL_RenderPresent(sysinfo.screen.renderer);

	sysinfo.fctDiscret->SETdeltaT
		(KeyboardMouse::CinNumberDouble(sysinfo, "Sampling time : ", SCREEN_WIDTH / 2, 150));

	Texte::loadTexte
	(sysinfo.screen.renderer, sysinfo.allTextes.font,
		sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.CreateNumDen,
		blended, "Sampling time : " + std::to_string(sysinfo.fctDiscret->GETdeltaT()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, nonTransparent,
		no_angle, center_x
	);

	rendueEcran(sysinfo);

	sysinfo.var.stateScreen = STATEfunctionTransfer;
	rendueEcran(sysinfo);

	IHM::logfileconsole("_ End CreateNumDen _");
}






void IHM::displayTF(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_ Start displayTF _");
	std::ostringstream stream; std::string texte;
	std::string barre;

	if (sysinfo.fctDiscret == nullptr)
	{
		Texte::writeTexte
		(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "TF doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 175, 148,
			no_angle, center_y
		);

		SDL_RenderPresent(sysinfo.screen.renderer);
	}
	else
	{
		unsigned int stringSize = 0;
		stringSize = std::max(sysinfo.fctDiscret->GETnum()->GETstringSize(), sysinfo.fctDiscret->GETden()->GETstringSize());

		for (unsigned int i = 0; i < sysinfo.fctDiscret->GETden()->GETstringSize(); i++)
			barre += "-";

		stream << sysinfo.fctDiscret->GETnum()->printOn(false); texte = stream.str(); stream.str(""); stream.clear();

		Texte::writeTexte
		(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, texte, { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 550,
			no_angle, center_x
		);

		Texte::writeTexte
		(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, barre, { 0, 64, 255, 255 }, NoColor, 24, SCREEN_WIDTH / 2, 564,
			no_angle, center_x
		);

		stream << sysinfo.fctDiscret->GETden()->printOn(false); texte = stream.str(); stream.str(""); stream.clear();

		Texte::writeTexte
		(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, texte, { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 580,
			no_angle, center_x
		);

		SDL_RenderPresent(sysinfo.screen.renderer);
	}
	IHM::logfileconsole("_ End displayTF _");
}



void IHM::displayJury(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_ Start displayJury _");
	unsigned int initspace = 300;
	std::string texte; std::ostringstream stream;

	stream << std::fixed << std::setprecision(4);
	if (sysinfo.fctDiscret == nullptr)
	{
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "TF doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 175, 196, no_angle, center_y);
		SDL_RenderPresent(sysinfo.screen.renderer);
	}
	else
	{
		if (sysinfo.fctDiscret->tabJury())
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "The system is stable", { 0, 255, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 100, 196, no_angle, center_y);
		else
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "The system is unstable", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 100, 196, no_angle, center_y);

		for (unsigned int i = 0; i < sysinfo.fctDiscret->GETjury()->GETlength(); i++)
		{
			stream << "|";
			for (unsigned int j = 0; j < sysinfo.fctDiscret->GETjury()->GETheight(); j++)
				if(sysinfo.fctDiscret->GETjury()->GETthiscoef(i, j) >= 0)
					stream << "    " << sysinfo.fctDiscret->GETjury()->GETthiscoef(i, j) << " ";
				else
					stream << "   -" << abs(sysinfo.fctDiscret->GETjury()->GETthiscoef(i, j)) << " ";
			stream << "|";
			texte = stream.str();
			stream.str("");
			stream.clear();
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, texte, { 255, 255, 255, 255 }, NoColor, 16, 100, initspace += 16, no_angle);
		}
	}
	SDL_RenderPresent(sysinfo.screen.renderer);
	IHM::logfileconsole("_ End displayJury _");
}




void IHM::displayBode(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_ Start displayBode _");
	double wmin = 0, wmax = 0;
	unsigned int nbpoint = 0;

	FCTDiscret FCT;
	if (sysinfo.fctDiscret == nullptr) 
	{
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "TF doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 175, 244, no_angle, center_y);
		SDL_RenderPresent(sysinfo.screen.renderer);
	}
	else 
	{
		sysinfo.var.stateScreen = STATETFcreateBode;
		IHM::rendueEcran(sysinfo);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "W min : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, no_angle, center_x);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 50, no_angle);
		SDL_RenderPresent(sysinfo.screen.renderer);
		wmin = KeyboardMouse::CinNumberDouble(sysinfo, "W min : ", SCREEN_WIDTH / 2, 50);
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
			blended, "W min : " + std::to_string(wmin), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, nonTransparent, no_angle, center_x);
		IHM::rendueEcran(sysinfo);

		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "W max : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, no_angle, center_x);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 100, no_angle);
		SDL_RenderPresent(sysinfo.screen.renderer);
		wmax = KeyboardMouse::CinNumberDouble(sysinfo, "W max : ", SCREEN_WIDTH / 2, 100);
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
			blended, "W max : " + std::to_string(wmax), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, nonTransparent, no_angle, center_x);
		IHM::rendueEcran(sysinfo);

		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "Number of points : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, no_angle, center_x);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 150, no_angle);
		SDL_RenderPresent(sysinfo.screen.renderer);
		nbpoint = KeyboardMouse::CinNumberUnsignedInt(sysinfo, "Number of points : ", SCREEN_WIDTH / 2, 150);
		Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
			blended, "Number of points : " + std::to_string(nbpoint), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, nonTransparent, no_angle, center_x);
		IHM::rendueEcran(sysinfo);

		sysinfo.var.stateScreen = STATETFdisplayBode;
		IHM::rendueEcran(sysinfo);

		double** gainPhase = new double*[3];
		for (unsigned int i = 0; i < 3; i++)
			gainPhase[i] = new double[nbpoint];

		for (unsigned int i = 0; i < 3; i++)
		{
			for (unsigned int j = 0; j < nbpoint; j++)
				gainPhase[i][j] = 0;
		}
		sysinfo.fctDiscret->Bode(wmin, wmax, nbpoint, gainPhase);

		double gainMax = gainPhase[1][0], gainMin = gainPhase[1][0];
		double phaseMax = gainPhase[2][0], phaseMin = gainPhase[2][0];
		for (unsigned int i = 0; i < nbpoint; i++)
		{
			if (gainPhase[1][i] > gainMax)
				gainMax = gainPhase[1][i];
			if (gainPhase[1][i] < gainMin)
				gainMin = gainPhase[1][i];

			if (gainPhase[2][i] > phaseMax)
				phaseMax = gainPhase[2][i];
			if (gainPhase[2][i] < phaseMin)
				phaseMin = gainPhase[2][i];
		}

		double amplitudeGain = std::max(abs(gainMax), abs(gainMin));
		double amplitudePhase = std::max(abs(phaseMax), abs(phaseMin));

		std::string barre;
		barre = "";
		for (unsigned int z = 0; z < 100; z++)
			barre += "-";
		barre += ">w(2xPixf)";
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, barre, { 255, 255, 255, 255 }, NoColor, 16, 40, 460, no_angle, center_y);
		barre = "";
		unsigned int initspace = 14;
		for (unsigned int z = 0; z < 30; z++)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "|", { 255, 255, 255, 255 }, NoColor, 16, 50, initspace += 16, no_angle, center_x);

		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, std::to_string(wmin), { 255, 255, 255, 255 }, NoColor, 10, 30, 472, no_angle, center_y);
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, std::to_string(wmax), { 255, 255, 255, 255 }, NoColor, 10, 530, 472, no_angle, center_y);

		unsigned int x0 = 50, xmax = 550;
		unsigned int ymingain = 30, ymaxgain = 230;
		unsigned int yminphase = 250, ymaxphase = 450;
		//double pasGraph = (xmax - x0) / nbpoint;
		double ecartRelatif = wmax / wmin;
		unsigned int longeurAxe = xmax - x0;
		double* pasGraph = new double[nbpoint];
		pasGraph[0] = 0;
		double increment = (wmax - wmin) / nbpoint;
		double nbpointParDecade = 50;
		for (unsigned int i = 0; i < 10; i++)
		{
			pasGraph[i] = ((longeurAxe * log(gainPhase[0][i])) / log(ecartRelatif)) + 250;
			std::cout << std::endl << i << " , " << pasGraph[i] << " , " << gainPhase[0][i];
		}


		for (unsigned int z = x0, n = 0; z < xmax, n < 10; z += (unsigned int)pasGraph[n], n++)
		{
			Texte::writeTexte
			(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "+", { 255, 0, 0, 255 }, NoColor, 8,
				x0 + z, ymaxgain - (unsigned int)((gainPhase[1][n] / amplitudeGain) * (ymaxgain - ymingain)),
				no_angle, center
			);
			//writetxt(sysinfo, "+", { 0, 255, 0, 255 }, 8, x0 + z, yminphase - ((gainPhase[2][n] / amplitudePhase) * (ymaxphase - yminphase)), center);
		}
		SDL_RenderPresent(sysinfo.screen.renderer);


		delete[] pasGraph;

		for (unsigned int i = 0; i < 3; i++)
			delete[] gainPhase[i];
		delete[] gainPhase;
	}

	IHM::logfileconsole("_ End displayBode _");
}




void IHM::createMatrice(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_ Start createMatrice _");
	sysinfo.var.stateScreen = STATESScreateMatrice;
	IHM::rendueEcran(sysinfo);

	End::deleteSYSETATDiscret(sysinfo.sysetatDiscret);
	sysinfo.sysetatDiscret = new SYSETATDiscret;

	unsigned int length = 0;


	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Length or height of A : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, no_angle, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 50, no_angle);
	SDL_RenderPresent(sysinfo.screen.renderer);
	length = KeyboardMouse::CinNumberUnsignedInt(sysinfo, "Length or height of A : ", SCREEN_WIDTH / 2, 50);
	sysinfo.sysetatDiscret->SETeditSizeA(length, length);
	sysinfo.sysetatDiscret->SETeditSizeB(length, 1);
	sysinfo.sysetatDiscret->SETeditSizeC(1, length);
	sysinfo.sysetatDiscret->SETeditSizeD(1, 1);
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select,
		sysinfo.allTextes.txtEcranTitre, blended,
		"Length of A : " + std::to_string(sysinfo.sysetatDiscret->GETA()->GETlength()) + " and Height of A : " + std::to_string(sysinfo.sysetatDiscret->GETA()->GETheight()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 50, nonTransparent, no_angle, center_x);
	IHM::rendueEcran(sysinfo);

	displayStateSystem(sysinfo);

	for (unsigned int i = 0; i < sysinfo.sysetatDiscret->GETA()->GETlength(); i++)
	{
		for (unsigned int j = 0; j < sysinfo.sysetatDiscret->GETA()->GETheight(); j++)
		{
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 75, no_angle, center_x);
			SDL_RenderPresent(sysinfo.screen.renderer);
			sysinfo.sysetatDiscret->SETthisCoefA(i, j, KeyboardMouse::CinNumberDouble(sysinfo, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", SCREEN_WIDTH / 2, 75));
			IHM::rendueEcran(sysinfo);
			displayStateSystem(sysinfo);
		}
	}

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select,
		sysinfo.allTextes.txtEcranTitre, blended,
		"Length of B : " + std::to_string(sysinfo.sysetatDiscret->GETB()->GETlength()) + " and Height of B : " + std::to_string(sysinfo.sysetatDiscret->GETB()->GETlength()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 100, nonTransparent, no_angle, center_x);
	IHM::rendueEcran(sysinfo);
	displayStateSystem(sysinfo);

	for (unsigned int i = 0; i < sysinfo.sysetatDiscret->GETB()->GETlength(); i++)
	{
		for (unsigned int j = 0; j < sysinfo.sysetatDiscret->GETB()->GETheight(); j++)
		{
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 125, no_angle, center_x);
			SDL_RenderPresent(sysinfo.screen.renderer);
			sysinfo.sysetatDiscret->SETthisCoefB(i, j, KeyboardMouse::CinNumberDouble(sysinfo, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", SCREEN_WIDTH / 2, 125));
			IHM::rendueEcran(sysinfo);
			displayStateSystem(sysinfo);
		}
	}

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select,
		sysinfo.allTextes.txtEcranTitre, blended,
		"Length of C : " + std::to_string(sysinfo.sysetatDiscret->GETC()->GETlength()) + " and Height of C : " + std::to_string(sysinfo.sysetatDiscret->GETC()->GETheight()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, nonTransparent, no_angle, center_x);
	IHM::rendueEcran(sysinfo);
	displayStateSystem(sysinfo);

	for (unsigned int i = 0; i < sysinfo.sysetatDiscret->GETC()->GETlength(); i++)
	{
		for (unsigned int j = 0; j < sysinfo.sysetatDiscret->GETC()->GETheight(); j++)
		{
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 175, no_angle, center_x);
			SDL_RenderPresent(sysinfo.screen.renderer);
			sysinfo.sysetatDiscret->SETthisCoefC(i, j, KeyboardMouse::CinNumberDouble(sysinfo, "coef [" + std::to_string(i) + "][" + std::to_string(j) + "] = ", SCREEN_WIDTH / 2, 175));
			IHM::rendueEcran(sysinfo);
			displayStateSystem(sysinfo);
		}
	}

	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select,
		sysinfo.allTextes.txtEcranTitre, blended,
		"Length of D : " + std::to_string(sysinfo.sysetatDiscret->GETD()->GETlength()) + " and Height of D : " + std::to_string(sysinfo.sysetatDiscret->GETD()->GETheight()),
		{ 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 200, nonTransparent, no_angle, center_x);
	rendueEcran(sysinfo);
	displayStateSystem(sysinfo);

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "coef [0][0] = ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 225, no_angle, center_x);
	SDL_RenderPresent(sysinfo.screen.renderer);
	sysinfo.sysetatDiscret->SETthisCoefD(0, 0, KeyboardMouse::CinNumberDouble(sysinfo, "coef [0][0] = ", SCREEN_WIDTH / 2, 225));
	rendueEcran(sysinfo);
	displayStateSystem(sysinfo);


	IHM::logfileconsole("_ End createMatrice _");
}



void IHM::computeABCD(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_ Start computeABCD _");
	if (sysinfo.fctDiscret == nullptr)
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "TF doesn't exist", { 255, 0, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 148, no_angle, center_y);
	else
	{
		End::deleteSYSETATDiscret(sysinfo.sysetatDiscret);
		sysinfo.sysetatDiscret = new SYSETATDiscret;

		if (sysinfo.fctDiscret->GETden()->GETorder() > sysinfo.fctDiscret->GETnum()->GETorder())
		{
			sysinfo.sysetatDiscret->calculABCD(*sysinfo.fctDiscret);
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "OK", { 0, 255, 0, 255 }, NoColor, 16, (SCREEN_WIDTH / 2) + 150, 148, no_angle, center_y);
		}
		else
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "Order of Num >= Den", { 255, 0, 0, 255 }, NoColor, 14, (SCREEN_WIDTH / 2) + 150, 148, no_angle, center_y);
	}
	SDL_RenderPresent(sysinfo.screen.renderer);
	IHM::logfileconsole("_ End computeABCD _");
}



void IHM::displayStateSystem(Sysinfo& sysinfo)
{
	IHM::logfileconsole("_ Start displayStateSystem _");
	unsigned int initspace = 300;
	std::string texte; std::ostringstream stream;
	stream << std::fixed << std::setprecision(4);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Matrix A", { 0, 64, 255, 255 }, NoColor, 16, 100, initspace += 16, no_angle);
	for (unsigned int i = 0; i < sysinfo.sysetatDiscret->GETA()->GETlength(); i++)
	{
		stream << "|";
		for (unsigned int j = 0; j < sysinfo.sysetatDiscret->GETA()->GETheight(); j++)
			if(sysinfo.sysetatDiscret->GETA()->GETthiscoef(i, j) >= 0)
				stream << "   " << sysinfo.sysetatDiscret->GETA()->GETthiscoef(i, j) << " ";
			else 
				stream << "  -" << abs(sysinfo.sysetatDiscret->GETA()->GETthiscoef(i, j)) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 100, initspace += 16, no_angle);
	}

	initspace = 100;
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Matrix B", { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16, no_angle);
	for (unsigned int i = 0; i < sysinfo.sysetatDiscret->GETB()->GETlength(); i++)
	{
		stream << "|";
		for (unsigned int j = 0; j < sysinfo.sysetatDiscret->GETB()->GETheight(); j++)
			stream << " " << sysinfo.sysetatDiscret->GETB()->GETthiscoef(i, j) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16, no_angle);
	}

	initspace += 32;
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Matrix C", { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16, no_angle);
	for (unsigned int i = 0; i < sysinfo.sysetatDiscret->GETC()->GETlength(); i++)
	{
		stream << "|";
		for (unsigned int j = 0; j < sysinfo.sysetatDiscret->GETC()->GETheight(); j++)
			stream << " " << sysinfo.sysetatDiscret->GETC()->GETthiscoef(i, j) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16, no_angle);
	}

	initspace += 32;
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Matrix D", { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16, no_angle);
	stream << "| " << sysinfo.sysetatDiscret->GETD()->GETthiscoef(0, 0) << " |";
	texte = stream.str();
	stream.str("");
	stream.clear();
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, texte, { 0, 64, 255, 255 }, NoColor, 16, 0, initspace += 16, no_angle);

	SDL_RenderPresent(sysinfo.screen.renderer);
	IHM::logfileconsole("_ End displayStateSystem _");
}




void IHM::createSignal(Sysinfo& sysinfo, Signal& sig)
{
	IHM::logfileconsole("_ Start createSignal _");
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Number of samples : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, no_angle, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 150, no_angle);
	SDL_RenderPresent(sysinfo.screen.renderer);
	sig.SETnbech(KeyboardMouse::CinNumberUnsignedInt(sysinfo, "Number of samples : ", SCREEN_WIDTH / 2, 150));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Number of samples : " + std::to_string(sig.GETnbech()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 150, nonTransparent, no_angle, center_x);
	rendueEcran(sysinfo);

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "DeltaT : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 200, no_angle, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 200, no_angle);
	SDL_RenderPresent(sysinfo.screen.renderer);
	sig.SETdeltaT(KeyboardMouse::CinNumberDouble(sysinfo, "DeltaT : ", SCREEN_WIDTH / 2, 200));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "DeltaT : " + std::to_string(sig.GETdeltaT()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 200, nonTransparent, no_angle, center_x);
	rendueEcran(sysinfo);

	IHM::logfileconsole("_ End createSignal _");
}




void IHM::createStep(Sysinfo& sysinfo, Echelon& step)
{
	IHM::logfileconsole("_ Start createStep _");

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Amplitude : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, no_angle, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 70, 250, no_angle);
	SDL_RenderPresent(sysinfo.screen.renderer);
	step.SETamplitude(KeyboardMouse::CinNumberDouble(sysinfo, "Amplitude : ", SCREEN_WIDTH / 2, 250));
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Amplitude : " + std::to_string(step.GETamplitude()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, no_angle, center_x);
	rendueEcran(sysinfo);

	IHM::logfileconsole("_ End createStep _");
}




void IHM::createRamp(Sysinfo& sysinfo, Rampe& ramp)
{
	IHM::logfileconsole("_ Start createRamp _");

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Slope : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, no_angle, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 50, 250, no_angle);
	SDL_RenderPresent(sysinfo.screen.renderer);
	ramp.SETslope(KeyboardMouse::CinNumberDouble(sysinfo, "Slope : ", SCREEN_WIDTH / 2, 250));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Slope : " + std::to_string(ramp.GETslope()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, nonTransparent, no_angle, center_x);
	rendueEcran(sysinfo);

	IHM::logfileconsole("_ End createRamp _");
}



void IHM::createSinus(Sysinfo& sysinfo, Sinus& sinus)
{
	IHM::logfileconsole("_ Start createSinus _");

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Amplitude : ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, no_angle, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 70, 250, no_angle);
	SDL_RenderPresent(sysinfo.screen.renderer);
	sinus.SETamplitude(KeyboardMouse::CinNumberDouble(sysinfo, "Amplitude : ", SCREEN_WIDTH / 2, 250));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Amplitude : " + std::to_string(sinus.GETamplitude()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 250, nonTransparent, no_angle, center_x);
	rendueEcran(sysinfo);

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Angular velocity (w): ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 300, no_angle, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 100, 300, no_angle);
	SDL_RenderPresent(sysinfo.screen.renderer);
	sinus.SETw(KeyboardMouse::CinNumberDouble(sysinfo, "Angular velocity (w): ", SCREEN_WIDTH / 2, 300));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Angular velocity (w): " + std::to_string(sinus.GETw()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 300, nonTransparent, no_angle, center_x);
	rendueEcran(sysinfo);

	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Phase (phi): ", { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 350, no_angle, center_x);
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, "Enter a number", { 255, 215, 0, 255 }, NoColor, 18, SCREEN_WIDTH / 2 + 70, 350, no_angle);
	SDL_RenderPresent(sysinfo.screen.renderer);
	sinus.SETdephasage(KeyboardMouse::CinNumberDouble(sysinfo, "Phase (phi): ", SCREEN_WIDTH / 2, 350));
	Texte::loadTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, sysinfo.var.stateScreen, sysinfo.var.select, sysinfo.allTextes.txtEcranTitre,
		blended, "Phase (phi): " + std::to_string(sinus.GETdephasage()), { 0, 64, 255, 255 }, NoColor, 18, SCREEN_WIDTH / 2, 350, nonTransparent, no_angle, center_x);
	rendueEcran(sysinfo);

	IHM::logfileconsole("_ End createSinus _");
}



void IHM::displayReponseTemp(Sysinfo& sysinfo, Signal& sig)
{
	IHM::logfileconsole("_ Start displayReponseTemp _");
	std::string barre;
	barre = "0";
	for (unsigned int z = 0; z < 100; z++)
		barre += "-";
	barre += ">t(s)";
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, barre, { 255, 255, 255, 255 }, NoColor, 16, 40, 250, no_angle, center_y);
	barre = "";
	unsigned int initspace = 34;
	for (unsigned int z = 0; z < 30; z++)
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "|", { 255, 255, 255, 255 }, NoColor, 16, 50, initspace += 16, no_angle, center_x);


	Matrice X0(sysinfo.sysetatDiscret->GETA()->GETlength(), 1);

	double* yOut = new double[sig.GETnbech()];
	sysinfo.sysetatDiscret->simulation("bin/files/ReponseTemporelle.txt", sig, X0, yOut);


	unsigned int xmin = 50, xmax = 550;
	unsigned int y0 = 250, ymin = 450, ymax = 50;
	

	double max = 0, min = 0;
	for (unsigned int z = 0; z < sig.GETnbech(); z++)
	{
		if (sig.GETthiscoef(z) > max)
			max = sig.GETthiscoef(z);
		if (yOut[z] > max)
			max = yOut[z];
		if (sig.GETthiscoef(z) < min)
			min = sig.GETthiscoef(z);
		if (yOut[z] < min)
			min = yOut[z];
	}

	unsigned int pasGraph = (xmax - xmin) / sig.GETnbech();
	Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
		blended, std::to_string(max), { 255, 0, 0, 255 }, NoColor, 8, 20, 50, no_angle, center);
	for (unsigned int z = xmin, n = 0; z < xmax, n < sig.GETnbech(); z += pasGraph, n++)
	{
		Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
			blended, "|", { 255, 255, 255, 255 }, NoColor, 8, z, y0, no_angle, center);

		if (sig.GETthiscoef(n) > 0)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font, 
				blended, "+", { 255, 0, 0, 255 }, NoColor, 8, z, y0 - (unsigned int)((sig.GETthiscoef(n) / max) * (y0 - ymax)), no_angle, center);
		else if (sig.GETthiscoef(n) < 0)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "+", { 255, 0, 0, 255 }, NoColor, 8, z, y0 + (unsigned int)((sig.GETthiscoef(n) / min) * (ymin - y0)), no_angle, center);

		if (yOut[n] > 0)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "+", { 0, 255, 0, 255 }, NoColor, 8, z, y0 - (unsigned int)((yOut[n] / max) * (y0 - ymax)), no_angle, center);
		else if (yOut[n] < 0)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, "+", { 0, 255, 0, 255 }, NoColor, 8, z, y0 + (unsigned int)((yOut[n] / min) * (ymin - y0)), no_angle, center);

		if (n == 10)
			Texte::writeTexte(sysinfo.screen.renderer, sysinfo.allTextes.font,
				blended, std::to_string(sig.GETdeltaT() * 10), { 255, 255, 255, 255 }, NoColor, 8, z, y0 + 10, no_angle, center);
	}
	delete[] yOut;
	SDL_RenderPresent(sysinfo.screen.renderer);
	IHM::logfileconsole("_ Start displayReponseTemp _");
}

/*
*	End Of File : IHM.cpp
*/
