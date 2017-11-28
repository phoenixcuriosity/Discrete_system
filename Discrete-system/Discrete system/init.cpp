#include "init.h"



using namespace std;

bool initfile(fichier& file) {
	/*
	initialisation des fichiers
	tests d'ouverture
	*/
	ofstream log(file.log);
	if (log) {}
	else {
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.log;
		return false;
	}
	ofstream reponseTemporelle(file.reponseTemporelle);
	if (reponseTemporelle) {}
	else {
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.reponseTemporelle;
		return false;
	}
	ofstream bode(file.bode);
	if (bode) {}
	else {
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.bode;
		return false;
	}
	ofstream load(file.load, ios::app);
	if (load) {}
	else {
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << file.load;
		return false;
	}

	return true;
}

/*
bool initsdl(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font* font[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		logfileconsole("SDL could not initialize! SDL_Error");
	else {
		window = SDL_CreateWindow("Discret System",
			0, 0,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (window == nullptr) {
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("CreateWindow Success");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr) {
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("CreateRenderer Success");

		if (TTF_Init() != 0) {
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}
		else
			logfileconsole("TTF_Init Success");


		const std::string fontFile = "arial.ttf";

		for (unsigned int i = 1; i < 80; i++)
			font[i] = TTF_OpenFont(fontFile.c_str(), i);

		logfileconsole("SDL_Init Success");
		return true;
	}
}
*/

void logfileconsole(const std::string &msg) {
	const std::string logtxt = "bin/log/log.txt";
	ofstream log(logtxt, ios::app);
	if (log) {
		cout << endl << msg;
		log << endl << msg;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}