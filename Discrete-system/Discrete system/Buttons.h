#ifndef Buttons_H
#define Buttons_H

#include "Texture.h"


class Buttons : public Texture {
public:
	Buttons() {};
	Buttons(SDL_Texture*, const std::string&, unsigned int, unsigned int, int, int, int, int,
		SDL_Texture*, int, int, int, SDL_Color, SDL_Color, bool = false);
	~Buttons();


	virtual unsigned int testcolor(SDL_Color, SDL_Color) const;
	virtual unsigned int searchButton(std::string& msg, unsigned int, signed int, signed int);

	virtual void resetOnStatescreen(unsigned int, unsigned int);
	virtual void resetOnPlayer(unsigned int, std::vector<std::string> );
	virtual void renderButton(SDL_Renderer*&, unsigned int);

	virtual void changeOn();

	virtual SDL_Texture* GETimageOn() const;
	virtual int GETx() const;
	virtual int GETy() const;
	virtual int GETsize() const;
	virtual SDL_Color GETtxtcolor() const;
	virtual SDL_Color GETbackcolor() const;
	virtual bool GETon() const;

	virtual void SETon(bool);

protected:
	SDL_Texture* _imageOn;
	int _x;
	int _y;
	int _size;
	SDL_Color _txtcolor;
	SDL_Color _backcolor;
	bool _on;

};


#endif // !Buttons_H

