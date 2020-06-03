
#ifndef PLAYER_LIVES_H
#define PLAYER_LIVES_H

#include "BaseObjects.h"
#include <vector>
class PlayerLives : public BaseObjects{
public:
	PlayerLives();
	~PlayerLives();
	void SetNumber(const int& num){
		live_number_ = num;
	}
	
	void addpos (const int& xpos);

	void Render(SDL_Surface* des);

	void Init();

	void LifeDecrease();
private:
	int live_number_;
	std::vector <int> pos_list_;
};

#endif