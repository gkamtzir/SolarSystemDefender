#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


class Player{

	int x;
	int y;
	int speed;
	int boundx;
	int boundy;
	int score;
	int bulletSpeed;


public:
	Player();
	int GetX();
	int GetY();	
	void DrawPlayer(ALLEGRO_BITMAP *Spacecraft);
	void MovePlayerUp();
	void MovePlayerDown();
	void MovePlayerRight();
	void MovePlayerLeft();

};
