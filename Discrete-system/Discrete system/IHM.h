/*

	Discrete_system
	Copyright SAUTER Robin 2017-2018 (robin.sauter@orange.fr)
	last modification on this file on version:2.9

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


#ifndef IHM_H
#define IHM_H

#include "LIB.h"
#include "FCTDiscret.h"
#include "SYSETATDiscret.h"
#include "Signal.h"
#include "Complexe.h"
#include "discrete_system_LIB.h"
#include "Texture.h"


class IHM{
public:

	static bool initfile(fichier& file);
	static void logfileconsole(const std::string& msg);
	static void logSDLError(std::ostream &os, const std::string &msg);
	static void initsdl(sysinfo&);
	static void deleteAll(sysinfo&);

public:
	IHM();
	~IHM();

	void SETfct(FCTDiscret* fct);
	void SETsys(SYSETATDiscret* sys);
	FCTDiscret* GETfct()const;
	SYSETATDiscret* GETsys()const;

	bool assertFCT(const FCTDiscret fct, const FCTDiscret test);

protected:
	friend void loadAllTextures(sysinfo&);
	friend void rendueEcran(sysinfo&);

	friend void mouse(IHM& ,sysinfo&, SDL_Event);
	friend unsigned int CinNumberUnsignedInt(sysinfo&, const std::string& msg, unsigned int, unsigned int);
	friend double CinNumberDouble(sysinfo&, const std::string& msg, unsigned int, unsigned int);
	friend void CreateNumDen(IHM& ihm, sysinfo& information);
	friend void displayTF(IHM& ihm, sysinfo& information);
	friend void displayJury(IHM& ihm, sysinfo& information);
	friend void displayBode(IHM& ihm, sysinfo& information);
	friend void createMatrice(IHM& ihm, sysinfo& information);
	friend void computeABCD(IHM& ihm, sysinfo& information);
	friend void displayStateSystem(IHM& ihm, sysinfo& information);
	friend void createSignal(IHM& ihm, sysinfo& information, Signal& sig);
	friend void createStep(IHM& ihm, sysinfo& information, Echelon& step);
	friend void createRamp(IHM& ihm, sysinfo& information, Rampe& ramp);
	friend void createSinus(IHM& ihm, sysinfo& information, Sinus& sinus);
	friend void displayReponseTemp(IHM& ihm, sysinfo& information, Signal& sig);

private:
	FCTDiscret* _fct;
	SYSETATDiscret* _sys;
};


template<class T>
void deleteDyTabPlayerAndTextures(T& dytab, const std::string& name) {
	unsigned int size = dytab.size();
	for (unsigned int i = 0; i < size; i++) {
		IHM::logfileconsole("Delete " + name + " n:" + std::to_string(i) + " name = " + dytab[i]->GETname() + " Success");
		delete dytab[i];
	}
	for (unsigned int i = 0; i < size; i++)
		dytab.pop_back();
	if (dytab.size() != 0)
		IHM::logfileconsole("___________ERROR : " + name + ".size() != 0");
	else
		IHM::logfileconsole("Delete ALL " + name + " Success");
}



#endif