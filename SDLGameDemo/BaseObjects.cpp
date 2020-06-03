
#include "BaseObjects.h"

BaseObjects::BaseObjects(){
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
}

BaseObjects::~BaseObjects(){
	if(p_object_ != NULL){
		SDL_FreeSurface(p_object_);
	}
}

bool BaseObjects::LoadImg(const char* file_name){
	p_object_ = SDLCommonFuncs::LoadImage(file_name);
	if(p_object_ == NULL){
		return false;
	}
	return true;
}

void BaseObjects::Show(SDL_Surface* des){
	if(p_object_ != NULL){
		rect_ = SDLCommonFuncs::ApplySurface(p_object_, des, rect_.x, rect_.y);
	}
}