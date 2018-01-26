/*
Discrete_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.31

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/


#ifndef IHM_H
#define IHM_H

#include "Buttons.h"
#include "LIB.h"
#include "FCTDiscret.h"
#include "SYSETATDiscret.h"
#include "Signal.h"
#include "Complexe.h"


const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;

enum { STATEnothing, STATEecrantitre, STATEecrannewgame, STATEmainmap, STATEscience, STATEcitiemap };
enum { selectnothing, NotToSelect, selectcreate, selectinspect, selectmove };
enum { nocenter, center_x, center_y, center };

typedef struct screen screen;
struct screen {
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;

	unsigned int statescreen = 0; // selectnothing par défaut
};

typedef struct var var;
struct var {
	unsigned int nbturn = 0;

	unsigned int select = selectnothing;

	unsigned int mouse_x = 0;
	unsigned int mouse_y = 0;
	unsigned int ywheel = 0;
	unsigned int xwheel = 0;

	bool continuer = true;
};

typedef struct texture texture;
struct texture {
	TTF_Font *font[80];
	std::vector<Texture*> tabTexture;
};

typedef struct sysinfo sysinfo;
struct sysinfo {
	var variables;
	screen ecran;
	texture allTextures;
	std::vector<Buttons*> tabbutton;
};

class IHM{
public:
	IHM();
	~IHM();

	void SETfct(FCTDiscret* fct);
	void SETsys(SYSETATDiscret* sys);
	FCTDiscret* GETfct()const;
	SYSETATDiscret* GETsys()const;


protected:
	friend void mainLoop(IHM& ihm);
	friend void initsdl(sysinfo&);
	friend SDL_Texture* renderText(SDL_Renderer*&, const std::string&, SDL_Color, TTF_Font*[], int);

	friend void createbutton(sysinfo&, const std::string &msg, SDL_Color, SDL_Color, int, int, int, int = 0); // parametre par defaut -> nocenter
	friend void writetxt(sysinfo&, const std::string &msg, SDL_Color, int, unsigned int, unsigned int, int = 0);
	friend void writetxtshaded(sysinfo&, const std::string &msg, SDL_Color, SDL_Color, int, unsigned int, unsigned int, int = 0);
	friend void loadAndWriteImage(SDL_Renderer*&, SDL_Texture*, unsigned int, unsigned int, int = 0);
	friend void centrage(int&, int&, int, int, int = 0);

	friend void mouse(sysinfo&, SDL_Event);

	friend void logfileconsole(const std::string& msg);

private:
	FCTDiscret* _fct;
	SYSETATDiscret* _sys;
};



#endif