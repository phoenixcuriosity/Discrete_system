#ifndef Texture_H
#define Texture_H

#include "LIB.h"

class Texture{
public:
	Texture(){};
	Texture(SDL_Texture*, const std::string&, unsigned int, unsigned int, unsigned int, unsigned int, int, int);
	~Texture();

	virtual void render(SDL_Renderer*&, int, int);
	virtual void renderTexture(SDL_Renderer*&, int = -1, int = -1);
	virtual void renderTextureTestStates(SDL_Renderer*&,unsigned int, unsigned int, int = -1, int = -1);
	virtual void renderTextureTestString(SDL_Renderer*&, const std::string&, int = -1, int = -1);

	virtual void changeAlpha(Uint8);

	virtual SDL_Texture* GETtexture() const;
	virtual std::string GETname() const;
	virtual unsigned int GETstatescreen() const;
	virtual int GETxc() const;
	virtual int GETyc() const;
	virtual int GETw() const;
	virtual int GETh() const;

protected:
	SDL_Texture* _texture;
	std::string _name;
	unsigned int _statescreen;
	unsigned int _select;
	int _xc;
	int _yc;
	int _w;
	int _h;
};



#endif

