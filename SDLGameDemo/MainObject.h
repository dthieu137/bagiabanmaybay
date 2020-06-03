
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#define WIDTH_MAIN_OBJECT 78
#define HEIGHT_MAIN_OBJECT 52

#include "CommonFuncs.h"
#include "BaseObjects.h"
#include "bulletObjects.h"
#include <vector>

class MainObject: public BaseObjects{
public:
	MainObject();
	~MainObject();
	void HandleMove();
	void HandleInputAction(SDL_Event events,  Mix_Chunk* bullet_sound[2]);
	void SetbulletList(std::vector<bulletObjects*> bullet_list){
		p_bullet_list_ = bullet_list;
	}
	void Makebullet(SDL_Surface* des);
	void Removebullet(const int &idx);
	std::vector<bulletObjects*> GetbulletList() const {return p_bullet_list_;}
private:
	int x_val_;
	int y_val_;
	std::vector<bulletObjects*> p_bullet_list_;
};


#endif //MAIN_OBJECT_H_