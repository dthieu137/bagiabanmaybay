
#ifndef COMMON_FUNCS_H_
#define COMMON_FUNCS_H_

#include<string>
#include<SDL_image.h>
#include<Windows.h>
#include<SDL.h>
#include<SDL_mixer.h>


//Global constants go here!
const int BACKGROUND_WIDTH = 4800;
const int BACKGROUND_HEIGHT = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int NUM_THREATS = 8;

static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_bkground = NULL;
static SDL_Surface *g_img_menu = NULL;	
static SDL_Event g_event;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_explosion[1];
static Mix_Chunk* g_sound_collision[1];
static Mix_Chunk* g_sound_ingame[1];

unsigned static int bullets_fired = 0;
unsigned static int& blf = bullets_fired;
static double accuracy = 0;

namespace SDLCommonFuncs{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	void CleanUp();
	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	bool CheckFocusWithRect(const int &x, const int &y, const SDL_Rect& rect);
}

#endif