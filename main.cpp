#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Player.h"
#include "Bullet.h"
#include "Comets.h"
#include "Background.h"



const int WIDTH = 1200;
const int HEIGHT = 800;
enum KEYS{UP, DOWN, RIGHT, LEFT, SPACE, R};
enum STATES{MENU, PLAYING, GAMEOVER};
bool Keys[6] = { false, false, false, false, false, false};

Player Zentes;
Bullet bullet[4];
Comets comets[7];
int score = 0;
int highscore = 0;
int lives = 5;
bool live[4] = { false, false, false, false};
bool liveC[7] = { false, false, false, false, false, false, false};


void ChangeState(int &state, int newState);


int main()
{

	//intializing variables
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	int state = -1;


	//initializing ALLEGRO stuff
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font, *font1;
	ALLEGRO_BITMAP *Spacecraft, *Comet, *Bullets, *CometExplosion;
	ALLEGRO_BITMAP *BG, *MG, *FG, *Menu, *Gameover;
	ALLEGRO_SAMPLE *samplePew, *sampleExplosion, *sampleSoundtrack;
	ALLEGRO_SAMPLE_INSTANCE *instancePew, *instanceExplosion, *instanceSoundtrack;


	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(WIDTH, HEIGHT);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	//Initializing ALLEGRO's tools
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();

	//font initialization
	font = al_load_font("Aero.ttf", 50, 0);
	font1 = al_load_font("Aero.ttf", 90, 0);


	//Image importing
	Spacecraft = al_load_bitmap("Spacecraft.gif");
	Comet = al_load_bitmap("Comet.gif");
	Bullets = al_load_bitmap("Bullets.gif");
	BG = al_load_bitmap("BG.jpg");
	MG = al_load_bitmap("MG.gif");
	FG = al_load_bitmap("FG.gif");
	Menu = al_load_bitmap("Menu.jpg");
	Gameover = al_load_bitmap("Gameover.png");
	CometExplosion = al_load_bitmap("CometExplosion.gif");

	al_reserve_samples(3);

	//Sound importing
	samplePew = al_load_sample("Pew.ogg");
	sampleExplosion = al_load_sample("Explosion.ogg");
	sampleSoundtrack = al_load_sample("Soundtrack.ogg");

	//Instances
	instancePew = al_create_sample_instance(samplePew);
	instanceExplosion = al_create_sample_instance(sampleExplosion);
	instanceSoundtrack = al_create_sample_instance(sampleSoundtrack);

	//Attaching our instances to mixer
	al_attach_sample_instance_to_mixer(instancePew, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instanceExplosion, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(instanceSoundtrack, al_get_default_mixer());

	//initialization of Background's objects
	Background Bground(BG, 0, 0, 1, 1200, 800);
	Background Mground(MG, 0, 0, 3, 1800, 800);
	Background Fground(FG, 0, 0, 4, 1200, 800);

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	ChangeState(state, MENU);

	al_start_timer(timer);

	//Game Loop
	while (!done){

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//keyboard
		if (ev.type == ALLEGRO_EVENT_TIMER){

			redraw = true;
			
			if (state == PLAYING){
				if (Keys[UP]){
					Zentes.MovePlayerUp();
				}
				else if (Keys[DOWN]){
					Zentes.MovePlayerDown();
				}
				else if (Keys[RIGHT]){
					Zentes.MovePlayerRight();
				}
				else if (Keys[LEFT]){
					Zentes.MovePlayerLeft();
				}
				
				for (int i = 0; i < 4; i++){
					if (live[i]){
						bullet[i].UpdateBullet();
						live[i] = bullet[i].AliveBullet();
					}
				}
				for (int i = 0; i < 4; i++){
					if (!liveC[i]){
						comets[i].DrawCometsF();
						liveC[i] = true;
						break;
					}
				}
				for (int i = 0; i < 4; i++){
					if (liveC[i]){
						comets[i].UpdateComets(score);
						liveC[i] = comets[i].AliveComets();
						if (liveC[i] == false){
							lives--;
						}
					}
				}

				//Checking for collision
				for (int i = 0; i < 4; i++){

					if (live[i]){

						for (int j = 0; j < 4; j++){

							if (bullet[i].CheckForCollisionComet(comets[j])){
								live[i] = false;
								liveC[j] = false;
								score += 100;
								al_play_sample_instance(instanceExplosion);
							}
						}

					}
				}
				

				if (lives == 0){
					ChangeState(state, GAMEOVER);
				}


				Bground.UpdateBackground();
				Mground.UpdateBackground();
				Fground.UpdateBackground();
				score++;
				al_play_sample_instance(instanceSoundtrack);

			}
			
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

			done = true;

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
			
			switch (ev.keyboard.keycode){
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				Keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				Keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				Keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				Keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				Keys[SPACE] = true;
				if (state == MENU){
					ChangeState(state, PLAYING);
				}
				else if (state == PLAYING){
					for (int i = 0; i < 4; i++){
						if (!live[i]){
							bullet[i].GetCooBullet(Zentes);
							live[i] = true;
							al_play_sample_instance(instancePew);
							break;
						}
					}
				}
				break;
			case ALLEGRO_KEY_R:
				Keys[R] = true;
				if (state == GAMEOVER){
					ChangeState(state, PLAYING);
					continue;
				}
				break;
			}
		}else if (ev.type == ALLEGRO_EVENT_KEY_UP){

			switch (ev.keyboard.keycode){
			case ALLEGRO_KEY_UP:
				Keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				Keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				Keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				Keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				Keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_R:
				Keys[R] = false;
				break;
			}
		}
		//Drawing on screen
		if (redraw && al_is_event_queue_empty(event_queue)){
			if (state == MENU){
				al_draw_bitmap(Menu, 0, 0, 0);
				al_draw_textf(font, al_map_rgb(255, 0, 0), 350, 15, 0, "Press Space to begin");
				al_draw_textf(font, al_map_rgb(0, 0, 255), 250, HEIGHT - 150, 0, "Programmunity Software", score);
				al_draw_textf(font, al_map_rgb(0, 0, 255), 350, HEIGHT - 100, 0, "Music: DJ Ragemix", score);
				al_draw_textf(font, al_map_rgb(0, 0, 255), 300, HEIGHT - 50, 0, "Spacecraft by Skorpio", score);
			}
			else if (state == PLAYING){
				Bground.DrawBackground();
				Mground.DrawBackground();
				Fground.DrawBackground();
				Zentes.DrawPlayer(Spacecraft);
		
				for (int i = 0; i < 4; i++){
					if (live[i]){
						bullet[i].DrawBullet(Bullets);
					}
				}
				for (int i = 0; i < 4; i++){
					if (liveC[i]){
						comets[i].DrawComets(Comet);
					}
				}
				for (int i = 0; i < 4; i++){
					for (int j = 0; j < 4; j++){
						bullet[i].CheckForDrawingExplosionComet(comets[j], CometExplosion);
					}
				}
				al_draw_textf(font, al_map_rgb(0, 0, 255), 800, 10, 0, "Score:%i", score);
				al_draw_textf(font, al_map_rgb(0, 0, 255), 100, 10, 0, "Lives:%i", lives);
			}
			else if (state == GAMEOVER){
	
				al_draw_bitmap(Gameover, 0, 0, 0);
				al_draw_textf(font, al_map_rgb(255, 0, 0), 325, 15, 0, "Press 'R' to play again");
				al_draw_textf(font, al_map_rgb(255, 0, 0), 400, 60, 0, "or 'Escape' to quit");
				al_draw_textf(font, al_map_rgb(0, 0, 255), 450, HEIGHT - 50, 0, "Score:%i", score);
				al_draw_textf(font, al_map_rgb(0, 0, 255), 410, HEIGHT - 100, 0, "Highscore:%i", highscore);
				if (score == highscore+1){
					al_draw_textf(font1, al_map_rgb(255, 0, 0), 150, HEIGHT - 200, 0, "New Highscore:%i", highscore);
				}
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			redraw = false;
		}
	}
	//freeing the memory that we don't need
	al_destroy_sample(samplePew);
	al_destroy_sample(sampleExplosion);
	al_destroy_sample(sampleSoundtrack);
	al_destroy_sample_instance(instancePew);
	al_destroy_sample_instance(instanceExplosion);
	al_destroy_sample_instance(instanceSoundtrack);
	al_destroy_bitmap(Spacecraft);
	al_destroy_bitmap(Comet);
	al_destroy_bitmap(Bullets);
	al_destroy_bitmap(CometExplosion);
	al_destroy_bitmap(BG);
	al_destroy_bitmap(FG);
	al_destroy_bitmap(MG);
	al_destroy_bitmap(Menu);
	al_destroy_font(font);
	al_destroy_font(font1);
	al_destroy_bitmap(Gameover);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return 0;
}

void ChangeState(int &state, int newState){

	if (state == MENU){

	}
	else if (state == PLAYING){
		
	}
	else if (state == GAMEOVER){

	}

	state = newState;

	if (state == MENU){

	}
	else if (state == PLAYING){
		for (int i = 0; i < 4; i++){
			live[i] = false;
		}
		for (int i = 0; i < 4; i++){
			liveC[i] = false;
		}
		score = 0;
	}
	else if (state == GAMEOVER){
		if (score > highscore){
			highscore = ++score;
		}
		lives = 5;
	}


}