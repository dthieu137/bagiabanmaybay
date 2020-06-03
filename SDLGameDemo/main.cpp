
#include "CommonFuncs.h"
#include "MainObject.h"
#include "Threats.h"
#include "PlayerLives.h"
#include "TextObject.h"

TTF_Font* g_font_text = NULL; 
TTF_Font* g_font_menu = NULL;


//Character var
SDL_Surface *g_object = NULL;

//Game initialization (fonts, audibles go here!)
bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL){
		return false;
	}

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
		return false;	
	}
	//read wav file
	g_sound_bullet[0] = Mix_LoadWAV("audio/laser.wav");
	g_sound_bullet[1] = Mix_LoadWAV("audio/bullet.wav");
	g_sound_explosion[0] = Mix_LoadWAV("audio/explosion.wav");
	g_sound_collision[0] = Mix_LoadWAV("audio/coll.wav");
	g_sound_ingame[0] = Mix_LoadWAV("audio/poth.wav");

	if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_explosion[0] == NULL || g_sound_collision[0] == NULL || g_sound_ingame[0] == NULL){
		return false;
	}

	//text init
	if (TTF_Init() == -1){
		return false;
	}

	g_font_text = TTF_OpenFont("miscs/tfc.ttf", 16);
	g_font_menu = TTF_OpenFont("miscs/tfc.ttf", 32);
	if (g_font_text == NULL || g_font_menu == NULL){
		return false;
	}
	return true;
}

//Images loading goes here!
SDL_Surface* LoadImage(std::string file_path){
	SDL_Surface * load_image = NULL;
	SDL_Surface* optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL){
		optimize_image= SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
	}
	
	//transparent background for char; 
	//NOTE: 0, 0xFF, 0xFF is the background colour of the image.
	if (optimize_image != NULL) {
		UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF);
		SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
	}
	return optimize_image;
}

//Apply images into screen
void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);
}

//Free resources functions go here!
void CleanUp(){
  SDL_FreeSurface(g_screen);
  SDL_FreeSurface(g_bkground);
}

