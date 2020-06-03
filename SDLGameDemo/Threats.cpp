
#include "Threats.h"

Threats::Threats(){
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT*0.5;
	rect_.w = THREAT_WIDTH;
	rect_.h = THREAT_HEIGHT;

	x_val_ = 0;
	y_val_ = 0;
}

Threats::~Threats(){
	if(p_bullet_list_.size() > 0){
		for(int i = 0; i < p_bullet_list_.size(); i++){
			bulletObjects* p_bullet = p_bullet_list_.at(i);
			if(p_bullet != NULL){
				delete p_bullet;
				p_bullet = NULL;
			}
		}
		p_bullet_list_.clear();
	}
}

void Threats::Initbullet(bulletObjects* p_bullet){
	if(p_bullet != NULL){
		bool check = p_bullet->LoadImg("projectiles/sphere.png");
		if(check){
			p_bullet->set_is_move(true);
			p_bullet->SetWidthHeight(SPHERE_WIDTH, SPHERE_HEIGHT);
			p_bullet->set_type(bulletObjects::SPHERE);
			p_bullet->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
			p_bullet->set_x_val(11);
			p_bullet_list_.push_back(p_bullet);
		}
	}
}

void Threats::Makebullet(SDL_Surface* des, const int& x_limit, const int& y_limit){
	for(int i = 0; i < p_bullet_list_.size(); i++){
		bulletObjects* p_bullet = p_bullet_list_.at(i);
		if(p_bullet){
			if(p_bullet->get_is_move()){
				p_bullet->Show(des);
				p_bullet->ThreatHandleMove();
			}
			else{
				p_bullet->set_is_move(true);
				p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
			}

		}
	}
}

void Threats::HandleMove(const int& x_border, const int& y_border){
	rect_.x -= x_val_;
	if(rect_.x < 0){
		rect_.x = SCREEN_WIDTH;
		int rand_y = rand()%450;
		if (rand_y > SCREEN_HEIGHT - 100){
			rand_y = SCREEN_HEIGHT * 0.45;
		}
		rect_.y = rand_y;
	}
}

void Threats::HandleInputAction(SDL_Event events){

}

void Threats::Reset(const int& xborder){
	rect_.x = xborder;
	int rand_y = rand()%450;
	if (rand_y > SCREEN_HEIGHT - 100){
		rand_y = SCREEN_HEIGHT * 0.45;
	}
	rect_.y = rand_y;
	for (int i = 0; i < p_bullet_list_.size(); i++){
		bulletObjects* p_bullet = p_bullet_list_.at(i);
		if(p_bullet){
			Resetbullet(p_bullet);
		}
	}
}

void Threats::Resetbullet(bulletObjects* p_bullet){
	p_bullet->SetRect(rect_.x, rect_.y + rect_.h * 0.5);
}