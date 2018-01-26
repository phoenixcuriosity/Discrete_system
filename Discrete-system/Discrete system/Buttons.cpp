#include "Buttons.h"

using namespace std;



Buttons::Buttons(SDL_Texture* image, const string& msg, unsigned int statescreen, unsigned int select, int xc, int yc, int w, int h,
	SDL_Texture* imageOn, int x, int y, int size, SDL_Color txtcolor, SDL_Color backcolor, bool on)
	: Texture(image, msg, statescreen, select, xc, yc, w, h),
	_imageOn(imageOn), _x(x), _y(y), _size(size), _txtcolor(txtcolor), _backcolor(backcolor), _on(on)
{

}

Buttons::~Buttons() {
	if (_imageOn != nullptr) {
		SDL_DestroyTexture(_imageOn);
		_imageOn = nullptr;
	}
}





unsigned int Buttons::testcolor(SDL_Color txt, SDL_Color back) const {
	if (_txtcolor.a != txt.a || _txtcolor.b != txt.b || _txtcolor.g != txt.g || _txtcolor.r != txt.r ||
		_backcolor.a != back.a || _backcolor.b != back.b || _backcolor.g != back.g || _backcolor.r != back.r)
		return 1;
	else
		return 0;
}

unsigned int Buttons::searchButton(string& msg, unsigned int statescreen, signed int x, signed int y) {
	if (statescreen == _statescreen) {
		if (x >= _xc - _w / 2 && x <= _xc + _w / 2) {
			if (y >= _yc - _h / 2 && y <= _yc + _h / 2) {
				if (_name.compare(msg) == 0)
					return 1;
			}
		}
	}
	return 0;
}




void Buttons::resetOnStatescreen(unsigned int select, unsigned int selectnothing) {
	if (_select != select && _select != selectnothing)
		_on = false;
}

void Buttons::resetOnPlayer(unsigned int selectplayer, std::vector<std::string> tabPlayerName) {
	for(unsigned int i = 0; i < tabPlayerName.size(); i++){
		if (i != selectplayer && _name.compare(tabPlayerName[i]) == 0)
			_on = false;
	}
}

void Buttons::renderButton(SDL_Renderer*& renderer, unsigned int statescreen) {
	if (_statescreen == statescreen) {
		SDL_Rect dst;
		dst.x = _x;
		dst.y = _y;
		dst.w = _w;
		dst.h = _h;
		if (_on)
			SDL_RenderCopy(renderer, _imageOn, NULL, &dst);
		else
			SDL_RenderCopy(renderer, _texture, NULL, &dst);
	}
}


void Buttons::changeOn() {
	_on = !_on;
}





SDL_Texture* Buttons::GETimageOn() const {
	return _imageOn;
}

int Buttons::GETx() const {
	return _x;
}
int Buttons::GETy() const {
	return _y;
}
int Buttons::GETsize() const {
	return _size;
}
SDL_Color Buttons::GETtxtcolor() const {
	return _txtcolor;
}
SDL_Color Buttons::GETbackcolor() const {
	return _backcolor;
}
bool Buttons::GETon() const {
	return _on;
}






void Buttons::SETon(bool state) {
	_on = state;
}