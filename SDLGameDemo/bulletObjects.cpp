
#include "bulletObjects.h"

bulletObjects::bulletObjects(){
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	bullet_type_ = NONE;
}

bulletObjects::~bulletObjects(){
}

void bulletObjects::HandleMove(const int& x_border, const int& y_border){
	rect_.x += x_val_;
	if (rect_.x > x_border){
		is_move_ = false;
	}
}

void bulletObjects::ThreatHandleMove(){
	rect_.x -= x_val_;
	if (rect_.x < 0){
		is_move_ = false;
	}
}

void bulletObjects::HandleInputAction(SDL_Event events){

}