int main(int argc, char* argv[]){
	bool is_run_screen = true;
	int bkgn_x = 0;

	//Check if successfully initialized
	bool is_quit = false;
	if (Init() == false){
		return 0;
	}
	
	//Create main lives
	PlayerLives player_lives;
	player_lives.Init();

	//text related
	TextObject game_score;
	game_score.SetColor(TextObject::RED_TEXT);
	TextObject game_accuracy;
	game_accuracy.SetColor(TextObject::BLACK_TEXT);
	TextObject game_bullets_fired;
	game_bullets_fired.SetColor(TextObject::BLACK_TEXT);
	TextObject game_final;
	game_final.SetColor(TextObject::BLACK_TEXT);

	//load image to screen
	g_bkground = SDLCommonFuncs::LoadImage("background/bg4800.png");
	if (g_bkground == NULL){
		return 0;
	}
	
	//character's avatar
	MainObject main_object;
	main_object.SetRect(100, 200);
	bool checkif = main_object.LoadImg("objects/boshymain.png");
	if(!checkif){
		return 0;
	}
	main_object.Show(g_screen);

	//threats display & movement
	Threats* p_num_threats = new Threats[NUM_THREATS];
	for (int j = 0; j < NUM_THREATS; j++){
		Threats* p_threat = (p_num_threats + j);
		if(p_threat){
			checkif = p_threat->LoadImg("threats/boshythreat.png");
			if(!checkif){
				return 0;
			}

			int rand_y = rand()%400;
			if (rand_y > SCREEN_HEIGHT - 100){
				rand_y = SCREEN_HEIGHT * 0.45;
			}

			p_threat->SetRect(SCREEN_WIDTH + j*628, rand_y);
			p_threat->set_x_val(6);
			bulletObjects* p_bullet = new bulletObjects();
			p_threat->Initbullet(p_bullet);
		}
	}
	
	Threats* p_threat = new Threats();
	checkif = p_threat->LoadImg("threats/boshythreat.png");
	if(!checkif){
		return 0;
	}

	int rand_y = rand()%450;
	if (rand_y > SCREEN_HEIGHT - 100){
		rand_y = SCREEN_HEIGHT * 0.45;
	}

	p_threat->SetRect(SCREEN_WIDTH, rand_y);
	p_threat->set_x_val(4);
	bulletObjects* p_bullet = new bulletObjects();
	p_threat->Initbullet(p_bullet);
	
	unsigned int player_death = 0;
	unsigned int score_value = 0;

	int chkmenu = SDLCommonFuncs::ShowMenu(g_screen, g_font_menu);
	if (chkmenu == 1){
		is_quit = true;
	}
		
	//event poll, exit when quit event
	while (!is_quit) {
		while (SDL_PollEvent(&g_event)) {
			if (g_event.type == SDL_QUIT){
				is_quit = true;
			break;
			}
			main_object.HandleInputAction(g_event, g_sound_bullet);
		}

		//Apply background

		if(is_run_screen == true){
			bkgn_x -= 2;
			if(bkgn_x <= -(BACKGROUND_WIDTH - SCREEN_WIDTH)){
				is_run_screen = false;

				Mix_PlayChannel(-1, g_sound_ingame[0], 5);
			}
			else{
				SDLCommonFuncs::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
			}	
		}
		else{
			SDLCommonFuncs::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
		}
		
		//Show player lives
		player_lives.Render(g_screen);

		//Implement main objs
		main_object.HandleMove();
		main_object.Show(g_screen);
		main_object.Makebullet(g_screen);


		
		//Run threats
		for (int k = 0; k < NUM_THREATS; k++){
			Threats* p_threat = (p_num_threats + k);
			if (p_threat){
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);
				p_threat->Makebullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);

				if(SDL_Flip(g_screen) == -1){
					return 0;
				}

				//Check collision main/threats
				//1.Col between main and threat
				bool chkcol1 = SDLCommonFuncs::CheckCollision(main_object.GetRect(), p_threat->GetRect());
				if (chkcol1){
					Mix_PlayChannel(-1, g_sound_collision[0], 0);	
					player_death++;
					//reset player's location
					if (player_death <= 2){
						SDL_Delay(200);
						main_object.SetRect(100, 400);
						player_lives.LifeDecrease();
						player_lives.Render(g_screen);

						if(SDL_Flip(g_screen) == -1){
							delete [] p_threat;
							SDLCommonFuncs::CleanUp();
							SDL_Quit();		
							return 0;
						}
					}

					else{
						if(MessageBox(NULL, L"You fookin' crashed! Game Over!", L"Ban' kem' thi` an dong` bang` an cat' ", MB_OK) == IDOK){
							delete [] p_num_threats;
							SDLCommonFuncs::CleanUp();
							SDL_Quit();
							return 1;
						}
					}
				}
				//2.Col between your bullet and threats
				std::vector<bulletObjects*> bullet_list = main_object.GetbulletList();
				for (int l = 0; l < bullet_list.size(); l++){
					bulletObjects* p_bullet = bullet_list.at(l);
					if (p_bullet != NULL){
						bool chkcol2 = SDLCommonFuncs::CheckCollision(p_bullet->GetRect(), p_threat->GetRect());
						if (chkcol2){
							score_value++;
							if (bullets_fired == 0){
								accuracy = 0;
							}
							else{
								accuracy = (score_value)/(bullets_fired);
							}
							p_threat->Reset(SCREEN_WIDTH + k*628);
							main_object.Removebullet(l);
							Mix_PlayChannel(-1, g_sound_explosion[0], 0);
					    }
						
						else if (!chkcol2){
						}
					}
				}
				//3. Col between threat bullets and main
				std::vector<bulletObjects*> bullet_list1 = p_threat->GetbulletList();
				for (int l = 0; l < bullet_list1.size(); l++){
					bulletObjects* p_bullet = bullet_list1.at(l);
					if (p_bullet != NULL){
						bool chkcol3 = SDLCommonFuncs::CheckCollision(p_bullet->GetRect(), main_object.GetRect());
						if (chkcol3){
							Mix_PlayChannel(-1, g_sound_collision[0], 0);
							player_death++;
							//reset player's location
							if (player_death <= 2){
								SDL_Delay(200);
								main_object.SetRect(100, 400);
								player_lives.LifeDecrease();
								player_lives.Render(g_screen);

								if(SDL_Flip(g_screen) == -1){
									delete [] p_threat;
									SDLCommonFuncs::CleanUp();
									SDL_Quit();		
									return 0;
								}
							}
							else{
								if(MessageBox(NULL, L"You fookin' crashed! Game Over!", L"Ban' kem' thi` an dong` bang` an cat' ", MB_OK) == IDOK){
									delete [] p_num_threats;
									SDLCommonFuncs::CleanUp();
									SDL_Quit();
									return 1;
								}
							}
						}
					}
				}
			}
		}
		//Show score and accuracy
		std::string val_str_score = std::to_string(score_value);
		std::string strScore("SCORE: ");
		strScore += val_str_score;
		
		game_score.SetText(strScore);
		game_score.CreateGameText(g_font_text, g_screen);

		
		std::string val_str_fired = std::to_string(bullets_fired);
		std::string strFired("TOTAL FIRED: ");
		strFired += val_str_fired;
		
		game_bullets_fired.SetText(strFired);
		game_bullets_fired.SetRect(500, 30);
		game_bullets_fired.CreateGameText(g_font_text, g_screen);

		//Update screen
		if(SDL_Flip(g_screen) == -1){
			return 0;
		}
	}

	//Upon exiting free resources
	delete [] p_num_threats;
	SDLCommonFuncs::CleanUp();
	SDL_Quit();
	return 1;
}