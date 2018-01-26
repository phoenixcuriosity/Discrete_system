/*
Discrete_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.31

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "IHM.h"


using namespace std;

IHM::IHM() : _fct(0), _sys(0)
{
	_fct = new FCTDiscret;
	_sys = new SYSETATDiscret;
}
IHM::~IHM()
{	
	if (_fct != nullptr){
		delete _fct;
		_fct = nullptr;
	}
	if (_sys != nullptr){
		delete _sys;
		_sys = nullptr;
	}
}

void IHM::SETfct(FCTDiscret* fct){
	if (_fct != nullptr)
		delete _fct;
	_fct = fct;
}
void IHM::SETsys(SYSETATDiscret* sys){
	if (_sys != nullptr)
		delete _sys;
	_sys = sys;
}
FCTDiscret* IHM::GETfct()const{
	return _fct;
}
SYSETATDiscret* IHM::GETsys()const{
	return _sys;
}


void mainLoop(IHM& ihm){
	/*
		Menu principal
	*/
	unsigned int request = 0;
	FCTDiscret testFCT;
	logfileconsole("_________Init Success_________");

	sysinfo information;
	initsdl(information);

	logfileconsole("_________START PROGRAM_________");
	logfileconsole("Dev version: 2.1");
	logfileconsole("This is a free software, you can redistribute it and/or modify it\n");

	SDL_RenderClear(information.ecran.renderer);
	writetxt(information, "Dev version: 2.1", { 255, 255, 255, 255 }, 16, 0, 0);
	writetxt(information, "Develop by SAUTER Robin", { 255, 255, 255, 255 }, 16, 0, 16);
	writetxt(information, "Discret System", { 0, 255, 255, 255 }, 24, SCREEN_WIDTH / 2, 50, center_x);
	
	SDL_RenderPresent(information.ecran.renderer);

	SDL_Event event;
	int SDL_EnableUNICODE(1); // on azerty

	while (information.variables.continuer){
		SDL_WaitEvent(&event);
			switch (event.type){
			case SDL_QUIT:	// permet de quitter
				information.variables.continuer = false;
				break;
			case SDL_KEYDOWN: // test sur le type d'événement touche enfoncé
				switch (event.key.keysym.sym) {
				case SDLK_F5:
					
					break;
				case SDLK_F6:
					
					break;
				case SDLK_ESCAPE:
					information.variables.continuer = false;
					break;
				case SDLK_SPACE:
					
					break;
				case SDLK_KP_1:
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN: // test sur le type d'événement click souris (enfoncé)
				break;
			case SDL_MOUSEWHEEL:
				break;
			}
		}
	logfileconsole("__");
}
	


bool assertFCT(const FCTDiscret fct, const FCTDiscret test){
	if (fct == test){
		logfileconsole("_____FCT doesn't exist");
		return false;
	}
	return true;
}


