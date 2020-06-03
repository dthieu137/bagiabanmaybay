
#include "PlayerLives.h"

PlayerLives::PlayerLives(){



}

PlayerLives::~PlayerLives(){

}

void PlayerLives::addpos(const int& pos){
	pos_list_.push_back(pos);
}

void PlayerLives::Render(SDL_Surface* des){
	if (live_number_ == pos_list_.size()){
		for(int i = 0; i < pos_list_.size(); i++){
			rect_.x = pos_list_.at(i);
			Show(des);
		}
	}
}

void PlayerLives::Init(){
	LoadImg("miscs/heart.png");
	live_number_ = 3;
	if (pos_list_.size() > 0){
		pos_list_.clear();
	}
	addpos(1);
	addpos(50);
	addpos(99);

}

void PlayerLives::LifeDecrease(){
	live_number_--;
	pos_list_.pop_back();
}