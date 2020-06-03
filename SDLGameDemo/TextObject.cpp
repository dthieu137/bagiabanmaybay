
#include "TextObject.h"

TextObject::TextObject(){
	rect_.x = 550;
	rect_.y = 10;
	text_color_.r = 255;
	text_color_.g = 0;
	text_color_.b = 0;
}

TextObject::~TextObject(){
}

void TextObject::SetColor(const int& type){
	if(type == RED_TEXT){
		SDL_Color color = {255, 0, 0};
	}
	else if(type == WHITE_TEXT){
		SDL_Color color = {255, 255, 255};
	}
	else if(type == BLACK_TEXT){
		SDL_Color color = {0, 0, 0};
	}
}

void TextObject::CreateGameText(TTF_Font* font, SDL_Surface* des){
	p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
	Show(des);
}