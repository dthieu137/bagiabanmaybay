//Threats exec
#ifndef THREATS_H_
#define THREATS_H_

#define THREAT_WIDTH 80
#define THREAT_HEIGHT 33

#include "CommonFuncs.h"
#include "BaseObjects.h"
#include "bulletObjects.h"
#include <vector>

class Threats : public BaseObjects{
public:
	Threats();
	~Threats();

	void HandleMove(const int& x_border, const int& y_border);
	void HandleInputAction(SDL_Event events);
	
	void set_x_val(const int& val){
		x_val_ = val;
	}
	void set_y_val(const int& val){
		y_val_ = val;
	}
	int get_x_val() const{return x_val_;}
	int get_y_val() const{return y_val_;}

	void SetbulletList(std::vector<bulletObjects*> bullet_list){
		p_bullet_list_ = bullet_list;
	}
	std::vector<bulletObjects*> GetbulletList() const {return p_bullet_list_;}

	void Initbullet(bulletObjects* p_bullet);

	void Makebullet(SDL_Surface* des, const int& x_limit, const int& y_limit);

	void Reset(const int& xborder);
	void Resetbullet(bulletObjects* p_bullet);

private:
	int x_val_;
	int y_val_;
	std::vector<bulletObjects*> p_bullet_list_;

};


#endif