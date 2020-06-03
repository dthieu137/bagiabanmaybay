
#include "MainObject.h"
//Main char exec
MainObject::MainObject(){
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}

MainObject::~MainObject(){

}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]){
	if(events.type == SDL_KEYDOWN){
		switch (events.key.keysym.sym){
		case SDLK_w:
			y_val_ -= HEIGHT_MAIN_OBJECT/3,14;
			break;
		case SDLK_a:
			x_val_ -= WIDTH_MAIN_OBJECT/3,14;
			break;
		case SDLK_s:
			y_val_ += HEIGHT_MAIN_OBJECT/3,14;
			break;
		case SDLK_d:
			x_val_ += WIDTH_MAIN_OBJECT/3,14;
			break;
		default:
			break;
		}
	}

	else if(events.type == SDL_KEYUP){
		switch (events.key.keysym.sym){
		case SDLK_w:
			y_val_ += HEIGHT_MAIN_OBJECT/3,14;
			break;
		case SDLK_a:
			x_val_ += WIDTH_MAIN_OBJECT/3,14;
			break;
		case SDLK_s:
			y_val_ -= HEIGHT_MAIN_OBJECT/3,14;
			break;
		case SDLK_d:
			x_val_ -= WIDTH_MAIN_OBJECT/3,14; 
			break;
		default:
			break;
		}
	}

	else if(events.type == SDL_MOUSEBUTTONDOWN){
		bulletObjects* p_bullet = new bulletObjects();
		if (events.button.button == SDL_BUTTON_LEFT){
			blf++;
			p_bullet->SetWidthHeight(LASER_WIDTH, LASER_HEIGHT);
			p_bullet->LoadImg("projectiles/laser.png");
			p_bullet->set_type(bulletObjects::LASER);
			Mix_PlayChannel(-1, bullet_sound[0], 0);

		}
		else if (events.button.button == SDL_BUTTON_RIGHT){
			blf++;
			p_bullet->SetWidthHeight(SPHERE_WIDTH, SPHERE_HEIGHT);
			p_bullet->LoadImg("projectiles/sphere.png");
			p_bullet->set_type(bulletObjects::SPHERE);
			Mix_PlayChannel(-1, bullet_sound[1], 0);
		}
		p_bullet->SetRect(this->rect_.x + this->rect_.w*0.5 , this->rect_.y + this->rect_.h*0.5);
		p_bullet->set_is_move(true);
		p_bullet->set_x_val(21);
		p_bullet_list_.push_back(p_bullet);
	}

	else if(events.type == SDL_MOUSEBUTTONUP){
	}

	else{
	}
}


void MainObject::Makebullet(SDL_Surface* des){
	for(int i = 0; i < p_bullet_list_.size(); i++){
		bulletObjects* p_bullet = p_bullet_list_.at(i);
		if (p_bullet != NULL){
			if(p_bullet->get_is_move()){
				p_bullet->Show(des);
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			
			else{
				if(p_bullet != NULL){
					p_bullet_list_.erase(p_bullet_list_.begin() + i);
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}
}


void MainObject::HandleMove(){
	rect_.x += x_val_;
	if(rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH - 80){
		rect_.x -= x_val_;
	}

	rect_.y += y_val_;
	if(rect_.y < 0 || rect_.y + WIDTH_MAIN_OBJECT > SCREEN_HEIGHT - 80){
		rect_.y -= y_val_;
	}
}

//Remove bullets when hit enemy.
void MainObject::Removebullet(const int &idx){
	for (int i = 0; i < p_bullet_list_.size(); i++){
		if(idx < p_bullet_list_.size()){
			bulletObjects* p_bullet = p_bullet_list_.at(idx);
			p_bullet_list_.erase(p_bullet_list_.begin() + idx);
			if (p_bullet != NULL){
				delete p_bullet;
				p_bullet = NULL;
			}
		}	
	}
}