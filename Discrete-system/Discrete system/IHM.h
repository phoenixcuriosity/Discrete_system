/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.23-A

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/


#ifndef IHM_H
#define IHM_H

#include "LIB.h"
#include "FCTDiscret.h"
#include "SYSETATDiscret.h"
#include "Signal.h"
#include "Complexe.h"




enum { selectnothing, selectFCT, selectSYSETAT, exitProgram };
enum { nothing, createNumDen, editFCT, displayFCT, jury, bode,previousMenuFCT };
enum { nothingtoedit, editnum, editden, editdeltaT, previousMenuEditFCT };
enum { not, editMatrice, calculMatriceABCD, simulationTemporelle, previousMenuSYS };


class IHM{
public:
	IHM();
	~IHM();


	friend void mainLoop(IHM& ihm);

	friend void FCTLoop(IHM& ihm);
	friend void modifFCT(IHM& ihm);
	friend void createNum(IHM& ihm);
	friend void createDen(IHM& ihm);
	friend void diagBode(IHM& ihm);

	friend void SYSLoop(IHM& ihm);

	void SETfct(FCTDiscret* fct);
	void SETsys(SYSETATDiscret* sys);
	FCTDiscret* GETfct()const;
	SYSETATDiscret* GETsys()const;

	friend void testIHM();
	friend void logfileconsole(const std::string& msg);

private:
	FCTDiscret* _fct;
	SYSETATDiscret* _sys;
};



#endif