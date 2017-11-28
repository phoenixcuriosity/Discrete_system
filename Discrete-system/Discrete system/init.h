#ifndef init_H
#define init_H

#include "ConstantesAndStructures.h"


bool initfile(fichier& file);
bool initsdl(SDL_Window*&, SDL_Renderer*&, TTF_Font*[]);
void logfileconsole(const std::string &msg);


#endif
