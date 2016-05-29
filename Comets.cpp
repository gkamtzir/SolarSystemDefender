#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Comets.h"


const int WIDTH = 1200;
const int HEIGHT = 800;


void Comets::DrawCometsF(){

	Cometx = WIDTH + rand() % 500;
	Comety = rand() % HEIGHT - 25;

}

void Comets::UpdateComets(int score){

	if (score > 15000){
		SpeedInc = 3;
	}
	else if (score > 10000){
		SpeedInc = 1;
	}
	else{
		SpeedInc = 0;
	}

	Cometx -= CometSpeed + SpeedInc;
	

}

void Comets::DrawComets(ALLEGRO_BITMAP *Comet){

	al_draw_bitmap(Comet, Cometx + 5, Comety, 0);
	
}

bool  Comets::AliveComets(){

	if (Cometx <= 0){
		return false;
	}
	else{
		return true;
	}
}

int Comets::GetCometX(){

	return Cometx;
}

int Comets::GetCometY(){

	return Comety;
}

int Comets::GetCometBX(){

	return boundx;
}

int Comets::GetCometBY(){

	return boundy;
}

