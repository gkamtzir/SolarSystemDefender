#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Player.h"

const int WIDTH = 1200;
const int HEIGHT = 800;

// constructor
Player::Player(){

	//initialization

	x = 15;
	y = HEIGHT/2;
	score = 0;
	boundx = 6;
	boundy = 7;


}

int Player::GetX(){
	return x;
}

int Player::GetY(){
	return y;
}

void Player::DrawPlayer(ALLEGRO_BITMAP *Spacecraft){

	
	al_draw_bitmap(Spacecraft, x, y, 0);
	
}

void Player::MovePlayerUp(){

	if (y >-35){
		y -= 12;
	}

}

void Player::MovePlayerDown(){

	if (y < HEIGHT - 80){
		y += 12;
	}
}

void Player::MovePlayerRight(){

	if (x < WIDTH - 40){
		x += 12;
	}

}

void Player::MovePlayerLeft(){

	if (x > 25){
		x -= 12;
	}

}

