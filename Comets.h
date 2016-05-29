#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>




class Comets{

	int Cometx;
	int Comety;
	int CometSpeed = 5;
	int boundx = 20;
	int boundy = 25;
	int SpeedInc = 0;

public:
	void DrawCometsF();
	void DrawComets(ALLEGRO_BITMAP *Comet);
	void UpdateComets(int score);
	bool AliveComets();
	int GetCometX();
	int GetCometY();
	int GetCometBX();
	int GetCometBY();


};



