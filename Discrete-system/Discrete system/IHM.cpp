/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.21

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "IHM.h"

using namespace std;

void IHM::SETfct(const FCTDiscret& fct){
	_fct = fct;
}
void IHM::SETsys(const SYSETATDiscret& sys){
	_sys = sys;
}
FCTDiscret IHM::GETfct()const{
	return _fct;
}
SYSETATDiscret IHM::GETsys()const{
	return _sys;
}

FCTDiscret IHM::MODIFfct(){
	return _fct;
}
SYSETATDiscret IHM::MODIFsys(){
	return _sys;
}