void logfileconsole(const std::string &msg) {
	const string logtxt = "bin/files/log.txt";
	ofstream log(logtxt, ios::app);
	if (log) {
		cout << endl << msg;
		log << endl << msg;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}
void initsdl(sysinfo& information){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cout << endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
	else{
		information.ecran.window = SDL_CreateWindow("Discret System", 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (information.ecran.window == nullptr) 
			SDL_Quit();
		else
			logfileconsole("CreateWindow Success");
		information.ecran.renderer = SDL_CreateRenderer(information.ecran.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (information.ecran.renderer == nullptr) {
			SDL_DestroyWindow(information.ecran.window);
			SDL_Quit();
		}
		else
			logfileconsole("CreateRenderer Success");

		if (TTF_Init() != 0) {
			SDL_DestroyRenderer(information.ecran.renderer);
			SDL_DestroyWindow(information.ecran.window);
			SDL_Quit();
		}
		else
			logfileconsole("TTF_Init Success");

		
		const std::string fontFile = "arial.ttf";

		for (unsigned int i = 1; i < 80; i++)
			information.allTextures.font[i] = TTF_OpenFont(fontFile.c_str(), i);

		logfileconsole("SDL_Init Success");
	}
}
SDL_Texture* renderText(SDL_Renderer*& renderer, const std::string &message, SDL_Color color, TTF_Font* font[], int fontSize){

	SDL_Surface *surf = TTF_RenderText_Blended(font[fontSize], message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
		logfileconsole("___________ERROR : renderText nullptr for : " + message);
	SDL_FreeSurface(surf);
	return texture;
}
SDL_Texture* renderTextShaded(SDL_Renderer*& renderer, const std::string &message, SDL_Color color, SDL_Color colorback, TTF_Font* font[], int fontSize){

	SDL_Surface *surf = TTF_RenderText_Shaded(font[fontSize], message.c_str(), color, colorback);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
		logfileconsole("___________ERROR : renderTextShaded nullptr for : " + message);
	SDL_FreeSurface(surf);
	return texture;
}

void searchcenter(int &x, int &y, int &xc, int &yc, int iW, int iH, int centerbutton) {
	switch (centerbutton) {
	case nocenter:
		xc = x + iW / 2;
		yc = y + iH / 2;
		break;
	case center_x:
		xc = x;
		yc = y + iH / 2;
		x = x - iW / 2;
		break;
	case center_y:
		xc = x + iW / 2;
		yc = y;
		y = y - iH / 2;
		break;
	case center:
		xc = x;
		yc = y;
		x = x - iW / 2;
		y = y - iH / 2;
		break;
	}
}

void createbutton(sysinfo& information, const string& msg, SDL_Color color, SDL_Color backcolor, int size, int x, int y, int centerbutton) {
	int iW = 0, iH = 0;
	unsigned int i = 0;
	int xc = 0, yc = 0;
	SDL_Texture *image = nullptr;
	SDL_Texture *imageOn = nullptr;
	unsigned int tabsize = information.tabbutton.size();

	if (tabsize > 0) {
		i++;
	}
	for (i; i <= tabsize; i++) {
		if (i == tabsize) {
			image = renderTextShaded(information.ecran.renderer, msg, color, backcolor, information.allTextures.font, size);
			imageOn = renderTextShaded(information.ecran.renderer, msg, color, { 64, 128, 64, 255 }, information.allTextures.font, size);
			SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
			searchcenter(x, y, xc, yc, iW, iH, centerbutton);
			information.tabbutton.push_back(new Buttons(image, msg, information.ecran.statescreen, information.variables.select, xc, yc, iW, iH, imageOn, x, y, size, color, backcolor));

			logfileconsole("Create Button n:" + to_string(i) + " msg = " + information.tabbutton[i]->GETname() + " Success");
			break;
		}
	}
}

void writetxt(sysinfo& information, const std::string &msg, SDL_Color color, int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderText(information.ecran.renderer, msg, color, information.allTextures.font, size);
	loadAndWriteImage(information.ecran.renderer, image, x, y, cnt);
	SDL_DestroyTexture(image);
}
void writetxtshaded(sysinfo& information, const std::string &msg, SDL_Color color, SDL_Color backcolor, int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderTextShaded(information.ecran.renderer, msg, color, backcolor, information.allTextures.font, size);
	loadAndWriteImage(information.ecran.renderer, image, x, y, cnt);
	SDL_DestroyTexture(image);
}

void loadAndWriteImage(SDL_Renderer*& renderer, SDL_Texture *image, unsigned int x, unsigned int y, int cnt) {
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);

	SDL_Rect dst;
	dst.x = xc;
	dst.y = yc;
	dst.w = iW;
	dst.h = iH;
	SDL_RenderCopy(renderer, image, NULL, &dst);
}


void centrage(int& xc, int& yc, int iW, int iH, int cnt) {
	switch (cnt) {
	case nocenter:
		break;
	case center_x:
		xc = xc - (iW / 2);
		break;
	case center_y:
		yc = yc - (iH / 2);
		break;
	case center:
		xc = xc - (iW / 2);
		yc = yc - (iH / 2);
		break;
	}
}

void mouse(sysinfo& information, SDL_Event event){
	/*
	Handle Mouse Event
	BUTTON_LEFT
	BUTTON_RIGHT

	*/


	string test, fct;

	if (event.button.button == SDL_BUTTON_LEFT){

		if (information.ecran.statescreen == STATEmainmap) {

		}

		for (unsigned int i = 0; i < information.tabbutton.size(); i++){ // recherche si une bouton est dans ces coordonnées


			if (information.tabbutton[i]->searchButton(fct = "New Game", information.ecran.statescreen, event.button.x, event.button.y)){
				
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Reload", information.ecran.statescreen, event.button.x, event.button.y)){
				
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Quit", information.ecran.statescreen, event.button.x, event.button.y)) {
				information.variables.continuer = false;
				break;
			}
		}


		// reset de l'affichage On des boutons
		for (unsigned int i = 0; i < information.tabbutton.size(); i++) {
			if (information.ecran.statescreen == STATEmainmap) 
				information.tabbutton[i]->resetOnStatescreen(information.variables.select, selectnothing);
		}
	}



	if (event.button.button == SDL_BUTTON_RIGHT && information.ecran.statescreen == STATEmainmap) {
		
	}
}
