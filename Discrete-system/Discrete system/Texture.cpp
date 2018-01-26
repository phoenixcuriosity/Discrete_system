#include "Texture.h"

#include "LIB.h"

using namespace std;


Texture::Texture(SDL_Texture* image, const string& msg, unsigned int statescreen, unsigned int select, unsigned int xc, unsigned int yc, int w, int h)
	: _texture(image), _name(msg), _statescreen(statescreen), _select(select), _xc(xc), _yc(yc), _w(w), _h(h)
{
}

Texture::~Texture() {
	if (_texture != nullptr){
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
}



void Texture::render(SDL_Renderer*& renderer, int xc, int yc) {
	SDL_Rect dst;
	if (xc != -1 && yc != -1) {
		dst.x = xc;
		dst.y = yc;
	}
	else {
		dst.x = _xc;
		dst.y = _yc;
	}
	dst.w = _w;
	dst.h = _h;
	SDL_RenderCopy(renderer, _texture, NULL, &dst);
}


void Texture::renderTexture(SDL_Renderer*& renderer, int xc, int yc) {
	render(renderer, xc, yc);
}

void Texture::renderTextureTestStates(SDL_Renderer*& renderer, unsigned int statescreen, unsigned int select, int xc, int yc) {
	if (_statescreen == statescreen)
		render(renderer, xc, yc);
}

void Texture::renderTextureTestString(SDL_Renderer*& renderer, const std::string& msg, int xc, int yc) {
	if (_name == msg)
		render(renderer, xc, yc);
}



void Texture::changeAlpha(Uint8 alpha) {
	if (SDL_SetTextureAlphaMod(_texture, alpha) != 0)
		alpha = alpha;
}




SDL_Texture* Texture::GETtexture() const{
	return _texture;
}
string Texture::GETname() const{
	return _name;
}
unsigned int Texture::GETstatescreen() const {
	return _statescreen;
}
int Texture::GETxc() const {
	return _xc;
}
int Texture::GETyc() const {
	return _yc;
}
int Texture::GETw() const {
	return _w;
}
int Texture::GETh() const {
	return _h;
}

