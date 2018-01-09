/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.21

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/


#ifndef IHM_H
#define IHM_H

#include "LIB.h"
#include "ConstantesAndStructures.h"

class IHM{
public:
	IHM(){};
	~IHM(){};

	void SETfct(const FCTDiscret& fct);
	void SETsys(const SYSETATDiscret& sys);
	FCTDiscret GETfct()const;
	SYSETATDiscret GETsys()const;

	FCTDiscret MODIFfct();
	SYSETATDiscret MODIFsys();

protected:

private:
	FCTDiscret _fct;
	SYSETATDiscret _sys;
};



#endif